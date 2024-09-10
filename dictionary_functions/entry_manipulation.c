#include "..\definition\definitions.h"

// function to create a new entry
dic_entry *create_new_entry(void)
{
    // allocate memory for a new entry
    dic_entry *new_entry = (dic_entry *)malloc(sizeof(dic_entry));

    // check for successful dynamic memory allocation
    if (new_entry == NULL)
    {
        fprintf(stderr, "Error allocating memory for a new entry in function: %s\n", __func__);
        return NULL;
    }

    // initialise the values for the entry
    new_entry->word = NULL;
    new_entry->definitions = NULL;
    new_entry->definition_count = 0;

    return new_entry;
}

// function to add data to an entry
void add_entry_data(dic_entry *entry, char *word, char *definition)
{
    // check if nothing is in the word
    if (entry->word == NULL && word != NULL)
    {
        // this is an attempt to be more efficient and in control of the memory for the words
        // the length of the word is checked and cutoff if it exceeds our set limit
        size_t word_length = strlen(word);

        if (word_length > MAX_WORD_SIZE)
        {
            fprintf(stderr, "Word truncated in the function: %s\n", __func__);
            write_logs("TRUNC", DATA_TRUNCATION, "Word truncated", __func__);
            word_length = MAX_WORD_SIZE;
            word[word_length - 1] = '\0';
        }

        entry->word = strdup(word);
    }

    // add the definition to the word
    add_definition_to_entry(entry, definition);
}

// function to create a new dectionary memory space
full_dictionary *create_dictionary(void)
{
    full_dictionary *dictionary = (full_dictionary *)malloc(sizeof(full_dictionary));

    // check for successful dynamic memory allocation
    if (dictionary == NULL)
    {
        fprintf(stderr, "Error allocating memory to dictionary in function: %s\n", __func__);
        return NULL;
    }

    dictionary->entries = NULL;
    dictionary->number_of_entries = 0;

    return dictionary;
}

// function to expand the memory for the dictionary and add a new entry to the dictionary
void add_entry_to_dictionary(full_dictionary *dict_struct, dic_entry *entry)
{
    dict_struct->number_of_entries++;
    dict_struct->entries = (dic_entry **)realloc(dict_struct->entries, sizeof(dic_entry *) * dict_struct->number_of_entries);
    dict_struct->entries[dict_struct->number_of_entries - 1] = entry;
}

// function to free the memory for an entry
void free_entry(dic_entry *entry)
{
    for (int i = (int) entry->definition_count - 1; i >= 0; i--)
        free(entry->definitions[i]);

    free(entry);
}

// function to free the memory for the dictionary
void free_dictionary(full_dictionary *dictionary)
{
    // loop through the entries from the last to the first
    for (int i = (int)dictionary->number_of_entries - 1; i >= 0; i--)
        free_entry(dictionary->entries[i]);

    // free the dictionary
    free(dictionary);
}