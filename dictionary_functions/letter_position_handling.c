#include "../definition/definitions.h"

#define NO_OF_LETTERS 26

// function to allocate memory for the alphabet
alphabet *create_alphabet(void)
{
    alphabet *new_alphabet = (alphabet *)malloc(sizeof(alphabet));

    // check for successful dynamic memory allocation
    if(new_alphabet == NULL)
    {
        fprintf(stderr, "Error allocating memory to alpahbet in function: %s\n", __func__);
        return NULL;
    }

    new_alphabet->markers = NULL;
    new_alphabet->number_of_letters = 0;

    return new_alphabet;
}

// function to add a new letter to the alphabet, memory for the alphabet is expanded and the new letter is added
void add_letter_to_alphabet(alphabet *new_alphabet, letter_position *letter)
{
    new_alphabet->number_of_letters++;
    new_alphabet->markers = (letter_position **)realloc(new_alphabet->markers, sizeof(letter_position *) * new_alphabet->number_of_letters);
    new_alphabet->markers[new_alphabet->number_of_letters - 1] = letter;
}

// function to create memory for a new letter
letter_position *create_new_letter(char character, long beginning_pos, long ending_pos, int number_of_entries)
{
    // allocate new memory for a new letter
    letter_position *new_letter = (letter_position *)malloc(sizeof(letter_position));

    // check for successful dynamic memory allocation
    if(new_letter == NULL)
    {
        fprintf(stderr, "Error allocating memory to letter in function: %s\n", __func__);
        return NULL;
    }

    // initialise the values for the letter
    new_letter->beginnning_position = beginning_pos;
    new_letter->ending_position = ending_pos;
    new_letter->letter = character;
    new_letter->number_of_letter_entries = number_of_entries;
}

// function to set the position in the file for every hundred eentries in the dictionary
// position1\\space_ch//position2\\space_ch//position3\\space_ch// ...positionN
bool set_hundred_point_markers(FILE *dictionary_source_file)
{
    // file to print the hundred point markers
    new_file hundred_file;
    hundred_file.filename = "positions/hundred_point.txt";
    hundred_file.mode = "w";

    if (!open_file(&hundred_file))
        return FAILURE;

    int line_no = 1;
    int index = 1;
    const int hundred_marker = 100;
    char line[LINE_ENTRY];

    // get the first line which is the header
    if (fgets(line, LINE_ENTRY, dictionary_source_file) == NULL)
        return FAILURE;

    // read the lines and set the markers in the hundred marker file
    while (fgets(line, LINE_ENTRY, dictionary_source_file) != NULL)
    {
        if (line_no == hundred_marker)
        {
            line_no = 1;
            fprintf(hundred_file.fileptr, "%ld ", ftell(dictionary_source_file));
            index++;
        }
        else
            line_no++;
    }

    fclose(hundred_file.fileptr);
    return SUCCESS;
}

// function to read the hundred_point_markers from a file
// uses for the hundred point markers
//  - display of a hundred entries by getting them using the positions shown in the hundreds_file
//  - may be useful for the search function by being markers
bool get_hundred_point_markers(int *hundred_positions, int number_of_points_to_read)
{
    new_file hundred_file;
    hundred_file.filename = "positions/hundred_point.txt";
    hundred_file.mode = "r";

    // open file
    if (!open_file(&hundred_file))
        return FAILURE;

    int index = 0;

    // get a fixed number of markers as specified by the number_of_points variable
    for (int scan_result; index < number_of_points_to_read; index++)
    {
        if ((scan_result = fscanf(hundred_file.fileptr, "%d", hundred_positions + index)) == 0 || scan_result == EOF)
            break;
    }

    // check if anything was read from the file meaning this is a check to see if the file is empty
    if (index == 0)
        return FAILURE;

    return SUCCESS;
}

// typedef struct
// {
//     char letter;
//     long int beginnning_position;
//     long int ending_position;
//     int number_of_letter_entries;
// } letter_position;
// function to set the markers for the letters in a specified file
bool set_letter_markers(FILE *dictionary_source_file)
{
    new_file letter_pos_file;
    letter_pos_file.filename = "positions/letter_positions.txt";
    letter_pos_file.mode = "w";

    // check file was opened
    if (!open_file(&letter_pos_file))
        return FAILURE;

    // initialise variables for the function
    char line[LINE_ENTRY];
    char previous_character = EOF;
    char current_character;
    long int current_line;
    long int previous_line = ftell(dictionary_source_file);
    char alphabet[NO_OF_LETTERS] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    long int alphabet_positions[NO_OF_LETTERS];
    int found = 0;
    int number_of_entries = 0;

    // get the first line that is a header
    fgets(line, LINE_ENTRY, dictionary_source_file);

    // loop through all the lines in the source to get the lines and the first character
    while (current_line = ftell(dictionary_source_file), (fgets(line, LINE_ENTRY, dictionary_source_file) != NULL))
    {
        current_character = line[0];
        alphabet_positions[found] = current_line;

        if (current_character != previous_character && (current_character == alphabet[found]))
        {
            // skip the first unnecessary line, then continue to print the rest
            if (found > 0)
                fprintf(letter_pos_file.fileptr, "%ld, %d\n", previous_line, number_of_entries);

            // change the previous character to the current one, so it is checked next
            previous_character = current_character;

            // print the required values to the fiel
            fprintf(letter_pos_file.fileptr, "%c, %ld, ", current_character, current_line);

            // reset the number of entries for the letter
            number_of_entries = 0;
            found++;
        }

        previous_line = current_line;
        number_of_entries++;
    }
    // print the details for the last letter
    fprintf(letter_pos_file.fileptr, "%ld, %d\n", previous_line, number_of_entries);

    fclose(letter_pos_file.fileptr);
    return SUCCESS;
}

// function to get the positions for all the letters in our dictionary
bool get_letter_markers(alphabet *new_alphabet)
{
    new_file letter_pos_read;
    letter_pos_read.filename = "positions/letter_positions.txt";
    letter_pos_read.mode = "r";

    // open the file
    if(!open_file(&letter_pos_read))
        return FAILURE;

    char *character;
    long beginning_pos;
    long ending_pos;
    int number_of_entries;

    const int line_size = 50;
    char line[line_size];
    char *delimiter = ",";

    while(fgets(line, line_size, letter_pos_read.fileptr) != NULL)
    {
        // get the details from the line read from the file
        character = strtok(line, delimiter);
        beginning_pos = atoi(strtok(NULL, delimiter));
        ending_pos = atoi(strtok(NULL, delimiter));
        number_of_entries = atoi(strtok(NULL, delimiter));

        // create memory for a new letter
        letter_position *new_letter = create_new_letter(character[0], beginning_pos, ending_pos, number_of_entries);

        if(new_letter == NULL)
            return FAILURE;
        
        add_letter_to_alphabet(new_alphabet, new_letter);
    }

    return SUCCESS;
}

// function to check for a character within a range
bool check_char_in_range(char character, char *range, int limit)
{
    const int max_size = 26;
    for(int index = 0; index < limit && index < max_size; index++)
    {
        if(character == range[index])
            return SUCCESS;
    }

    return FAILURE;
}

// function to free memory for a single letter
void free_letter(letter_position *letter)
{
    free(letter);
}

// function to free memory for the entire alphabet
void free_alphabet(alphabet *new_alphabet)
{
    // loop through the alphabet and free the memory
    for(int i = new_alphabet->number_of_letters - 1; i >= 0; i--)
        free_letter(new_alphabet->markers[i]);

    // free the alphabet
    free(new_alphabet);
}
