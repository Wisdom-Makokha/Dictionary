#include"definitions.h"

struct entry *searchentry(struct entry *ptrdiction, int *ptrcount, char *search);


int main(void)
{
    struct entry dictionary[DICTIONARY_SIZE];
    int entrycount = 0;
    int *ptrcount = &entrycount;
    char response[500] = {'z'};
    int addresult;

    bool addentry(struct entry *ptrdiction, int *ptrcount);
    
    addresult = addentry(dictionary, ptrcount);

    if(addresult == true)
        printf("%s - - %s\n", dictionary->word, dictionary->definition);
    else
        printf("\nEntry not added! Word is already in the dictionary!!\n");

    while(1)
    {
        printf("Do you have more entries to enter(y/n): ");
        gets(response);

        if(response[0] == 'y')
        {
            addresult = addentry(dictionary, ptrcount);
            
            if(addresult == false)
                printf("\nEntry not added! Word is already in the dictionary!!\n");
        }
        else if(response[0] == 'n')
            break;
        else
            printf("\nUnrecognized response!!\nPress y for yes and n for no then press ENTER to the query\n");
    }

    printf("%i\n\n", *ptrcount);

    for(int i = 0; i < *ptrcount; i++)
        printf("%s - - %s\n", (dictionary + i)->word, (dictionary + i)->definition);

    exit(EXIT_SUCCESS);
}

bool addentry(struct entry *ptrdiction, int *ptrcount)
{
    bool entryadded = false; 

    char word[WORD_SIZE];
    char definition[DEFINITION_SIZE];
    struct entry *ptrchecknew;

    printf("Enter the word and definition for your new entry: ");
    fscanf(stdin, "%30s", word);
    fgets(definition, DEFINITION_SIZE, stdin);

    ptrchecknew = searchentry(ptrdiction, ptrcount, word);

    ptrdiction += *ptrcount;

    if(ptrchecknew == NULL)
    {
        strcpy(ptrdiction->word, word);
        strcpy(ptrdiction->definition, definition);

        (*ptrcount)++;

        entryadded = true;
    }
    

    return entryadded;
}

struct entry * searchentry(struct entry *ptrdiction, int *ptrcount, char *search)
{
    int i;

    for(i = 0; i < *ptrcount; i++, ptrdiction++)
    {
        if(strcmp(search, ptrdiction->word) == 0)
            return ptrdiction;
    }

    return NULL;
}