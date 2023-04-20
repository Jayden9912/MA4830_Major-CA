#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#define FLOAT_EPSILON 1e-5

/*
 w key to increase amp,
 s key to decrease amp,
 a key to decrease freqency,
 d key to increse frequency,
 1 for waveform sine
 2 for waveform triangle
 3 for waveform sawtooth
 4 for waveform square
 amp: amplitude 0-100
 freq: frequency 1-10

*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// defult settings
float amp = 50.0;
float freq = 5.0;
int waveforms = 1;

// convert str to float
float string2float(char *str)
{
    return strtod(str, NULL);
}

// save setting to setting.dat
int save2file()
{

    char buffer[100];
    char wave[12] = " ";
    FILE *setting;
    setting = fopen("setting1.dat", "w+");
    pthread_mutex_lock(&mutex);
    if (waveforms == 1)
    {
        strcpy(wave,"sine");
    }
    else if (waveforms == 2)
    {

        strcpy(wave,"triangle");
    }
    else if (waveforms == 3)
    {
      
        strcpy(wave,"sawtooth");
    }
    else if (waveforms == 4)
    {

        strcpy(wave,"square");
    }

    pthread_mutex_unlock(&mutex);
    sprintf(buffer, "waveforms: %s\nfreq: %f\namp: %f", wave, freq, amp);
    fputs(buffer, setting);
    fclose(setting);
    printf("Saved successfully.\n");
    return 1;
}

// ask user to input default settings

void *default_setting(void *arg)
{
    printf("Please choose a waveform: \n");
    printf("1: sine wave \n");
    printf("2: triangle wave \n");
    printf("3: sawtooth wave \n");
    printf("4: square wave \n");
    char wave;
    while (1)
    {
        wave = getchar();
        if (wave == '1')
        {
            waveforms = 1;
            printf("sine wave is chosen. \n");
            break;
        }
        else if (wave == '2')
        {
            waveforms = 2;
            printf("triangle wave is chosen. \n");
            break;
        }
        else if (wave == '3')
        {
            waveforms = 3;
            printf("sawtooth wave is chosen. \n");
            break;
        }
        else if (wave == '4')
        {
            waveforms = 4;
            printf("square wave is chosen. \n");
            break;
        }
        printf("Invalid input. Please input again ");
    }
    printf("Please enter frequency in HZ: \n");
    float input;
    float freq_dummy;
    char c;
    while (1)
    {
        // clear input buffer
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        scanf("%f", &input);
        freq_dummy = input;
        if (freq_dummy >= 1.0 && freq_dummy <= 20.0)
        {
            printf("Frequency %.2f is chosen. \n", freq_dummy);
            freq = freq_dummy;
            break;
        }
        else
        {
            printf("Invalid input. Please input again ");
        }
    }

    printf("Please enter amplitude from 1 to 100: \n");
    // float input;
    float amp_dummy;
    while (1)
    {
        // clear input buffer
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        scanf("%f", &input);
        amp_dummy = input;
        if (amp_dummy >= 1 && amp_dummy <= 100)
        {
            printf("Amplitude %.2f is chosen. \n", amp_dummy);
            amp = amp_dummy;
            break;
        }
        else
        {
            printf("Invalid input. Please input again ");
        }
    }
    save2file();
}

void *parse_arg(void *arg)
{
    system("stty -icanon");
    system("stty -echo");
    char c;

    printf("Press 'w' to increment amplitude, 's' to decrement amplitude\n");
    printf("Press 'd' to increment frequency, 'd' to decrement frequency\n");
    printf("1: sine wave \n");
    printf("2: triangle wave \n");
    printf("3: sawtooth wave \n");
    printf("4: square wave \n");

    while (1)
    {
        // scanf(" %c", &c); // note the space before %c to skip whitespace
        c = getchar();
        if (c == 'a')
        {
            if (freq >= 1)
            {
                freq -= 1.0;
                printf("Frequency decreased to %f.\n", freq);
                // save2file();
            }
            else if (freq < 1)
            {
                printf("Frequency cannot be lower than 1.\n");
            }
        }
        else if (c == 'd')
        {
            if (freq < 10)
            {
                freq += 1.0;
                printf("Frequency increased to %f.\n", freq);
                // save2file();
            }
            else if (freq > 10)
            {
                printf("Frequency cannot be higher than 10.\n");
            }
        }
        else if (c == 'w')
        {
            if (amp < 100.0)
            {
                amp += 1.0;
                printf("Amplitude increased to %f.\n", amp);
                // save2file();
            }
            else
            {
                printf("Amplitude cannot be higher than 100.\n");
            }
        }
        else if (c == 's')
        {
            if (amp > 1.0)
            {
                amp -= 1.0;
                printf("Amplitude decreased to %f.\n", amp);
                // save2file();
            }
            else
            {
                printf("Amplitude cannot be lower than 1.\n");
            }
        }
        else if (c == '1')
        {
            waveforms = 1;
            printf("sine wave is chosen. \n");
        }
        else if (c == '2')
        {
            waveforms = 2;
            printf("triangle wave is chosen. \n");
        }
        else if (c == '3')
        {
            waveforms = 3;
            printf("sawtooth wave is chosen. \n");
        }
        else if (c == '4')
        {
            waveforms = 4;
            printf("square wave is chosen. \n");
        }
        else
        {
            printf("Please enter a valid option. \n");
        }

        save2file();
        // printf("amp = %f\n", amp);
        // printf("freq = %f\n", freq);
        pthread_mutex_lock(&mutex);
        amp = amp;
        freq = freq;
        waveforms = waveforms;
        pthread_mutex_unlock(&mutex);
        // sleep(1);
    }
    return 0;
}

float remap(float value, float from_min, float from_max, float to_min, float to_max)
{
    float from_range = from_max - from_min;
    float to_range = to_max - to_min;
    return (((value - from_min) * to_range) / from_range) + to_min;
}

void *print()
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        printf("amp = %f\n", amp);
        printf("amp remapped = %f\n", remap(amp, 0.0, 100.0, 0.0, 2.5));
        printf("freq = %f\n", freq);
        pthread_mutex_unlock(&mutex);

        /* snooze for 2 seconds */
        // sleep( 2 );
    }

    return 0;
}

int main()
{
    pthread_t id;
    pthread_create(&id, NULL, &parse_arg, NULL);
    pthread_create(&id, NULL, &print, NULL);

    /* Let the threads run for 20 seconds. */
    sleep(20);

    return 0;
}
