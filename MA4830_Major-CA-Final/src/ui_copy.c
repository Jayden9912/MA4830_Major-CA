
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>


// float freq = 1.0;
// float amp = 2.5;
// int waveforms = 1;


void print_table(char *waveform, float amp, float freq){
    printw("+-----------------+-----------------+-----------------+\n");
    printw("|       wave      |    amplitude    |    frequency    |\n");
    printw("+-----------------+-----------------+-----------------+\n");
    printw("|  %13s  | %15.2f |     %8.2f    |\n", waveform, amp, freq);
    printw("+-----------------+-----------------+-----------------+\n");
}


void print_interface(){
    printw("+----------------------------------------------------------------------------------------------------------------+\n");
    printw("|                                                Waveform Generator                                              |\n");
    printw("+----------------------------------------------------------------------------------------------------------------+\n");
    printw("|   Types of waveforms:                                                                                          |\n");    
    printw("|   1. sine                                                                                                      |\n");
    printw("|   2. square                                                                                                    |\n");
    printw("|   3. triangle                                                                                                  |\n");
    printw("|   4. sawtooth                                                                                                  |\n");
    printw("+----------------------------------------------------------------------------------------------------------------+\n");
    printw("|   Controls Available:                                                                                          |\n");
    printw("|   To change the type of waveform generated, enter a value from 1 to 4.                                         |\n");
    printw("|   To change the amplitude of the waveform, press 'w' to increment it by 1 or press 's' to decrement it by 1.   |\n");
    printw("|   To change the frequency of the waveform, press 'a' to increment it by 1 or press 'd' to decrement it by 1.   |\n");
    printw("|                                                                                                                |\n");
    printw("+----------------------------------------------------------------------------------------------------------------+\n");
}

int main()
{	
    char *waveform = "sine";
    float amp = 2.5;
    float freq = 1.0;
    // print interface
    // init curses
    initscr();
    noecho();
    print_interface();
    refresh();
    print_table(waveform, amp, freq);
    refresh();


    
    // get user input
    
}

