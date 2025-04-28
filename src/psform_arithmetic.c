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
  multiplicand_t *multiplicand, *a_list, *b_list;
  size_t a_list_size, b_list_size;
  int constant_a, constant_b, found;
  /* Init psform result */
  psform_t* result = (psform_t*)malloc(sizeof(psform_t));
  result->size = 0;
  result->elements = NULL;
  
  for (size_t i = 0; i < psform_a->size; i++) {
	a_list = a->elements;
	a_list_size = a->size;
	
	if (a_list->type == CONSTANT) {
	  constant_a = a_list->value.value;
	  a_list = a_list->next;
	  a_list_size--;
	}
	else {
	  constant_a = 1;	  
	}

	if (a->sign == NEGATIVE)
	  constant_a *= -1;

	found = 0;

	b = psform_b->elements;
	for (size_t j = 0; j < psform_b->size; j++) {
	  b_list = b->elements;
	  b_list_size = b->size;
	  
	  if (b_list->type == CONSTANT) {
		constant_b = b_list->value.value;
		b_list = b_list->next;
		b_list_size--;
	  }
	  else {
		constant_b = 1;
	  }

	  if (b->sign == NEGATIVE)
		constant_b *= -1;

	  /* If multiplicands are the same (apart from constants),
		 sum this two addends */
	  if (a_list_size == b_list_size && \
		  compare_multiplicands_list(a_list, b_list,\
									 a_list_size)) {
		constant_a += constant_b;

		if (constant_a != 0) {
		  el = copy_addend(a);
		  
		  if (constant_a < 0) {
			constant_a *= -1;
			el->sign = NEGATIVE;
		  }
		  
		  multiplicand = create_con_multiplicand(constant_a);
		  el->elements = multiplicand;
		  
		  el->elements->next = copy_multiplicands_list(a_list);
		  el->size += a_list_size;
		  
		  ADD_ADDEND(result, el);
		  result->size++;
		}

		found = 1;
		indexs[j] = 1;
		break;
	  }

	  b = b->next;
	} /* End for loop psform_b */

	/* If suitable addend wasn't found in b list,
	   then add unchanged elements to result*/ 
	if(!found) {
	  el = copy_addend(a);
	  el->elements = copy_multiplicands_list(a->elements);
	  ADD_ADDEND(result, el);
	  result->size++;
	}

	a = a->next;
  } /* End for loop psform_a */

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
  
  free(indexs);
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
	addend = copy_addend(psform_a->elements);
	addend->elements = copy_multiplicands_list(addend->elements);
	add_multiplicand(addend->elements, \
					 copy_multiplicands_list(b_el->elements));

	/* If result is empty, just add new element. If it ins't,
	 sum current result to new addend */
	if (result == NULL)
	  result ->elements = addend;
	else {
	}
	// ADD_ADDEND(result, );
  }
  
  return result;  
}

/* return NULL if division is impossible */
psform_t* psform_divide(psform_t* psform_a, psform_t* psform_b) {
  psform_t* result = NULL;
  addend_t *divisor, *el = psform_a->elements, *addend;
  multiplicand_t *multiplicand, *divided;
  int found; 

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
	found = 0;

	/* If dividend is equal to zero, go to the next addend */
	if (el->elements->type == CONSTANT && el->elements->value.value == 0) {
	  el = el->next;
	  continue;
	}	  
	
	divided = divide(el->elements, divisor->elements, divisor->size);
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
  if (psform_a->size != psform_b->size)
	return 0;

  return compare_addends_list(psform_a->elements, psform_b->elements,\
							  psform_a->size);
}
