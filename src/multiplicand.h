#ifndef MULTIPLICAND_H
#define MULTIPLICAND_H

/* PSF consists of addends, and addends consists of multiplicands*/

/* enum for two possible type of multiplicand - constant of variable*/
typedef enum  {CONSTANT, VARIABLE} multiplicand_type;

/* If multiplicand is variable, it's value is a variable's name,
   if multiplicand is constant, it's value is a constant's value */
typedef union {
  char name;
  int value;
} multiplicand_value_t;

/* Each multiplicand consists of it's value, type and
   pointer to next multiplicand */
typedef struct multiplicand_st{
  multiplicand_type type;
  multiplicand_value_t value;
  struct multiplicand_st* next;
} multiplicand_t;

/* function prototype */
multiplicand_t* create_var_multiplicand(char); /* Create variable
												  multiplicand*/
multiplicand_t* create_con_multiplicand(int); /* Create constant
												  multiplicand */
multiplicand_t* copy_multiplicands_list(multiplicand_t*);
multiplicand_t* divide(multiplicand_t*, multiplicand_t*);
multiplicand_t* multiply(multiplicand_t*, multiplicand_t*);
void add_multiplicand(multiplicand_t*, multiplicand_t*); /* Add
												new multiplicand in list */ 
void free_multiplicands_list(multiplicand_t*); /* Recursively free
												  all elements in list */

int compare_multiplicands_list(multiplicand_t*, multiplicand_t*); 

void print_multiplicands_list(multiplicand_t*, char*); 

#endif
