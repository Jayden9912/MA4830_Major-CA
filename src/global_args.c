#include "global_args.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

const char *defaultfile = "default_config/default.dat";
const char *userfile = "user_setting/setting.dat";

float freq = 0.0;
float duration = 0.0;
float amp = 0.0;
int waveforms = 0;
int wave_valid = 0;
int freq_valid = 0;
int amp_valid = 0;
int input_mode = 0;