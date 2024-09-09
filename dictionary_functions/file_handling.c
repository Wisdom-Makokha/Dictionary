#include "..\definition\definitions.h"

// function to open a file in a specific mode as specified in the structure new_file
bool open_file(new_file *file_to_open)
{
    // check if opening the file was successful
    if ((file_to_open->fileptr = fopen(file_to_open->filename, file_to_open->mode)) == NULL)
    {
        fprintf(stderr, "Unable to open file: \'%s\' in mode \'%s'\'!\n", file_to_open->filename, file_to_open->mode);
        return FAILURE;
    }

    return SUCCESS;
}