#ifndef PSFORM_ARITHMETIC_H
#define PSFORM_ARITHMETIC_H

#include "psform.h"


/* function prototype */
psform_t* psform_add(psform_t*, psform_t*); /* Add two PS form,
											   and return result*/
psform_t* psform_subtract(psform_t*, psform_t*); /* Subtract the first PS
													form the second one, and
													return result*/
psform_t* psform_multiply(psform_t*, psform_t*); /* Multiply two PS form,
													and return result */
psform_t* psform_divide(psform_t*, psform_t*); /* Divide the first PS form
												  by the second one, and
												  return result */
int psform_compare(psform_t*, psform_t*); /* Compare two PS form,
											 and return result */


#endif
