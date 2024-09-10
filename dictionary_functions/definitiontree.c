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
    // remove the first 3 quotation marks
    definition += 3;

    // get definition length then reduce the length to remove the last 3 quotation marks
    size_t length = strlen(definition) - 3;

    // remove the quotation marks
    // since there's a possibility that those quotation marks are what is affecting the length of the given string
    definition[length] = '\0';

    if ((length) > MAX_DEF_SIZE)
    {
        fprintf(stderr, "Definition truncated in the function: %s\nString length: %lld\n", __func__, length);
        write_logs("TRUNC", DATA_TRUNCATION, "Definition truncated", __func__);
        length = MAX_DEF_SIZE;
        definition[length - 1] = '\0';
    }

    entry->definition_count++;
    entry->definitions = (char **)realloc(entry->definitions, sizeof(char *) * entry->definition_count);
    entry->definitions[entry->definition_count - 1] = strdup(definition);
}