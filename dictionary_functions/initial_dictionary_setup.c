#include "../definition/definitions.h"

// function to do the initial setup for the dictionary app
// it will start with retrieving a hundred words from the database
// and putting them within our dictionary
int retrieve_records(HSTMT *h_statement, full_dictionary *dictionary, unsigned *starting_entry, int number_of_entries)
{
    // printf("Starting record retrieval!\n");
    int result = OP_SUCCESS;
    unsigned number_of_records = 0;
    SQLCHAR word[MAX_WORD_SIZE];
    SQLCHAR definition[MAX_DEF_SIZE];
    SQLLEN tr_definition_len = 0, tr_word_len = 0;

    // statement to retrieve the word
    // format for the word statement
    char *statement_format = "SELECT word_TB.word, definition_TB.definitions FROM word_TB JOIN definition_TB on word_TB.word_ID = definition_TB.word_ID WHERE word_TB.word_ID BETWEEN %d AND %d";
    size_t length = 0;

    length = snprintf(NULL, length, statement_format, *starting_entry, number_of_entries);
    printf("Size of created string: %lld\n", length);

    // allocate memory
    char *statement_str = create_string_memory(length + 1);
    CHECK_MEMORY_GOTO_EXIT(statement_str, result);

    if ((unsigned)(snprintf(statement_str, length + 1, statement_format, *starting_entry, number_of_entries)) > length + 1)
    {
        write_logs("TRUNC", DATA_TRUNCATION, "sprintf truncated data", __func__);
        result = OP_FAILURE;
        goto Exit;
    }

    // printf("Executing statement: %s\n", statement_str);
    TRYODBC(
        *h_statement,
        SQL_HANDLE_STMT,
        SQLExecDirect(*h_statement, (SQLCHAR *)statement_str, (SQLINTEGER)length),
        result)

    // printf("Binding columns to string pointers\n");
    SQLBindCol(*h_statement, 1, SQL_C_CHAR, word, MAX_WORD_SIZE, &tr_word_len);
    SQLBindCol(*h_statement, 2, SQL_C_CHAR, definition, MAX_DEF_SIZE, &tr_definition_len);

    dic_entry *new_entry = create_new_entry();

    while (SQL_SUCCEEDED(SQLFetch(*h_statement)))
    {
        // printf("Number of records: %d\n", number_of_records);

        // skip any null values
        if (tr_word_len == SQL_NULL_DATA || tr_definition_len == SQL_NULL_DATA)
            continue;
        // printf("%s - %s\n", word, definition);

        if (number_of_records > 1)
        {
            // this check assumes that the retrieved records are already alphabetically sorted
            if (strcmp((char *)word, new_entry->word) == 0)
            {
                add_entry_data(new_entry, (char *)word, (char *)definition);
                number_of_records++;
                continue;
            }
        }

        new_entry = create_new_entry();
        add_entry_data(new_entry, (char *)word, (char *)definition);
        add_entry_to_dictionary(dictionary, new_entry);

        number_of_records++;
    }

    // check that we have retrieved some records
    if (number_of_records == 0)
    {
        result = OP_FAILURE;
        goto Exit;
    }

Exit:
    if (statement_str != NULL)
        free(statement_str);

    if (result == OP_FAILURE)
        write_logs("INIT", RECORD_RETRIEVAL_ERROR, "Failed to retrieve records", __func__);

    return result;
}

// we can retrieve a word then follow it up with all the definitions next
// this way it will be easier to control the number of entries retrieved