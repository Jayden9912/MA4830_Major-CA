#include "utils.h"

// convert string to lower case
void toLowerCase(char *str)
{
    unsigned int i;
    for (i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}

// calculate delay duration
int calculateDuration()
{
    pthread_mutex_lock(&mutex);
    duration = 100 / freq;
    pthread_mutex_unlock(&mutex);
    return (unsigned int)duration;
}

// check if the string is a valid float
int isValidFloat(const char *str)
{
    unsigned int i;
    int dotFound;
    size_t len = strlen(str);
    if (len == 0)
    {
        return 1; // Empty string is not a valid float
    }

    if (!(str[0] >= '0') || !(str[0] <= '9')) // first char is not number
    {
        if (len == 1)
        { // sign without any digits is not a valid float
            return 1;
        }
        if (str[0] == '-')
        {
            str++; // move past the sign character
            len--;
        }
    }

    dotFound = 0; // Flag to keep track of the decimal dot
    // Check that all remaining characters are digits (0-9) or a single decimal dot
    for (i = 0; i < len; i++)
    {
        if (str[i] == '.')
        {
            if (dotFound)
            {
                return 1; // More than one decimal dot found, not a valid float
            }
            dotFound = 1; // Set dotFound to true after encountering the first dot
        }
        else if (str[i] < '0' || str[i] > '9')
        {
            return 1; // Non-digit or non-dot character found, not a valid float
        }
    }

    return 0; // String represents a valid float
}

// check amplitude range from 0 to 2.5 v
int checkAmpRange(const float check_amp)
{
    if (check_amp >= 0 && check_amp <= 2.5)
    {
        pthread_mutex_lock(&mutex);
        amp = check_amp;
        amp_valid = 1;
        pthread_mutex_unlock(&mutex);
        printf("%-10s| Setting amplitude to %.2f...\n", "[INFO]", check_amp);
        return 0;
    }
    else
    {
        return 1;
    }
}


// check frequency range from 1 to 100 hz 
int checkFreqRange(const float check_freq)
{
    if (check_freq >= 1.0 && check_freq <= 100.0)
    {
        pthread_mutex_lock(&mutex);
        freq = check_freq;
        freq_valid = 1;
        pthread_mutex_unlock(&mutex);
        printf("%-10s| Setting frequency to %.2f...\n", "[INFO]", freq);
        return 0;
    }
    else
    {
        return 1;
    }
}

// check wave type
int checkWaveform(char *check_waveform)
{
    toLowerCase(check_waveform);
    if (!strcmp(check_waveform, "sine"))
    {
        pthread_mutex_lock(&mutex);
        waveforms = 1;
        wave_valid = 1;
        pthread_mutex_unlock(&mutex);
        printf("%-10s| Setting waveform to sine...\n", "[INFO]");
        return 0;
    }
    else if (!strcmp(check_waveform, "triangular"))
    {
        pthread_mutex_lock(&mutex);
        waveforms = 2;
        wave_valid = 1;
        pthread_mutex_unlock(&mutex);
        printf("%-10s| Setting waveform to triangular...\n", "[INFO]");
        return 0;
    }
    else if (!strcmp(check_waveform, "sawtooth"))
    {
        pthread_mutex_lock(&mutex);
        waveforms = 3;
        wave_valid = 1;
        pthread_mutex_unlock(&mutex);
        printf("%-10s| Setting waveform to sawtooth...\n", "[INFO]");
        return 0;
    }
    else if (!strcmp(check_waveform, "square"))
    {
        pthread_mutex_lock(&mutex);
        waveforms = 4;
        wave_valid = 1;
        pthread_mutex_unlock(&mutex);
        printf("%-10s| Setting waveform to square...\n", "[INFO]");
        return 0;
    }
    else
    {
        return 1;
    }
}