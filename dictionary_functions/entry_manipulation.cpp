#include "..\definition\definitions.h"

// function to create a new entry
dic_entry * create_new_entry(void)
{
    //allocate memory for a new entry
    dic_entry *new_entry = (dic_entry *) malloc(sizeof(dic_entry));
    
    // initialise the values for the entry
    new_entry->word = NULL;
    new_entry->definitions = NULL;
    new_entry->definition_count = 0;

    return new_entry;
}

//function to add data to an entry
void add_entry_data(dic_entry *entry, char *word, char *definition)
{
    // check if nothing is in the word 
    if(entry->word == NULL)
        entry->word = strdup(word);

    // add the definition to the word
    add_definition_to_entry(entry, definition);
}

// function to create a new dectionary memory space
full_dictionary *create_dictionary(void)
{
    full_dictionary *dictionary = (full_dictionary *) malloc(sizeof(full_dictionary));
    dictionary->entries = NULL;
    dictionary->number_of_entries = 0;

    return dictionary;
}

//function to expand the memory for the dictionary and add a new entry to the dictionary
void add_entry_to_dictionary(full_dictionary *dict_struct, dic_entry *entry)
{
    dict_struct->number_of_entries++;
    dict_struct->entries = (dic_entry **) realloc(dict_struct->entries, sizeof(dic_entry *) * dict_struct->number_of_entries);
    dict_struct->entries[dict_struct->number_of_entries - 1] = entry;
}