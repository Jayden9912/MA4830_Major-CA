#include "kbd.h"
#include "utils.h"

// save setting to setting.dat
void save2file()
{
    char buffer[100];
    char wave[12] = " ";
    FILE *setting;
  //  setting = fopen(userfile, "w+");
    
    if((setting=fopen(userfile,"w"))==NULL){
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
    sprintf(buffer, "waveforms: %s\nfreq: %f\namp: %f\n", wave, freq, amp);
    fputs(buffer, setting);
    fclose(setting);
    // printf("Saved successfully.\n");
}

void *kbdUpdate( void* arg)
{
    char c;
    system("stty -icanon");
    system("stty -echo");

    while (1)
    {
        if (input_mode == 0)
        {
            c = getchar();
            if (c == 'a')
            {

                if (freq >= 2)
                {
                                pthread_mutex_lock(&mutex);
                    freq -= 1.0;
                                    pthread_mutex_unlock(&mutex);
                    calculateDuration();
                    save2file();
                }
                else if (freq < 2)
                {
                    //printf("%-10s| Frequency cannot be lower than 1.\n", "[WARNING]");
                    strcpy(loginfo, "[WARNING]  Frequency cannot be lower than 1.\n");
                }

            }
            else if (c == 'd')
            {
                
                if (freq <= 99)
                {
                    pthread_mutex_lock(&mutex);
                    freq += 1.0;
                    pthread_mutex_unlock(&mutex);
                    calculateDuration();
                    save2file();
                }
                else if (freq > 99)
                {
                	strcpy(loginfo, "[WARNING]  Frequency cannot be higher than 100.\n");
                	 //printf("%-10s| Frequency cannot be higher than 100.\n", "[WARNING]");
                }

            }
            else if (c == 'w')
            {
                
                if (amp <= 2.4)
                {
                pthread_mutex_lock(&mutex);
                    amp += 0.1;
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
               
                if (amp >= 0.1)
                {
                 pthread_mutex_lock(&mutex);
                    amp -= 0.1;
                    pthread_mutex_unlock(&mutex);
                    save2file();
                }
                else
                {
                   // printf("%-10s| Amplitude cannot be lower than 0\n", "[WARNING]");
                    strcpy(loginfo, "[WARNING]  Amplitude cannot be lower than 0.\n");
                }
                
            }
            else if (c == '1')
            {
                pthread_mutex_lock(&mutex);
                waveforms = 1;
                pthread_mutex_unlock(&mutex);
                save2file();
            }
            else if (c == '2')
            {
                pthread_mutex_lock(&mutex);
                waveforms = 2;
                pthread_mutex_unlock(&mutex);
                save2file();
            }
            else if (c == '3')
            {
                pthread_mutex_lock(&mutex);
                waveforms = 3;
                pthread_mutex_unlock(&mutex);
                save2file();
            }
            else if (c == '4')
            {
                pthread_mutex_lock(&mutex);
                waveforms = 4;
                pthread_mutex_unlock(&mutex);
                save2file();
            }
            else
            {
                //printf("\a");
                strcpy(loginfo, "[WARNING]  Invalid inputs, please follow the instructions.\n");
            }
        }
    }
}