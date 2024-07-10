#include "..\definitions.h"

// prefix for all files
const char file_prefix[] = "word_storage\\";
// delimiters for the strtok
const char *delimiter_word = "%%";
const char *delimiter_definition = "&";

// format for storage of dictionary entries
// entry1: word%definition1&definition2...& newline
// entry2: word%definition1&definition2...& newline

// function to write to my own storage system to


// function to read a csv file for the entries
bool read_dictionary_to_mem(full_dictionary *dict_struct)
{
    //initialise the struct for the file
    new_file dictionary_csv;
    dictionary_csv.filename = "source/OPTED-Dictionary.csv";
    dictionary_csv.mode = "r";

    if(!open_file(&dictionary_csv))
        return FAILURE;

    fclose(dictionary_csv.fileptr);
    return SUCCESS;
}

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