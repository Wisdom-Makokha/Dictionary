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
    SQLLEN tr_definition_len = 0, tr_word_len = 0, bind_word = 0;

    // shifted to using a parameterised statement that is shown by the ? in the statement
    // when preparing the statement, the data source will expect a bound parameter be tied to it
    char *statement_str = "SELECT definition_TB.definitions FROM definition_TB WHERE word_ID = (SELECT word_TB.word_ID FROM word_TB WHERE word = ?)";

    // prepare the statement
    SQLPrepare(*h_statement, (SQLCHAR *)statement_str, SQL_NTS);

    // bind the parameters
    SQLBindParameter(*h_statement, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_WORD_SIZE, 0, (SQLPOINTER)word, 0, &bind_word);

    // execute the statement
    TRYODBC(
        *h_statement,
        SQL_HANDLE_STMT,
        SQLExecute(*h_statement),
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
        return NULL_ENTRY;
    else
        return new_entry;
}