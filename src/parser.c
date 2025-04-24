#include "parser.h"

/* Parse first line, and return operation */
operation_t parse_operation(const char* line) {
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



