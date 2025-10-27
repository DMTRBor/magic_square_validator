#include <stdio.h>
#include <stdlib.h>
#include "magic.h"


/**
 * helper function - receives 1D
 * array of integers, that is a
 * row in 2D array, computes the
 * sum of the row and returns it.
*/
int calc_row_sum(int arr[]) {
    int col;
	int sum = 0;
	
	/* size of row is N (square width) */
    for (col = 0; col < N; col++) {
        sum += arr[col];
    }
    return sum;
}


/**
 * helper function - receives 1D
 * array of integers and a column
 * index, computes the sum of this
 * column, and returns it.
*/
int calc_col_sum(int arr[][N], int col) {
    int row;
	int sum = 0;
	
	/* size of column is N (square height) */
    for (row = 0; row < N; row++) {
        sum += arr[row][col];
    }
    return sum;
}


/**
 * helper function - receives 2D
 * square array of integers, checks
 * if all rows in the array have an
 * equal sum. If the sum in all rows
 * is equal, a code that represents
 * equality is returned, otherwise
 * inequality code returned -
 * YES=1, NO=0
*/
int is_all_rows_sum_equal(int magic[][N]) {
    int row = 0;
	int row_sum;
	int prev_row_sum;
    /* get sum of first row */
    prev_row_sum = calc_row_sum(magic[row]);

    /* compare sum to the rest of the rows */
    for (row = 1; row < N; row++) {
        row_sum = calc_row_sum(magic[row]);
        /* check if rows sums are equal */
        if (prev_row_sum != row_sum)
            return NO;
        prev_row_sum = row_sum;
    }
    return YES;
}


/**
 * helper function - receives 2D
 * square array of integers, checks
 * if all columns in the array have an
 * equal sum. If the sum in all columns
 * is equal, a code that represents
 * equality is returned, otherwise
 * inequality code returned -
 * YES=1, NO=0
*/
int is_all_cols_sum_equal(int magic[][N]) {
	int col = 0;
	int col_sum;
	int prev_col_sum;
    /* get sum of first column */
    prev_col_sum = calc_col_sum(magic, col);

    /* compare sum to the rest of the columns */
    for (col = 1; col < N; col++) {
        col_sum = calc_col_sum(magic, col);

        if (prev_col_sum != col_sum)
            return NO;
        prev_col_sum = col_sum;
    }
    return YES;
}


/**
 * helper function - receives 2D
 * square array of integers, checks
 * if both diagonals in the array 
 * have an equal sum. If the sum in
 * both is equal, a code that represents
 * equality is returned, otherwise
 * inequality code returned -
 * YES=1, NO=0
*/
int is_diagonals_sum_equal(int magic[][N]) {
    int row;
	int col;
	int primary_diagonal_sum = 0;
	int secondary_diagonal_sum = 0;
    
    for (row = 0; row < N; row++) {
        /* add to secondary diagonal sum*/
        secondary_diagonal_sum += magic[row][N-row-1];

        for (col = 0; col < N; col++) {
            /* add to primary diagonal sum*/
            if (row == col)
                primary_diagonal_sum += magic[row][col];
        }
    }
    /* check if diagonals sums are equal */
    if (primary_diagonal_sum != secondary_diagonal_sum)
        return NO;
    return YES;
}


/**
 * helper function - comparison function
 * for qsort to compare elements in array.
 * Receives two pointers to array elemtnts
 * and returns the difference between them.
*/
int compare(const void *elem1, const void *elem2) {
    return (*(int*)elem1 - *(int*)elem2);
}


/**
 * helper function - receives 2D
 * square array of integers, checks
 * if all array elements are unique.
 * Returns YES(=1) if all elements are
 * uniques, otherwise returns NO(=0).
*/
int is_all_numbers_unique(int magic[][N]) {
    int flat_arr_size = MAX_ALLOWED_NUMS;
	/* dyn-allocate 1D array for flattening 2D array */
	int *flat_arr = (int*)malloc(flat_arr_size * sizeof(int));
	int row;
	int col;
	int i_flat = 0;
	
	/* flatten the square array*/
	for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            flat_arr[i_flat++] = magic[row][col];
        }
    }
	
	/* sort the flattened array using quicksort (O(nlogn)) */
	qsort(flat_arr, flat_arr_size, sizeof(int), compare);

	/* check in sorted array if consecutive elements duplicated */
	for (i_flat = 1; i_flat < flat_arr_size; i_flat++) {
        if (flat_arr[i_flat] == flat_arr[i_flat-1]) {
            free(flat_arr);  /* free the dyn-allocated memory */
            return NO;  /* duplicated element found - not unique */
        }
    }
	
	free(flat_arr);  /* free dyn-allocate memory*/
	return YES;
}


/**
 * helper function - receives 2D
 * square array of integers, checks
 * if the array is a basic magic square -
 * all array elements are unique and
 * the sum in all rows, columns and
 * diagonals is equal. If the sum is
 * equal, a code that represents
 * equality is returned, otherwise
 * inequality code returned.
*/
int is_magic(int magic[][N]) {
    return is_all_numbers_unique(magic) &&
		   is_all_rows_sum_equal(magic) &&
           is_all_cols_sum_equal(magic) &&
           is_diagonals_sum_equal(magic);
}


/**
 * helper function - receives 2D
 * square array of integers and
 * prints the array in a matrix
 * manner, i.e rows and columns.
*/
void print_square(int magic[][N]) {
	int row;
	int col;
    printf("\nThe received square is:\n\n");

    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            printf("%d\t", magic[row][col]);
        }
        printf("\n");  /* go to next row in new line */
    }
    printf("\n");
}
