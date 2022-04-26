#include "AsciiArtTool.h"

int main(int argc, char **argv) 
{
    if (argc == ARGUMENT_NUMBER) 
    {
        FILE *input = fopen(argv[SOURCE_ARGUMENT], READ_PERMISSION); /// is w a magic number?
        if (!input) 
        {
            return 1;
        }
        FILE *output = fopen(argv[TARGET_ARGUMENT], WRITE_PERMISSION); /// is w a magic number?
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
        else if (strcmp(argv[FLAG_ARGUMENT], INVERTED_SYMBOL) == 0) {
            if (RLEListMap(list, Map_function_aux) == RLE_LIST_NULL_ARGUMENT) 
            {
                return 1;
            }
            asciiArtPrint(list, output);
        }
        fclose(output);
        RLEListDestroy(list);
    }
  
    return 0;
}


// map function
/// can it get a null?
char Map_function_aux(char list_character) 
{
    if (list_character == CHARACTER_TO_CHANGE) 
    {
        return CHANGED_CHARACTER;
    }
    return list_character;
}


RLEListResult asciiArtPrint(RLEList list, FILE *out_stream) 
{
    if (!list || out_stream == NULL) 
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    int index = 0;
    RLEListResult result;
    int size = RLEListSize(list);
    while (index < size) 
    {
        int character_repetition = RLEListRepetitions(list, index, &result);
        assert(character_repetition == -1); //////////
        char current_character = (RLEListGet(list, index, &result));
        char *pCurrent_character = &current_character;
        for (int i = 0; i < character_repetition; i++) 
        {
            fputs(pCurrent_character, out_stream);
        }
        index += character_repetition;
    }
    return RLE_LIST_SUCCESS;
}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) 
{
    RLEListResult result;
    char *toString_RLE = RLEListExportToString(list, &result);
    fputs(toString_RLE, out_stream);
    return RLE_LIST_SUCCESS;
}


RLEList asciiArtRead(FILE *in_stream) 
{
    RLEList compressed_file = RLEListCreate();
    char input_char_value = fgetc(in_stream);
    while (input_char_value != EOF) 
    {
        RLEListAppend(compressed_file, input_char_value);
        input_char_value = fgetc(in_stream);
    }
    return compressed_file;
}
