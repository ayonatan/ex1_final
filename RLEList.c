#include "RLEList.h"

typedef struct RLEList_t {
    char ch;
    int appear;
    struct RLEList_t *next;
} *RLEList;


void RLEListDestroy(RLEList list) {
    if (!list)
        return;
    RLEListDestroy(list->next);
    free(list);
}


char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if (list == NULL) {
        *result = RLE_LIST_NULL_ARGUMENT;
        return '/0';
    }
    if (index < 0) {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return '/0';
    }
    while (list) { // list!=NULL
        if (index < list->appear) {
            *result = RLE_LIST_SUCCESS;
            return list->ch;
        }
        list = list->next;
    }
    *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    return '/0';
}


char *RLEListExportToString(RLEList list, RLEListResult *result) {
    if (!list) { // list == NULL
        result * = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    char *tos = "";
    while (list) { // list!=NULL
        tos += list->ch;
        tos += list->appear;
        tos += "\n";
        list = list->next;
    }
    result *= RLE_LIST_SUCCESS;
    return tos;
}

