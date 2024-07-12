#include "..\definitions.h"

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

// function to read a line from a file
void read_line(char *line, FILE *fileptr)
{
    static int longest_line = 0;
    int index = 0;
    char character;

    while ((character = fgetc(fileptr)) != '\n' && character != EOF)
    {
        // skip any quotation characters
        // if (character != '\"')

        line[index] = character;
        index++;
    }

    if (index > longest_line)
    {
        longest_line = index;
        printf("Longest line: %d\n", longest_line);
    }
}