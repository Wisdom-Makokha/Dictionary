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

// tree node to store the definitions in
typedef struct definitions_tree
{
    char *definition;
    struct definitions_tree *previous_def;
    struct definitions_tree *next_def;
} definitions_node;

// structure for a dictionary entry
typedef struct dictionary
{
    char *word;
    definitions_node *definition;
} dic_entry;

// structure for file details
typedef struct file_struct
{
    char *filename;
    FILE *fileptr;
    char *mode;
} new_file;

//prefix for all files
const char file_prefix[] = "word_storage\\";
// delimiters for the strtok
const char *delimiter_word = "%%";
const char *delimiter_definition = "&";

void user_interface(void);
definitions_node *create_definition_node(char *definition);
bool add_definition(definitions_node *previous, definitions_node *new);
// 4 scenarios for removing
//  1. next is null
//  2. next is not null
//  3. previous is null
//  4. previous is not null
void remove_definition(definitions_node *previous, definitions_node **current_to_remove);
dic_entry** read_entries_from_file(char *character, int *entry_number);
bool open_file(new_file *file_to_open);