#include <stdlib.h> /* calloc free malloc */

#include "psform_arithmetic.h"
#include "psform.h"
#include "parser.h"

/* Sum two PS form*/
psform_t* psform_add(psform_t* psform_a, psform_t* psform_b) {
  /* Run througth all elements in PS form a, and try to add
   suitable (same variable multiplicands) elements from PS form b.
   If sutable elements in a list isn't found, then add to
   multiplicands list*/

  int* indexs = (int*)calloc(psform_b->size, sizeof(int));
  addend_t *a = psform_a->elements, *b = psform_b->elements, *el;
  multiplicand_t* multiplicand;
  int constant_a, constant_b, found;
  /* Init psform result */
  psform_t* result = (psform_t*)malloc(sizeof(psform_t));
  result->size = 0;
  result->elements = NULL;
  
  for (size_t i = 0; i < psform_a->size; i++) {
	if (a->elements->type == CONSTANT) {
	  constant_a = a->elements->value.value;
	  a->elements = a->elements->next;
	  a->size--;
	  continue;
	}
	else {
	  constant_a = 1;	  
	}

	found = 0;
	for (size_t j = 0; j < psform_b->size; j++) {
	  if (b->elements->type == CONSTANT) {
		constant_b = b->elements->value.value;
		b->elements = b->elements->next;
		b->size--;
		continue;
	  }
	  else {
		constant_b = 1;
	  }

	  /* If multiplicands are the same (apart from constants),
		 sum this two addends */
	  if (a->size == b->size && \
		  compare_multiplicands_list(a->elements, b->elements,\
									 a->size)) {
		constant_a += constant_b;

		if (constant_a != 0) {
		  el = copy_addend(a);		
		  multiplicand = create_con_multiplicand(constant_a);
		  el->elements = multiplicand;
		  el->elements->next = copy_multiplicands_list(a->elements);
		  ADD_ADDEND(result, el);
		  result->size++;
		}

		found = 1;
		indexs[j] = 1;
	  }
	}

	/* If suitable addend wasn't found in b list,
	   then add unchanged elements to result*/ 
	if(!found) {
	  el = copy_addend(a);
	  el->elements = copy_multiplicands_list(a->elements);
	  ADD_ADDEND(result, el);
	  result->size++;
	}	
  }

  /* After handling all addends in list a, add all unchanged
	 elements in list b into result*/
  b = psform_b->elements;
  for (size_t i = 0; i < psform_b->size; i++) {
	if (!indexs[i]) {
	  el = copy_addend(b);
	  el->elements = copy_multiplicands_list(b->elements);
	  ADD_ADDEND(result, el);	  
	}

	b = b->next;
  }

  return result;
}

/* Substact PS form b from PS form a */
psform_t* psform_subtract(psform_t* psform_a, psform_t* psform_b) {
  /* Change signs to opposite for each elements in PS form b
	 and sum this two form*/
  
}

/* Multiply two PS form*/
psform_t* psform_multiply(psform_t* psform_a, psform_t* psform_b) {
  
}

/* return NULL if division is impossible */
psform_t* psform_divide(psform_t* psform_a, psform_t* psform_b) {
  /* Check if divisor isn't bigger, that 1 */
  if (psform_b->size > 1) {
	return NULL;
  }

  
}


int psform_compare(psform_t* psform_a, psform_t* psform_b) {
  /* Compare length */
  if (psform_a->size != psform_b->size)
	return 0;

  return compare_addends_list(psform_a->elements, psform_b->elements,\
							  psform_a->size);
}
