#include <stdlib.h> /* malloc calloc size_t */
#include <string.h> /* bzero */

#include "addend.h"
#include "multiplicand.h"

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

/* Compare two lists of addends with the same lengths */
int compare_addends_list(addend_t* a, addend_t* b, size_t length) {
  /* Run througth all elements in list a, and try to find this
	 element in b. If such element is found, it's index in written
	 into array */

  int* indexs = (int*)calloc(length, sizeof(int));
  addend_t* _b = b;
  int found; 

  for (size_t i = 0; i < length; i++) {
	found = 0;
	b = _b;
	for (size_t j = 0; j < length; j++) {
	  if (a->size == b->size && a->sign == b->sign && \
		  compare_multiplicands_list(a->elements, b->elements, a->size) \
		  && !indexs[j]) {
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

/* Print addends list */
char* print_addends_list(addend_t* addend) {
  multiplicand_t* multiplicand = addend->elements;
  char* line = (char*)malloc(1024);
  bzero(line, 1024);
  size_t length = 1024;
  
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
  copy->next = addend->next;
}
