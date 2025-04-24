#include <stdio.h> /* puts */

#include "psform.h"
#include "parser.h"
#include "psform_arithmetic.h"


int main() {
  char* line = NULL;
  size_t buf_size;
  ssize_t length;
  operation_t operation;

  /* Form a and b  */
  psform_t *psform_a, *psform_b;
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
  parse_psform(line, length, psform_b);  

  printf("%zu %zu", psform_a->size, psform_b->size);
  
  free(line);
  
  return 0;
}
