#include "display.h"

void ncurses_init(){

  // Curses init
  screen = initscr();

  // Intial setup
  nodelay(screen, 1);
  cbreak();
  noecho();
  curs_set(0);
  keypad(screen, TRUE);

  // Dot settings
  //attron(A_BOLD);
  attron(A_STANDOUT);

  // Wave attributes
  delayx = DEFAULT_DELAY_MULTIPLIER;
  phase_shift = 0;
  choice = 1;
  period = DEFAULT_PERIOD;
}


void print_instructions(WINDOW *instructions)
{

char log[20] = "[INFO]  OKOK";
  // Set up the container box
  box(instructions, 0, 0);

  // Print respective keys to change amplitude and frequency
  
   mvwprintw(instructions, 0, 1, " INSTRUCTIONS: ");
    mvwprintw(instructions,1,1,"+----------------------------------------------------------------------------------------------------------------+\n");
    
    mvwprintw(instructions,2,1,"|                                                Waveform Generator                                              |\n");
    mvwprintw(instructions,3,1,"+----------------------------------------------------------------------------------------------------------------+\n");
    mvwprintw(instructions,4,1,"|   Types of waveforms:                                                                                          |\n");    
    mvwprintw(instructions,5,1,"|   1. sine                                                                                                      |\n");
    mvwprintw(instructions,6,1,"|   2. square                                                                                                    |\n");
    mvwprintw(instructions,7,1,"|   3. triangle                                                                                                  |\n");
    mvwprintw(instructions,8,1,"|   4. sawtooth                                                                                                  |\n");
    mvwprintw(instructions,9,1,"+----------------------------------------------------------------------------------------------------------------+\n");
    mvwprintw(instructions,10,1,"|   Controls Available:                                                                                          |\n");
    mvwprintw(instructions,11,1,"|   To change the type of waveform generated, enter a value from 1 to 4.                                         |\n");
    mvwprintw(instructions,12,1,"|   To change the amplitude of the waveform, press 'w' to increment it by 1 or press 's' to decrement it by 1.   |\n");
    mvwprintw(instructions,13,1,"|   To change the frequency of the waveform, press 'a' to increment it by 1 or press 'd' to decrement it by 1.   |\n");
    mvwprintw(instructions,14,1,"|                                                                                                                |\n");
    mvwprintw(instructions,15,1,"+----------------------------------------------------------------------------------------------------------------+\n");
    mvwprintw(instructions,16,1,"\n");
    mvwprintw(instructions,17,1,"\n");
    
    mvwprintw(instructions,18,1,"+-----------------+-----------------+-----------------+\n");
    mvwprintw(instructions,19,1,"|       wave      |    amplitude    |    frequency    |\n");
    mvwprintw(instructions,20,1,"+-----------------+-----------------+-----------------+\n");
    refresh();
    pthread_mutex_lock(&mutex);
    mvwprintw(instructions,21,1,"|  %13s  | %15.2f |     %8.2f    |\n", waveforms, amp, freq);
    refresh();
    
    mvwprintw(instructions,22,1,"+-----------------+-----------------+-----------------+\n");
    
    mvwprintw(instructions,23,1,"\n");
    mvwprintw(instructions,24,1,"\n");
    refresh();
    mvwprintw(instructions,25,1,"+-----------------+-----------------+-----------------+\n");
    refresh();
    mvwprintw(instructions,26,1,"+ Debugger Log + %s \n", log );
    refresh();
    mvwprintw(instructions,27,1,"+-----------------+-----------------+-----------------+\n");

    pthread_mutex_unlock(&mutex);
  refresh();
	//getch();
	//endwin();
}

void* display(void* arg){
 ncurses_init();
 while (1){
 print_instructions(screen);
 }
}