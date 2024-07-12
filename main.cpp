#include "definitions.h"

int main(void)
{
    full_dictionary *dictionary = create_dictionary();

    SAConnection new_connection;
    char *Database_name = "Dictionary";
    char *DB_Username = "";
    char *DB_Password = "";

    try
    {
        new_connection.Connect(Database_name, DB_Username, DB_Password, SA_SQLServer_Client);
        printf("We are connected\n");

        new_connection.Disconnect();
        printf("We are disconnected!\n");
    }
    catch(SAException &x)
    {
        new_connection.Rollback();
        printf("%s\n", x.ErrText().GetMultiByteChars());
    }

    // display_100_entries(*dictionary, 0, stdout);

    user_interface(dictionary);

    exit(EXIT_SUCCESS);
}