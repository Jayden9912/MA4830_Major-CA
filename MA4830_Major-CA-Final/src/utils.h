#ifndef UTILS_H
#define UTILS_H
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "global_args.h"

// This function converts a string to lowercase
// Argument:
//         str: pointer to the string
void toLowerCase(char *str);

// This function calculates the delay duration for the specific frequency
// Argument:
//         freq: frequency value
int calculateDuration();

// This function checks if the string is a valid float
// Argument:
//         str: pointer to the string
// Return:
//          1: not a valid float
//          0: a valid float
int isValidFloat(const char *str);

// This function checks if the amplitude is within the range
// Argument:
//         checkAmp: amplitude value to be checked
// Return:
//          1: not within the range
//          0: within the range
int checkAmpRange(const float check_amp);

// This function checks if the frequency is within the range
// Argument:
//         checkFreq: frequency value to be checked
// Return:
//          1: not within the range
//          0: within the range
int checkFreqRange(const float check_freq);

// This function check the value of waveforms and assign the corresponding value to the variable waveform
// Argument:
//         checkWaveform: waveform value to be checked
// Return:
//          1: not a valid waveform
//          0: a valid waveform
int checkWaveform(char *check_waveform);

#endif