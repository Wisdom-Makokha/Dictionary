#include "../definition/database_definitions.h"

// function to extract error info from the occurred issues
void get_diagnostics(char *function, SQLHANDLE handle, SQLSMALLINT type)
{
    SQLINTEGER i = 0;
    SQLINTEGER native_code;
    char sql_state[7];
    char error_text[1024];
    SQLSMALLINT length;
    SQLRETURN return_code;

    do
    {
        i++;
        return_code = SQLGetDiagRec(type, handle, i, (SQLCHAR *) sql_state, &native_code, (SQLCHAR *) error_text, sizeof(error_text), &length);

        if (SQL_SUCCEEDED(return_code))
        {
            // fprintf(stderr, "[%5.5s] %ld: %s\n", sql_state, native_code, error_text);
            write_logs(sql_state, native_code, error_text, function);
        }
    } while (return_code == SQL_SUCCESS);
}

// format for logs will be [state], code, message, function
// function to write the logs for the application
int write_logs(char *state, long int code, char *message, const char *function)
{
    new_file log_file;
    log_file.filename = "generated\\logs.txt";
    log_file.mode = "a";

    if (new_open_file(&log_file) != OP_SUCCESS)
        return OP_FAILURE;

    char *log_entry_format = "[%5.5s], %ld, %s, %s\n";

    // print the entry to the file
    fprintf(log_file.fileptr, log_entry_format, state, code, message, function);
    // fprintf(stdout, log_entry_format, state, code, message, function);

    return OP_SUCCESS;
}