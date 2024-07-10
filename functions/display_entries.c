#include "..\definitions.h"

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
        fprintf(fileptr, "\t%d. %s\n", i, entry_display->definitions[i]);
}

// function to display 100 entries
void display_100_entries(dic_entry **dictionary, int number_of_entries, int starting_entry, FILE *fileptr)
{
    const int entries_to_print = 100;

    // print a total of 100 entries unless the are 
    for(; starting_entry < entries_to_print && starting_entry < number_of_entries; starting_entry++)
        display_entry(dictionary[starting_entry], fileptr);
}