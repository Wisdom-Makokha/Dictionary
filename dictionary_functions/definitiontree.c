#include "..\definition\definitions.h"

// structure for a dictionary entry
// typedef struct dictionary
// {
//     char *word;
//     // an array of strings where the definitions will be stored
//     char **definitions;
//     int definition_count;
// } dic_entry;

// function to add a new definition to an entry
void add_definition_to_entry(dic_entry *entry, char *definition)
{
    // remove the quotation marks around the string
    definition[strlen(definition) - 3] = '\0';

    entry->definition_count++;
    entry->definitions = (char **)realloc(entry->definitions, sizeof(char *) * entry->definition_count);
    entry->definitions[entry->definition_count - 1] = strdup(definition + 3);
}