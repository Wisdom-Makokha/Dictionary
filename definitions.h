#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define WORD_SIZE 30
#define DEFINITION_SIZE 200
#define SUCCESS true
#define FAILURE false
#define DICTIONARY_SIZE 100

// tree node to store the definitions in
typedef struct definitions_tree
{
    char definition[DEFINITION_SIZE];
    struct definitions_tree *next_def;
} definitions_node;

// structure for a dictionary entry
typedef struct dictionary
{
    char word[WORD_SIZE];
    definitions_node *definition;
} dic_entry;
