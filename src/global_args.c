#include "global_args.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// default args file path
const char *defaultfile = "default_config/default.dat";
const char *userfile = "user_setting/setting.dat";

// arguments
float freq = 0.0;     // 0.1 - 10.0 Hz
float duration = 0.0; // 0.02 - 0.002 s (1Hz - 10Hz)
float amp = 0.0;      // 0 - 2.5V
int waveforms = 0;    // 1 = Sine wave
                      // 2 = Triangular wave
                      // 3 = Sawtooth wave
                      // 4 = Square wave

// three variables for validation of the arguments
int wave_valid = 0;
int freq_valid = 0;
int amp_valid = 0;

int input_mode = 0;