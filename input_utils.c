#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "magic.h"


/* stack storage and pointer to element */
static char stack[MAX_ALLOWED_CHARS];
static int stack_ptr = 0;
/* count received valid numbers */
static int count_nums = 0;


/**
 * helper function - the function
 * receives a character and pushes
 * character to stack, only if the the
 * stack is not full. If the stack 
 * is full, return appropriate status
 * code that the stack is full. Otherwise,
 * return ok status code and push the character.
*/
int push(int ch) {
	if (stack_ptr < MAX_ALLOWED_CHARS){  /* check if stack is not full */
    	stack[stack_ptr++] = ch;
		return EXIT_OK;
	}
	else {
		printf("Error! The input element is too big!\n");
		return STACK_FULL;
	}
}


/**
 * helper function - pop character
 * from stack. Returns the element
 * from stack if the stack is not
 * empty, otherwise, returns empty
 * stack return code.
*/
int pop() {
    if (stack_ptr > MIN_ALLOWED_CHARS)  /* check if stack is not empty */
        return stack[--stack_ptr];
    return STACK_EMPTY;
}


/**
 * helper function - the function
 * receives 2D square array, row and
 * column and inserts an integer number
 * into it, only if a valid integer
 * could be inserted. Otherwise,
 * do nothing. Returns 1 if the
 * input inserted, otherwise 0.
*/
int insert_input(int magic[][N], int row, int col) {
    int ch;
    int num = 0;
    int power = 0;
	int is_number_received = NO;  /* valid input indication flag */
    
	/* use stack to construct the number from user input chars */
    while ((ch = pop()) != STACK_EMPTY) {
        if (ch == NEGATIVE_SYMBOL) /* take care of negative integers input */
            num *= -1;
        else {
			/* insert each digit in number on it's place */
            ch -= ZERO_CHAR;
            num += (ch * pow(DECIMAL_BASE, power));
            power++;
        }
		is_number_received = YES;
    }
	
	if (is_number_received) {  /* insert if the input is valid */
		magic[row][col] = num;
		count_nums++;
	}

	return is_number_received; 
}


/**
 * helper function - receives an
 * empty 2D square array and (if
 * no errors) fills it with integer
 * numbers. The function returns a
 * status code that indicates if the
 * array was filled successfully or
 * if there was an error - not an
 * integer input, not enough numbers
 * to fill the array or too many
 * numbers.
*/
int get_input_square(int magic[][N]) {
    int ch;
	int row = 0;
	int col = 0;

    printf("Please enter %d numbers from 1 to %d to create a magic square:\n\n", MAX_ALLOWED_NUMS, MAX_NUMBER);

    while((ch = getchar()) != EOF) {
        if (isspace(ch)) {  /* skip whitespaces */
			/* row ended, go to next row */
            if (col == N) {
                row++;
                col = 0;
            }
            
			/* try to insert input to array - if suceeded, go to next element */
			if (insert_input(magic, row, col))
            	col++;

            continue;
        }
      
        if (!isdigit(ch)) {
            if (ch == NEGATIVE_SYMBOL) {  /* take care of negative numbers */
                if (push(ch) == EXIT_OK)
                	continue;
				return ERROR_INPUT;
            }
            printf("\nError! One or more characters are not an integer! Abort!\n");
            return ERROR_INPUT;
        }
        
        if (count_nums > MAX_ALLOWED_NUMS-1) {
            printf("\nError! Too many numbers received!\n");
            return ERROR_INPUT;
        }
        
        if (push(ch) == STACK_FULL)
			return ERROR_INPUT;
    }

    if (count_nums < MAX_ALLOWED_NUMS-1) {
        printf("\nError! Not enough numbers received! Abort!\n");
        return ERROR_INPUT;
    }
	
    return EXIT_OK;
}
