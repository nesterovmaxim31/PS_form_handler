#include <ctype.h>  /* isdigit isalpha */
#include <string.h> /* bzero */
#include <stdlib.h> /* size_t*/

#include "parser.h"
#include "addend.h" 


/* Parse first line, and return operation */
operation_t parse_operation(const char* line, ssize_t length) {
  if (length <= 0)
	return UNKNOW_OPERATION;
  
  switch (line[0]) {
  case '+':
	return ADDITION;
  case '-':
	return SUBTRACTION;
  case '*':
	return MULTIPLICATION;
  case '/':
	return DIVISION;
  case '=':
	return COMPARISON;
  default:
	return UNKNOW_OPERATION;
  }
}


/* Parse line, and create PS form
   If return -1 -> error during parsing */
int parse_psform(const char* line, ssize_t length, psform_t* form) {
  size_t i = 0;
  addend_t* addend = init_addend();
  multiplicand_t* multiplicand;

  /* string buffer, to store value, during parsing */  
  char buffer[1024];
  bzero(buffer, 1024);
  /* Max unsigned integer is 10 symbols in length in decimal,
	 so, i believe 1024 chars would be enough */
	
  /* This to state control behavior of a program */
  int is_digit = 0;
  
  if (length <= 0)
	return -1;

  for (i = 0; i < length; i++) {
	/* If digit isn't started  */
	if (!is_digit) {
	  /* Skip if space */
	  if (line[i] == ' ') {
		continue;
	  }

	  /* If digit, set is_digit to 1 and add to buffer */
	  else if (isdigit(line[i])) {
		is_digit = 1;
		buffer[0] = line[i];
	  }

	  /* If alpha, add new multiplicand */
	  else if (isalpha(line[i])) {
		multiplicand = create_var_multiplicand(line[i]);
		addend->size++;
		ADD_MULTIPLICAND(addend, multiplicand);
	  }

	  /* If plus (+), create new addend */
	  else if (line[i] == '+') {
		/* Add addent to psform */
		form->size++;
		ADD_ADDEND(form, addend);

		/* And create new addend */
		addend = init_addend();
	  }

	  /* If minus (-), create new negative addend */
	  else if (line[i] == '-') {
		/* If this minus before first addend, then make it negative */
		if (form->size == 0 && addend->size == 0) {
		  addend->sign = NEGATIVE;
		}
		
		/* Else, create new negative addend */
		else {
		  /* Add addent to psform */
		  form->size++;
		  ADD_ADDEND(form, addend);

		  /* And create new addend */
		  addend = init_addend();
		  addend->sign = NEGATIVE;
		}
	  }

	  /* If asterisk (*), add new multiplicand */
	  else if (line[i] == '*') {
	  
	  }
	} /* End if digit */

	/* If digit is started, one by one, new digits are
	   inserting in buffer. */
	else if (is_digit) {
	  /* If space or newline, digit is over */
	  if (line[i] == ' ' || line[i] == '\n') {
		is_digit = 0;
		/* Create new multiplicand and add it to current addent */
		multiplicand = create_con_multiplicand(atoi(buffer));
		ADD_MULTIPLICAND(addend, multiplicand);
		addend->size++;

		bzero(buffer, 1024);
	  }

	  /* If digit, add it in buffer */
	  else if (isdigit(line[i])) {
		buffer[strlen(buffer)] = line[i];
	  }

	  /* Alpha  can't occur in this situation
		 according to the condition */


	  /* If plus (+), digit is over, create new addend */
	  else if (line[i] == '+') {
		is_digit = 0;

		multiplicand = create_con_multiplicand(atoi(buffer));
		ADD_MULTIPLICAND(addend, multiplicand);
		addend->size++;
		bzero(buffer, 1024);

		/* Add addent to psform */
		form->size++;
		ADD_ADDEND(form, addend);

		/* And create new addend */
		addend = init_addend();
	  }

	  /* If minus (-), digit is over,
		 create new negative addend */	  
	  else if (line[i] == '-') {
		is_digit = 0;

		multiplicand = create_con_multiplicand(atoi(buffer));
		ADD_MULTIPLICAND(addend, multiplicand);
		addend->size++;
		bzero(buffer, 1024);

		/* Add addent to psform */
		form->size++;
		ADD_ADDEND(form, addend);

		/* And create new addend */
		addend = init_addend();
		addend->sign = NEGATIVE;
	  }

	  /* If asterisk (*), digit is over */
	  else if (line[i] == '*') {
		is_digit = 0;
		multiplicand = create_con_multiplicand(atoi(buffer));
		ADD_MULTIPLICAND(addend, multiplicand);
		addend->size++;
		bzero(buffer, 1024);
	  }
	} /* End if digit */
  }

  /* If last addend isn't empty, add it to form */
  if (addend->size != 0) {
	form->size++;
	ADD_ADDEND(form, addend);
  }
  else {
	free(addend);
  }
  
  return 0;
}
