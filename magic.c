#include <stdio.h>
#include "magic.h"


/**
 * The program asks for an input
 * that could represent a square
 * array of natural numbers, and
 * checks if the square array is
 * a magic square - equal sum in
 * each row, column and diagonal.
 * The array has dimensions of NxN.
 * Returns status code for success
 * and failure within magic square
 * input and computation.
*/
int main() {
    int magic_square[N][N];
    int is_input_valid;
	
	/* Exclude matrices under minimal dimensions (2x2) */
	if (N < N_MIN) {
		printf("Matrix size is less than minimum allowed: %d < %d. Abort!\n", N, N_MIN);
		return ERROR_INPUT;
	}

    is_input_valid = get_input_square(magic_square);
    if (is_input_valid == ERROR_INPUT)
        return ERROR_INPUT;

    print_square(magic_square);

    if (is_magic(magic_square) == NO)
        printf("This is not a magic square!\n");
    else
        printf("This is a magic square!\n");
    
    return EXIT_OK;
}
