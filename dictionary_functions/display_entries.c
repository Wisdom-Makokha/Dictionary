#include "..\definition\definitions.h"

// structure for a dictionary entry
// typedef struct dictionary
// {
//     char *word;
//     // an array of strings where the definitions will be stored
//     char **definitions;
//     int definition_count;
// } dic_entry;

// function to display a single entry
void display_entry(dic_entry *entry_display, FILE *fileptr)
{
    // print the word
    fprintf(fileptr, "%s:-\n", entry_display->word);

    // print the definitions for the word
    for(int i = 0; i < entry_display->definition_count; i++)
        fprintf(fileptr, "\t%d. %s\n", i + 1, entry_display->definitions[i]);

    fprintf(fileptr, "\n");
}

// function to display 100 entries
void display_100_entries(full_dictionary dict_struct, int starting_entry, FILE *fileptr)
{
    const int entries_to_print = 100;

    // print a total of 100 entries unless the are 
    for(; starting_entry < entries_to_print && starting_entry < dict_struct.number_of_entries; starting_entry++)
        display_entry(dict_struct.entries[starting_entry], fileptr);
}