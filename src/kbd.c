#include "kbd.h"
#include "utils.h"

// save setting to setting.dat
void save2file()
{
    char buffer[100];
    char wave[12] = " ";
    FILE *setting;
    setting = fopen(userfile, "w+");
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

    pthread_mutex_unlock(&mutex);
    sprintf(buffer, "waveforms: %s\nfreq: %f\namp: %f", wave, freq, amp);
    fputs(buffer, setting);
    fclose(setting);
    printf("Saved successfully.\n");
}

void *kbdUpdate()
{
    char c;
    system("stty -icanon");
    system("stty -echo");

    printf("%-10s| Press 'w' to increment amplitude, 's' to decrement amplitude\n", "[INFO]");
    printf("%-10s| Press 'd' to increment frequency, 'd' to decrement frequency\n", "[INFO]");
    printf("%-10s| 1: sine wave \n", "[INFO]");
    printf("%-10s| 2: triangle wave \n", "[INFO]");
    printf("%-10s| 3: sawtooth wave \n", "[INFO]");
    printf("%-10s| 4: square wave \n", "[INFO]");

    while (1)
    {
       if (input_mode == 0){
        c = getchar();
        if (c == 'a')
        {
         pthread_mutex_lock(&mutex);
            if (freq >= 2)
            {
                freq -= 1.0;
                printf("%-10s| Frequency decreased to %f.\n", "[INFO]", freq);
                calculateDuration();
            }
            else if (freq < 1)
            {
                printf("%-10s| Frequency cannot be lower than 1.\n", "[WARNING]");
            }
             pthread_mutex_unlock(&mutex);
        }
        else if (c == 'd')
        {
         pthread_mutex_lock(&mutex);
            if (freq < 100)
            {
                freq += 1.0;
                printf("%-10s| Frequency increased to %f.\n", "[INFO]", freq);
                calculateDuration();
            }
            else if (freq > 100)
            {
                printf("%-10s| Frequency cannot be higher than 100.\n", "[WARNING]");
            }
         pthread_mutex_unlock(&mutex);
        }
        else if (c == 'w')
        {
         pthread_mutex_lock(&mutex);
            if (amp <= 2.4)
            {
                amp += 0.1;
                printf("%-10s| Amplitude increased to %f.\n", "[INFO]", amp);
            }
            else
            {
                printf("%-10s| Amplitude cannot be higher than 100.\n", "[WARNING]");
            }
             pthread_mutex_unlock(&mutex);
        }
        else if (c == 's')
        {
         pthread_mutex_lock(&mutex);
            if (amp > 0.1)
            {
                amp -= 0.1;
                printf("%-10s| Amplitude decreased to %f.\n", "[INFO]", amp);
            }
            else
            {
                printf("%-10s| Amplitude cannot be lower than 1.\n", "[WARNING]");
            }
             pthread_mutex_unlock(&mutex);
        }
        else if (c == '1')
        {
         pthread_mutex_lock(&mutex);
            waveforms = 1;
             pthread_mutex_unlock(&mutex);
            printf("%-10s| sine wave is chosen. \n", "[INFO]");
        }
        else if (c == '2')
        {
         pthread_mutex_lock(&mutex);
            waveforms = 2;
             pthread_mutex_unlock(&mutex);
            printf("%-10s| triangle wave is chosen. \n", "[INFO]");
        }
        else if (c == '3')
        {
         pthread_mutex_lock(&mutex);
            waveforms = 3;
             pthread_mutex_unlock(&mutex);
            printf("%-10s| sawtooth wave is chosen. \n", "[INFO]");
        }
        else if (c == '4')
        {
         pthread_mutex_lock(&mutex);
            waveforms = 4;
             pthread_mutex_unlock(&mutex);
            printf("%-10s| square wave is chosen. \n", "[INFO]");
        }
                else if (c == 'k')
        {
         pthread_mutex_lock(&mutex);
            input_mode = 0;
             pthread_mutex_unlock(&mutex);
            printf("%-10s| keyboard input mode is chosen. \n", "[INFO]");
        }
                else if (c == 'p')
        {
         pthread_mutex_lock(&mutex);
             input_mode = 1;
             pthread_mutex_unlock(&mutex);
            printf("%-10s| potential meter input mode is chosen. \n", "[INFO]");
        }
        else
        {
            printf("%-10s| Please enter a valid option. \n", "[WARNING]");
        }
        save2file();
    }}
}