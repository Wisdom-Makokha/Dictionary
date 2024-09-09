#include "../definition/database_definitions.h"

// function to get the string for a terminal option
int get_option_from_user(char *user_input, char *message)
{
    printf("Previous input: %s\nEnter your %s: ", user_input, message);

    // check the success of the operation
    if (fgets(user_input, MAX_OPTION_VALUE_LEN, stdin) == NULL)
    {
        printf("Unable to read %s from input\n", message);
        return OP_FAILURE;
    }

    int index = 0;
    while (index < MAX_OPTION_VALUE_LEN)
    {
        if (user_input[index] == '\n')
        {
            user_input[index] = '\0';
            break;
        }

        index++;
    }

    return OP_SUCCESS;
}

// function to do the initial setup for the odbc
// it will handle environment handle allocation, environment attribute setting
// connection handle allocation and connection attempt then return a statement handle that will be used to make requests
int initialise_ODBC(HENV *h_environment, HDBC *h_connection, int argc, char **argv)
{
    int initialisation_result = OP_SUCCESS;
    // declare arrays for database, file dsn, savefile, dsn
    char *dsn = create_string_memory(MAX_OPTION_VALUE_LEN);
    CHECK_MEMORY_GOTO_EXIT(dsn, initialisation_result);

    char *database_name = create_string_memory(MAX_OPTION_VALUE_LEN);
    CHECK_MEMORY_GOTO_EXIT(database_name, initialisation_result);

    char *file_dsn = create_string_memory(MAX_OPTION_VALUE_LEN);
    CHECK_MEMORY_GOTO_EXIT(file_dsn, initialisation_result);

    char *save_file = create_string_memory(MAX_OPTION_VALUE_LEN);
    CHECK_MEMORY_GOTO_EXIT(save_file, initialisation_result);

    // driver will only have one value for now
    char *driver_str = create_string_memory(MAX_OPTION_VALUE_LEN);
    CHECK_MEMORY_GOTO_EXIT(driver_str, initialisation_result);
    strcpy(driver_str, "ODBC Driver 17 for SQL Server");

    // create struct to store terminal options
    terminal_options *options_to_set = create_options_struct(&database_name, &dsn, &file_dsn, &save_file);
    CHECK_MEMORY_GOTO_EXIT(options_to_set, initialisation_result);

    // get any terminal arguements and use them to supply values
    if (terminal_processing(argc, argv, options_to_set) == OP_SUCCESS)
        printf("Terminal processing successful\n");
    else
        printf("Error Processing terminal arguements\n");

    // confirm options set through the terminal
    // confirm_options(options_to_set);

    // create a struct to store all details needed for a manual connection
    connection_struct *connection_str = create_connection_struct();
    CHECK_MEMORY_GOTO_EXIT(connection_str, initialisation_result);

    // create structs for the parts of the strings needed to connect to the data source
    connection_part *dsn_part = create_connection_part("DSN", dsn);
    CHECK_MEMORY_GOTO_EXIT(dsn_part, initialisation_result);
    connection_part *db_part = create_connection_part("DATABASE", database_name);
    CHECK_MEMORY_GOTO_EXIT(db_part, initialisation_result);
    connection_part *save_file_part = create_connection_part("SAVEFILE", save_file);
    CHECK_MEMORY_GOTO_EXIT(save_file_part, initialisation_result);
    //set default driver to ODBC Driver 17 for SQL Server
    connection_part *driver_part = create_connection_part("DRIVER", driver_str);
    CHECK_MEMORY_GOTO_EXIT(driver_part, initialisation_result);

    // add the separate parts to the main connection struct
    add_part_to_connection_struct(connection_str, db_part);
    add_part_to_connection_struct(connection_str, dsn_part);
    add_part_to_connection_struct(connection_str, save_file_part);
    add_part_to_connection_struct(connection_str, driver_part);

    // string for making the dsn connection if file dsn fails
    char *dsn_connection_str = new_create_data_source_string(connection_str);
    CHECK_MEMORY_GOTO_EXIT(dsn_connection_str, initialisation_result);

    // string for the filedsn which will be the initial option that will be tried first
    char *file_dsn_part_str = create_connection_part_string("FILEDSN", file_dsn);

    // Allocate environment handle
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, h_environment) == SQL_ERROR)
    {
        fprintf(stderr, "Unable to allocate an environment handle\n");
        exit(EXIT_FAILURE);
    }

    // set environment attribute
    TRYODBC(
        *h_environment,
        SQL_HANDLE_ENV,
        SQLSetEnvAttr(*h_environment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0),
        initialisation_result);

    // allocate connection handle
    TRYODBC(
        *h_connection,
        SQL_HANDLE_DBC,
        SQLAllocHandle(SQL_HANDLE_DBC, *h_environment, h_connection),
        initialisation_result);

    // connect to the dsn
    if (try_connection(h_connection, (SQLCHAR *)dsn_connection_str, (SQLCHAR *)file_dsn_part_str) == OP_FAILURE)
    {
        initialisation_result = OP_FAILURE;
        goto Exit;
    }

Exit:
    if (connection_str != NULL)
        free_connection_struct(connection_str);

    if (file_dsn_part_str != NULL)
        free(file_dsn_part_str);

    if (options_to_set != NULL)
        free(options_to_set);

    return initialisation_result;
}