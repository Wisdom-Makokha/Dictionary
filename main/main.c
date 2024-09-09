#include "..\definition\definitions.h"
#define HUNDREDS_ARRAY_SIZE 2000

int main(void)
{
    // declare ODBC variables
    HENV h_environment = NULL;
    HDBC h_connection = NULL;
    HSTMT h_statement = NULL;
    int result;

    full_dictionary *new_dict = create_dictionary();
    CHECK_MEMORY_GOTO_EXIT(new_dict, result);

    // these options could be set through the terminal but for now they are set through this instead
    // the options are meant to be permanent
    char *specifications[] = {"program_name",
                              "-f", "dictionary_connnection",
                              "-db", "Dictionary",
                              "-dsn", "Test_DSN",
                              "-s", "dictionary_connection"};

    int number_of_args = _countof(specifications);

    if (initialise_ODBC(&h_environment, &h_connection, number_of_args, specifications) == OP_FAILURE)
    {
        fprintf(stderr, "Error initialising ODBC\n");
        goto Exit;
    }

    TRYODBC(
        h_statement,
        SQL_HANDLE_STMT,
        SQLAllocHandle(SQL_HANDLE_STMT, h_connection, &h_statement),
        result)

    unsigned entries = 1;

    result = retrieve_records(&h_statement, new_dict, &entries, 100);
    if (result == OP_FAILURE)
    {
        fprintf(stderr, "Error retrieving records!\n");
        goto Exit;
    }
    display_no_of_entries(new_dict, 0, stdout, 20);

Exit:
    if (new_dict != NULL)
        free_dictionary(new_dict);

    // free statement handles
    if (h_statement)
        SQLFreeHandle(SQL_HANDLE_STMT, h_statement);

    // disconnect and free connection handle
    if (h_connection)
    {
        SQLRETURN ret_code = SQLGetInfo(h_connection, SQL_DBMS_VER, NULL, 0, NULL);

        SQLDisconnect(h_connection);
        SQLFreeHandle(SQL_HANDLE_DBC, h_connection);

        // only print this if the connection was successfully made
        if (SQL_SUCCEEDED(ret_code))
            printf("Disconnected!\n");
    }

    // free environment handle
    if (h_environment)
        SQLFreeHandle(SQL_HANDLE_ENV, h_environment);

    exit(EXIT_SUCCESS);
}
