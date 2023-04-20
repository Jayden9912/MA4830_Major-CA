#include "display_ui.h"

void ncurses_init()
{

  // Curses init
  screen = initscr();

  // Intial setup
  nodelay(screen, 1);
  cbreak();
  noecho();
  curs_set(0);

  mvprintw(115, 155, " ");
  keypad(screen, TRUE);

  // Dot settings
  attron(A_STANDOUT);
}

// main window to show all information
void print_instructions(WINDOW *instructions)
{
  char wave[12] = " "; // wave name buffer
  char mode[20] = " "; // input mode buffer

  pthread_mutex_lock(&mutex);
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
  if (input_mode == 0)
  {
    strcpy(mode, "keyboard mode");
  }
  else if (input_mode == 1)
  {
    strcpy(mode, "potentiometer mode");
  }
  else
  {
    strcpy(mode, "No input mode");
  }
  pthread_mutex_unlock(&mutex);

  // Set up the container box
  box(instructions, 0, 0);

  // Print respective keys to change amplitude and frequency

  mvwprintw(instructions, 0, 1, " INSTRUCTIONS: ");
  mvwprintw(instructions, 1, 1, "+----------------------------------------------------------------------------------------------------------------+\n");
  mvwprintw(instructions, 2, 1, "|                                                Waveform Generator                                              |\n");
  mvwprintw(instructions, 3, 1, "+----------------------------------------------------------------------------------------------------------------+\n");
  mvwprintw(instructions, 4, 1, "|   Types of waveforms:                                                                                          |\n");
  mvwprintw(instructions, 5, 1, "|   1. sine                                                                                                      |\n");
  mvwprintw(instructions, 6, 1, "|   2. square                                                                                                    |\n");
  mvwprintw(instructions, 7, 1, "|   3. triangle                                                                                                  |\n");
  mvwprintw(instructions, 8, 1, "|   4. sawtooth                                                                                                  |\n");
  mvwprintw(instructions, 9, 1, "+----------------------------------------------------------------------------------------------------------------+\n");
  mvwprintw(instructions, 10, 1, "|   Controls Available:                                                                                          |\n");
  mvwprintw(instructions, 11, 1, "|   To change the type of waveform generated, enter a value from 1 to 4.                                         |\n");
  mvwprintw(instructions, 12, 1, "|   To change the amplitude of the waveform, press 'w' to increment it by 1 or press 's' to decrement it by 1.   |\n");
  mvwprintw(instructions, 13, 1, "|   To change the frequency of the waveform, press 'a' to increment it by 1 or press 'd' to decrement it by 1.   |\n");
  mvwprintw(instructions, 14, 1, "|                                                                                                                |\n");
  mvwprintw(instructions, 15, 1, "+----------------------------------------------------------------------------------------------------------------+\n");
  mvwprintw(instructions, 16, 1, "\n");
  mvwprintw(instructions, 17, 1, "\n");
  mvwprintw(instructions, 18, 1, "+-------------------+-----------------+-----------------+\n");
  mvwprintw(instructions, 19, 1, "|       wave        |    amplitude    |    frequency    |\n");
  mvwprintw(instructions, 20, 1, "+-------------------+-----------------+-----------------+\n");
  refresh();
  pthread_mutex_lock(&mutex);
  mvwprintw(instructions, 21, 1, "|  %-15s  | %15.2f |     %8.2f    |\n", wave, amp, freq);
  refresh();
  mvwprintw(instructions, 22, 1, "+-------------------+-----------------+-----------------+\n");
  mvwprintw(instructions, 23, 1, "\n");
  mvwprintw(instructions, 24, 1, "\n");
  refresh();
  mvwprintw(instructions, 25, 1, "+-------------------+--------------------------------------------------------------------------------------------+\n");
  refresh();
  mvwprintw(instructions, 26, 1, "| %-17s | %-90s |\n", "Log", loginfo);
  mvwprintw(instructions, 27, 1, "+-------------------+--------------------------------------------------------------------------------------------+\n");
  mvwprintw(instructions, 28, 1, "| %-17s | %-90s |\n", "Input Mode", mode);
  refresh();
  mvwprintw(instructions, 29, 1, "+-------------------+--------------------------------------------------------------------------------------------+\n");
  pthread_mutex_unlock(&mutex);
  refresh();
}

// display thread, display all information on screen in real time
void *display(void *arg)
{
  ncurses_init();
  while (1)
  {
    print_instructions(screen);
  }
}
