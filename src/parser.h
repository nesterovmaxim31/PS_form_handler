#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h> /* size_t */

#include "psform.h"
#include "addend.h"
#include "multiplicand.h"

/* All operations program can perform with PS forms */
typedef enum {ADDITION, SUBTRACTION, MULTIPLICATION, \
			  DIVISION, COMPARISON, UNKNOW_OPERATION} operation_t;


/* function prototype */
operation_t parse_operation(const char*, ssize_t);
int parse_psform(const char*, ssize_t, psform_t*);


#define ADD_MULTIPLICAND(addend, multiplicand)			\
  if (addend->elements == NULL)							\
	addend->elements = multiplicand;					\
  else													\
	add_multiplicand(addend->elements, multiplicand);	\


#define ADD_ADDEND(form, addend)								\
  if (addend->size > 1 && addend->elements->value.value == 1) { \
	addend->elements = addend->elements->next;					\
	addend->size--;												\
  }																\
  if (form->elements == NULL)									\
	form->elements = addend;									\
  else															\
	add_addend(form->elements, addend);


#endif
