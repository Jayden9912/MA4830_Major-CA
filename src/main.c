#include "pass_args.h"
#include "kbd.h"
#include "waves.h"
#include "global_args.h"
#include "ui.h"

void signal_handler(int sig)
{
	printf("\f");
    printf("SIGINT signal Received. Exiting Program\n");
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
            printf("%-10s| Unsuccessful attempt in reading default config file!\n", "[ERROR]");
        }
    }
    setupPCI();
	printf("\nHit any key to continue\n");
	getchar();
	
    // Multithread creation
    pthread_create(NULL, NULL, &kbdUpdate, NULL);
    pthread_create(NULL, NULL, &readDIO, NULL);
    pthread_create(NULL, NULL, &readADC, NULL);
    pthread_create(NULL, NULL, &print_interface, NULL);
    
    // Generating wave output
    while (1)
    {
        generateWave(waveforms, amp, freq);

        // kills the program if the first switch is OFF
        if (dio_in == 0xf0)
        {
            fflush(stdout);
            printf("Kill switch activated!");
            printf("Exiting Program\n");
            break;
        }
        
        // Keyboard input mode
        else if (dio_in == 0xf3)
        {
            fflush(stdout);
            input_mode = 0;
            if (current_input!=0xf3){
           		printf("%-10s| Input mode changed to keyboard\n", "[INFO]");
           		}
            current_input = 0xf3;
        }
        
        // Potentiometer input mode
        else if (dio_in == 0xf5 )
        {
            fflush(stdout);
            input_mode = 1;
            if (current_input!=0xf5){
            	printf("%-10s| Input mode changed to potential meter\n", "[INFO]");
            	}
            current_input = 0xf5;
        }
        else
        {
            input_mode = 2;		 // Invalid Option
        }
    }

    return 0;
}