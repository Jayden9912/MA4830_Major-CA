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
    strcpy(wave, "Sine");
  }
  else if (waveforms == 2)
  {
    strcpy(wave, "Triangle");
  }
  else if (waveforms == 3)
  {
    strcpy(wave, "Sawtooth");
  }
  else if (waveforms == 4)
  {
    strcpy(wave, "Square");
  }
  if (input_mode == 0)
  {
    strcpy(mode, "Keyboard mode");
  }
  else if (input_mode == 1)
  {
    strcpy(mode, "Potentiometer mode");
  }
  else
  {
    strcpy(mode, "No input mode");
  }
  pthread_mutex_unlock(&mutex);

  // Set up the container box
  box(instructions, 0, 0);

  // Print respective keys to change amplitude and frequency

  mvwprintw(instructions, 0, 1, "|   %-108s |\n", "INSTRUCTIONS:");
  mvwprintw(instructions, 1, 1, "+----------------------------------------------------------------------------------------------------------------+\n");
  mvwprintw(instructions, 2, 1, "|                                                Waveform Generator                                              |\n");
  mvwprintw(instructions, 3, 1, "+----------------------------------------------------------------------------------------------------------------+\n");
  mvwprintw(instructions, 4, 1, "|   Types of waveforms:                                                                                          |\n");
  mvwprintw(instructions, 5, 1, "|   1. Sine                                                                                                      |\n");
  mvwprintw(instructions, 6, 1, "|   2. Square                                                                                                    |\n");
  mvwprintw(instructions, 7, 1, "|   3. Triangle                                                                                                  |\n");
  mvwprintw(instructions, 8, 1, "|   4. Sawtooth                                                                                                  |\n");
  mvwprintw(instructions, 9, 1, "+----------------------------------------------------------------------------------------------------------------+\n");
  mvwprintw(instructions, 10, 1, "|   %-108s |\n", "Controls Available:");
  mvwprintw(instructions, 11, 1, "|   %-108s |\n",  " ");
  mvwprintw(instructions, 12, 1, "|   %-108s |\n","Potentiometer mode");
  mvwprintw(instructions, 13, 1, "|   %-108s |\n", "Wave amplitude  | turn clockwise to increase (+), anticlockwise to decrease (-)");
  mvwprintw(instructions, 14, 1, "|   %-108s |\n", "Wave frequency  | turn clockwise to increase (+), anticlockwise to decrease (-)");
  mvwprintw(instructions, 15, 1, "|   %-108s |\n",  " ");
  mvwprintw(instructions, 16, 1, "|   %-108s |\n", "Keyboard mode");
  mvwprintw(instructions, 17, 1, "|   %-108s |\n", "Wave amplitude  | 'w' to increase (+), 's' to decrease (-)");
  mvwprintw(instructions, 18, 1, "|   %-108s |\n", "Wave frequency  | 'd' increase (+), 'a' to decrease (-)");  
  mvwprintw(instructions, 19, 1, "|   %-108s |\n", "Wave type       | '1' for sine, '2' for triangular, '3' for sawtooth, '4' for square");
  mvwprintw(instructions, 20, 1, "|                                                                                                                |\n");
  mvwprintw(instructions, 21, 1, "+----------------------------------------------------------------------------------------------------------------+\n");
  mvwprintw(instructions, 22, 1, "\n");
  mvwprintw(instructions, 23, 1, "\n");
  mvwprintw(instructions, 24, 1, "+-------------------+-----------------+-----------------+\n");
  mvwprintw(instructions, 25, 1, "| Wave              | Amplitude       | Frequency       |\n");
  mvwprintw(instructions, 26, 1, "+-------------------+-----------------+-----------------+\n");
  refresh();
  pthread_mutex_lock(&mutex);
  mvwprintw(instructions, 27, 1, "| %-15s   | %-15.2f | %-8.2f        |\n", wave, amp, freq);
  refresh();
  mvwprintw(instructions, 28, 1, "+-------------------+-----------------+-----------------+\n");
  mvwprintw(instructions, 29, 1, "\n");
  mvwprintw(instructions, 30, 1, "\n");
  refresh();
  mvwprintw(instructions, 31, 1, "+-------------------+--------------------------------------------------------------------------------------------+\n");
  refresh();
  mvwprintw(instructions, 32, 1, "| %-17s | %-90s |\n", "Log", loginfo);
  mvwprintw(instructions, 33, 1, "+-------------------+--------------------------------------------------------------------------------------------+\n");
  mvwprintw(instructions, 34, 1, "| %-17s | %-90s |\n", "Input Mode", mode);
  refresh();
  mvwprintw(instructions, 35, 1, "+-------------------+--------------------------------------------------------------------------------------------+\n");
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
