#include "definitions.h"

int main(void)
{
    int entries = 0;
    read_entries_from_file("v", &entries);
    user_interface();

    exit(EXIT_SUCCESS);
}