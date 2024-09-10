#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILE_PATH_LENGTH 1024
#define MAX_TERMINAL_ARGS 9
#define MAX_OPTION_VALUE_LEN 128
#define MAX_FILE_DSN_LEN 144
#define MAX_DSN_CONNECTION_LEN 512
#define DEFAULT_OPTION_VALUE "<No value set>"
#define TRYODBC(handle, handle_type, odbc_function, result)             \
    {                                                                   \
        RETCODE rt_code = (odbc_function);                              \
        if (rt_code != SQL_SUCCESS)                                     \
        {                                                               \
            get_diagnostics((#odbc_function), (handle), (handle_type)); \
            result = OP_FAILURE;                                        \
        }                                                               \
        if (rt_code == SQL_ERROR || rt_code == SQL_NO_DATA)             \
        {                                                               \
            fprintf(stderr, "Error in: " #odbc_function "\n");          \
            result = OP_FAILURE;                                        \
            goto Exit;                                                  \
        }                                                               \
    }
#define CHECK_MEMORY_GOTO_EXIT(ptr, result)                           \
    if (ptr == NULL)                                                  \
    {                                                                 \
        result = OP_FAILURE;                                          \
        fprintf(stderr, "Error in memory allocation for %s\n", #ptr); \
        goto Exit;                                                    \
    }
#define CHECK_MEMORY_N_RETURN_NULL(ptr, function)                                                    \
    if (ptr == NULL)                                                                                 \
    {                                                                                                \
        fprintf(stderr, "Error allocating memory to new pointer in: %s\n", function);                \
        write_logs("MEMALLOC", MEM_ALLOC_ERROR, "Error allocating memory to new pointer", function); \
        return NULL;                                                                                 \
    }

// let's go with an enum that can be shifted around
typedef enum
{
    OP_FAILURE,
    OP_SUCCESS,
    FILENAME_ERROR,
    FILE_MODE_ERROR,
    FILE_PATH_ERROR,
    MEM_ALLOC_ERROR,
    USER_INPUT_ERROR,
    DATA_TRUNCATION,
    DEFAULT_VALUE_USED,
    RECORD_RETRIEVAL_ERROR,
    MAX_STR_LENGTH_EXCEEDED_ERROR,
    UNKNOWN
} error_codes;

// enum for terminal options
typedef enum
{
    TO_DATABASE_NAME = 100,
    TO_DSN,
    TO_SAVE_FILE,
    TO_FILE_DSN,
    TO_NONE
} terminal_options_en;

// structure for a new file
typedef struct file_structure
{
    FILE *fileptr;
    char *filename;
    char *mode;
} new_file;

// union for the possible values for an option
// typedef union
// {
//     char **database_name;
//     char **file_dsn_path;
//     char **dsn_name;
//     char **save_file_path;
// } option_values;

// values we want to capture include savefile, filedsn, dsn, database,
// a structure for a single value on the terminal
typedef struct
{
    bool option_is_set;
    char **string_value;
    // option_values value;
} option;

// terminal options
typedef struct
{
    option database_name;
    option dsn;
    option fileDSN;
    option savefileDSN;
} terminal_options;

// a structure to show the two pieces of part of a connection string
typedef struct
{
    char *variable;
    char *value;
} connection_part;

// a structure to combine all the connection parts in one location
typedef struct
{
    connection_part **parts;
    unsigned number_of_parts;
} connection_struct;

// odbc functions
void get_diagnostics(char *function, SQLHANDLE handle, SQLSMALLINT type);
int try_connection(HDBC *h_connection, SQLCHAR *dsn_str, SQLCHAR *file_dsn_str);

// file handling
int new_open_file(new_file *file_to_open);
int write_logs(char *state, long int code, char *message, const char *function);

// string manipulation
// char *combine_strings(char *string1, char *string2, unsigned return_string_limit);
char *create_connection_part_string(char const *variable, char const *value);
char *new_create_data_source_string(connection_struct *connection_str);
connection_struct *create_connection_struct(void);
void add_part_to_connection_struct(connection_struct *connection, connection_part *part);
connection_part *create_connection_part(char *variable, char *value);
void free_connection_part(connection_part *part);
void free_connection_struct(connection_struct *connection);
char *create_string_memory(size_t size);

// intial setup
int get_option_from_user(char *user_input, char *message);
int initialise_ODBC(HENV *h_environment, HDBC *h_connection, int argc, char **argv);

// terminal processing
terminal_options *create_options_struct(char **database_name, char **dsn, char **fileDSN, char **save_file_DSN);
int terminal_processing(int argc, char **argv, terminal_options *options_to_set);
void confirm_options(terminal_options *set_options);