#include "kbd.h"
#include "utils.h"

// save setting to setting.dat
void save2file()
{
    char buffer[100];    // buffer used to store text
    char wave[12] = " "; // buffer used to store wave type
    FILE *setting;       // setting file name

    if ((setting = fopen(userfile, "w")) == NULL) // error checking
    {
        perror("cannot open");
        exit(1);
    }
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
    sprintf(buffer, "waveforms: %s\nfreq: %f\namp: %f\n", wave, freq, amp); // store text in buffer
    fputs(buffer, setting);
    fclose(setting); // close file
    // printf("Saved successfully.\n");
}

// check keyboard input and update global variable
void *kbdUpdate(void *arg)
{
    char c;
    system("stty -icanon"); // disable the canonical mode
    system("stty -echo");   // d is used in Unix-like operating systems to disable the terminal's echo mode

    while (1)
    {
        if (input_mode == 0) // if input mode is keyboard
        {
            c = getchar();
            if (c == 'a')
            {

                if (freq >= 2) // min frequecy is 1 hz
                {
                    pthread_mutex_lock(&mutex);
                    freq -= 1.0; // decrease freqency by 1 hz
                    pthread_mutex_unlock(&mutex);
                    calculateDuration(); // calculate delay time
                    save2file();
                }
                else if (freq < 2)
                {
                    strcpy(loginfo, "[WARNING]  Frequency cannot be lower than 1.\n");
                }
            }
            else if (c == 'd')
            {

                if (freq <= 99) // max frequency is 100 hz
                {
                    pthread_mutex_lock(&mutex);
                    freq += 1.0; // increase frequency by 1 hz
                    pthread_mutex_unlock(&mutex);
                    calculateDuration();
                    save2file();
                }
                else if (freq > 99)
                {
                    strcpy(loginfo, "[WARNING]  Frequency cannot be higher than 100.\n");
                }
            }
            else if (c == 'w') // control amplitude of the wave
            {

                if (amp <= 2.4) // max amplitude is 2.5 v
                {
                    pthread_mutex_lock(&mutex);
                    amp += 0.1; // increase amplitude by 0.1 v
                    pthread_mutex_unlock(&mutex);
                    save2file();
                }
                else
                {
                    // printf("%-10s| Amplitude cannot be higher than 2.5.\n", "[WARNING]");
                    strcpy(loginfo, "[WARNING]  Amplitude cannot be higher than 2.5.\n");
                }
            }
            else if (c == 's')
            {

                if (amp >= 0.1) // min amplitude is 0 v
                {
                    pthread_mutex_lock(&mutex);
                    amp -= 0.1; // decrease amplitude by 0.1 v
                    pthread_mutex_unlock(&mutex);
                    save2file();
                }
                else
                {
                    // printf("%-10s| Amplitude cannot be lower than 0\n", "[WARNING]");
                    strcpy(loginfo, "[WARNING]  Amplitude cannot be lower than 0.\n");
                }
            }
            else if (c == '1') // sine wave
            {
                pthread_mutex_lock(&mutex);
                waveforms = 1;
                pthread_mutex_unlock(&mutex);
                save2file();
            }
            else if (c == '2') // triangle wave
            {
                pthread_mutex_lock(&mutex);
                waveforms = 2;
                pthread_mutex_unlock(&mutex);
                save2file();
            }
            else if (c == '3') // sawtooth wave
            {
                pthread_mutex_lock(&mutex);
                waveforms = 3;
                pthread_mutex_unlock(&mutex);
                save2file();
            }
            else if (c == '4') // square wave
            {
                pthread_mutex_lock(&mutex);
                waveforms = 4;
                pthread_mutex_unlock(&mutex);
                save2file();
            }
            else
            {
                strcpy(loginfo, "[WARNING]  Invalid inputs, please follow the instructions.\n");
            }
        }
    }
}