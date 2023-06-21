#include"definitions.h"

struct entry *searchentry(struct entry *ptrdiction, int const *ptrcount, char *search);

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

    int entrycount = 0;
    int const *ptrcount = &entrycount;
}

bool modifyentry(struct entry *ptrdiction, struct entry *ptrchange, int const *ptrcount)
{
    struct entry temp;
    bool entrymodified = false;
    int buffersize = 500;
    char discardbuffer[buffersize];

    if(ptrchange == NULL || (ptrchange < ptrdiction || ptrchange > (ptrdiction + *ptrcount)))
    {
        printf("Enter a word to change its entry: ");
        scanf("%30s", temp.word);

        ptrchange = searchentry(ptrdiction, ptrcount, temp.word);

        if(ptrchange == NULL)
            return entrymodified;
    }

    printf("Enter the new word and definition to replace: \"%s - - %s\" ", ptrchange->word, ptrchange->definition);
    scanf("%30s", temp.word);
    fgets(temp.definition, DEFINITION_SIZE, stdin);

    do
    {
        printf("Change entry(y/n) \nFROM: \"%s - - %s\nTO: \"%s - - %s\"\n", ptrchange->word, ptrchange->definition, temp.word, temp.definition);
        fgets(discardbuffer, buffersize,  stdin);

        if(discardbuffer[0] == 'n')
            return entrymodified;
        else if(discardbuffer[0] == 'y')
        {
            if(strcmp(ptrchange->word, temp.word) != 0)
                entrymodified = true;

            *ptrchange = temp;
        }
        else
        {
            printf("Unrecognized response!!\n\n");

            discardbuffer[0] = '\0';
        }
    } while (discardbuffer[0] != 'y' || discardbuffer[0] != 'n');
    

    return entrymodified;
}

struct entry *searchentry(struct entry *ptrdiction, int const *ptrcount, char *search)
{
    for(int i = 0; i < *ptrcount; i++, ptrdiction++)
        if(strcmp(ptrdiction->word, search) == NULL)
            return ptrdiction;

    return NULL;
}