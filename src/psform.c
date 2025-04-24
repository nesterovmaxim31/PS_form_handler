#include <stdio.h>

#include "psform.h"
#include "parser.h"
#include "psform_arithmetic.h"


int main() {
  char* line = NULL;
  size_t buf_size, length;
  operation_t operation;
    
  length = getline(&line, &buf_size, stdin);

  

  free(line);
  
  return 0;
}
