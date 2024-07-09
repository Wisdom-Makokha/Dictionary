#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define WORD_SIZE 30
#define DEFINITION_SIZE 200
#define SUCCESS true
#define FAILURE false
#define DICTIONARY_SIZE 100
#define FILENAME_LENGTH 20
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