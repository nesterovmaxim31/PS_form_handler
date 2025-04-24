#ifndef PARSER_H
#define PARSER_H

/* All operations program can perform with PS forms */
typedef enum {ADDITION, SUBTRACTION, MULTIPLICATION, \
			  DIVISION, COMPARISON, UNKNOW_OPERATION} operation_t;

/* function prototype */

operation_t parse_operation(const char*);

#endif
