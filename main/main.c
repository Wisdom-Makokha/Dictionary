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

    // user_interface(dictionary);
    int hundreds_array[HUNDREDS_ARRAY_SIZE];

    // get the hundred point markers
    if(!get_hundred_point_markers(hundreds_array, HUNDREDS_ARRAY_SIZE))
    {
        fprintf(stderr, "Resetting the markers in positions/hundred_point.txt file\n");
        if(set_hundred_point_markers(source_dictionary.fileptr))
        {
            fprintf(stderr, "Trying to read hundred point file again\n");
            if(!get_hundred_point_markers(hundreds_array, HUNDREDS_ARRAY_SIZE))
                exit(EXIT_FAILURE);
        }
        else
            exit(EXIT_FAILURE);
    }

    
    fclose(source_dictionary.fileptr);
    exit(EXIT_SUCCESS);
}