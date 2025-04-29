#include <stdlib.h> /* malloc calloc size_t exit */
#include <stdio.h>  /* fprintf */
#include <string.h> /* bzero */

#include "addend.h"
#include "multiplicand.h"

/* Return length of list of addends */
size_t get_addends_list_length(addend_t* list) {
  size_t size = 0;

  while (list != NULL) {
	size++;
	list = list->next;
  }

  return size;
}

/* Create new addend and set it's values to default */
addend_t* init_addend() {
  addend_t* addend = (addend_t*)malloc(sizeof(addend_t));
  /* Default values */
  addend->sign = POSITIVE;
  addend->size = 0;
  addend->elements = NULL;
  addend->next = NULL;

  return addend;
}


void add_addend(addend_t* leading, addend_t* new) { 
  while(leading->next != NULL) {
	leading = leading->next;
  }

  leading->next = new;
}

/* Free addends list */
void free_addends_list(addend_t* list) {
  addend_t* _el;
	  
  while (list != NULL) {
	free_multiplicands_list(list->elements);
	_el = list;
	list = list->next;
	free(_el);
  }
}

/* Compare two lists of addends with the same lengths */
int compare_addends_list(addend_t* a, addend_t* b) {
  /* Run througth all elements in list a, and try to find this
	 element in b. If such element is found, it's index in written
	 into array */
  /* Compare lengths */
  if (get_addends_list_length(a) != get_addends_list_length(b))
	return 0;
  
  size_t length = get_addends_list_length(a);
  int* indexs = (int*)calloc(length, sizeof(int));
  addend_t* _b = b;
  int found;

  if (indexs == NULL) {
	fprintf(stderr, "Unable to allocate memory\n");
	exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < length; i++) {
	found = 0;
	b = _b;
	for (size_t j = 0; j < length; j++) {
	  if (a->size == b->size && a->sign == b->sign && \
		  compare_multiplicands_list(a->elements, b->elements) \
		  && !indexs[j]) {
		indexs[j] = 1;
		found = 1;
		break;
	  }

	  b = b->next;
	}

	/* Return 0, if this element from list a, isn't found in list b */
	if (!found) {
	  free(indexs);
	  return 0;
	}
	
	a = a->next;
  }
  
  free(indexs);
  
  return 1;
}

/* Print addends list */
char* print_addends_list(addend_t* addend) {
  if (addend == NULL)
	return NULL;

  /* To store 100 addends with 27 multiplicand in each
	 is enough 8192 bytes */
  char* line = (char*)malloc(8192);
  bzero(line, 8192);
  
  if (addend->sign == NEGATIVE)
	line[0] = '-';
  
  while(addend != NULL) {
	print_multiplicands_list(addend->elements, line);
	if (addend->next != NULL && addend->next->sign == POSITIVE)
	  strcat(line, " + ");
	else if (addend->next != NULL && addend->next->sign == NEGATIVE)
	  strcat(line, " - ");
	addend = addend->next;
  }

  return line;
}

/* Copy addend */
addend_t* copy_addend(addend_t* addend) {
  addend_t* copy = init_addend();
  copy->sign = addend->sign;
  copy->size = addend->size;
  copy->elements = addend->elements;
  copy->next = NULL;

  return copy;
}

/* Allocate memory and sum two addends list */
addend_t* sum_addends_list(addend_t* a, addend_t* b) {
  size_t size_a =  get_addends_list_length(a);
  size_t size_b = get_addends_list_length(b);
  int* indexs = (int*)calloc(size_b, sizeof(int));
  multiplicand_t *multiplicand, *a_list, *b_list;
  size_t a_list_size, b_list_size;
  addend_t* result = NULL, *el, *_b;
  int constant_a, constant_b, found;
  _b = b;

  if (indexs == NULL) {
	fprintf(stderr, "Unable to allocate memory\n");
	exit(EXIT_FAILURE);
  }

  /* Run througth all addends in a, and try to find
	 suitable addend in b. In indexs are stored index of
	 suitable addend form b */
  for (size_t i = 0; i < size_a; i++) {
	a_list = a->elements;
	a_list_size = get_multiplicans_list_length(a->elements);

	/* Handle constant */
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

	/* Run througth all addends in b */
	found = 0;
	b = _b;
	for (size_t j = 0; j < size_b; j++) {
	  b_list = b->elements;
	  b_list_size = get_multiplicans_list_length(b->elements);
	  
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
		  compare_multiplicands_list(a_list, b_list)) {
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

		  if (result == NULL)
			result = el;
		  else {
			add_addend(result, el);
			result->size++;
		  }
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

	  if (result == NULL)
		result = el;
	  else
		add_addend(result, el);
	  result->size++;
	}

	a = a->next;
  } /* End for loop psform_a */

  b = _b;
  for (size_t i = 0; i < size_b; i++) {
	if (!indexs[i]) {
	  el = copy_addend(b);
	  el->elements = copy_multiplicands_list(b->elements);
	  
	  if (result == NULL)
		result = el;
	  else {
		add_addend(result, el);
		result->size++;
	  }
	}

	b = b->next;
  }

  free(indexs);
  
  return result;
}

/* Multiply two multiplicands list */
static inline
multiplicand_t* multiply(multiplicand_t* a, multiplicand_t* b) {	
  if (a == NULL && b == NULL) {								
	return NULL;													
  } 														
  else if (a == NULL && b != NULL) {						
	return multiply_multiplicands_list(NULL, b);			
  }															
  else if (a != NULL && b == NULL) {						
	return multiply_multiplicands_list(a, NULL);			
  }															
  else {													
	return multiply_multiplicands_list(a, b);	
  }
}


/* Allocate memory and multiply addends list on addend el */
addend_t* multiply_addends_list(addend_t* list, addend_t* el) {
  int list_element_constant, el_constant;
  sign_t list_element_sign, el_sign;
  addend_t *result = NULL, *new_el;
  multiplicand_t *list_elements, *el_elements;

  el_sign = el->sign;
  el_elements = el->elements;
  /* Handle el constant */
  if (el_elements->type == CONSTANT) {
	el_constant = el->elements->value.value;
	el_elements = el_elements->next;
  }
  else {
	el_constant = 1;
  }
  
  while (list != NULL) {
	list_element_sign = list->sign;
	list_elements = list->elements;
	/* Handle element's constant from list */
	if (list_elements->type == CONSTANT) {
	  list_element_constant = list->elements->value.value;
	  list_elements = list_elements->next;
	}
	else {
	  list_element_constant = 1;
	}

	/* Check if zero */
	if (list_element_constant * el_constant == 0) {
	  list = (list != NULL) ? list->next : NULL; 
	  continue;
	}
	
	/* If constant is equal to 1, then do not add multiplicand */
	new_el = init_addend();
	if (list_element_constant * el_constant != 1) {
	  new_el->elements = create_con_multiplicand(list_element_constant * \
									   el_constant);
	}

	/* Handle var-multiplicands */
	if (new_el->elements != NULL)
	  add_multiplicand(new_el->elements, multiply(list_elements, \
												  el_elements));
	else
	  new_el->elements = multiply(list_elements, el_elements);

	if (list_element_sign != el_sign)
	  new_el->sign = NEGATIVE;

	/* If result is empty, than head of a list is a new element*/
	if (result == NULL) {
	  result = new_el;
	}
	/* Else just add new elements to the end of list */
	else {
	  add_addend(result, new_el);
	}
	  
	list = list->next;
  }

  return result;
}
