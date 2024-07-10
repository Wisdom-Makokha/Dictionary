#include "../definitions.h"

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