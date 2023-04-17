#include "waves.h"

void setupPCI()
{
	printf("Setting up PCI-DAS 1602\n");
	memset(&info, 0, sizeof(info));

	// connect to PCI server
	if (pci_attach(0) < 0)
	{
		perror("pci_attach");
		exit(EXIT_FAILURE);
	}

	// assign vendor and device number
	info.VendorId = 0x1307;
	info.DeviceId = 0x01;

	if ((hdl = pci_attach_device(0, PCI_SHARE | PCI_INIT_ALL, 0, &info)) == 0)
	{
		perror("pci_attach_device");
		exit(EXIT_FAILURE);
	}

	printf("\nDAS 1602 Base addresses:\n\n");
	for (i = 0; i < 5; i++)
	{
		badr[i] = PCI_IO_ADDR(info.CpuBaseAddress[i]);
		printf("Badr[%d] : %x\n", i, badr[i]);
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
		perror("Thread Control");
		exit(1);
	}
}

void generateWave(const int *waveforms, const float *amplitude, const float *frequency)
{
	unsigned int i;
	unsigned int data[100];
	float delta, dummy;
	//-----------------------------------------
	// extra variables declared
	unsigned int steps = 50;
	unsigned int halfSteps = steps / 2;
	unsigned int duration;

	// variables for square waves
	unsigned int squareMinValue;
	squareMinValue = 0;
	//******************************************************************************
	// D/A Port Functions
	//******************************************************************************

	printf("\n\nWrite Sine Demo to multiple DAC\n");
	switch (waveforms)
	{
	case 1:							   // Sine wave
		delta = (2.0 * 3.142) / steps; // increment
		for (i = 0; i < steps; i++)
		{
			dummy = ((sinf((float)(i * delta)) * amp + amp)) * (0x8000 / (amp)) * ((2 * amp) / 5);
			data[i] = (unsigned)dummy; // add offset +  scale
		}
		break;
	case 2:						   // Triangular wave
		delta = amp / (halfSteps); // increment
		printf("%f\n", delta);
		for (i = 0; i <= halfSteps; i++)
		{ // first half
			dummy = i * delta * (0xFFFF / 5);
			data[i] = (unsigned)dummy;
			printf("%x\n", data[i]);
		}
		for (i = halfSteps + 1; i <= steps; i++)
		{ // second half
			dummy = (steps - i) * delta * (0xFFFF / 5);
			data[i] = (unsigned)dummy;
			// printf("%x\n", data[i]);
		}
		break;
	case 3:					   // sawtooth
		delta = amp / (steps); // increment
		printf("%f\n", delta);
		for (i = 0; i <= steps; i++)
		{ // first half
			dummy = i * delta * (0xFFFF / 5);
			data[i] = (unsigned)dummy;
			printf("%x\n", data[i]);
		}
		break;
	case 4: // square
		for (i = 0; i <= halfSteps; i++)
		{ // first half
			dummy = squareMinValue * (0xFFFF / 5) * amp;
			data[i] = (unsigned)dummy;
			printf("%x\n", data[i]);
		}
		for (i = halfSteps; i <= steps; i++)
		{ // second half
			dummy = amp * (0xFFFF / 5) * amp;
			data[i] = (unsigned)dummy;
			printf("%x\n", data[i]);
		}
		break;
	default:
		printf("BUGS!!!");
		break;
	}

	for (i = 0; i < steps; i++)
	{
		// DAC0
		out16(DA_CTLREG, 0x0a23); // DA Enable, #0, #1, SW 5V unipolar		2/6
		out16(DA_FIFOCLR, 0);	  // Clear DA FIFO  buffer
		out16(DA_Data, (short)data[i]);
		delay(duration);
	}
}

void detachPCI()
{
	// Unreachable code
	// Reset DAC to 5v
	out16(DA_CTLREG, (short)0x0a23);
	out16(DA_FIFOCLR, (short)0);
	out16(DA_Data, 0x8fff); // Mid range - Unipolar

	out16(DA_CTLREG, (short)0x0a43);
	out16(DA_FIFOCLR, (short)0);
	out16(DA_Data, 0x8fff);

	printf("\n\nExit Demo Program\n");
	pci_detach_device(hdl);
	return (0);
}

int main()
{
	waveforms = 1;
	amplitude = 1.0;
	frequency = 1.0;
	setupPCI();
	generateWave(&waveforms, &amplitude, &frequency);
	detachPCI();
	return 0;
}