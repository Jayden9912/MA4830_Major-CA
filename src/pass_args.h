#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// default args file path
const char *defaultfile = "default_config\\default.dat";

// three arguments
float freq;    // 0.1 - 10.0 Hz
float amp;     // 0 - 2.5V
int waveforms; // 1 = Sine wave
               // 2 = Triangular wave
               // 3 = Sawtooth wave
               // 4 = Square wave

// three variables for validation of the arguments
int wave_valid = 0;
int freq_valid = 0;
int amp_valid = 0;

// This function pass the argument
// Argument:
//      argc: number of argument
//      argv: pointer to pointer of argument
// Return:
//      0: success
//      1: no command line argument used
//      2: invalid option
//      3: choose default setting while providing values
int passArgs(int argc, char *argv[]);

// This function reads the default values for all the arguments.
// Value from this file will only be used if the user opts to do so
// Argument:
//      default_config_path: the filepath to the default config file
void readDefaultArgs(const char *default_config_path);
