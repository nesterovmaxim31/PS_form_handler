#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h> /* size_t */

#include "psform.h"

/* All operations program can perform with PS forms */
typedef enum {ADDITION, SUBTRACTION, MULTIPLICATION, \
			  DIVISION, COMPARISON, UNKNOW_OPERATION} operation_t;

/* function prototype */
operation_t parse_operation(const char*, ssize_t);
int parse_psform(const char*, ssize_t, psform_t*);

#endif
