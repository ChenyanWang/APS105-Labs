#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
	// Declaring variables
	const double TOTAL_INPUT = 3.0;
	double inputNumber1, inputNumber2, inputNumber3;
	double mean, standardDeviation;

	// Prompts user input of three numbers
	printf("Enter three numbers: ");
	scanf("%lf%lf%lf", &inputNumber1, &inputNumber2, &inputNumber3);
	
	// Calculating the mean and standard deviation
	mean = (inputNumber1 + inputNumber2 + inputNumber3) / TOTAL_INPUT;
	standardDeviation = sqrt((pow((inputNumber1 - mean), 2) + pow((inputNumber2 - mean), 2) + pow((inputNumber3 - mean), 2)) / (TOTAL_INPUT - 1));

	// Output of mean and standard deviation
	printf("The mean is %.2lf and the standard deviation is %.2lf \n", mean, standardDeviation);
	
	return 0;
}