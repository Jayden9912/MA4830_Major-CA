#include "waves.h"

void setupPCI()
{
	unsigned int i;
	printf("%-10s| Setting up PCI-DAS 1602\n", "[INFO]");
	memset(&info, 0, sizeof(info));

	// connect to PCI server
	if (pci_attach(0) < 0)
	{
		printf("%-10s| ", "[ERROR]");
		perror("pci_attach");
		exit(EXIT_FAILURE);
	}

	// assign vendor and device number
	info.VendorId = 0x1307;
	info.DeviceId = 0x01;

	if ((hdl = pci_attach_device(0, PCI_SHARE | PCI_INIT_ALL, 0, &info)) == 0)
	{
		printf("%-10s| ", "[ERROR]");
		perror("pci_attach_device");
		exit(EXIT_FAILURE);
	}

	printf("\nDAS 1602 Base addresses:\n\n");
	for (i = 0; i < 5; i++)
	{
		badr[i] = PCI_IO_ADDR(info.CpuBaseAddress[i]);
		printf("%-10s| Badr[%d] : %x\n", "[INFO]", i, badr[i]);
	}

	printf("\nReconfirm Iobase:\n"); // map I/O base address to user space
	for (i = 0; i < 5; i++)
	{ // expect CpuBaseAddress to be the same as iobase for PC
		iobase[i] = mmap_device_io(0x0f, badr[i]);
		printf("Index %d : Address : %x ", i, badr[i]);
		printf("IOBASE  : %x \n", iobase[i]);
	}

	// Modify thread control privity
	if (ThreadCtl(_NTO_TCTL_IO, 0) == -1)
	{
		printf("%-10s| ", "[ERROR]");
		perror("Thread Control");
		exit(1);
	}
}

void generateWave(const int waveforms, const float amplitude, const float frequency)
{
	unsigned int i;
	unsigned int data[100];
	float delta, dummy;
	unsigned int delay_time;
	//-----------------------------------------
	// extra variables declared
	unsigned int steps = 50;
	unsigned int halfSteps = steps / 2;

	// variables for square waves
	unsigned int squareMinValue;
	squareMinValue = 0;
	pthread_mutex_lock(&mutex);
	switch (waveforms)
	{
	case 1: // Sine wave
		delta = (2.0 * 3.142) / steps;
		for (i = 0; i < steps; i++)
		{
			// printf("amp %.2f\n", amp);
			// pthread_mutex_lock(&mutex);
			dummy = ((sinf((float)(i * delta)) * amp + amp)) * (0xFFFF / 5);
			// pthread_mutex_unlock(&mutex);
			data[i] = (unsigned)dummy;
		}
		break;
	case 2: // Triangular wave
		delta = (2 * amp) / (halfSteps);
		for (i = 0; i <= halfSteps; i++)
		{ // first half
			// pthread_mutex_lock(&mutex);
			dummy = i * delta * (0xFFFF / 5);
			// pthread_mutex_unlock(&mutex);
			data[i] = (unsigned)dummy;
		}
		for (i = halfSteps + 1; i <= steps; i++)
		{ // second half
			dummy = (steps - i) * delta * (0xFFFF / 5);
			data[i] = (unsigned)dummy;
		}
		break;
	case 3: // sawtooth
			// pthread_mutex_lock(&mutex);
		delta = (2 * amp) / (steps);
		// pthread_mutex_unlock(&mutex);
		for (i = 0; i <= steps; i++)
		{ // first half
			dummy = i * delta * (0xFFFF / 5);
			data[i] = (unsigned)dummy;
		}
		break;
	case 4: // square
		for (i = 0; i <= halfSteps; i++)
		{ // first half
			// pthread_mutex_lock(&mutex);
			dummy = squareMinValue * (0xFFFF / 5) * amp;
			// pthread_mutex_unlock(&mutex);
			data[i] = (unsigned)dummy;
		}
		for (i = halfSteps; i <= steps; i++)
		{ // second half
			// pthread_mutex_lock(&mutex);
			dummy = (0xFFFF / 5) * (2 * amp);
			// pthread_mutex_unlock(&mutex);
			data[i] = (unsigned)dummy;
		}
		break;
	default:
		printf("%-10s| Invalid waveform selected\n", "[ERROR]");
		exit(1);
	}
	pthread_mutex_unlock(&mutex);
	delay_time = calculateDuration();
	// Write to DAC
	for (i = 0; i < steps; i++)
	{
		// DAC0
		out16(DA_CTLREG, 0x0a23); // DA Enable, #0, #1, SW 5V unipolar		2/6
		out16(DA_FIFOCLR, 0);	  // Clear DA FIFO  buffer
		out16(DA_Data, (short)data[i]);
		// DAC1
		out16(DA_CTLREG, 0x0a43); // DA Enable, #1, #1, SW 5V unipolar		2/6
		out16(DA_FIFOCLR, 0);	  // Clear DA FIFO  buffer
		out16(DA_Data, (short)data[i]);
		delay(delay_time);
	}
}

void detachPCI()
{
	// Reset DAC to 5v
	out16(DA_CTLREG, (short)0x0a23);
	out16(DA_FIFOCLR, (short)0);
	out16(DA_Data, 0x8fff); // Mid range - Unipolar

	out16(DA_CTLREG, (short)0x0a43);
	out16(DA_FIFOCLR, (short)0);
	out16(DA_Data, 0x8fff);

	printf("\n\n%-10s| PCI detached.\n", "[INFO]");
	pci_detach_device(hdl);
}

void *readADC()
{
	float new_amplitude;
	float new_frequency;
	float diff_amp = 0.0;
	float diff_freq = 0.0;
	// add a filter such that the amplitude and frequency are not changed too often due to noise
	float amp_fluct_threshold = 0.03;
	float freq_fluct_threshold = 0.03;
	// printf("input mode %d", input_mode);
	while (1)
	{
		if (input_mode == 1)
		{
			out16(INTERRUPT, 0x60c0); // sets interrupts	 - Clears
			out16(TRIGGER, 0x2081);	  // sets trigger control: 10MHz, clear, Burst off,SW trig. default:20a0
			out16(AUTOCAL, 0x007f);	  // sets automatic calibration : default

			out16(AD_FIFOCLR, 0);	// clear ADC buffer
			out16(MUXCHAN, 0x0D00); // Write to MUX register - SW trigger, UP, SE, 5v, ch 0-0
									// x x 0 0 | 1  0  0 1  | 0x 7   0 | Diff - 8 channels
									// SW trig |Diff-Uni 5v| scan 0-7| Single - 16 channels

			count = 0x00;

			// read two potentiometers values
			while (count < 0x02)
			{
				chan = ((count & 0x0f) << 4) | (0x0f & count);
				out16(MUXCHAN, 0x0D00 | chan); // Set channel	 - burst mode off.
				delay(1);					   // allow mux to settle
				out16(AD_DATA, 0);			   // start ADC
				while (!(in16(MUXCHAN) & 0x4000))
					;
				adc_in = in16(AD_DATA);
				if (count == 0x00)
				{
					// convert potentiometer 0 to new frequency
					new_frequency = (adc_in / 65535.0) * 100.0;
					if (new_frequency <= 1)
					{
						new_frequency = 1.0;
					}
					pthread_mutex_lock(&mutex);
					diff_freq = fabs(new_frequency - freq);
					// printf("diff_freq %f\n", diff_freq);
					// printf("%d\n\n", (diff_freq > 0.01));
					//  replace current frequency with new frequency if greater than threshold

					if (diff_freq)
					{
						freq = new_frequency;
					}
					pthread_mutex_unlock(&mutex);
					// printf("Frequency Analogue: %.2f\n", freq);
				}
				else
				{
					// convert potentiometer 1 to new amplitude
					new_amplitude = (adc_in / 65535.0) * 2.5;
					pthread_mutex_lock(&mutex);
					diff_amp = abs(new_amplitude - amp);
					// replace current amplitude with new amplitude if greater than threshold
					if (!(diff_amp > amp_fluct_threshold))
					{
						amp = new_amplitude;
					}
					pthread_mutex_unlock(&mutex);
					// printf("Amplitude Analogue: %f\n", amp);
				}
				// printf("ADC Chan: %02x Data [%3d]: %4d \n", chan, (int)count, (unsigned int)adc_in);		// print ADC
				fflush(stdout);
				count++;
				delay(50); // Write to MUX register - SW trigger, UP, DE, 5v, ch 0-7
			}
		}
	}
}

void *readDIO()
{
	while (1)
	{
		out8(DIO_CTLREG, 0x90); // set Port A to output
		dio_in = in8(DIO_PORTA);
		// printf("DIO Port A : %2x\n", dio_in);
		out8(DIO_PORTB, dio_in); // write to Port B for display
								 // delay(500);
	}
}
