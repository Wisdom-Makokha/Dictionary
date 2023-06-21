#include"definitions.h"


int main(void)
{
    struct entry * searchentry(struct entry *ptrdiction, int *ptrcount, char *search);
    
    struct entry dictionary[DICTIONARY_SIZE] = 
    {
        {"aardvark", "a burrowing african mammal"}, 
        {"abyss", "a bottomless pit"},
        {"acumen", "mentally sharp; keen"},
        {"addle", "to become confused"},
        {"aerie", "a high nest"},
        {"affix", "to append; attach"},
        {"agar", "a jelly made from seaweed"},
        {"ahoy", "a nautical call of greeting"},
        {"aigrette", "an ornamental cluster of feathers"},
        {"ajar", "partially operned"}
    };

    int entrycount = 10;
    int *ptrcount = &entrycount;
    struct entry *ptrlookup;
    char wordsearch[WORD_SIZE];

    printf("Enter a word to lookup in the dictionary: ");
    scanf("%30s", wordsearch);

    ptrlookup = searchentry(dictionary, ptrcount, wordsearch);

    if(ptrlookup != NULL)
        printf("%s - - %s\n", ptrlookup->word, ptrlookup->definition);
    else
        printf("Word not found in dictionary!!\n");

    ptrlookup = searchentry(dictionary, ptrcount, "ahoy");

    if(ptrlookup != NULL)
        printf("\n%s - - %s\n", ptrlookup->word, ptrlookup->definition);
    else
        perror("Word not found in dictionary!!\n");

    printf("Enter a word for error checking: ");
    scanf("%30s", wordsearch);

    ptrlookup = searchentry(dictionary, ptrcount, wordsearch);

    if(ptrlookup != NULL)
        printf("%s - - %s\n", ptrlookup->word, ptrlookup->definition);
    else
        perror("Word not found in dictionary!!\n");

    exit(EXIT_SUCCESS);
}

struct entry * searchentry(struct entry *ptrdiction, int *ptrcount, char *search)
{
    int i;

    for(i = 0; i < *ptrcount; i++)
        if((strcmp(search, (ptrdiction + i)->word)) == 0)
            return (ptrdiction + i);

    return NULL;
}