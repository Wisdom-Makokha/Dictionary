#include "..\definitions.h"

//function for the main user interface, this is the first thing the user will see when they start the application
void user_interface(full_dictionary *dictionary)
{
    int response;
    bool stop = false;

    while (!stop)
    {
        printf("What would you like to do? \n");
        printf("\n(Type an integer corresponding to your option then press <enter>)\n\n");
        printf("  -Display dictionary entries: %d\n", DISPLAY);
        printf("  -Search for an entry: %d\n", SEARCH);
        printf("  -Stop: %d\n", STOP);

        printf("Enter response: ");
        scanf("%d", &response);

        switch (response)
        {
        case DISPLAY:
            printf("\nDisplaying now...\n");
            break;
        case SEARCH:
            printf("\nSearching now...\n");
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
