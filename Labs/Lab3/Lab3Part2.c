#include <stdio.h>
#include <stdlib.h>
	
// declaring variables
double firstNumber, secondNumber, solution;
char operator;

int main(int argc, char **argv)
{
	
	// Prompting for user input of two numbers and a calculation command
	printf("Enter first number: ");
    scanf("%lf", &firstNumber);
    printf("Enter second number: ");
    scanf("%lf", &secondNumber);
    printf("Enter calculation command (one of a, s, m, or d): ");
    scanf(" %c", &operator);


	// Performing the calculations and outputting the result
    // addition
	if (operator == 'a'){
        solution = firstNumber + secondNumber;
        printf("Sum of %.2lf and %.2lf is %.2lf\n", firstNumber, secondNumber, solution);
    }
	
	// subtraction
	else if (operator == 's'){
        solution = firstNumber - secondNumber;
        printf("Difference of %.2lf from %.2lf is %.2lf\n", firstNumber, secondNumber, solution);
    }
	
	// multiplication
	else if (operator == 'm'){
	    solution = firstNumber * secondNumber;
        printf("Product of %.2lf and %.2lf is %.2lf\n", firstNumber, secondNumber, solution);
    } 
	
	// division
	else if (operator == 'd'){
        if (secondNumber == 0) {
			// If user attempts to divide a number by zero, an error message displays
            printf("Error, trying to divide by zero\n");
			
        } else {
            solution = firstNumber / secondNumber;
            printf("Division of %.2lf by %.2lf is %.2lf\n", firstNumber, secondNumber, solution);
        }
		
    }
	
	// If a user enters an unknown calculation command, then an error displays
	else {
        printf("Error, unknown calculation command given\n");
    }

	return 0;
}
