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
/* Create variable multiplicand */
multiplicand_t* create_var_multiplicand(char);
/* Create constant multiplicand */
multiplicand_t* create_con_multiplicand(int);
/* Allocate and copy multiplicands list */
multiplicand_t* copy_multiplicands_list(multiplicand_t*);
/* Allocate and divide two multiplicands lists */
multiplicand_t* divide_multiplicands_list(multiplicand_t*,\
                                          multiplicand_t*);
/* Allocate and multiply two multiplicands lists*/
multiplicand_t* multiply_multiplicands_list(multiplicand_t*,\
                                            multiplicand_t*);

/* Add new multiplicand in list */ 
void add_multiplicand(multiplicand_t*, multiplicand_t*);
/* Recursively free all elements in list */
void free_multiplicands_list(multiplicand_t*);

/* Get length of multiplicands list */
size_t get_multiplicans_list_length(multiplicand_t*);

/* Compare two multiplicands lists */
int compare_multiplicands_list(multiplicand_t*, multiplicand_t*); 

/* Generate string with all multiplicands in list */
void print_multiplicands_list(multiplicand_t*, char*); 

#endif
