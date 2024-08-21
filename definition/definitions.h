#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #ifndef HEADER_GUARDS
// #define HEADER_GUARDS

// #endif

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

//structure for the letter positions in the file
typedef struct let_pos
{
    char letter;
    long int beginnning_position;
    long int ending_position;
    int number_of_letter_entries;
} letter_position;

// structure for the alphabet of the letters
typedef struct letter_mark
{
    letter_position **markers;
    int number_of_letters;
} alphabet;

void user_interface(full_dictionary *dictionary);
bool open_file(new_file *file_to_open);
void add_definition_to_entry(dic_entry *entry, char *definition);
dic_entry * create_new_entry(void);
void free_entry(dic_entry *entry);
void add_entry_data(dic_entry *entry, char *word, char *definition);
full_dictionary *create_dictionary(void);
void free_dictionary(full_dictionary *dictionary);
void add_entry_to_dictionary(full_dictionary *dict_struct, dic_entry *entry);
dic_entry *search_entry(full_dictionary dict_struct, int starting_entry, char *word);
void display_entry(dic_entry *entry_display, FILE *fileptr);
void display_100_entries(full_dictionary dict_struct, int starting_entry, FILE *fileptr);
void read_line(char *line, FILE *fileptr);
bool set_hundred_point_markers(FILE *dictionaary_source_file);
bool get_hundred_point_markers(int *hundred_positions, int number_of_points_to_read);
bool set_letter_markers(FILE *dictionary_source_file);
bool check_char_in_range(char character, char *range, int limit);
