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

/* Parse strind and return operation */
operation_t parse_operation(const char*, ssize_t);

/* Create PS form from string */
int parse_psform(const char*, ssize_t, psform_t*);

/* Macro to add new multiplicand to addend list of multiplicands */
#define ADD_MULTIPLICAND(addend, multiplicand)                  \
    if (addend->elements == NULL)                               \
        addend->elements = multiplicand;                        \
    else                                                        \
        add_multiplicand(addend->elements, multiplicand);       \

/* Macro to add new addend to PS form list of addends.
   It check, if first multiplicand is 1, and delete it */
#define ADD_ADDEND(form, addend)                                        \
    multiplicand_t* deleted = NULL;                                     \
    if (addend->size > 1 && addend->elements->value.value == 1) {       \
        deleted = addend->elements;                                     \
        addend->elements = addend->elements->next;                      \
        free(deleted);                                                  \
        addend->size--;                                                 \
    }                                                                   \
    if (form->elements == NULL)                                         \
        form->elements = addend;                                        \
    else                                                                \
        add_addend(form->elements, addend);                             \


#endif
