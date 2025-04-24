#include <stdio.h>

#include "psform.h"
#include "parser.h"
#include "psform_arithmetic.h"


int main() {
  char* line = NULL;
  size_t buf_size, length;
  operation_t operation;

  /* Get operation */
  length = getline(&line, &buf_size, stdin);
  operation = parse_operation(line);
  if (operation == UNKNOW_OPERATION) {
	puts("The entered operation is not supported");
	return -1;
  }  
  
  free(line);
  
  return 0;
}
