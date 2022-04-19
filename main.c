#include <stdio.h>
#include "RLEList.h"


int main() {
    RLEList head= RLEListCreate();
    char input;
    while (scanf("%c",&input) && input!='0') {
        RLEListAppend(head,input);
    }
    RLEListResult result;
    printf("%c!\n", RLEListGet(head,3,&result));
    char* tos =RLEListExportToString(head,&result);
    printf("%s",tos);
    destroyList(head);
    return 0;
}
