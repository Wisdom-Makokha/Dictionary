#include "../definition/database_definitions.h"

// function to open a file given a structure containing the file details
int new_open_file(new_file *file_to_open)
{
    const unsigned mode_limit = 2;

    // check if the file name is valid
    if (file_to_open->filename == NULL)
    {
        // fprintf(stderr, "Invalid filename provided: Filename is blank\n");
        write_logs("FILE", FILENAME_ERROR, "Invalid filename provided: Filename cannot be a null value", __func__);
        // handle_Errors(FILENAME_ERROR, __func__, "Invalid filename provided: Filename is blank");
        return FILENAME_ERROR;
    }

    // truncate the mode to the right size if it exceeds the expected size
    unsigned mode_size = strlen(file_to_open->mode);
    if (mode_size > mode_limit)
        file_to_open->mode[mode_limit] = '\0';

    // check if the mode is valid
    switch (file_to_open->mode[0])
    {
    case 'w':
        break;
    case 'r':
        break;
    case 'a':
        break;
    default:
        fprintf(stderr, "Unrecognised mode requested: %s\n", file_to_open->mode);
        write_logs("FILE", FILE_MODE_ERROR, "Unrecognised mode requested", __func__);
        return FILE_MODE_ERROR;
    }

    // check if the filepath is valid and the file can be open in the required mode
    if ((file_to_open->fileptr = fopen(file_to_open->filename, file_to_open->mode)) == NULL)
    {
        // fprintf(stderr, "Error opening file: %s\n", file_to_open->filename);
        write_logs("FILE", FILE_PATH_ERROR, "Error opening file", __func__);
        // handle_Errors(FILE_PATH_ERROR, __func__, "Error opening file");
        return FILE_PATH_ERROR;
    }

    return OP_SUCCESS;
}