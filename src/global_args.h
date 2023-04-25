#ifndef GLOBAL_ARGS_H
#define GLOBAL_ARGS_H
#include <pthread.h>

extern pthread_mutex_t mutex;
// default args file path
extern const char *defaultfile;
extern const char *userfile;

// arguments
extern float freq; // 1.0 - 100 Hz
extern float duration;
extern float amp;     // 0 - 2.5V
extern int waveforms; // 1 = Sine wave
                      // 2 = Triangular wave
                      // 3 = Sawtooth wave
                      // 4 = Square wave

// three variables for validation of the arguments
extern int wave_valid;
extern int freq_valid;
extern int amp_valid;
char loginfo[70];

// input conditions
// 0: kbd
// 1 :potentiometer
extern int input_mode;

#endif