#include "ui.h"

void *print_interface()
{
    while (1)
    {
        printf("\033c");
        printf("+----------------------------------------------------------------------------------------------------------------+\n");
        printf("|                                                Waveform Generator                                              |\n");
        printf("+----------------------------------------------------------------------------------------------------------------+\n");
        printf("|   Types of waveforms:                                                                                          |\n");
        printf("|   1. sine                                                                                                      |\n");
        printf("|   2. square                                                                                                    |\n");
        printf("|   3. triangle                                                                                                  |\n");
        printf("|   4. sawtooth                                                                                                  |\n");
        printf("+----------------------------------------------------------------------------------------------------------------+\n");
        printf("|   Controls Available:                                                                                          |\n");
        printf("|   To change the type of waveform generated, enter a value from 1 to 4.                                         |\n");
        printf("|   To change the amplitude of the waveform, press 'w' to increment it by 1 or press 's' to decrement it by 1.   |\n");
        printf("|   To change the frequency of the waveform, press 'a' to increment it by 1 or press 'd' to decrement it by 1.   |\n");
        printf("|                                                                                                                |\n");
        printf("+----------------------------------------------------------------------------------------------------------------+\n");

        printf("\n\n");

        printf("+-----------------+-----------------+-----------------+\n");
        printf("|       wave      |    amplitude    |    frequency    |\n");
        printf("+-----------------+-----------------+-----------------+\n");
        printf("|  %13d  | %15.2f |     %8.2f    |\n", waveforms, amp, freq);
        printf("+-----------------+-----------------+-----------------+\n");
        sleep(1);
    }
}

/*
int main()
{
    char *waveform = "sine";
    float amp = 2.5;
    float freq = 1.0;
    // print interface
    print_interface();
    print_table(waveform, amp, freq);

    // get user input

}
*/
