#include <stdlib.h> /* malloc calloc free */
#include <string.h>
#include <stdio.h> /* fprintf */

#include "multiplicand.h"

/* Return length of list of multiplicands */
size_t get_multiplicans_list_length(multiplicand_t* list) {
  size_t size = 0;

  while (list != NULL) {
	size++;
	list = list->next;
  }

  return size;
}

/* Create new variable multiplicand, and set default values */
multiplicand_t* create_var_multiplicand(char name) {
  multiplicand_t* multiplicand;
  multiplicand = (multiplicand_t*)malloc(sizeof(multiplicand_t));

  if (multiplicand == NULL) {
	fprintf(stderr, "Unable to allocate memory\n");
	exit(EXIT_FAILURE);
  }

  multiplicand->type = VARIABLE;
  multiplicand->value.name = name;
  multiplicand->next = NULL;

  return multiplicand;
}

/* Create new constant multiplicand, and set default values */
multiplicand_t* create_con_multiplicand(int value) {
  multiplicand_t* multiplicand;
  multiplicand = (multiplicand_t*)malloc(sizeof(multiplicand_t));

  if (multiplicand == NULL) {
	fprintf(stderr, "Unable to allocate memory\n");
	exit(EXIT_FAILURE);
  }
  
  multiplicand->type = CONSTANT;
  multiplicand->value.value = value;
  multiplicand->next = NULL;

  return multiplicand;
}

/* Add new multiplicand to the tail of this list of multiplicands */
void add_multiplicand(multiplicand_t* leading, multiplicand_t* new) {
  if (leading == NULL)
	return;
	
  while (leading->next != NULL) {
	leading = leading->next;	
  }

  leading->next = new;
}

/* Free list of multiplicands */ 
void free_multiplicands_list(multiplicand_t* leading) {
  multiplicand_t* next;

  if (leading == NULL)
	return;
  
  while (leading->next != NULL) {
	next = leading;
	leading = leading->next;
	free(next);
  }

  free(leading);
}

/* Copy multiplicands list */
multiplicand_t* copy_multiplicands_list(multiplicand_t* list) {
  multiplicand_t *copy = NULL, *result = NULL;

  if (list == NULL)
	return result;

  do {
	if (list->type == CONSTANT) {
	  if (copy == NULL) {
		copy = create_con_multiplicand(list->value.value);
		result = copy;
	  }
	  else {
		copy->next = create_con_multiplicand(list->value.value);
		copy = copy->next;
	  }
	}
	if (list->type == VARIABLE) {
	  if (copy == NULL) {
		copy = create_var_multiplicand(list->value.name);
		result = copy;
	  }
	  else {
		copy->next = create_var_multiplicand(list->value.name);
		copy = copy->next;
	  }
	}

	list = list->next;
  } while (list != NULL);

  return result;
}

/* Compare two lists of multiplicands with the same lengths */
int compare_multiplicands_list(multiplicand_t* a, multiplicand_t* b) {
  /* Run througth all elements in list a, and try to find this
	 element in b. If such element is found, it's index in written
	 into array */

  /* Compare lengths */
  if (get_multiplicans_list_length(a) != get_multiplicans_list_length(b))
	return 0;
  
  size_t length = get_multiplicans_list_length(a);  
  int* indexs = (int*)calloc(length, sizeof(int));

  if (indexs == NULL) {
	fprintf(stderr, "Unable to allocate memory\n");
	exit(EXIT_FAILURE);
  }
  
  multiplicand_t* _b = b;
  int found; 

  for (size_t i = 0; i < length; i++) {
	found = 0;
	b = _b;
	for (size_t j = 0; j < length; j++) {
	  if (a->type == b->type && a->value.value == b->value.value && \
		  !indexs[j]) {
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

/* Generate string, that contain all multiplicand in current list */
void print_multiplicands_list(multiplicand_t* multiplicand, char* line) {
  size_t length = strlen(line);
  
  if (multiplicand->type == CONSTANT) {
	length += sprintf(line + length, "%d", multiplicand->value.value);
	
	if (multiplicand->next != NULL) {
	  line[length] = '*';
	  length++;
	}
	
	multiplicand = multiplicand->next;
  }

  while(multiplicand != NULL) {
	if (multiplicand->next == NULL) {
	  line[length] = multiplicand->value.name;
	}
	else {
	  line[length] = multiplicand->value.name;
	  line[length + 1] = '*';
	  length += 2;
	}

	multiplicand = multiplicand->next;
  }
}


/* Allocate new multiplicand list, and add here elements from
   list a, that aren't represented in list b. If list b isn't empty
   by the end. Return NULL, because it means divisor is uncorrect */
multiplicand_t* divide_multiplicands_list(multiplicand_t* dividend,\
										  multiplicand_t* divisor) {
  size_t divisor_length = get_multiplicans_list_length(divisor);
  multiplicand_t *result = NULL, *_divisor, *multiplicand;
  int *indexs = (int*)calloc(divisor_length, sizeof(int)), found, \
	constant_divisor, constant_dividend;
  _divisor = divisor;

  if (indexs == NULL) {
	fprintf(stderr, "Unable to allocate memory\n");
	exit(EXIT_FAILURE);
  }
  
  /* Handle constants */
  if (dividend->type == CONSTANT) {
	constant_dividend = dividend->value.value;
	dividend = dividend->next;
  }
  else {
	constant_dividend = 1;
  }

  if (divisor->type == CONSTANT) {
	constant_divisor = divisor->value.value;
	divisor = divisor->next;
	indexs[0] = 1;
  }
  else {
	constant_divisor = 1;
  }

  /* If constatns aren't divisible evenly */
  if (((double)constant_dividend) / ((double) constant_divisor) - \
	  ((double) (constant_dividend / constant_divisor)) != 0.0){
	return NULL;
  }
  
  else if (constant_dividend  / constant_divisor != 1){
	multiplicand = create_con_multiplicand(constant_dividend / \
										   constant_divisor);
	
	result = multiplicand;
  }

	
  while(dividend != NULL) {
	divisor = _divisor;
	found = 0;

	for (size_t j = 0; j < divisor_length; j++) {
	  if (dividend->value.name == divisor->value.name && \
		  !indexs[j]) {
		indexs[j] = 1;
		found = 1;
	  }

	  divisor = divisor->next;
	}

	if (!found) {
	  if (result == NULL) 
		result = create_var_multiplicand(dividend->value.name);	  
	  else 
		add_multiplicand(result, create_var_multiplicand(dividend->		\
													   value.name));
	}
	
	dividend = dividend->next;
  }

  for (size_t i = 0; i < divisor_length; i++) {
	if (!indexs[i]) {
	  free_multiplicands_list(result);
	  free(indexs);
	  return NULL;
	}
  }

  free(indexs);

  return result;
}

/* Allocate new multiplicand list. To each elements in list,
   add new multiplicand */
multiplicand_t* multiply_multiplicands_list(multiplicand_t* list,\
											multiplicand_t* mul) {
  multiplicand_t *result = NULL, *_mul ;
  size_t mul_length = get_multiplicans_list_length(mul);
  int* indexs = (int*)calloc(mul_length, sizeof(int));
  _mul = mul;

  if (indexs == NULL) {
	fprintf(stderr, "Unable to allocate memory\n");
	exit(EXIT_FAILURE);
  }
  
  while(list != NULL) {
	if (result == NULL) {
	  result = create_var_multiplicand(list->value.name);
	}
	else {
	  add_multiplicand(result, create_var_multiplicand(list->\
													 value.name));
	}

	/* To keep correct order in case of power. (x*y *x == x*x*y)
	   not (x*y *x != x*y*x) */
	mul = _mul;
	for (size_t i = 0; i < mul_length; i++) {
	  if (mul->value.name == list->value.name && !indexs[i]) {
		add_multiplicand(result, create_var_multiplicand(mul->value.name));
		indexs[i] = 1;
	  }

	  mul = mul->next;
	}	

	list = list->next;
  }

  mul = _mul;
  /* Remaining elements */
  for (size_t i = 0; i < mul_length; i++) {
	if (!indexs[i]) {
	  if (result == NULL) {
		result = create_var_multiplicand(mul->value.name);
	  }
	  else {
		add_multiplicand(result, create_var_multiplicand(mul->value.name));
	  }
	}

	mul = mul->next;
  }
  
  free(indexs);

  return result;
} 
