#include "..\definition\definitions.h"

#define STRINGS_EQUAL 0
#define STR_1_GREATER 1
#define STR_1_LESSER -1

// function to search for a word from the dictionary using a binary search
dic_entry *search_entry(char *word, HSTMT *h_statement)
{
    dic_entry *new_entry = create_new_entry();
    int result = OP_SUCCESS;
    unsigned number_of_records = 0;
    SQLCHAR definition[MAX_DEF_SIZE];
    SQLLEN tr_definition_len = 0, tr_word_len = 0;

    char *statement_format = "SELECT definition_TB.definitions FROM definition_TB WHERE word_ID = (SELECT word_TB.word_ID FROM word_TB WHERE word = '%s')";
    size_t length = 0;

    // check that our word does not exceed a certain size
    length = (unsigned)snprintf(NULL, length, statement_format, word);
    if (length >= (strlen(statement_format) + MAX_WORD_SIZE))
    {
        write_logs("LONG_STR", MAX_STR_LENGTH_EXCEEDED_ERROR, "Length of search statement exceeds allowed limit", __func__);
        result = OP_FAILURE;
        goto Exit;
    }

    // allocate memory for the statement
    char *statement_str = create_string_memory(length + 1);
    CHECK_MEMORY_GOTO_EXIT(statement_str, result);

    if ((unsigned)(snprintf(statement_str, length + 1, statement_format, word)) > length + 1)
    {
        write_logs("TRUNC", DATA_TRUNCATION, "sprintf truncated data", __func__);
        result = OP_FAILURE;
        goto Exit;
    }

    // execute the statement
    TRYODBC(
        *h_statement,
        SQL_HANDLE_STMT,
        SQLExecDirect(*h_statement, (SQLCHAR *)statement_str, SQL_NTS),
        result)

    // bind the resulting columns to a 
    SQLBindCol(*h_statement, 1, SQL_C_CHAR, definition, MAX_DEF_SIZE, &tr_definition_len);

    // retrieve records and put the data in memory
    while (SQL_SUCCEEDED(SQLFetch(*h_statement)))
    {
        if (tr_word_len == SQL_NULL_DATA || tr_definition_len == SQL_NULL_DATA)
            break;

        add_entry_data(new_entry, word, (char *)definition);
        number_of_records++;
    }
    // close the cursor
    SQLCloseCursor(*h_statement);

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
        return NULL_ENTRY;
    else
        return new_entry;
}