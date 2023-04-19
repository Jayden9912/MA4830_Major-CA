#include "ui.h"

void *print_interface()
{
    while (1)
    {
        printf("\f");
        printf("Types of waveform: 1 - sine, 2 - triangular, 3 - sawtooth, 4 - square\n");
        printf("Press 'w' and 's' to increase/decrease wave amplitude\n");
        printf("Press 'd' and 'a' to increase/decrease wave frequency\n\n");
        printf("Waveforms: %d\nAmplitude: %.2f\nFrequency: %.2f\n", waveforms, amp, freq);

        delay(800);
  	}
}
