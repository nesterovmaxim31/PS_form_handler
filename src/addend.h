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
addend_t* init_addend(); /* Create new empty addend */
void add_addend(addend_t*, addend_t*); /* Add new addend to list */
int compare_addends_list(addend_t*, addend_t*, size_t); /* Compare two
														   addend */
size_t get_addends_list_length(addend_t* list); 
addend_t* copy_addend(addend_t*);
addend_t* multipy_addends_list(addend_t*, addend_t*);
addend_t* sum_addends_list(addend_t*, addend_t*, size_t, size_t);
char* print_addends_list(addend_t*);

#endif
