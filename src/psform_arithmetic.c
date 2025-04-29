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
  addend_t *a = psform_a->elements, *b = psform_b->elements;
  /* Init psform result */
  psform_t* result = (psform_t*)malloc(sizeof(psform_t));
  
  result->elements = sum_addends_list(a, b);
  result->size = get_addends_list_length(result->elements);
  /* After handling all addends in list a, add all unchanged
	 elements in list b into result*/

  return result;
}

/* Substact PS form b from PS form a */
psform_t* psform_subtract(psform_t* psform_a, psform_t* psform_b) {
  /* Change signs to opposite for each elements in PS form b
	 and sum this two form*/

  //  psform_t* result = (psform_t*)malloc(sizeof(psform_t));
  addend_t* el = psform_b->elements;

  for (size_t i = 0; i < psform_b->size; i++) {
	if (el->sign == NEGATIVE)
	  el->sign = POSITIVE;
	else
	  el->sign = NEGATIVE;

	el = el->next;
  }

  return psform_add(psform_a, psform_b);
}

/* Multiply two PS form. Multiply all addends in PS form a for each
   elements in PS form b, then sum. */
psform_t* psform_multiply(psform_t* psform_a, psform_t* psform_b) {
  psform_t* result = (psform_t*)malloc(sizeof(psform_t));
  addend_t *addend, *a_list = psform_a->elements, *b_el = psform_b->\
	elements, *summed;

  /* */
  for (size_t i = 0; i < psform_b->size; i++) {
	addend = multiply_addends_list(a_list, b_el);

	if (get_addends_list_length(result->elements) == 0) {
	  result->elements = addend;
	}
	else {
	  summed = sum_addends_list(result->elements, addend);
	  result->elements = summed;
	}

	b_el = b_el->next;
  }

  result->size = get_addends_list_length(result->elements);
  
  return result;  
}

/* return NULL if division is impossible */
psform_t* psform_divide(psform_t* psform_a, psform_t* psform_b) {
  psform_t* result = NULL;
  addend_t *divisor, *el = psform_a->elements, *addend;
  multiplicand_t *multiplicand, *divided;
  
  /* Check if divisor isn't bigger, that 1 */
  if (psform_b->size > 1) {
	return result;
  }
  divisor = psform_b->elements;

  /* Check for division on zero */
  if (divisor->elements->type == CONSTANT \
	  && divisor->elements->value.value == 0)
	return NULL;

  result = (psform_t*)malloc(sizeof(psform_t));
  
  for (size_t i = 0; i < psform_a->size; i++) {
	/* If dividend is equal to zero, go to the next addend */
	if (el->elements->type == CONSTANT && \
		el->elements->value.value == 0) {
	  el = el->next;
	  continue;
	}	  
	
	divided = divide_multiplicands_list(el->elements, divisor->elements);
	if (divided == NULL)
	  return NULL;
	else {
	  addend = init_addend();

	  if (el->sign != divisor->sign)
		addend->sign = NEGATIVE;

	  addend->elements = divided;
	}
	
	ADD_ADDEND(result, addend);
	result->size++;
	
	el = el->next;
  }

  return result;  
}


int psform_compare(psform_t* psform_a, psform_t* psform_b) {
  /* Compare length */
  /* if (psform_a->size != psform_b->size) */
  /* 	return 0; */

  return compare_addends_list(psform_a->elements, psform_b->elements);
}
