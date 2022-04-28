#include "tool/RLEListTotalIncluder.h"

struct RLEList_t {
    char char_value;
    int repetitions;
    struct RLEList_t *next;
};


RLEList RLEListCreate()
{
    RLEList list = malloc(sizeof(*list));
    if (!list)
    {
        return NULL;
    }
    list->repetitions = 0;
    list->next = NULL;
    return list;
}

void RLEListDestroy(RLEList list)
{
    if (!list)
    {
        return;
    }
    RLEListDestroy(list->next);
    free(list);
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList tempList = list;
    while (tempList->next)
    {
        tempList = tempList->next;
    }
    if (tempList->repetitions > 0)
    {
        if (value == tempList->char_value)
        {
            tempList->repetitions++;
            return RLE_LIST_SUCCESS;
        }
    }
    tempList->next = malloc(sizeof(*list));
    if (!tempList->next)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    tempList = tempList->next;
    tempList->repetitions = 1;
    tempList->char_value = value;
    tempList->next = NULL;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    int size = 0;
    if (!list)
    {
        return NULL_LIST_SIZE;
    }
    RLEList tempList = list->next;
    if (!tempList && list->repetitions == IMAGINARY_NODE_REP)
    {
        return NULL_LIST_SIZE;
    }
    while (tempList)
    {
        size += tempList->repetitions;
        tempList = tempList->next;
    }
    return size;
}

//merge the next node into node.
//assumptions checked by the calling functions: the next node exists and it has the same char value
void merge(RLEList node)
{
    RLEList nodeNext = node->next;
    node->repetitions += nodeNext->repetitions;
    node->next = nodeNext->next;
    nodeNext->next = NULL;
    free(nodeNext);
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int size = RLEListSize(list);
    if (index < 0 || index > size - 1)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList tempList = list->next;
    while (tempList)
    {
        if (index < tempList->repetitions)
        {
            if (tempList->repetitions > 1)
            {
                tempList->repetitions--;
                return RLE_LIST_SUCCESS;
            }
            RLEList tempList2 = list;
            while (tempList2->next != tempList)
            {
                tempList2 = tempList2->next;
            }
            tempList2->next = tempList->next;
            tempList->next = NULL;
            free(tempList);
            if (tempList2->next && tempList2->char_value == tempList2->next->char_value)
            {
                merge(tempList2);
            }
            return RLE_LIST_SUCCESS;
        }
        index -= tempList->repetitions;
        tempList = tempList->next;
    }
    return RLE_LIST_ERROR;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (!list)
    {
        if(result)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return ZERO;
    }
    int size = RLEListSize(list);
    if (index < 0 || index > size - 1)
    {
        if (result)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return ZERO;
    }
    RLEList tempList = list->next;
    while (tempList)
    {
        if (index < tempList->repetitions)
        {
            if (result)
            {
                *result = RLE_LIST_SUCCESS;
            }
            return tempList->char_value;
        }
        index -= tempList->repetitions;
        tempList = tempList->next;
    }
    if (result)
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    return ZERO;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList tempList = list->next;
    while (tempList)
    {
        tempList->char_value = map_function(tempList->char_value);
        tempList = tempList->next;
    }
    tempList = list;
    while (tempList->next)
    {
        if (tempList->next->char_value == tempList->char_value)
        {
            merge(tempList);
        }
        else
        {
            tempList = tempList->next;
        }
    }
    return RLE_LIST_SUCCESS;
}

int numOfDigits(int num)
{
    if (num == 0)
    {
        return 1;
    }
    int counter = 0;
    while (num != 0)
    {
        counter++;
        num /= CUT_BY_DIGIT;
    }
    return counter;
}

char *RLEListExportToString(RLEList list, RLEListResult *result)
{
    if (!list)
    {
        if (result)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    int sizeString = 0;
    RLEList tempList = list->next;
    int digits;
    while (tempList)
    {
        digits = numOfDigits(tempList->repetitions);
        sizeString += CHAR_AND_LINE_DROP;//for one char and one \n
        sizeString += digits;
        tempList = tempList->next;
    }
    tempList = list->next;
    char *listToString = malloc(sizeString + ZERO_SPOT);
    if (!listToString)
    {
        if (result)
        {
            *result = RLE_LIST_ERROR;
        }
        return NULL;
    }
    listToString[sizeString] = ZERO;

    int lastCharIndex = sizeString - digits - LINE_PLUS_SPACE;
    for (int i = 0; i <= lastCharIndex; i += (LINE_PLUS_SPACE + digits))
    {
        digits = numOfDigits(tempList->repetitions);
        listToString[i] = tempList->char_value;
        sprintf((listToString + i + 1), INT_FORMAT, tempList->repetitions);
        listToString[i + 1 + digits] = LINE_DOWN;
        tempList = tempList->next;
    }

    if (result)
    {
        *result = RLE_LIST_SUCCESS;
    }
    return listToString;
}

int RLEListRepetitions(RLEList list, int index, RLEListResult *result)
{
    if (!list)
    {
        if (result)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return INDEX_ILLEGAL;
    }
    int size = RLEListSize(list);
    if (index < 0 || index > size - 1)
    {
        if (result)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return INDEX_ILLEGAL;
    }
    RLEList tempList = list->next;
    while (tempList)
    {
        if (index < tempList->repetitions)
        {
            if (result)
            {
                *result = RLE_LIST_SUCCESS;
            }
            return tempList->repetitions;
        }
        index -= tempList->repetitions;
        tempList = tempList->next;
    }
    if (result)
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    return INDEX_ILLEGAL;
}
