#include <stdio.h>
#include "RLEList.h"
#include <string.h>

int main() {
    RLEListResult result;
    RLEList head= RLEListCreate();
    char input;
    printf("enter input:\n");
    while (scanf("\n%c",&input) && input!='0') {
        result=RLEListAppend(head,input);
    }
    putchar(RLEListGet(head,0,&result));
    RLEListRemove(head,0);
    putchar('\n');
    printf("the size is: %d\n",RLEListSize(head));
    char* tos =RLEListExportToString(head,&result);
    printf("%s",tos);
    RLEListDestroy(head);
    return 0;
}
