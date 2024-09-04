#include "../definition/database_definitions.h"

// SQLCHAR *dsn_str = "DATABASE=Dictionary;SAVEFILE=dictionary_connection.dsn";
// SQLCHAR *file_dsn_str = "FILEDSN=dictionary_connection.dsn;SAVEFILE=dictionary_connection.dsn";

// function to make the connection to the data sources
int try_connection(HDBC *h_connection, SQLCHAR *dsn_str, SQLCHAR *file_dsn_str)
{
    int status;
    const SQLSMALLINT out_str_size = 1024;
    SQLCHAR out_connection_str[out_str_size];
    SQLSMALLINT out_str_actual_len;
    SQLRETURN ret_code;

    ret_code = SQLDriverConnect(
        *h_connection,
        NULL,
        file_dsn_str,
        SQL_NTS,
        out_connection_str,
        out_str_size,
        &out_str_actual_len,
        SQL_DRIVER_NOPROMPT);

    if (ret_code != SQL_SUCCESS)
        get_diagnostics("SQLDriverConnect", *h_connection, SQL_HANDLE_DBC);

    if (ret_code == SQL_ERROR)
    {
        TRYODBC(
            *h_connection,
            SQL_HANDLE_DBC,
            SQLDriverConnect(
                *h_connection,
                GetDesktopWindow(),
                dsn_str,
                SQL_NTS,
                out_connection_str,
                out_str_size,
                &out_str_actual_len,
                SQL_DRIVER_COMPLETE),
            status);
    }

Exit:
    ret_code = SQLGetInfo(*h_connection, SQL_DBMS_VER, NULL, 0, NULL);

    // check connection status
    if (SQL_SUCCEEDED(ret_code))
    {
        status = OP_SUCCESS;
        printf("Connection test successful\n");
    }
    else
    {
        status = OP_FAILURE;
        printf("Connection test unsuccessful\n");
    }

    return status;
}