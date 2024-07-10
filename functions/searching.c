#include "../definitions.h"

#define STRINGS_EQUAL 0
#define STR_1_GREATER 1
#define STR_1_LESSER -1

// function to search for a word from the dictionary using a binary search
dic_entry *search_entry(full_dictionary dict_struct, int starting_entry, char *word)
{
    while (starting_entry <= dict_struct.number_of_entries)
    {
        int mid = starting_entry + (dict_struct.number_of_entries - starting_entry) / 2;

        // compare the two strings using strcmp function
        int comparison_result = strcmp(dict_struct.entries[mid]->word, word);

        switch (comparison_result)
        {
        case STRINGS_EQUAL:
            return dict_struct.entries[mid];
            break;
        case STR_1_GREATER:
            dict_struct.number_of_entries = mid - 1;
            break;
        case STR_1_LESSER:
            starting_entry = mid + 1;
            break;
        }
    }

    return NULL;
}