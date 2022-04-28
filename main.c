#include "AsciiArtTool.h"

#define FLAG_ARGUMENT 1
#define SOURCE_ARGUMENT 2
#define TARGET_ARGUMENT 3
#define ARGUMENT_NUMBER 4
#define ENCODED_SYMBOL "-e"
#define INVERTED_SYMBOL "-i"
#define CHARACTER_SPACE ' '
#define CHARACTER_STRUDEL '@'
#define READ_PERMISSION "r"
#define WRITE_PERMISSION "w"

/**    Map_function_aux
 * The function gets a character and changes it if needed.
 *
 * @param list_character - character that is being checked.
 * @return
 *    @ if the list_character is space (' '), if not the character does not changed
 */
char MapInvertFunction(char list_character);


int main(int argc, char **argv)
{
    if (argc == ARGUMENT_NUMBER)
    {
        FILE *input = fopen(argv[SOURCE_ARGUMENT], READ_PERMISSION);
        if (!input)
        {
            return 1;
        }
        FILE *output = fopen(argv[TARGET_ARGUMENT], WRITE_PERMISSION);
        if (!output)
        {
            fclose(input);
            return 1;
        }

        RLEList list = asciiArtRead(input);
        if (list == NULL)
        {
            fclose(output);
            fclose(input);
            return 1;
        }
        if (strcmp(argv[FLAG_ARGUMENT], ENCODED_SYMBOL) == 0)
        {
            asciiArtPrintEncoded(list, output);
        }
        else if (strcmp(argv[FLAG_ARGUMENT], INVERTED_SYMBOL) == 0)
        {
            if (RLEListMap(list, MapInvertFunction) == RLE_LIST_NULL_ARGUMENT)
            {
                return 1;
            }
            asciiArtPrint(list, output);
        }
        fclose(input);
        fclose(output);
        RLEListDestroy(list);
    }
    return 0;
}



// map function --> changes '@' to ' ' and  ' ' to '@'
char MapInvertFunction(char listCharacter)
{
    if (listCharacter == CHARACTER_STRUDEL)
    {
        return CHARACTER_SPACE;
    }
    if (listCharacter == CHARACTER_SPACE)
    {
        return CHARACTER_STRUDEL;
    }
    return listCharacter;
}
