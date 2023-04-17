#include <ctype.h>
#include <unistd.h>
#include <string.h>

void toLowerCase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}

// This function checks if the string is a valid float
// Argument:
//         str: pointer to the string
// Return:
//          1: not a valid float
//          0: a valid float
int isValidFloat(const char *str)
{
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

    int dotFound = 0; // Flag to keep track of the decimal dot
    // Check that all remaining characters are digits (0-9) or a single decimal dot
    for (size_t i = 0; i < len; i++)
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

// This function checks if the amplitude is within the range
// Argument:
//         checkAmp: amplitude value to be checked
// Return:
//          1: not within the range
//          0: within the range
int checkAmpRange(float check_amp)
{
    if (check_amp >= -5.0 && check_amp <= 5.0)
    {
        amp = check_amp;
        amp_valid = 1;
        printf("Setting amplitude to %f...\n", check_amp);
        return 0;
    }
    else
    {
        return 1;
    }
}

// This function checks if the frequency is within the range
// Argument:
//         checkFreq: frequency value to be checked
// Return:
//          1: not within the range
//          0: within the range
int checkFreqRange(float check_freq)
{
    if (check_freq >= 0.1 && check_freq <= 10.0)
    {
        freq = check_freq;
        freq_valid = 1;
        printf("Setting frequency to %f...\n", freq);
        return 0;
    }
    else
    {
        return 1;
    }
}

// This function check the value of waveforms and assign the corresponding value to the variable waveform
// Argument:
//         checkWaveform: waveform value to be checked
// Return:
//          1: not a valid waveform
//          0: a valid waveform
int checkWaveform(char *check_waveform)
{
    toLowerCase(check_waveform);
    if (!strcmp(check_waveform, "sine"))
    {
        waveforms = 1;
        wave_valid = 1;
        printf("Setting waveform to sine...\n");
        return 0;
    }
    else if (!strcmp(check_waveform, "triangular"))
    {
        waveforms = 2;
        wave_valid = 1;
        printf("Setting waveform to triangular...\n");
        return 0;
    }
    else if (!strcmp(check_waveform, "sawtooth"))
    {
        waveforms = 3;
        wave_valid = 1;
        printf("Setting waveform to sawtooth...\n");
        return 0;
    }
    else if (!strcmp(check_waveform, "square"))
    {
        waveforms = 4;
        wave_valid = 1;
        printf("Setting waveform to square...\n");
        return 0;
    }
    else
    {
        return 1;
    }
}