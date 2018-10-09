#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Prototypes to declare functions
int factorial (int);
int choose (int, int);
void spaces (int, int);
void triangle (int);

// Main program asking for user input and displaying triangle until user enters a negative number
int main(int argc, char **argv)
{
	// Declaring variables
	int inputRows = 0;
	int numRows = 0;
	
	// Program runs until user inputs a negative number
	while (inputRows >= 0){
	    // Prompt for user input
	    printf("Enter the number of rows: ");
	    scanf ("%d", &inputRows);
	    numRows = inputRows - 1;
	    
	    // Displays triangle
	    triangle(numRows);
	}
	return 0;
}


// Calculates n factorial
int factorial (int n){
	// Declaring variables
	int i;
	
	// Initializing variables
	int nFactorial = 1;
	
	// Calculating the factorial
	for (i = 1; i <= n; i++){
		nFactorial = nFactorial * i;
	}
	
	return nFactorial;
}

// Performs the choose function as nCr
int choose (int n, int r){
	// Declaring variables
	int chooseResult;
	
	// Performing the choose calculation
	chooseResult = factorial(n) / (factorial(r) * factorial(n - r));
	
	return chooseResult;
}

// Prints number of spaces before first item of specified row
void spaces (int rowNum, int totalRows){
	// Delaring counter variable
	int i;
	
	// Initializing variables
	int numSpaces = 0;
	
	// Should only print spaces if the row number is less than the total number of rows
	if (rowNum < totalRows){
		numSpaces = 3 * (totalRows - rowNum);
		
		// Printing the number of spaces
		for (i = 1; i <= numSpaces; i++){
			printf(" ");
		}
	}
}

// Function to display a pascal's triangle, given the row number
void triangle (int rowInput){
	// Declaring variables
	int i, j, currentNum;
	
	// to traverse down each row
	for (i = 0; i <= rowInput; i++){
		spaces(i, rowInput);
		
		// to traverse across a row
		for (j = 0; j <= i; j++){
			currentNum = choose(i, j);
			printf("%-6d", currentNum);
		}
		printf("\n");
		
	}
}