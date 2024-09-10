#include "../definition/definitions.h"

// function to retrieve a given number of records from the database
int retrieve_records(HSTMT *h_statement, full_dictionary *dictionary, unsigned *starting_entry, unsigned ending_entry)
{
    // printf("Starting record retrieval!\n");
    int result = OP_SUCCESS;
    unsigned number_of_records = 0;
    SQLCHAR word[MAX_WORD_SIZE];
    SQLCHAR definition[MAX_DEF_SIZE];
    SQLLEN tr_definition_len = 0, tr_word_len = 0, bind_word = 0, bind_def = 0;

    // statement to retrieve the word
    // format for the word statement
    char *statement_str = "SELECT word_TB.word, definition_TB.definitions FROM word_TB INNER JOIN definition_TB on word_TB.word_ID = definition_TB.word_ID WHERE word_TB.word_ID BETWEEN ? AND ?";

    // could probably proceed by just parameterising the directly executed statement
    // and binding them to our variables but I want to use prepare instead just because
    // prepare the statement
    SQLPrepare(*h_statement, (SQLCHAR *)statement_str, SQL_NTS);

    // bind the parameters
    SQLBindParameter(*h_statement, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 10, 0, (SQLPOINTER) starting_entry, 0, &bind_word);
    SQLBindParameter(*h_statement, 2, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 10, 0, (SQLPOINTER) &ending_entry, 0, &bind_def);

    // printf("Executing statement: %s\n", statement_str);
    TRYODBC(
        *h_statement,
        SQL_HANDLE_STMT,
        SQLExecute(*h_statement),
        result)

    // printf("Binding columns to string pointers\n");
    SQLBindCol(*h_statement, 1, SQL_C_CHAR, word, MAX_WORD_SIZE, &tr_word_len);
    SQLBindCol(*h_statement, 2, SQL_C_CHAR, definition, MAX_DEF_SIZE, &tr_definition_len);

    dic_entry *new_entry;

    // fetch the records from the prepared database
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
    // close the cursor after executing a select statement to make the handle reusable for another statement
    SQLCloseCursor(*h_statement);

    // check that we have retrieved some records
    if (number_of_records == 0)
    {
        result = OP_FAILURE;
        goto Exit;
    }

Exit:
    if (result == OP_FAILURE)
        write_logs("INIT", RECORD_RETRIEVAL_ERROR, "Failed to retrieve records", __func__);

    return result;
}

// we can retrieve a word then follow it up with all the definitions next
// this way it will be easier to control the number of entries retrieved