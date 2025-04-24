#include <stdlib.h> /* malloc free */

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
