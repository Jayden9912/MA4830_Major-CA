#ifndef PASS_ARGS_H
#define PASS_ARGS_H

#include <stdio.h>
#include <stdlib.h>
// #include <conio.h>

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

#endif