#include "AsciiArtTool.h"

RLEListResult asciiArtPrint(RLEList list, FILE *outStream)
{
    if (!list || outStream == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    int index = 0;
    RLEListResult result;
    int size = RLEListSize(list);
    while (index < size)
    {
        int characterRepetition = RLEListRepetitions(list, index, &result);
        char characterRepetition = (RLEListGet(list, index, &result));
        char *pCurrentCharacter = &currentCharacter;
        for (int i = 0; i < characterRepetition; i++)
        {
            fputs(pCurrentCharacter, outStream);
        }
        index += characterRepetition;
    }
    return RLE_LIST_SUCCESS;
}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *outStream)
{
    RLEListResult result;
    char *toStringRLE = RLEListExportToString(list, &result);
    fputs(toStringRLE, outStream);
    return RLE_LIST_SUCCESS;
}


RLEList asciiArtRead(FILE *inStream)
{
    RLEList compressedFile = RLEListCreate();
    char inputCharValue = fgetc(inStream);
    while (inputCharValue != EOF)
    {
        RLEListAppend(compressedFile, inputCharValue);
        inputCharValue = fgetc(inStream);
    }
    return compressedFile;
}

