#include"definitions.h"

int main(void)
{
    int entrycount = 0;
    int *ptrcount = &entrycount;

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
}

int displaydictionary(struct entry *diction, int *ptrcount)
{
    printf("Display one word(1)\n\nDisplay entire dictionary(w)\n"); 
}