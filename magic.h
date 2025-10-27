#ifndef MAGIC_H
#define MAGIC_H

#define N 5      /* square size */
#define N_MIN 2  /* minimal allowed square size */

#define YES 1
#define NO 0
#define TRUE YES
#define FALSE NO

#define STACK_EMPTY -1
#define STACK_FULL -1000

/* exit codes */
#define ERROR_INPUT -1
#define EXIT_OK 0

#define MAX_ALLOWED_NUMS N*N
#define MAX_NUMBER N*N
#define DECIMAL_BASE 10
#define MAX_ALLOWED_CHARS 1000
#define MIN_ALLOWED_CHARS 0
#define ZERO_CHAR '0'
#define NEGATIVE_SYMBOL '-'

/* forward declaration */
void print_square(int [][N]);
int is_magic(int [][N]);

int get_input_square(int magic[][N]);

#endif
