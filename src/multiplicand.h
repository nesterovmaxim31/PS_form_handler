#ifndef MULTIPLICAND_H
#define MULTIPLICAND_H

/* PSF consists of addends, and addends consists of multiplicands*/

/* enum for two possible type of multiplicand - constant of variable*/
typedef enum  {CONSTANT, VARIABLE} multiplicand_type;

/* If multiplicand is variable, it's value is a variable's name,
   if multiplicand is constant, it's value is a constant's value */
typedef union {
  char name;
  int val;
} multiplicand_value_t;

/* Each multiplicand consists of it's value, type and
   pointer to next multiplicand */
typedef struct multiplicand_st{
  multiplicand_type type;
  multiplicand_value_t value;
  struct multiplicand_st* next;
} multiplicand_t;

/* function prototype */


#endif
