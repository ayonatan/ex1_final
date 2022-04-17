#include "RLEList.h"

// tell me what do you think about the implementation of the RLELIst struct
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

int RLEListSize(RLEList list) {
    int num = 0;
    if (list == NULL)
        return -1;
    while (list) {
        list = list->next;
        num++;
    }
    return num;
}

char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if (list == NULL)
        *result = RLE_LIST_NULL_ARGUMENT;
    return '/0';
    while (list != NULL && index != 0) {
        int appear = list->appear;
        while (appear > 0 && list != NULL && index > 0) {
            index--;
            appear--;
        }
        if (list == NULL) {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
            return 0;
        }
        if (index == 0) {
            *result = RLE_LIST_SUCCESS;
            return list->ch;
        }
        list = list->next;
    }
}
// michal keep changing the file and implement the funcs
// good lack and HAPPY PASSOVER !!!!



