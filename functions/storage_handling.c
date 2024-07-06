#include "..\definitions.h"

// format for storage of dictionary entries
// entry1: word%definition1&definition2...& newline
// entry2: word%definition1&definition2...& newline

// function to read files and add them to an array
dic_entry** read_entries_from_file(char *character, int *entrynumber)
{
    //struct for reading entries from a gile
    new_file read_struct;
    read_struct.filename = strdup(strcat(file_prefix, character));
    read_struct.mode = "r";

    char input_char;
    
    //open file to read
    if(open_file(&read_struct))
        return NULL;

    dic_entry **dictionary;

    // scan the file and get the entries for the dictionary
    do
    {
        int char_index;
        char entry[LINE_ENTRY];
        // create a new entry and allocate memory for it
        dic_entry *new_entry = (dic_entry *) malloc(sizeof(dic_entry));

        //read an entire line from the file
        while((input_char = fgetc(read_struct.fileptr)) != EOF && input_char != '\n')
        {
            entry[char_index] = input_char;
            char_index++;
        }

        char_index++;
        entry[char_index] = '\0';

        //get the word for the entry
        new_entry->word = strdup(strtok(entry, delimiter_word));
        // first have this point to a null
        definitions_node *current_definition = NULL;

        //get any extra definitions that exist
        while (true)
        {
            char *next_definition;
            //get a new definition
            next_definition = strtok(NULL, delimiter_definition);
            
            if(next_definition == NULL)
                break;
            
            definitions_node *new_definition = create_definition_node(new_definition);
            add_definition(current_definition, new_definition);
            current_definition = new_definition;
        }
    } while (input_char != EOF);

    return dictionary;
}

bool write_entries_to_file()
{}

//function to open a file in a specific mode as specified in the structure new_file
bool open_file(new_file *file_to_open)
{
    if((file_to_open->fileptr = fopen(file_to_open->filename, file_to_open->mode) == NULL))
    {
        perror("Unable to open file: \'%s\' in mode \'%s'\'!\n", file_to_open->filename, file_to_open->mode);
        return FAILURE;
    }

    return SUCCESS;
}