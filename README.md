# Product-Summ Form interpreter
This project implements a interpreter for performing arithmetic operations on PS-Forms (Product-Sum Forms), a symbolic representation of arithmetic expressions as sums of products. PS-Forms are used in optimizing compilers to represent computations symbolically, supporting operations like addition, subtraction, multiplication, division, and equality comparison.

## Overview
A PS-Form represents an arithmetic expression as a sum of products, using only the operators +, -, and *. For example:
```
8 + x - 5*y + 3*x*y
```
Here, x and y are variables, and the expression adheres to the following canonical form constraints:
- Each addend (term) has at most one constant multiplicand, which appears at the beginning of the term.
- The PS-Form is not simplified (e.g., x + y is canonical, but 2*x + y - x is not, as it simplifies to x + y).
- Parentheses are not used, and exponentiation is represented as repeated multiplication (e.g., x * x * x for x^3)

The order of addends and multiplicands within an expression does not affect equivalence (e.g., x + y * z, y * z + x, and z * y + x are equivalent).
This interpreter supports the following operations on pairs of PS-Forms:
- Addition: Combines two PS-Forms into a new PS-Form.
- Subtraction: Subtracts one PS-Form from another.
- Multiplication: Multiplies two PS-Forms.
- Division: Divides a PS-Form by another PS-Form containing exactly one term (summand).
- Equality Comparison: Checks if two PS-Forms are equivalent, accounting for the commutative property of terms and factors

We will consider only PS-Forms in canonical form, which have the following properties:
- Constant multiplicands in addends can only appear at the beginning of the term; as a result, each term can have only one constant multiplicand.
- The PS-Form is not simplified, meaning no terms can be combined or canceled; for example:
x + y is in canonical form. 2*x + y - x is NOT in canonical form (as it can be simplified to x + y).

## Build
To build interpreter clone the repository:
``` bash
git clone https://github.com/nesterovmaxim31/PS_form_handler.git
```
Navigate to the project directory:
```bash
cd PS_form_handler
```
Run autoconf and configure:
``` bash
autoconf
./configure
```
And run make:
``` bash
make -j8
```
To start interpreter run:
```bash
./prog
```
or 
```bash
make run
```

## Usage
Read three input strings: operation (+, -, *, /, =), PS-Form 1, and PS-Form 2.
Example:
```
-
a + 3*y - b
-1*x + 3*y - 5*z
```
Output:
```
a - b + x + 5*z
```

## Debug and tests
For run tests:
```bash
make test
```
Test's input and output data are located in directory ./test.

### Sanitizers and benchmark
To run program with benchmark or saniterzers resteart ./configure script with specific flag. (Run 
```bash
./configure --help
``` 
and check for 'Optional Features').
After reconfigure run 
```bash
make run
```
or
```bash
make test
```
## Clean
To delete service files run:
```bash
make clean
```
or
```bash
make distclean
```

## License
This project is licensed under the GPLv3 License. See the LICENSE file for details.
