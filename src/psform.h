#ifndef PSFORM_H
#define PSFORM_H

#include "addend.h"

/* All operations program can perform with PS forms */
typedef enum {ADDITION, SUBTRACTION, MULTIPLICATION, \
				  DIVISION, COMPARISON} operation_t;

/* Each PS form consists of size and pointer to a first addend*/
typedef struct {
  size_t sign;
  addend_t* elements;
} psform_t;


/* function prototype */

#endif
