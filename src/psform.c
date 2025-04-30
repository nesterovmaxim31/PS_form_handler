#include <stdio.h>  /* puts printf fprintf fflush */
#include <stdlib.h> /* size_t malloc free */

#ifdef ENABLE_BENCHMARK_OPERATION
#include <time.h>
#endif

#include "psform.h"
#include "parser.h"
#include "psform_arithmetic.h"

/* Free allocated memory for PS form */
static void psform_free(psform_t* form) {
  if (form == NULL)
	return;

  free_addends_list(form->elements);

  free(form);
}

/* Print PS form */
static void psform_print(psform_t* form) {
  char* line = NULL;
  if (form == NULL || form->size == 0) {
	printf("0");
  }
  else {
	line = print_addends_list(form->elements);
	printf("%s", line);
	free(line);
  }
}


int main() {
  char* line = NULL;
  size_t buf_size;
  ssize_t length;
  operation_t operation;

  /* Form a and b */
  psform_t *psform_a = NULL, *psform_b = NULL, *psform_result = NULL;
  psform_a = (psform_t*)malloc(sizeof(psform_t));
  psform_a->size = 0;
  psform_a->elements = NULL;
  
  psform_b = (psform_t*)malloc(sizeof(psform_t));
  psform_b->size = 0;
  psform_b->elements = NULL;

  /* If memory allocation is failed */ 
  if (psform_a == NULL || psform_b == NULL) {
	fprintf(stderr, "Unable to allocate memory\n");
	free(psform_a);
	free(psform_b);
	exit(EXIT_FAILURE);
  }
  
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
	psform_free(psform_a);
	psform_free(psform_b);
	puts("Wrong PS form");
	return -1;
  }

  length = getline(&line, &buf_size, stdin);
  if (parse_psform(line, length, psform_b) == -1) {
	puts("Wrong PS form");
	psform_free(psform_a);
	psform_free(psform_b);
	return -1;
  }

  /* Benchmark only time of execution operation,
	 not of all program*/
#ifdef ENABLE_BENCHMARK_OPERATION
  float startTime = (float)clock()/CLOCKS_PER_SEC;
#endif
  
  /* Perform operation */
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
	psform_result = psform_divide(psform_a, psform_b);
	if (psform_result == NULL)
	  printf("error");
	else
	  psform_print(psform_result);	  
	break;
  }
  case COMPARISON: {
	if (psform_compare(psform_a, psform_b)) {
	  printf("equal");
	}
	else {
	  printf("not equal");
	}
	break;
  }
  default:	
	break;
  }  

  /* Output time of execution operation */
#ifdef ENABLE_BENCHMARK_OPERATION
  float endTime = (float)clock()/CLOCKS_PER_SEC;
  fflush(stdout);
  fprintf(stderr, "It took %f to perform math operation\n\n", \
		  endTime - startTime);
#endif
  
  /* Free allocated memory */
  free(line);
  psform_free(psform_a);
  psform_free(psform_b);
  psform_free(psform_result);
  
  return 0;
}
