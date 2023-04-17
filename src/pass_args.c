#include "pass_args.h"
#include "utils.h"

void readDefaultArgs(const char *default_config_path)
{
    printf("Loading all default arguments...\n");
    FILE *fp;
    int count;
    float tmp;

    int check_freq_float = 0;
    int check_amp_float = 0;

    // Buffer to hold read data
    char buffer1[20];
    char buffer2[20];

    if ((fp = fopen(default_config_path, "r")) == NULL)
    {
        perror(default_config_path);
        printf("closing program...\n");
        exit(1);
    }

    while (1)
    {
        count = fscanf(fp, "%s %s", buffer1, buffer2);
        if (count == EOF)
        {
            if ferror (fp)
            {
                perror("Error encountered in reading the file!\n");
                break;
            }
            else if (!wave_valid || !freq_valid || !amp_valid)
            {
                printf("The default config provided is edited and incomplete! Please refer to the instruction manual and to fix the default config file!\n");
                break;
            }
            else
            {
                printf("All default arguments are parsed successfully!\n");
                break;
            }
        }
        else if (count != 2)
        {
            printf("[ERROR]: only %d value(s) is successfully read and assigned! This means the default config file has been edited incorrectly! Please refer to the instruction manual and to fix the default config file!", count);
            break;
        }
        else
        {
            // Convert key to lowercase
            toLowerCase(buffer1);

            // Compare key to determine which value to store
            // Only use default value when the user failed to provide value
            if (strcmp(buffer1, "wave") == 0)
            {
                if (!strcmp(buffer2, "sine"))
                {
                    printf("Setting waveform as sine wave...\n");
                    waveforms = 1;
                    wave_valid = 1;
                }

                else if (!strcmp(buffer2, "triangular"))
                {
                    printf("Setting waveform as triangular wave...\n");
                    waveforms = 2;
                    wave_valid = 1;
                }

                else if (!strcmp(buffer2, "sawtooth"))
                {
                    printf("Setting waveform as sawtooth wave...\n");
                    waveforms = 3;
                    wave_valid = 1;
                }
                else if (!strcmp(buffer2, "square"))
                {
                    printf("Setting waveform as square wave...\n");
                    waveforms = 4;
                    wave_valid = 1;
                }
                else
                {
                    printf("The default value provided for wave option is not a valid! Please fix the default config file!\n");
                    break;
                }
            }
            else if (strcmp(buffer1, "amplitude") == 0)
            {
                check_amp_float = isValidFloat(buffer2);
                if (check_amp_float == 0)
                {
                    printf("The default value provided for amplitude is not a valid float! Please fix the default config file!\n");
                    break;
                }
                tmp = strtod(buffer2, NULL);
                if (tmp >= -5.0 && tmp <= 5.0)
                {
                    amp = tmp;
                    amp_valid = 1;
                    printf("Setting amplitude to %f...\n", tmp);
                }
                else
                {
                    printf("The default value provided for amplitude is out of range! Please fix the default config file!\n");
                    break;
                }
            }
            else if (strcmp(buffer1, "frequency") == 0)
            {
                check_freq_float = isValidFloat(buffer2);
                if (check_freq_float == 0)
                {
                    printf("The default value provided for frequency is not a valid float! Please fix the default config file!\n");
                    break;
                }
                tmp = strtod(buffer2, NULL);
                if (tmp >= 0.1 && tmp <= 10.0)
                {
                    freq = tmp;
                    freq_valid = 1;
                    printf("Setting frequency to %f...\n", tmp);
                }
                else
                {
                    printf("The default value provided for freqeuncy is out of range! Please fix the default config file!\n");
                    break;
                }
            }
            else
            {
                printf("Unexpected arguments %s given. Continue checking other arguments given.\n", buffer1);
            }
        }
    }
    fclose(fp); // Close file
}

int passArgs(int argc, char *argv[])
{
    int pointer_i = 0;

    // variable for checking float given
    int check_freq_float = 0;
    int check_amp_float = 0;

    float tmp = 0.0;

    // no args used
    if (argc == 1)
    {
        printf("No arguments given\n");
        return 1;
    }

    // args are not paired with values
    if (argc % 2 == 0)
    {
        printf("Options are not in pair with values!\n");
        return 1;
    }

    // checking and assign the values based on args used
    while (argv[2 * pointer_i + 1] != NULL)
    {
        // invalid options such as a or - or -aa
        if (argv[2 * pointer_i + 1][0] != '-' || argv[2 * pointer_i + 1][1] == '\0' || strlen(argv[2 * pointer_i + 1]) != 2)
        {
            printf("Invalid options!\n");
            return 1;
        }
        switch (argv[2 * pointer_i + 1][1])
        {
        case 'w':
            if (!strcmp(argv[2 * pointer_i + 2], "sine"))
            {
                printf("Setting waveform as sine wave...\n");
                waveforms = 1;
                wave_valid = 1;
                break;
            }

            else if (!strcmp(argv[2 * pointer_i + 2], "triangular"))
            {
                printf("Setting waveform as triangular wave...\n");
                waveforms = 2;
                wave_valid = 1;
                break;
            }

            else if (!strcmp(argv[2 * pointer_i + 2], "sawtooth"))
            {
                printf("Setting waveform as sawtooth wave...\n");
                waveforms = 3;
                wave_valid = 1;
                break;
            }
            else if (!strcmp(argv[2 * pointer_i + 2], "square"))
            {
                printf("Setting waveform as square wave...\n");
                waveforms = 4;
                wave_valid = 1;
                break;
            }
            else
            {
                printf("Invalid wave option.\n");
                return 1;
            }
        case 'a':
            check_amp_float = isValidFloat(argv[2 * pointer_i + 2]);
            if (check_amp_float == 0)
            {
                printf("Invalid float value is given for \n");
                return 1;
            }
            tmp = strtod(argv[2 * pointer_i + 2], NULL);
            if (tmp >= -5.0 && tmp <= 5.0)
            {
                amp = tmp;
                amp_valid = 1;
                printf("Setting amplitude to %f...\n", tmp);
                break;
            }
            else
            {
                printf("Amplitude value provided is out of range!\n");
                return 1;
            }
        case 'f':
            check_freq_float = isValidFloat(argv[2 * pointer_i + 2]);
            if (check_freq_float == 0)
            {
                printf("Invalid float value is given\n");
                return 1;
            }
            tmp = strtod(argv[2 * pointer_i + 2], NULL);
            if (tmp >= 0.1 && tmp <= 10.0)
            {
                freq = tmp;
                freq_valid = 1;
                printf("Setting frequency to %f...\n", tmp);
                break;
            }
            else
            {
                printf("Frequency value provided is out of range!\n");
                return 1;
            }
        default:
            printf("Unexpected arguments %s given. Continue checking other arguments given.\n", argv[2 * pointer_i + 1][1]);
        }
        pointer_i++;
    }

    // if all arguments given are non valid e.g. -z 5 -r 4
    if (!wave_valid || !freq_valid || !amp_valid)
    {
        printf("Incomplete arguments are provided!\n");
        return 1;
    }
    else
    {
        printf("All arguments are parsed successfully!\n");
        return 0;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int state = 0;

    state = passArgs(argc, argv);

    // problem encountered in parsing arguments
    if (state != 0)
    {
        // load default value for waveform, amplitude and frequency
        readDefaultArgs(defaultfile);
        if (!wave_valid || !amp_valid || !freq_valid) // unsuccessful attempt in reading default config file
        {
            printf("[ERROR]: Unsuccessful attempt in reading default config file!\n");
        }
    }

    return 0;
}