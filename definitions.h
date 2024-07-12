#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sqlapi/SQLAPI.h>

#define SUCCESS true
#define FAILURE false
#define LINE_ENTRY 1024
#define NULL_ENTRY (dic_entry *) 0

// format for storage of dictionary entries
// entry1: word%definition1&definition2...& newline
// entry2: word%definition1&definition2...& newline

//enum for functions on the home page for the user interface
enum available_functions
{
    DISPLAY = 1,
    SEARCH,
    STOP
};

// structure for a dictionary entry
typedef struct dictionary_entry
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

// structure for the dictionary to make it easier to work with
typedef struct dictionary
{
    dic_entry **entries;
    int number_of_entries;
} full_dictionary;

void user_interface(full_dictionary *dictionary);
bool open_file(new_file *file_to_open);
void add_definition_to_entry(dic_entry *entry, char *definition);
dic_entry * create_new_entry(void);
void add_entry_data(dic_entry *entry, char *word, char *definition);
full_dictionary *create_dictionary(void);
void add_entry_to_dictionary(full_dictionary *dict_struct, dic_entry *entry);
dic_entry *search_entry(full_dictionary dict_struct, int starting_entry, char *word);
void display_entry(dic_entry *entry_display, FILE *fileptr);
void display_100_entries(full_dictionary dict_struct, int starting_entry, FILE *fileptr);
void read_line(char *line, FILE *fileptr);