#include "..\definition\definitions.h"

// function for the interface for searching
void search_interface(HSTMT *h_statement)
{
    char word[MAX_WORD_SIZE];
    printf(ANSI_COLOR_YELLOW "Enter the word you want to search for: " ANSI_COLOR_RESET);
    fgets(word, MAX_WORD_SIZE, stdin);

    // try to have only a normal string without any spaces, tabs or newline characters
    char *token = strtok(word, " \n\t\v");

    if (strlen(token) < MAX_WORD_SIZE)
    {
        dic_entry *found = search_entry(token, h_statement);

        // if an entry is found then return
        if (found != NULL)
        {
            display_entry(found, stdout);
            free(found);
            return;
        }
        else
            printf("Entry not found!\n");
    }
    else
        printf("Your input value was too large for the expected response\n");
}