#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
#include<stdbool.h>

#define WORD_SIZE       30
#define DEFINITION_SIZE 200
#define PASS            0
#define FAIL            1
#define DICTIONARY_SIZE 100

struct entry
{
    char word[WORD_SIZE];
    char definition[DEFINITION_SIZE];
};

/*ptrdiction = struct entry pointer to first element in the dictionary
ptrcount = int pointer to the count of elements in the dictionary*/