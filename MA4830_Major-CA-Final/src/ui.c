#include "ui.h"

void *print_interface(void* arg)
{
    while (1)
    {
    
      char wave[12] = " ";
      char mode[20]= " ";
       pthread_mutex_lock(&mutex);
     if (waveforms == 1)
    {
        strcpy(wave, "sine");
    }
    else if (waveforms == 2)
    {
        strcpy(wave, "triangle");
    }
    else if (waveforms == 3)
    {
        strcpy(wave, "sawtooth");
    }
    else if (waveforms == 4)
    {
        strcpy(wave, "square");
    }
    if (input_mode == 0){
    strcpy(mode ,"keyboard mode");}
    else if (input_mode == 1){
    strcpy(mode , "potentiometer mode");}
     pthread_mutex_unlock(&mutex);
        printf("\f");
        printf("Types of waveform: 1 - sine, 2 - triangular, 3 - sawtooth, 4 - square\n");
        printf("Press 'w' and 's' to increase/decrease wave amplitude\n");
        printf("Press 'd' and 'a' to increase/decrease wave frequency\n\n");
        printf("Current input mode: %s\n",mode);
        printf("Waveforms: %s\nFrequency: %.2f\nAmplitude: %.2f\n", wave,  freq,amp);

        delay(800);
  	}
}
