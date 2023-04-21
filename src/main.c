#include "pass_args.h"
#include "kbd.h"
#include "waves.h"
#include "global_args.h"
// #include "ui.h" // normal ui
#include "display_ui.h" // ncursese ui

pthread_t thread[4];
pthread_attr_t attr;
int state = 0;

// handle "ctrl + c"
void signal_handler(int sig)
{
 	//printf("SIGINT signal Received. Exiting Program\n");
	strcpy(loginfo,"SIGINT signal Received. Exiting Program");
    system("clear"); //clear terminal screen
    // printf("\x1b[2J");
    printf("\x1b[H"); // move the cursor to the top-left corner (home position) of the terminal or console window
    // pthread_exit(NULL);
    detachPCI(); // detach pci device
    refresh(); // refresh screen
    endwin(); // close ncurses window
      system("clear"); // clear terminal screen
    printf("Program Exited!!!\n");
    exit(0);
}

// main program
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
    pthread_create(&thread[0], &attr, &kbdUpdate, NULL); // thread for keyboard input
    pthread_create(&thread[1], &attr, &readDIO, NULL); // thread for toggle switch input
    pthread_create(&thread[2], &attr, &readADC, NULL); // thread for potentiometer input
    // pthread_create(&thread[3], &attr, &print_interface, NULL); // thread for normal display
    pthread_create(&thread[3], &attr, &display, NULL); // thread for ncurses display

    // Generating wave output
    while (1)
    {
        generateWave(waveforms, amp, freq); // generate wave by given wave type, amplitude and frequency

        // kills the program if the first switch is OFF
        if (dio_in == 0xf0)
        {
            fflush(stdout); // clear keyboard buffer
            //printf("SIGINT signal Received. Exiting Program\n");
			strcpy(loginfo,"SIGINT signal Received. Exiting Program");
            system("clear"); // clear terminal screen
            // printf("\x1b[2J");
            printf("\x1b[H");
            printf("Kill switch activated!"); // master toggle switch is toggled
            printf("Exiting Program\n");
            detachPCI(); // detach pci device
   			refresh(); // refresh screen
   			endwin(); // close ncurses window
   			  system("clear"); // clear terminal screen
   			printf("Program Exited!!!\n");
            break;
        }

        // Keyboard input mode
        else if (dio_in == 0xf3)
        {
            fflush(stdout);
            input_mode = 0; // keyboard input mode
            if (current_input != 0xf3)
            {
                // printf("%-10s| Input mode changed to keyboard\n", "[INFO]");
                // strcpy(loginfo, "[INFO] Input mode changed to keyboard.\n");
            }
            current_input = 0xf3;
        }

        // Potentiometer input mode
        else if (dio_in == 0xf5)
        {
            fflush(stdout);
            input_mode = 1;
            if (current_input != 0xf5)
            {
                // printf("%-10s| Input mode changed to potential meter\n", "[INFO]");
                // strcpy(loginfo, "[INFO] Input mode changed to potential meter.\n");
            }
            current_input = 0xf5;
        }
        else
        {
            input_mode = 2; // Invalid Option
        }
    }

    return 0;
}