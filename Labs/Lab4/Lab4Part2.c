#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// function to convert binary to decimal
int convertBinaryToDecimal (int inputBinary){
	// declaring variables
	int currentBinary, remainder, newDecimal, exponent;

    // initializing variables
    exponent = 0;
    newDecimal = 0;
    currentBinary = inputBinary;

	// calculating decimal number from binary using modulo and storing result in "newDecimal"
    while (currentBinary != 0){
        remainder = currentBinary % 10;
        newDecimal = newDecimal + remainder * pow(2, exponent);
        currentBinary = (currentBinary - remainder) / 10;
        exponent++;
    }
    
	// returning the decimal number
    return newDecimal;
}

// function to convert decimal to binary
int convertDecimalToBinary (int inputDecimal){
	// declaring variables
	int currentDecimal, remainder, newBinary, exponent;
	
	// initializing variables
	exponent = 0;
	newBinary = 0;
	currentDecimal = inputDecimal;
	
	// calculating binary number from decimal using modulo and storing result in "newBinary"
	while (currentDecimal != 0){
	    remainder = currentDecimal % 2;
	    newBinary = newBinary + remainder * pow(10, exponent);
	    currentDecimal = (currentDecimal - remainder) / 2;
	    exponent++;
	}
	
	// returning the binary number
	return newBinary;
}



int main(int argc, char **argv)
{
	// Declaring variables
	char inputCommand;
	int inputNumber, outputNumber;
	
	// Prompting for user input
	printf("Enter B for conversion of Binary to Decimal, OR\n");
	printf("Enter D for conversion of Decimal to Binary: ");
	scanf(" %c", &inputCommand);
	printf("Enter your number: ");

	// Converting number and outputting result
	// Converting binary to decimal
	if (inputCommand == 'B'){
    	scanf("%d", &inputNumber);
		outputNumber = convertBinaryToDecimal(inputNumber);
		printf("%d in binary = %d in decimal\n", inputNumber, outputNumber);
	}
	
	// Converting decimal to binary
	else if (inputCommand == 'D'){
    	scanf("%d", &inputNumber);
		outputNumber = convertDecimalToBinary(inputNumber);
		printf("%d in decimal = %d in binary\n", inputNumber, outputNumber);
	}
	
	// User did not enter either of the 'B' or 'D' commands
	else {
	    printf("Invalid input; Goodbye\n");
	}
	
	return 0;
}