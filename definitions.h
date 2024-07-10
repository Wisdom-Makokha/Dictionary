#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SUCCESS true
#define FAILURE false
#define LINE_ENTRY 1024

// format for storage of dictionary entries
// entry1: word%definition1&definition2...& newline
// entry2: word%definition1&definition2...& newline

//enum for functions on the home page for the user interface
enum available_functions
{
    DISPLAY = 1,
    SEARCH,
    ADD,
    REMOVE,
    STOP
};

// structure for a dictionary entry
typedef struct dictionary
{
    char *word;
    // an array of strings where the definitions will be stored
    char **definitions;
    int definition_count;
} dic_entry;

// structure for file details
typedef struct file_struct
{
    char *filename;
    FILE *fileptr;
    char *mode;
} new_file;

void user_interface(void);
bool open_file(new_file *file_to_open);
void add_definition_to_entry(dic_entry *entry, char *definition);
dic_entry * create_new_entry(void);
void add_entry_data(dic_entry *entry, char *word, char *definition);
dic_entry *search_entry(dic_entry **dictionary, char *word, int number_of_entries, int starting_entry);
void display_entry(dic_entry *entry_display, FILE *fileptr);
void display_100_entries(dic_entry **dictionary, int number_of_entries, int starting_entry, FILE *fileptr);