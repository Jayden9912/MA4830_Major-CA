#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "global_args.h"
#include <pthread.h>
#include <string.h>

WINDOW* screen;
void print_instructions(WINDOW *instructions);
void ncurses_init();

void* display(void* arg);

#endif