#include"definitions.h"

struct entry *searchentry(struct entry *ptrdction, int *ptrcount, char *search);
bool removeentry(struct entry *ptrdiction, struct entry *ptrdelete, int *ptrcount);

int main(void)
{
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
    int i;
    struct entry *ptrdiction = dictionary;

    for(i = 0; i < *ptrcount; i++, ptrdiction++)
        printf("%-*s - - %s\n", WORD_SIZE, ptrdiction->word, ptrdiction->definition);

    ptrdiction = dictionary;
    printf("%i\n\n", *ptrcount);

    removeentry(dictionary, dictionary + 6, ptrcount);

    for(i = 0; i < *ptrcount; i++, ptrdiction++)
        printf("%-*s - - %s\n", WORD_SIZE, ptrdiction->word, ptrdiction->definition);

    ptrdiction = dictionary;
    printf("%i\n\n", *ptrcount);

    removeentry(dictionary, 0, ptrcount);

    for(i = 0; i < *ptrcount; i++, ptrdiction++)
        printf("%-*s - - %s\n", WORD_SIZE, ptrdiction->word, ptrdiction->definition);

    ptrdiction = dictionary;
    printf("%i\n\n", *ptrcount);

    exit(EXIT_SUCCESS);
}

bool removeentry(struct entry *ptrdiction, struct entry *ptrdelete, int *ptrcount)
{
    struct entry temp;
    bool entrydeleted = true;
    
    if(ptrdelete == NULL || (ptrdelete < ptrdiction || ptrdelete > (ptrdiction + *ptrcount)))
    {
        char worddelete[WORD_SIZE];
        
        printf("Enter a word to delete its entry in the dictionary: ");
        scanf("%s30", worddelete);

        ptrdelete = searchentry(ptrdiction, ptrcount, worddelete);

        if(ptrdelete == NULL)
        {
            entrydeleted = false;
            return entrydeleted;
        }
    }

    ptrdiction += *ptrcount;
    ptrdiction--;

    temp = *ptrdiction;
    *ptrdiction = *ptrdelete;
    *ptrdelete = temp;

    (*ptrcount)--;

    return entrydeleted;
}

struct entry *searchentry(struct entry *ptrdiction, int *ptrcount, char *search)
{
    for(int i = 0; i < *ptrcount; i++, ptrdiction++)
        if(strcmp(search, ptrdiction->word) == 0)
            return ptrdiction;

    return NULL;
}