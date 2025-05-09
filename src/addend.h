#ifndef ADDEND_H
#define ADDEND_H

#include <stdlib.h> /* size_t */

#include "multiplicand.h"

/* Each addend consists of sign, amount of multiplicands,
   poiter to a first multiplicand, and poiter to next addend*/

typedef enum {POSITIVE, NEGATIVE} sign_t; 

typedef struct addend_st{
    sign_t sign;
    size_t size; /* Amount of multiplicand */
    multiplicand_t* elements;
    struct addend_st* next;
} addend_t;

/* function prototype */

/* Create new empty addend */
addend_t* init_addend();
/* Allocate memory and copy addend */
addend_t* copy_addend(addend_t*);
/* Allocate memory and sum two addends list */
addend_t* sum_addends_list(addend_t*, addend_t*);
/* Allocate memory and multiply two addends */
addend_t* multiply_addends_list(addend_t*, addend_t*);

/* Add new addend to list */
void add_addend(addend_t*, addend_t*);
/* Free allocated memory of all addends in list */
void free_addends_list(addend_t*);

/* Compare two addends lists */
int compare_addends_list(addend_t*, addend_t*);

/* Get length of addends list */
size_t get_addends_list_length(addend_t* list);

/* Return allocated string with all addends and their's multiplicands */
char* print_addends_list(addend_t*);

#endif
