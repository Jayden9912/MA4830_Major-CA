#ifndef KBD_H
#define KBD_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "global_args.h"

// This function receives input from user via keyboard and updates the global variables
// Usage:
// w key to increase amp
// s key to decrease amp
// a key to decrease freq
// d key to increse freq
// 1 for waveform sine
// 2 for waveform triangle
// 3 for waveform sawtooth
// 4 for waveform square
// amp: amplitude current: 0-2.5 future: 0-100
// freq: frequency 1-10
void *kbdUpdate(void* arg);

// This function saves the user setting to the file setting.dat
void save2file();
#endif