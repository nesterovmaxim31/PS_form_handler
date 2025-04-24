#include <stdlib.h> /* malloc */

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
