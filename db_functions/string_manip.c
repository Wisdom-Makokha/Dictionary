#include "../definition/database_definitions.h"

// function to create memory for a character string
char *create_string_memory(int size)
{
    // allocate new memory
    char *new_char_pointer = (char *)malloc(sizeof(char) * size);

    if (new_char_pointer == NULL)
    {
        // fprintf(stderr, "Error allocating memory to new character pointer in: %s\n", __func__);
        write_logs("MEMALLOC", MEM_ALLOC_ERROR, "Error allocating memory to new character pointer", __func__);
    }
    else
        // next time be careful about how giving data to dynamically allocated memory
        // initially this was how I did it new_char_pointer = "<no value set>"
        // this would reset the pointer from my allocated memory to instead point to this const char string
        strcpy(new_char_pointer, DEFAULT_OPTION_VALUE);

    return new_char_pointer;
}

// we need to combine the info we got into a string that can be used either for the filedsn and the test_DSN
// the file_dsn will be the initial point of attempted connection, then
// in case of issues, the dsn and database options will be used to make a connection
// the save file will store connection information to attempt a connection the next time

// a function to create the string for part of the string needed for a connection
// format is variable=value;
char *create_connection_part_string(char const *variable, char const *value)
{
    if (strcmp(value, DEFAULT_OPTION_VALUE) == 0)
    {
        write_logs("STRING", DEFAULT_VALUE_USED, "Default value used", __func__);
        return NULL;
    }
    // a file_dsn is enough to make a complete connection to a data source
    // there is no need to save a file_dsn since it is already complete and saving to it is just redundant and might cause issues
    const char *string_part_format = "%s=%s;";
    size_t length = 0;

    // get the length of the string to be generated
    length = snprintf(
        NULL,
        length,
        string_part_format,
        variable,
        value);

    // create the pointer to our string
    if (length > MAX_FILE_DSN_LEN - 1)
    {
        // fprintf(stderr, "String value too large in: %s\n", __func__);
        write_logs("STRING", MEM_ALLOC_ERROR, "String value too large", __func__);
        return NULL;
    }

    // allocate memory for our new string
    char *connection_part_str = (char *)malloc(sizeof(char) * length + 1);

    CHECK_MEMORY_N_RETURN_NULL(connection_part_str, __func__)

    // put the content in our allocated memory space
    if ((unsigned)(snprintf(
            connection_part_str,
            length + 1,
            string_part_format,
            variable,
            value)) > length + 1)
    {
        // fprintf(stderr, "sprintf truncated data in: %s\n", __func__);
        write_logs("TRUNC", DATA_TRUNCATION, "sprintf truncated data", __func__);
        return NULL;
    }

    // remember to free this memory
    return connection_part_str;
}

// function to create the string for a manual data source connection that might require further user action
char *new_create_data_source_string(connection_struct *connection_str)
{
    // an ideal version would be to only declare the pointer without any allocated memory then
    // realloc memory as needed rather than setting aside a pound of memory that might even end up insufficient
    char *data_source_str = (char *)malloc(sizeof(char) * MAX_DSN_CONNECTION_LEN);
    CHECK_MEMORY_N_RETURN_NULL(data_source_str, __func__)

    // set the first character to null character for strncat function
    data_source_str[0] = '\0';

    int empty_space = MAX_DSN_CONNECTION_LEN;
    for (unsigned index = 0; index < connection_str->number_of_parts; index++)
    {
        char *new_part = create_connection_part_string(connection_str->parts[index]->variable, connection_str->parts[index]->value);

        if (new_part != NULL)
        {
            strncat(data_source_str, new_part, empty_space);
            empty_space -= strlen(new_part);

            free(new_part);
        }
    }

    // printf("%s\n", data_source_str);
    if (data_source_str[0] == '\0')
        strcpy(data_source_str, DEFAULT_OPTION_VALUE);

    return data_source_str;
}

// function to create memory for the connection struct
connection_struct *create_connection_struct(void)
{
    connection_struct *new_conn_str = (connection_struct *)malloc(sizeof(connection_struct));

    CHECK_MEMORY_N_RETURN_NULL(new_conn_str, __func__);
    new_conn_str->number_of_parts = 0;
    new_conn_str->parts = NULL;

    return new_conn_str;
}

// function add part to connection struct
void add_part_to_connection_struct(connection_struct *connection, connection_part *part)
{
    connection->number_of_parts++;
    connection->parts = (connection_part **)realloc(connection->parts, sizeof(connection_part *) * connection->number_of_parts);
    connection->parts[connection->number_of_parts - 1] = part;
}

// function to create memory for a new part
connection_part *create_connection_part(char *variable, char *value)
{
    connection_part *part = (connection_part *)malloc(sizeof(connection_part));

    CHECK_MEMORY_N_RETURN_NULL(part, __func__);
    part->variable = variable;
    part->value = value;

    return part;
}

// funtion free connection part
void free_connection_part(connection_part *part)
{
    // free the memory for the value first
    // remember to skip this
    // free(part->value);
    free(part);
}

// function to free the memory for the connection struct
void free_connection_struct(connection_struct *connection)
{
    // loop through the parts and free those first then free the entire struct
    for (int i = connection->number_of_parts - 1; i >= 0; i--)
        free_connection_part(connection->parts[i]);

    free(connection);
}