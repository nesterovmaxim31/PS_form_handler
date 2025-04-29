#ifndef PSFORM_ARITHMETIC_H
#define PSFORM_ARITHMETIC_H

#include "psform.h"


/* function prototype */

/* Sum two PS form, and return allocated result */
psform_t* psform_add(psform_t*, psform_t*);
/* Subtract the first PS form the second one, and
   return allocated result*/
psform_t* psform_subtract(psform_t*, psform_t*);
/* Multiply two PS form and return allocated result */
psform_t* psform_multiply(psform_t*, psform_t*);
/* Divide the first PS form by the second one,
   and return allocated result */
psform_t* psform_divide(psform_t*, psform_t*); 

/* Compare two PS form. If return 1 -> equal, if return 0 -> not equal */
int psform_compare(psform_t*, psform_t*);

#endif
