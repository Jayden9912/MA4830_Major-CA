#include "global_args.h"
#include "pass_args.h"
#include "utils.h"

void readDefaultArgs(const char *default_config_path)
{
    FILE *fp;
    int count;
    float tmp;

    int check_freq_float = 0;
    int check_amp_float = 0;
    int check_freq_value = 0;
    int check_amp_value = 0;
    int wave_assignment = 0;

    // Buffer to hold read data
    char buffer1[20];
    char buffer2[20];
    printf("%-10s| Loading all default arguments...\n", "[INFO]");

    if ((fp = fopen(default_config_path, "r")) == NULL)
    {
        perror(default_config_path);
        printf("%-10s| closing program...\n", "[INFO]");
        exit(1);
    }

    while (1)
    {
        count = fscanf(fp, "%s %s", buffer1, buffer2);
        if (count == EOF)
        {
            if (ferror(fp))
            {
            	printf("%-10s| ","[ERROR]");
                perror("Error encountered in reading the file!\n");
                break;
            }
            else if (!wave_valid || !freq_valid || !amp_valid)
            {
                printf("%-10s| The default config provided is edited and incomplete! Please refer to the instruction manual and to fix the default config file!\n", "[ERROR]");
                break;
            }
            else
            {
                printf("%-10s| All default arguments are parsed successfully!\n", "[INFO]");
                break;
            }
        }
        else if (count != 2)
        {
            printf("%-10s| only %d value(s) is successfully read and assigned! This means the default config file has been edited incorrectly! Please refer to the instruction manual and to fix the default config file!", "[ERROR]", count);
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
                wave_assignment = checkWaveform(buffer2);
                if (wave_assignment)
                {
                    printf("%-10s| The default value provided for wave option is not a valid! Please fix the default config file!\n", "[ERROR]");
                    break;
                }
            }
            else if (strcmp(buffer1, "amplitude") == 0)
            {
                check_amp_float = isValidFloat(buffer2);
                if (check_amp_float == 1)
                {
                    printf("%-10s| The default value provided for amplitude is not a valid float! Please fix the default config file!\n", "[ERROR]");
                    break;
                }
                tmp = strtod(buffer2, NULL);
                check_amp_value = checkAmpRange(tmp);
                if (check_amp_value)
                {
                    printf("%-10s| The default value provided for amplitude is out of range! Please fix the default config file!\n", "[ERROR]");
                    break;
                }
            }
            else if (strcmp(buffer1, "frequency") == 0)
            {
                check_freq_float = isValidFloat(buffer2);
                if (check_freq_float == 1)
                {
                    printf("%-10s| The default value provided for frequency is not a valid float! Please fix the default config file!\n", "[ERROR]");
                    break;
                }
                tmp = strtod(buffer2, NULL);
                check_freq_value = checkFreqRange(tmp);
                if (check_freq_value)
                {
                    printf("%-10s| The default value provided for freqeuncy is out of range! Please fix the default config file!\n", "[ERROR]");
                    break;
                }
            }
            else
            {
                printf("%-10s| Unexpected arguments %s given. Continue checking other arguments given.\n", "[INFO]", buffer1);
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
    int check_freq_value = 0;
    int check_amp_value = 0;
    int wave_assignment = 0;

    float tmp = 0.0;

    // no args used
    if (argc == 1)
    {
        printf("%-10s| No arguments given\n", "[WARNING]");
        return 1;
    }

    // args are not paired with values
    if (argc % 2 == 0)
    {
        printf("%-10s| Options are not in pair with values!\n", "[WARNING]");
        return 1;
    }

    // checking and assign the values based on args used
    while (argv[2 * pointer_i + 1] != NULL)
    {
        // invalid options such as a or - or -aa
        if (argv[2 * pointer_i + 1][0] != '-' || argv[2 * pointer_i + 1][1] == '\0' || strlen(argv[2 * pointer_i + 1]) != 2)
        {
            printf("%-10s| Invalid options!\n", "[WARNING]");
            return 1;
        }
        switch (argv[2 * pointer_i + 1][1])
        {
        case 'w':
            wave_assignment = checkWaveform(argv[2 * pointer_i + 2]);
            if (wave_assignment == 0)
                break;
            else
            {
                printf("%-10s| Invalid wave option.\n", "[WARNING]");
                return 1;
            }
        case 'a':
            check_amp_float = isValidFloat(argv[2 * pointer_i + 2]);
            if (check_amp_float == 1)
            {
                printf("%-10s| Invalid float value is given for \n", "[WARNING]");
                return 1;
            }
            tmp = strtod(argv[2 * pointer_i + 2], NULL);
            check_amp_value = checkAmpRange(tmp);
            if (check_amp_value == 0)
                break;
            else
            {
                printf("%-10s| Amplitude value provided is out of range!\n", "[WARNING]");
                return 1;
            }
        case 'f':
            check_freq_float = isValidFloat(argv[2 * pointer_i + 2]);
            if (check_freq_float == 1)
            {
                printf("%-10s| Invalid float value is given\n", "[WARNING]");
                return 1;
            }
            tmp = strtod(argv[2 * pointer_i + 2], NULL);
            check_freq_value = checkFreqRange(tmp);
            if (check_freq_value == 0)
                break;
            else
            {
                printf("%-10s| Frequency value provided is out of range!\n", "[WARNING]");
                return 1;
            }
        default:
            printf("%-10s| Unexpected arguments %s given. Continue checking other arguments given.\n", "[INFO]", argv[2 * pointer_i + 1][1]);
        }
        pointer_i++;
    }

    // if all arguments given are non valid e.g. -z 5 -r 4
    if (!wave_valid || !freq_valid || !amp_valid)
    {
        printf("%-10s| Incomplete arguments are provided!\n", "[ERROR]");
        return 1;
    }
    else
    {
        printf("%-10s| All arguments are parsed successfully!\n", "[INFO]");
        return 0;
    }
    return 0;
}