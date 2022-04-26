#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H


#include "RLEList.h"

#ifndef FLAG_ARGUMENT
#define FLAG_ARGUMENT 1
#define SOURCE_ARGUMENT 2
#define TARGET_ARGUMENT 3
#define ARGUMENT_NUMBER 4
#define ENCODED_SYMBOL "-e"
#define INVERTED_SYMBOL "-i"
#define CHARACTER_TO_CHANGE ' '
#define CHANGED_CHARACTER '@'
#define READ_PERMISSION "r"
#define WRITE_PERMISSION "w"
#endif


/**    Map_function_aux
 * The function gets a character and changes it if needed.
 *
 * @param list_character - character that is being checked.
 * @return
 *    @ if the list_character is space (' '), if not the character does not changed
 */
char Map_function_aux(char list_character);


/**
 * The function reads the given file and compresses it using the RLE method.
 * 
 * @param in_stream - FILE* object that contains the image that needs to be compressed. 
 * @return 
 *    RLEList list which containes all of the picture's chars 
 */
RLEList asciiArtRead(FILE *in_stream);

/**
 * The function writes an image that is represented by an RLEList object to a file.
 * 
 * @param list - RLEList list which containes all of the image's chars
 * @param out_stream - A FILE* object to which the image will be written
 * @return
 *   RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
 *   RLE_LIST_SUCCESS if the function succeeded
 */
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/**
 *  The function writes the image to the file in a compressed form in a format returned from RLEListExportToString.
 * 
 * @param list - RLEList list which containes all of the image's chars
 * @param out_stream - A FILE* object to which the compressed image will be written
 * @return
 *   RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
 *   RLE_LIST_SUCCESS if the function succeeded
 */
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif
