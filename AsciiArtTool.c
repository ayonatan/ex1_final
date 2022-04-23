#include <stdio.h>
#include "AsciiArtTool.h"
#include <stdlib.h>
RLEList asciiArtRead(FILE* in_stream){
    RLEList compressed_file = RLEListCreate();
    char input_char_value = fgetc(in_stream);
    while (input_char_value)
    {
        RLEListAppend(compressed_file, input_char_value);
        input_char_value = fgetc(in_stream);
    }
    return compressed_file;
}
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream) {
    FILE *output = fopen(out_stream, "w");
    if (!output) {
        error("Error: cannot open", out_stream);
        return RLE_LIST_NULL_ARGUMENT;
    }

    // if (!list || out_stream == NULL)
    //   return RLE_LIST_NULL_ARGUMENT;

    RLEListResult result;
    char *toString_RLE; //////////////////
    toString_RLE = RLEListExportToString(list, &result);
    if (result != RLE_LIST_SUCCESS) {
        fclose(out_stream);
        return RLE_LIST_NULL_ARGUMENT;
    }
    fputs(toString_RLE, out_stream);
    fclose(out_stream);
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    if (!list || out_stream == NULL)
        return RLE_LIST_NULL_ARGUMENT;

    FILE *output = fopen(out_stream, "w");
    if (!output) {
        printf("Error: cannot open");
        return RLE_LIST_NULL_ARGUMENT;
    }

    int index = 0;
    RLEListResult result;
    while (list) {
        // if (!list || out_stream == NULL)
        //   return RLE_LIST_NULL_ARGUMENT;
        int character_repetition = RLEListRepetitions(list, index, &result);
        assert(character_repetition ==-1);
        char* current_character = (char*)(RLEListGet(list,index,&result));
            for (int i = 0; i < character_repetition; i++) {
                fputs(current_character, out_stream);
            }
        index++;
    }
    fclose(out_stream);
    return RLE_LIST_SUCCESS;
}
