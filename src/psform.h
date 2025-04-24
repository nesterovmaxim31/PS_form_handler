#ifndef PSFORM_H
#define PSFORM_H

#include "addend.h"

/* Each PS form consists of size and pointer to a first addend*/
typedef struct {
  size_t size; /* Amount of addends */
  addend_t* elements;
} psform_t;


/* function prototype */

#endif
