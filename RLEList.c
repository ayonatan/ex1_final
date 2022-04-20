#include "RLEList.h"
#include <stdlib.h>
#include <string.h>
#define ZERO '\0'

struct RLEList_t {
    char char_value;
    int repetitions;
    struct RLEList_t* next;
};

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
    if (!list)
        return RLE_LIST_NULL_ARGUMENT;
    RLEList temp_list = list;
    while (temp_list->next)
        temp_list = temp_list->next;
    if (value == temp_list->char_value)
    {
        temp_list->repetitions++;
        return RLE_LIST_SUCCESS;
    }
    temp_list->next = malloc(sizeof(RLEList));
    if (!temp_list->next)
        return RLE_LIST_OUT_OF_MEMORY;
    temp_list = temp_list->next;
    temp_list->repetitions = 1;
    temp_list->char_value = value;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list) {
    int size = 0;
    RLEList temp_list = list->next;
    if (!list)
        return -1;
    while (temp_list) {
        size += temp_list->repetitions;
        temp_list = temp_list->next;
    }
    return size;
}

RLEListResult RLEListRemove(RLEList list, int index){
    if (!list)
        return RLE_LIST_NULL_ARGUMENT;
    int size = RLEListSize(list);
    if (index < 0 || index > size - 1)
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    RLEList temp_list = list->next;
    while (temp_list)
    {
        if (index < temp_list->repetitions)
        {
            if (temp_list->repetitions > 1)
            {
                temp_list->repetitions--;
                return RLE_LIST_SUCCESS;
            }
            RLEList temp_list2 = list;
            while(temp_list2->next != temp_list)
                temp_list2 = temp_list2->next;
            temp_list2->next = temp_list->next;
            temp_list->next = NULL;
            free(temp_list);
            return RLE_LIST_SUCCESS;
        }
        index -= temp_list->repetitions;
        temp_list = temp_list->next;
    }
    return RLE_LIST_ERROR;
}

char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if (!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return ZERO;
    }
    int size = RLEListSize(list);
    if (index < 0 || index > size - 1)
    {
        if (!result)
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return ZERO;
    }
    RLEList temp_list = list->next;
    while (temp_list)
    {
        if (index < temp_list->repetitions)
        {
            if (!result)
                *result = RLE_LIST_SUCCESS;
            return temp_list->char_value;
        }
        index -= temp_list->repetitions;
        temp_list = temp_list->next;
    }
    *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    return ZERO;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if (!list)
        return RLE_LIST_NULL_ARGUMENT;
    RLEList temp_list = list->next;
    while (temp_list)
    {
        temp_list->char_value = map_function(temp_list->char_value);
        temp_list = temp_list->next;
    }
    return RLE_LIST_SUCCESS;
}

int numOfDigits(int num){
    int counter=0;
    while(num!=0)
    {
        counter++;
        num/=10;
    }
    return counter;
}

char *RLEListExportToString(RLEList list, RLEListResult *result) {
    if (!list)
    {
        if (!result)
            *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    int size_string = 0;
    RLEList temp_list = list->next;
    while(temp_list)
    {
        size_string += 2;//for one char and one \n
        size_string += numOfDigits(temp_list->repetitions);
        temp_list = temp_list->next;
    }
    temp_list = list->next;
    char *list_to_string = malloc(size_string + 1);
    list_to_string[size_string] = '\0';
    if (!list_to_string)
    {
        if (!result)
            *result = RLE_LIST_ERROR;
        return NULL;
    }
    int num_of_digits;
    for(int i = 0; i < size_string - 2; i += (2 + num_of_digits))
    {
        num_of_digits = numOfDigits(temp_list->repetitions);
        list_to_string[i] = temp_list->char_value;
        sprintf((list_to_string + i + 1), "%d", temp_list->repetitions);
        list_to_string[i + 1 + num_of_digits] = '\n';
        temp_list = temp_list->next;
    }
    if (!result)
        *result = RLE_LIST_SUCCESS;
    return list_to_string;
}
