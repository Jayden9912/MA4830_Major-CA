#include "display.h"
const char *choices[] = { 
                          "Sine_Wave         ",
                          "Square_Wave       ",
                          "Triangular_Wave   ",
                          "Sawtooth_Wave     ",
                        };
char title[]="Wave Generator\n";



void print_menu(WINDOW *choices_win)
{
  int widths, heights, number_of_choice;	

  // Set up the container box
	widths = 1;
	heights = 1;
	box(choices_win, 0, 0);
  attron(A_BOLD);
  mvwprintw(choices_win, 0, widths, " CHOICES: ");
  attroff(A_BOLD);

  n_choices = sizeof(choices) / sizeof(char *);
  for(number_of_choice = 0; number_of_choice < n_choices; ++number_of_choice)
	{
    // Print all the available waveform choices
    mvwprintw(choices_win, heights, widths, "%s", choices[number_of_choice]);
    heights+=1;    
	}
}

void print_details(WINDOW *wave_details)
{
  // Set up the container box
  box(wave_details, 0, 0);

  // Print all the parameters of the waveform
  mvwprintw(wave_details, 0, 1, " WAVE_DETAILS: ");
  mvwprintw(wave_details, 1, 1, "PERIOD:  %8.2f ", period);
  mvwprintw(wave_details, 2, 1, "AMPLITUDE:  %.2f ", 4.00);
  mvwprintw(wave_details, 3, 1, "PHASE: %7d    ", phase_shift);
  mvwprintw(wave_details, 4, 1, "FREQUENCY: %.1f    ", 4.00);
}

void print_instructions(WINDOW *instructions)
{
  // Set up the container box
  box(instructions, 0, 0);

  // Print respective keys to change amplitude and frequency
  mvwprintw(instructions, 0, 1, " INSTRUCTIONS: ");
  mvwprintw(instructions, 1, 1, "Press (key) to change VALUE:");
  mvwprintw(instructions, 2, 1, "                            ");
  mvwprintw(instructions, 3, 1, "    -(s) AMPLITUDE +(w)     ");
  mvwprintw(instructions, 4, 1, "    -(a) FREQUENCY +(d)     ");
  
}

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
int main(){
    while (1){
    ncurses_init();
     // Set these boxes as the sub-window of the main window (screen) and their sizes
  wave_details = derwin(screen, 6, 20, 2, (title_column-20)/2);

  choices_win = derwin(screen, 6, 20, 2, (title_column-20)*1/5);

  instructions = derwin(screen,6, 30, 2, (title_column-20)*4/5);

  // Print current type of waveform
  mvprintw(0, 0, "RUNNING: %s", "sine");

  // Print all the boxes
  print_details(wave_details);
  print_menu(choices_win);
  print_instructions(instructions);

    }
}