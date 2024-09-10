#include "../definition/database_definitions.h"
#include <string.h>

#define SUCCESS true
#define FAILURE false
#define LINE_ENTRY 1024
#define NULL_ENTRY (dic_entry *)0
#define MAX_WORD_SIZE 128
#define MAX_DEF_SIZE 1024

// format for storage of dictionary entries
// entry1: word%definition1&definition2...& newline
// entry2: word%definition1&definition2...& newline

// enum for functions on the home page for the user interface
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

// structure for the dictionary to make it easier to work with
typedef struct dictionary
{
    dic_entry **entries;
    int number_of_entries;
} full_dictionary;

// UI
void user_interface(HSTMT *h_display, HSTMT *h_search);
void search_interface(HSTMT *h_statement);
void display_interface(HSTMT *h_statement);

// file handling
bool open_file(new_file *file_to_open);

// definition_tree
void add_definition_to_entry(dic_entry *entry, char *definition);

// entry manipulation
dic_entry *create_new_entry(void);
void free_entry(dic_entry *entry);
void add_entry_data(dic_entry *entry, char *word, char *definition);
full_dictionary *create_dictionary(void);
void free_dictionary(full_dictionary *dictionary);
void add_entry_to_dictionary(full_dictionary *dict_struct, dic_entry *entry);

// searching
dic_entry *search_entry(char *word, HSTMT *h_statement);

// display
void display_entry(dic_entry *entry_display, FILE *fileptr);
void display_no_of_entries(full_dictionary *dict_struct, int starting_entry, FILE *fileptr, int number_of_entries);

// multi record retrieval
int retrieve_records(HSTMT *h_statement, full_dictionary *dictionary, unsigned *starting_entry, int number_of_entries);