#ifndef ADDEND_H
#define ADDEND_H

#include <stdlib.h> /* size_t */

#include "multiplicand.h"

/* Each addend consists of sign, amount of multiplicands,
   poiter to a first multiplicand, and poiter to next addend*/

typedef enum {POSITIVE, NEGATIVE} sign_t; 

typedef struct addend_st{
  sign_t sign;
  size_t size;
  multiplicand_t* elements;
  struct addend_st* next;
} addend_t;

/* function prototype */


#endif
