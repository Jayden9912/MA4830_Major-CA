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
        return 0; // Empty string is not a valid float
    }

    if (!(str[0] >= '0') || !(str[0] <= '9')) // first char is not number
    {
        if (len == 1)
        { // sign without any digits is not a valid float
            return 0;
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
                return 0; // More than one decimal dot found, not a valid float
            }
            dotFound = 1; // Set dotFound to true after encountering the first dot
        }
        else if (str[i] < '0' || str[i] > '9')
        {
            return 0; // Non-digit or non-dot character found, not a valid float
        }
    }

    return 1; // String represents a valid float
}