#include "RLEList.h"
#include "stdlib.h"
// tell me what do you think about the implementation of the RLELIst struct
typedef struct RLEList_t {
    char char_value;
    int appears;
    struct RLEList_t *next;
} *RLEList;

RLEList RLEListCreate(){
    RLEList list = malloc(sizeof(RLEList));
    if (!list)
        return NULL;
    return list;
}

void RLEListDestroy(RLEList list) {
    if (!list)
        return;
    RLEListDestroy(list->next);
    free(list);
}

RLEListResult RLEListAppend(RLEList list, char value){
    RLEList tempList = list;
    if (!list)
        return RLE_LIST_NULL_ARGUMENT;
    while (tempList->next)
        tempList = tempList->next;
    if(value == tempList->char_value)
    {
        tempList->appears++;
        return RLE_LIST_SUCCESS;
    }
    tempList->next = malloc(sizeof(RLEList));
    if (!tempList->next)
        return RLE_LIST_OUT_OF_MEMORY;
    tempList = tempList->next;
    tempList->appears = 1;
    tempList->char_value = value;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list) {
    int size = 0;
    RLEList tempList=list;
    if (!list)
        return -1;
    while (tempList) {
        size += tempList->appears;
        tempList = tempList->next;
    }
    return size;
}

RLEListResult RLEListRemove(RLEList list, int index){
    if (!list)
        return RLE_LIST_NULL_ARGUMENT;
    int size = RLEListSize(list);
    if (index < 0 || index > size - 1)
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    RLEList tempList = list;
    while (tempList)
    {
        if (index<tempList->appears)
        {
            tempList->appears--;
            return RLE_LIST_SUCCESS;
        }
        index -= tempList->appears;
    }
}

char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if (!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return '/0';
    }
    int size = RLEListSize(list);
    if (index < 0 || index > size - 1)
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return '/0';
    }
    while (list)
    {
        if (index < list->appears)
        {
            *result = RLE_LIST_SUCCESS;
            return list->char_value;
        }
        index -= list->appears;
        list = list->next;
    }
    *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    return '/0';
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if (!list)
        return RLE_LIST_NULL_ARGUMENT;
    RLEList tempList = list;
    while (tempList)
    {
        tempList->char_value = map_function(tempList->char_value);
        tempList=tempList->next;
    }
    return RLE_LIST_SUCCESS;
}

char *RLEListExportToString(RLEList list, RLEListResult *result) {
    if (!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    int sizeString = 0;
    RLEList tempList = list;
    while(tempList)
    {
        sizeString++;
        tempList = tempList->next;
    }
    sizeString *= 3;
    char *tostring = malloc(sizeString);
    for(int i = 0; i < sizeString - 1 ; i+=3)
    {
        tostring[i] = list->char_value;
        tostring[i + 1] = list->appears;
        tostring[i + 2] = '\n';
        list = list->next;
    }
    tostring[sizeString-1] = '\0';
    *result = RLE_LIST_SUCCESS;
    return tostring;
}
