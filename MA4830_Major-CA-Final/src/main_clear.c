#include "pass_args.h"
#include "kbd.h"
#include "waves.h"
#include "global_args.h"
//#include "ui.h"
#include "display_ui.h"
#include <ncurses.h>
 
pthread_t thread[4];
pthread_attr_t attr;
int state = 0;

void signal_handler(int sig)
{

	//printf("\f");
	refresh();
   endwin();
	//system("clear");
	 
	// printf("\x1b[2J");
	// printf("\x1b[H");
  
 //  refresh();
   //endwin();
   
   // pthread_exit(NULL);
      strcpy(loginfo, "[INFO]  Exiting Program.\n");
    detachPCI();
    
    system("clear");

    //printf("Signal Received, exiting program\n"); 
 
   // printf("Main: program completed.\n");

   //system("clear");
   
    printf("Main: program completed.\n");
    printf("\x1b[40H");
    exit(0);
}

int main(int argc, char *argv[])
{

    signal(SIGINT, signal_handler);
    state = passArgs(argc, argv);
	printf("\x1b[8;50;120t");
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
	  
   /* Initialize and set thread detached attribute */
   pthread_attr_init(&attr);

    // Multithread creation
 pthread_create(&thread[0], &attr, &kbdUpdate, NULL);
  pthread_create(&thread[1], &attr, &readDIO, NULL);
    pthread_create(&thread[2], &attr, &readADC, NULL);
 // pthread_create(&thread[3], &attr, &print_interface, NULL);
  pthread_create(&thread[3], &attr, &display, NULL);

    // Generating wave output
    while (1)
    {
        generateWave(waveforms, amp, freq);

        // kills the program if the first switch is OFF
        if (dio_in == 0xf0)
        {
            fflush(stdout);
           //system("clear");
           	 //printf("\x1b[2J");
			 //printf("\x1b[40H");
			 
           //printf("Kill switch activated!");
           // printf("Exiting Program\n");
            //input_mode = 2;
           // clear()
            refresh();
            endwin();
            strcpy(loginfo, "[INFO]  Exiting Program.\n");
			system("clear");
			 printf("\x1b[40H");
            
            break;
        }
        
        // Keyboard input mode
        else if (dio_in == 0xf3)
        {
            fflush(stdout);
            input_mode = 0;
            if (current_input!=0xf3){
           		//printf("%-10s| Input mode changed to keyboard\n", "[INFO]");
           		//strcpy(loginfo, "[INFO] Input mode changed to keyboard.\n");
           		}
            current_input = 0xf3;
        }
        
        // Potentiometer input mode
        else if (dio_in == 0xf5 )
        {
            fflush(stdout);
            input_mode = 1;
            if (current_input!=0xf5){
            	//printf("%-10s| Input mode changed to potential meter\n", "[INFO]");
            	//strcpy(loginfo, "[INFO] Input mode changed to potential meter.\n");
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