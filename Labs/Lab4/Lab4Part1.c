#include <stdio.h>
#include <stdlib.h>

// function to print an individual row of a triangle, given the current row number and the total number of rows
void printTriangleRow (int rowNumber, int totalRows){
	// declaring counter variable, i
	int i;
	
	// to print first row
	if (rowNumber == 1){
		for (i = 1; i < totalRows; i++){
			printf(" ");
		}
		printf("^");
	}
	
	// to print middle rows
	else if (rowNumber > 1 && rowNumber < totalRows){
		for (i = 1; i < (totalRows - (rowNumber - 1)); i++){
			printf(" ");
		}
		printf("^");
		for (i = 1; i <= (2 * rowNumber - 3); i++){
			printf(" ");
		}
		printf("^");
	}
	
	// to print last row
	else if (rowNumber == totalRows){
		for (i = 1; i <= (2 * totalRows - 1); i++){
			printf("^");
		}
	}
}


int main(int argc, char **argv)
{
	// declaring variables
	int inputRows, rowCounter;

	// asking for user input
	printf("Enter the number of rows in the triangle: ");
	scanf("%d", &inputRows);
	
	// printing the triangle
	for (rowCounter = 1; rowCounter <= inputRows; rowCounter++){
		printTriangleRow(rowCounter, inputRows);
		printf("\n");
	}

	return 0;
}