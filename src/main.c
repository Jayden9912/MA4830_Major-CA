#include "pass_args.h"
#include "kbd.h"
#include "waves.h"
#include "global_args.h"
#include "ui.h"

void signal_handler(int sig)
{
    printf("Signal Received. Exiting Program\n");
    detachPCI();
    exit(0);
}

int main(int argc, char *argv[])
{
    int state = 0;
    signal(SIGINT, signal_handler);
    state = passArgs(argc, argv);
    // problem encountered in parsing arguments
    if (state != 0)
    {
        // load default value for waveform, amplitude and frequency
        readDefaultArgs(defaultfile);
        if (!wave_valid || !amp_valid || !freq_valid) // unsuccessful attempt in reading default config file
        {
            printf("[ERROR]: Unsuccessful attempt in reading default config file!\n");
        }
    }
    setupPCI();
    pthread_create(NULL, NULL, &print_interface, NULL);
    pthread_create(NULL, NULL, &kbdUpdate, NULL);
    pthread_create(NULL, NULL, &readDIO, NULL);
    pthread_create(NULL, NULL, &readADC, NULL);
    while (1)
    {
        generateWave(waveforms, amp, freq);

        // kills the program if any of the switch is OFF
        
        
         if (dio_in == 0xf0)
         {
         	fflush(stdout);
             printf("Exiting Program\n");
             break;
         }
         else if (dio_in == 0xf3)
         {
         fflush(stdout);
             input_mode = 0;
               printf("Input mode changed to keyboard\n");
 
         }
          else if (dio_in == 0xf5)
         {
         fflush(stdout);
             input_mode = 1;
               printf("Input mode changed to potential meter\n");
 
         }
         else {
         input_mode = 2; // Invalid Option
         printf("Please choose one valid option.\n");
         printf("T1 and T2: Keyboard\n");
         printf("T1 and T3: Potentiometer\n");
         printf("T1: 0 Exits the programme\n");
         }
     
     }
    
    return 0;
}