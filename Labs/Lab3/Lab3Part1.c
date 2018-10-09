#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	// Declaring variables
	int inputAmount, newInput, quarters, dimes, nickels, cents, nextPunc;
	
	// Prompts user to input number of cents
	printf("Please give an amount in cents less than 100: ");
	scanf ("%d", &inputAmount);
	
	// Loop which exists when user inputs a valid amount within the range of 1-99 cents
	while ((inputAmount <= 99) && (inputAmount >= 1)) {
		
		// Initializing variables
		quarters = 0;
		dimes = 0;
		nickels = 0;
		cents = 0;
		nextPunc = 0;
		
		// Calculates the number of each coin 
		newInput = inputAmount;
		
		// To calculate the number of each coin, highest number of the highest denomination is found
		// then the remainder amount is used for the next highest denomination
		
		// Calculating number of quarters
		while (newInput >= 25) {
			newInput = newInput - 25;
			quarters = quarters + 1;
		}
		
		// Calculating number of dimes
		while (newInput >= 10) {
			newInput = newInput - 10;
			dimes = dimes + 1;
		}
		
		// Calculating number of nickels
		while (newInput >= 5) {
			newInput = newInput - 5;
			nickels = nickels + 1;
		}
		
		// Calculating number of cents
		while (newInput >= 1) {
			newInput = newInput - 1;
			cents = cents + 1;
		}
		
		// Determines output
		printf("%d cents: ", inputAmount);

		// quarters output
		if (quarters == 1) {
			printf("%d quarter", quarters);
			nextPunc = 1;
		} else if (quarters > 1) {
			printf("%d quarters", quarters);
			nextPunc = 1;
		}
		
		// dimes output
		if (dimes == 1) {
			if (nextPunc == 1) {
				printf(", ");
				nextPunc = 0;
			}
			printf("%d dime", dimes);
			nextPunc = 1;
		} else if (dimes > 1) {
			if (nextPunc == 1) {
				printf(", ");
				nextPunc = 0;
			}
			printf("%d dimes", dimes);
			nextPunc = 1;
		}
		
		// nickels output
		if (nickels == 1) {
			if (nextPunc == 1) {
				printf(", ");
				nextPunc = 0;
			}
			printf("%d nickel", nickels);
			nextPunc = 1;
		} else if (nickels > 1) {
			if (nextPunc == 1) {
				printf(", ");
				nextPunc = 0;
			}
			printf("%d nickels", nickels);
			nextPunc = 1;
		}
		
		// cents output
		if (cents == 1) {
			if (nextPunc == 1) {
				printf(", ");
				nextPunc = 0;
			}
			printf("%d cent", cents);
			nextPunc = 1;
		} else if (cents > 1) {
			if (nextPunc == 1) {
				printf(", ");
				nextPunc = 0;
			}
			printf("%d cents", cents);
			nextPunc = 1;
		}
		
		printf(".\n");
		
		// Prompts user to input number of cents
		printf("Please give an amount in cents less than 100: ");
		scanf ("%d", &inputAmount);
	} 
	
	printf("Goodbye.\n");

	return 0;
}
