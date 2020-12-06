/**
 * Multithread solution for checking a Sudoku puzzle
 * Solution to project 1
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_THREADS 	3
#define PUZZLE_SIZE 		9

void* column_worker(void* param); 	/* thread that checks columns */
void* row_worker(void* param); 		/* thread that checks rows */
void* subfield_worker(void* param); 	/* thread that checks subfields */
void traverse(int arr[PUZZLE_SIZE][PUZZLE_SIZE]);

/* example puzzle */
int puzzle[PUZZLE_SIZE][PUZZLE_SIZE] = {

			{5,3,4,6,7,8,9,1,2},
			{6,7,2,1,9,5,3,4,8},
			{1,9,8,3,4,2,5,6,7},
			{8,5,9,7,6,1,4,2,3},
			{4,2,6,8,5,3,7,9,1},
			{7,1,3,9,2,4,8,5,6},
			{9,6,1,5,3,7,2,8,4},
			{2,8,7,4,1,9,6,3,5},
			{3,4,5,2,8,6,1,7,9}
};

int main(int argc, char* argv[])
{
	traverse(puzzle);  //print out the sudoku first
	//Define threads
	pthread_t thread_1;
	pthread_t thread_2;
	pthread_t thread_3;
	//Create threads
	pthread_create(&thread_1, NULL, row_worker, NULL);
	pthread_create(&thread_2, NULL, column_worker, NULL);
	pthread_create(&thread_3, NULL, subfield_worker, NULL);
	//multi-threads wording simultaneously
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	pthread_join(thread_3, NULL);

	printf("\n\nOver...");
	return 0;
}

void* row_worker(void* params)
{
	int i, j, a;
	for (i = 0; i < PUZZLE_SIZE; i++) {	//the outter loop: check for different rows(1-9)

		int temp_flag[10] = { 0,0,0,0,0,0,0,0,0,0 }; //initialize the flags

		for (j = 0; j < PUZZLE_SIZE; j++) {
			if (temp_flag[puzzle[i][j]] == 0) temp_flag[puzzle[i][j]] = 1;	//change the flag of corresponding value to "1"
																									//which means it has already appeared; ep: puzzle[2][2] = 3;
																									//then change puzzle[0][3] = 1;
			else if (temp_flag[puzzle[i][j]] == 1){	//find a repeated number: fail to pass the row check
				printf("\nRow doesn't meat the Sudoku requiremens!   ERROR: (%d, %d)\n", i, j);
				pthread_exit(0);
			}
		}
	}
	//didn't find any repeated number: row check passed
	printf("\nRow meats the Sudoku requirements!");
	//exit the thread
	pthread_exit(0);
}

void* column_worker(void* params)
{
	int i, j, a;
	for (i = 0; i < PUZZLE_SIZE; i++) {	//the outter loop: check for different columnss(1-9)

		int temp_flag[10] = { 0,0,0,0,0,0,0,0,0,0 }; //initialize the column flags

		for (j = 0; j < PUZZLE_SIZE; j++) {
			if (temp_flag[puzzle[j][i]] == 0) temp_flag[puzzle[j][i]] = 1;	//change flag
			else if (temp_flag[puzzle[j][i]] == 1) {	//find a repeated number: fail to pass the column check
				printf("\nColumn doesn't meat the Sudoku requiremens!   ERROR: (%d, %d)\n", i, j);
				pthread_exit(0);
			}
		}
	}
	//didn't find any repeated number: column check passed
	printf("\nColumn meats the Sudoku requirements!");
	pthread_exit(0);
}

void* subfield_worker(void* params)
{
	int i, j, a, b;
	//Outter loop: Convolution moving in the units of 3
	for (i = 0; i < PUZZLE_SIZE; i+=3) {
		for (j = 0; j < PUZZLE_SIZE; j+=3) {
			int temp_flag[10] = { 0,0,0,0,0,0,0,0,0,0 };
			//Inner loop: check for ever sudoku
			for (a = 0; a < 3; a++) {
				for (b = 0; b < 3; b++) {

					if (temp_flag[puzzle[i + a][j + b]] == 0) temp_flag[puzzle[i + a][j + b]] = 1;
					else if (temp_flag[puzzle[i + a][j + b]] == 1) {
						printf("\nSubfield doesn't meat the Sudoku requiremens!   ERROR: (%d, %d)\n", i + a, j + b);
						pthread_exit(0);
					}
				}
			}
		}
	}
	//Sucess
	printf("\nSubfield meats the Sudoku requirements!");
	pthread_exit(0);
}
//traverse the whole sudoku
void traverse(int arr[PUZZLE_SIZE][PUZZLE_SIZE]) {
	int i, j;
	for (i = 0; i < PUZZLE_SIZE; i++) {
		for (j = 0; j < PUZZLE_SIZE; j++) {
			printf("%d ", puzzle[i][j]);
		}
		printf("\n");
	}
}
