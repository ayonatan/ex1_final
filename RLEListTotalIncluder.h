#include "RLEList.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef RLELIST_H_RLELISTTOTALHEADER_H
#define RLELIST_H_RLELISTTOTALHEADER_H
#define NULL_LIST_SIZE -1
#define IMAGINARY_NODE_REP 0
#define LINE_PLUS_SPACE 2
#define INDEX_ILLEGAL -1
#define ZERO_SPOT 1
#define CHAR_AND_LINE_DROP 2
#define LINE_DOWN '\n'
#define ZERO '\0'
#define CUT_BY_DIGIT 10
#define INT_FORMAT "%d"

/**
*   RLEListRepetitions: Returns the repetitions of the char at the chosen index.
* @param list - The RLE list.
* @param index - the wanted place int the RLEList.
* @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
*   RLE_LIST_INDEX_OUT_OF_BOUNDS if the index is smaller than 0 or bigger than list size.
* 	LIST_SUCCESS the repetitions has been successfuly returned.
* @return
* 	-1 if result is not LIST_SUCCESS
*   if result is LIST_SUCCESS, return the repetitions of the character at given index.
*/
int RLEListRepetitions(RLEList list, int index, RLEListResult *result);

#endif
