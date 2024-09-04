#include "..\definition\definitions.h"
#define HUNDREDS_ARRAY_SIZE 2000

int main(void)
{
    // full_dictionary *dictionary = create_dictionary();

    // file to read the dictionary entries from
    new_file source_dictionary;
    source_dictionary.filename = "data_source/OPTED-Dictionary.csv";
    source_dictionary.mode = "r";

    if (!open_file(&source_dictionary))
        exit(EXIT_FAILURE);


    fclose(source_dictionary.fileptr);
    exit(EXIT_SUCCESS);
}

