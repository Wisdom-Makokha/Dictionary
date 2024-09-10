#include "..\definition\definitions.h"

//function for the main user interface, this is the first thing the user will see when they start the application
void user_interface( HSTMT *h_display, HSTMT *h_search)
{
    int response;
    bool stop = false;
    char str_response[8];

    while (!stop)
    {
        printf("What would you like to do? \n");
        printf("(Type an integer corresponding to your option then press <enter>)\n\n");
        printf("  -Display dictionary entries: %d\n", DISPLAY);
        printf("  -Search for an entry: %d\n", SEARCH);
        printf("  -Stop: %d\n", STOP);

        printf("\nEnter response: ");
        fgets(str_response, 8, stdin);
        response = atoi(str_response);

        switch (response)
        {
        case DISPLAY:
            printf("\nDisplaying now...\n");
            display_interface(h_display);
            break;
        case SEARCH:
            printf("\nSearching now...\n");
            search_interface(h_search);
            break;
        case STOP:
            printf("\nStopping...\n");
            stop = true;
            break;
        }

        if(!stop)
            printf("\n\n");
    }
}
