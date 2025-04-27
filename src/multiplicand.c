#include <stdlib.h> /* malloc calloc free */
#include <string.h>
#include <stdio.h>

#include "multiplicand.h"

/* Create new variable multiplicand, and set default values */
multiplicand_t* create_var_multiplicand(char name) {
  multiplicand_t* multiplicand;
  multiplicand = (multiplicand_t*)malloc(sizeof(multiplicand_t));

  multiplicand->type = VARIABLE;
  multiplicand->value.name = name;
  multiplicand->next = NULL;

  return multiplicand;
}

/* Create new constant multiplicand, and set default values */
multiplicand_t* create_con_multiplicand(int value) {
  multiplicand_t* multiplicand;
  multiplicand = (multiplicand_t*)malloc(sizeof(multiplicand_t));

  multiplicand->type = CONSTANT;
  multiplicand->value.value = value;
  multiplicand->next = NULL;

  return multiplicand;
}

/* Add new multiplicand to the tail of this list of multiplicands */
void add_multiplicand(multiplicand_t* leading, multiplicand_t* new) {  
  while (leading->next != NULL) {
	leading = leading->next;	
  }

  leading->next = new;
}

/* Free list of multiplicands */ 
void free_multiplicands_list(multiplicand_t* leading) {
  multiplicand_t* next;
  
  if (leading->next != NULL) {
	next = leading->next;
	free(leading);
	free_multiplicands_list(next);
  }
}

/* Copy multiplicands list */
multiplicand_t* copy_multiplicands_list(multiplicand_t* list) {
  multiplicand_t *copy = NULL, *result;

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
int compare_multiplicands_list(multiplicand_t* a, multiplicand_t* b, \
							   size_t length) {
  /* Run througth all elements in list a, and try to find this
	 element in b. If such element is found, it's index in written
	 into array */

  int* indexs = (int*)calloc(length, sizeof(int));
  multiplicand_t* _b = b;
  int found; 

  for (size_t i = 0; i < length; i++) {
	found = 0;
	b = _b;
	for (size_t j = 0; j < length; j++) {
	  if (a->type == b->type && a->value.value == b->value.value && !indexs[j]) {
		indexs[j] = 1;
		found = 1;
		break;
	  }

	  b = b->next;
	}

	/* Return 0, if this element from list a, isn't found in list b */
	if (!found) {
	  return 0;
	}
	
	a = a->next;
  }
  
  free(indexs);
  
  return 1;
}


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
