#ifndef GLOBAL_ARGS_H
#define GLOBAL_ARGS_H
#include <pthread.h>

pthread_mutex_t mutex;
// default args file path
const char *defaultfile;
const char *userfile;

// arguments
extern float freq;     // 0.1 - 10.0 Hz
extern float duration; // 0.02 - 0.002 s (1Hz - 10Hz)
extern float amp;      // 0 - 2.5V
extern int waveforms;  // 1 = Sine wave
                       // 2 = Triangular wave
                       // 3 = Sawtooth wave
                       // 4 = Square wave

// three variables for validation of the arguments
int wave_valid;
int freq_valid;
int amp_valid;

// input conditions
//0: kbd
//1 :potentiometer
int input_mode;


#endif