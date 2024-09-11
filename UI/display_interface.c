#include "../definition/definitions.h"

// function to display entries, it displays 10 entries at a tim
void display_interface(HSTMT *h_statement)
{
    unsigned int starting_entry = 1;
    const unsigned no_of_entries_to_display = 10;
    enum display_options
    {
        NEXT = 1,
        PREVIOUS,
        STOP_DISP
    };

    bool stop = false;
    do
    {
        full_dictionary *dictionary = create_dictionary();
        if (dictionary == NULL)
        {
            fprintf(stderr, "Error allocating memory to new pointer in: %s\n", __func__);
            write_logs("MEMALLOC", MEM_ALLOC_ERROR, "Error allocating memory to new pointer", __func__);
            break;
        }

        // retrieve records and display them
        retrieve_records(h_statement, dictionary, &starting_entry, starting_entry + no_of_entries_to_display);
        display_no_of_entries(dictionary, 0, stdout, no_of_entries_to_display);

        // query the user for their option
        printf("\n\nView the next %d options or the previous %d options\n", no_of_entries_to_display, no_of_entries_to_display);
        printf("(Enter a number corresponding to your response)\n");
        printf("Next: %d  ", NEXT);
        printf("Previous: %d  ", PREVIOUS);
        printf("Stop: %d\n", STOP_DISP);
        printf(ANSI_COLOR_YELLOW "\nEnter response: " ANSI_COLOR_RESET);

        char response[6];
        fgets(response, 6, stdin);

        int int_response = atoi(response);
        switch (int_response)
        {
        // view the next ten options
        case NEXT:
            starting_entry += no_of_entries_to_display;
            break;
        // view the previous ten options
        case PREVIOUS:
            if (starting_entry > (unsigned)no_of_entries_to_display)
                starting_entry -= no_of_entries_to_display;
            else
                starting_entry = 1;
            break;
        // stop displaying entries
        case STOP_DISP:
            stop = true;
            break;
        default:
            printf("Unkown user response\n");
            break;
        }

        free_dictionary(dictionary);
    } while (!stop);
}