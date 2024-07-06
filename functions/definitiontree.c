#include "..\definitions.h"

// tree node to store the definitions in
// typedef struct definitions_tree
// {
//     char definition[DEFINITION_SIZE];
//     struct definitions_tree *next_def;
// } definitions_node;

// function to create a new definiition node
definitions_node *create_definition_node(char *definition)
{
    // allocate memory for a new node in a definition
    definitions_node *new_definition = (definitions_node *)malloc(sizeof(definitions_node));

    new_definition->definition = strdup(definition);
    new_definition->next_def = NULL;
    new_definition->previous_def = NULL;

    return new_definition;
}

// function to add a new definition to the word
bool add_definition(definitions_node *previous, definitions_node *new)
{
    bool operation;

    // check if previous is null, don't care that new can be NULL
    if (previous != NULL)
    {
        operation = SUCCESS;
        previous->next_def = new;
        new->previous_def = previous;
    }
    else
    {
        perror("\nError adding definition to NULL node!!\n");
        operation = FAILURE;
    }

    return operation;
}

// function to remove a node from the tree
void remove_definition(definitions_node *previous, definitions_node **current_to_remove)
{
    // 4. previous is not null
    if (previous != NULL)
    {
        // set the previous point to what is currently in the current next
        previous->next_def = (*current_to_remove)->next_def;

        // 2. next is not null
        if ((*current_to_remove)->next_def != NULL)
            // set the previous structure in the next structure point to the current previous
            (*current_to_remove)->next_def->previous_def = previous;

        // 1. next is null
        free(*current_to_remove);
    }
    // 3. previous is null
    else
    {
        *current_to_remove = (*current_to_remove)->next_def;

        // 2. next is not null
        if ((*current_to_remove)->next_def != NULL)
            (*current_to_remove)->next_def->previous_def = NULL;
        // 1. next is null
        else
            free(*current_to_remove);
    }
}