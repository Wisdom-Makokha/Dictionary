#include "../definition/database_definitions.h"

// function to create memory for the terminal options structure and initialise it with values
terminal_options *create_options_struct(char **database_name, char **dsn, char **fileDSN, char **save_file_DSN)
{
    terminal_options *options_to_set = (terminal_options *)malloc(sizeof(terminal_options));

    // check for memory allocation issues
    if (options_to_set == NULL)
    {
        // fprintf(stderr, "Error allocating memory to terminal options struct in: %s\n", __func__);
        write_logs("MEMALLOC", MEM_ALLOC_ERROR, "Error allocating memory to terminal options struct", __func__);
    }
    else
    {
        // initialise the values
        // all options are initialised with the option_to_set member set to false
        // the pointers to where the value will be stored is then given passed
        options_to_set->database_name.option_is_set = false;
        options_to_set->database_name.string_value = database_name;

        options_to_set->dsn.option_is_set = false;
        options_to_set->dsn.string_value = dsn;

        options_to_set->fileDSN.option_is_set = false;
        options_to_set->fileDSN.string_value = fileDSN;

        options_to_set->savefileDSN.option_is_set = false;
        options_to_set->savefileDSN.string_value = save_file_DSN;
    }

    return options_to_set;
}

int terminal_processing(int argc, char **argv, terminal_options *options_to_set)
{
    int dash = 0;
    int selection = 1;
    int result = OP_SUCCESS;
    unsigned longest_option = 6;

    // the loop condition is checking upto a -1 total since two values are evaluated the flag with the following string taken as a value
    // it is important to ensure that we do not try to enter into unassigned territory for the argv string array
    // segmentation fault evasion
    for (int index = 1; index < (argc - 1) && index < (MAX_TERMINAL_ARGS - 1); index++)
    {
        // cutoff the string in case the value exceeds a certain value specified by MAX_OPTION_VALUE_LEN
        if (strlen(argv[index + 1]) >= MAX_OPTION_VALUE_LEN)
            argv[index + 1][MAX_OPTION_VALUE_LEN] = '\0';

        // -fldsn dictionary_connection -svfl dictionary_connection -db Dictionary -dsn Test_DSN
        if ((strlen(argv[index]) <= longest_option) && argv[index][dash] == '-')
        {
            switch (tolower(argv[index][selection]))
            {
            // database and dsn selections
            case 'd':
                switch (tolower(argv[index][selection + 1]))
                {
                // dsn selection
                case 's':
                    if (!(options_to_set->dsn.option_is_set))
                    {
                        // set selection to no longer missing
                        options_to_set->dsn.option_is_set = true;

                        index++;
                        *(options_to_set->dsn.string_value) = argv[index];
                    }
                    else
                        index++;

                    break;
                // database selection
                case 'b':
                    if (!(options_to_set->database_name.option_is_set))
                    {
                        // set selection to no longer missing
                        options_to_set->database_name.option_is_set = true;

                        index++;
                        *(options_to_set->database_name.string_value) = argv[index];
                    }
                    else
                        index++;
                    break;
                default:
                    result = OP_FAILURE;
                    break;
                }
                break;
            // filedsn selection
            case 'f':
                if (!(options_to_set->fileDSN.option_is_set))
                {
                    // set selection no longer missing
                    options_to_set->fileDSN.option_is_set = true;

                    index++;
                    // set selection value
                    *(options_to_set->fileDSN.string_value) = argv[index];
                }
                else
                    index++;

                break;
            // savefile selection
            case 's':
                // check if save file has been set before since trying to set it twice is possible
                if (!(options_to_set->savefileDSN.option_is_set))
                {
                    // set selection no longer missing
                    options_to_set->savefileDSN.option_is_set = true;

                    index++;

                    // set selection value
                    *(options_to_set->savefileDSN.string_value) = argv[index];
                }
                else
                    index++;

                break;
            default:
                result = OP_FAILURE;
                break;
            }
        }
        else
            result = OP_FAILURE;

        // if any of the options return a failure the stop the loop
        if (result == OP_FAILURE)
            break;
    }

    return result;
}

// function to confirm set terminal options
void confirm_options(terminal_options *set_options)
{
    bool stop = false;
    const int response_size = 10;
    char response[response_size];

    while (!stop)
    {
        
        printf("These are your set options:- \n");
        printf("%15s: %s\n", "DSN", *(set_options->dsn.string_value));
        printf("%15s: %s\n", "Database", *(set_options->database_name.string_value));
        printf("%15s: %s\n", "File DSN", *(set_options->fileDSN.string_value));
        printf("%15s: %s\n", "Save file", *(set_options->savefileDSN.string_value));

        printf("Proceed with these options? (yes/no): ");
        fgets(response, response_size, stdin);

        if (response[0] == 'y')
            break;
        else if (response[0] == 'n')
        {
            printf("\nWhich selection do you want to change: (Enter the number for your picked selection)\n");
            printf("%15s: %d\n", "  Database name", TO_DATABASE_NAME - 99);
            printf("%15s: %d\n", "  DSN", TO_DSN - 99);
            printf("%15s: %d\n", "  Save file", TO_SAVE_FILE - 99);
            printf("%15s: %d\n", "  File DSN", TO_FILE_DSN - 99);
            printf("%15s: %d\n", "  None", TO_NONE - 99);
            printf("\nEnter response: ");

            fgets(response, response_size, stdin);
            int option_response = atoi(response) + 99;

            switch (option_response)
            {
            case TO_DATABASE_NAME:
                if(get_option_from_user(*(set_options->database_name.string_value), "database name") == OP_FAILURE)
                    printf("Error getting input\n");

                set_options->database_name.option_is_set = true;
                break;
            case TO_DSN:
                if(get_option_from_user(*(set_options->dsn.string_value), "data source") == OP_FAILURE)
                    printf("Error getting input\n");

                set_options->dsn.option_is_set = true;
                break;
            case TO_SAVE_FILE:
                if(get_option_from_user(*(set_options->savefileDSN.string_value), "save file name") == OP_FAILURE)
                    printf("Error getting input\n");

                set_options->savefileDSN.option_is_set = true;
                break;
            case TO_FILE_DSN:
                if(get_option_from_user(*(set_options->fileDSN.string_value), "file dsn") == OP_FAILURE)
                    printf("Error getting input\n");

                set_options->fileDSN.option_is_set = true;
                break;
            case TO_NONE:
                stop = true;
                break;
            default:
                printf("Unknown response: %d\n", option_response);
                break;
            }
        }
        else
            printf("Unknown response\n");
    }
}