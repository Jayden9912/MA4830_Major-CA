#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "global_args.h"
#include <pthread.h>
#include <string.h>

WINDOW *screen;

// This function is used to print the instructions on the screen
// Argument:
//  instructions: the pointer to ncurses window object
void print_instructions(WINDOW *instructions);

// This function is used to initialize the ncurses screen
void ncurses_init();

// This function is used to display all information on screen
void *display(void *arg);

#endif