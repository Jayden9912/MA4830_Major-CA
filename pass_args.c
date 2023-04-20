#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    FILE *setting;
    setting = fopen("setting.dat", "w+");
    sprintf(buffer, "waveforms: %d\nfreq: %f\namp: %d", waveforms, freq, amp);
    fputs(buffer, setting);
    fclose(setting);
    printf("Saved successfully.\n");
    return 1;
}

// ask user to input default settings

int default_setting()
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

int parse_arg()
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
                //save2file();
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
                //save2file();
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
                //save2file();
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
                //save2file();
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
    }
}

int main()
{
    parse_arg();
}
