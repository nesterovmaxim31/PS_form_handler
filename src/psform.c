#include <stdio.h> /* puts */

#include "psform.h"
#include "parser.h"
#include "psform_arithmetic.h"

/* Free allocated memory for PS form */
static int psform_free(psform_t* form) {
  for (size_t i = 0; i < form->size; i++) {
	free_multiplicands_list(form->elements->elements);
	form->elements = form->elements->next;
	free(form->elements);
  }

  free(form);
}

/* Print PS form */
static void psform_print(psform_t* form) {
  char* line;
  if (form == NULL) {
	printf("0");
  }
  else {
	line = print_addends_list(form->elements);
	printf("%s\n", line);
	free(line);
  }
}

int main() {
  char* line = NULL;
  int are_equal = 0;
  size_t buf_size;
  ssize_t length;
  operation_t operation;

  /* Form a and b  */
  psform_t *psform_a, *psform_b, *psform_result;
  psform_a = (psform_t*)malloc(sizeof(psform_t));
  psform_a->size = 0;
  psform_a->elements = NULL;
  psform_b = (psform_t*)malloc(sizeof(psform_t));
  psform_b->size = 0;
  psform_b->elements = NULL;

  /* Get operation */
  length = getline(&line, &buf_size, stdin);
  operation = parse_operation(line, length);
  if (operation == UNKNOW_OPERATION) {
	puts("The entered operation is not supported");
	return -1;
  }

  /* Parse two PS form */
  length = getline(&line, &buf_size, stdin);
  if (parse_psform(line, length, psform_a) == -1) {
	puts("Wrong PS form");
	return -1;
  }

  length = getline(&line, &buf_size, stdin);
  if (parse_psform(line, length, psform_b) == -1) {
	puts("Wrong PS form");
	return -1;
  }


  psform_print(psform_a);
  psform_print(psform_b);
  
  switch (operation) {
  case ADDITION:
	psform_result = psform_add(psform_a, psform_b);
	psform_print(psform_result);
	break;
  case SUBTRACTION:
	psform_result = psform_subtract(psform_a, psform_b);
	psform_print(psform_result);
	break;	
  case MULTIPLICATION:
	psform_result = psform_multiply(psform_a, psform_b);
	psform_print(psform_result);
	break;
  case DIVISION: {
	break;
  }
  case COMPARISON: {
	if (psform_compare(psform_a, psform_b)) {
	  printf("equal");
	}
	else {
	  printf("not equal");
	}
  }
	
  }  

  /* Free allocated memory */
  free(line);
  psform_free(psform_a);
  psform_free(psform_b);
  
  return 0;
}
