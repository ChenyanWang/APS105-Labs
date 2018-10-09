#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    // Declaring variables
    char inputBand1, inputBand2, inputMultiplier, inputTolerance;
    double resistance, tolerance, newResistance;
    
    // Asking for user input for band colours
    printf("Please enter the 1st band:\n");
    scanf(" %c", &inputBand1);
    printf("Please enter the 2nd band:\n");
    scanf(" %c", &inputBand2);
    printf("Please enter the multiplier band:\n");
    scanf(" %c", &inputMultiplier);
    printf("Please enter the tolerance band:\n");
    scanf(" %c", &inputTolerance);
    
    // Printing resistor band colours in words and calculating resistance
    printf("Resistor bands:");
    
    // 1st band output
    if ((inputBand1 == 'k') || (inputBand1 == 'K')){
        printf(" Black");
        resistance = resistance + 0 * 10;
    } else if ((inputBand1 == 'b') || (inputBand1 == 'B')){
        printf(" Brown");
        resistance = resistance + 1 * 10;
    } else if ((inputBand1 == 'r') || (inputBand1 == 'R')){
        printf(" Red");
        resistance = resistance + 2 * 10;
    } else if ((inputBand1 == 'o') || (inputBand1 == 'O')){
        printf(" Orange");
        resistance = resistance + 3 * 10;
    } else if ((inputBand1 == 'e') || (inputBand1 == 'E')){
        printf(" Yellow");
        resistance = resistance + 4 * 10;
    } else if ((inputBand1 == 'g') || (inputBand1 == 'G')){
        printf(" Green");
        resistance = resistance + 5 * 10;
    } else if ((inputBand1 == 'u') || (inputBand1 == 'U')){
        printf(" Blue");
        resistance = resistance + 6 * 10;
    } else if ((inputBand1 == 'v') || (inputBand1 == 'V')){
        printf(" Violet");
        resistance = resistance + 7 * 10;
    } else if ((inputBand1 == 'y') || (inputBand1 == 'Y')){
        printf(" Grey");
        resistance = resistance + 8 * 10;
    } else if ((inputBand1 == 'w') || (inputBand1 == 'W')){
        printf(" White");
        resistance = resistance + 9 * 10;
    }
    
    // 2nd band output
    if ((inputBand2 == 'k') || (inputBand2 == 'K')){
        printf(" Black");
        resistance = resistance + 0;
    } else if ((inputBand2 == 'b') || (inputBand2 == 'B')){
        printf(" Brown");
        resistance = resistance + 1;
    } else if ((inputBand2 == 'r') || (inputBand2 == 'R')){
        printf(" Red");
        resistance = resistance + 2;
    } else if ((inputBand2 == 'o') || (inputBand2 == 'O')){
        printf(" Orange");
        resistance = resistance + 3;
    } else if ((inputBand2 == 'e') || (inputBand2 == 'E')){
        printf(" Yellow");
        resistance = resistance + 4;
    } else if ((inputBand2 == 'g') || (inputBand2 == 'G')){
        printf(" Green");
        resistance = resistance + 5;
    } else if ((inputBand2 == 'u') || (inputBand2 == 'U')){
        printf(" Blue");
        resistance = resistance + 6;
    } else if ((inputBand2 == 'v') || (inputBand2 == 'V')){
        printf(" Violet");
        resistance = resistance + 7;
    } else if ((inputBand2 == 'y') || (inputBand2 == 'Y')){
        printf(" Grey");
        resistance = resistance + 8;
    } else if ((inputBand2 == 'w') || (inputBand2 == 'W')){
        printf(" White");
        resistance = resistance + 9;
    }
    
    // multiplier band output
    if ((inputMultiplier == 'k') || (inputMultiplier == 'K')){
        printf(" Black");
        resistance = resistance * 1;
    } else if ((inputMultiplier == 'b') || (inputMultiplier == 'B')){
        printf(" Brown");
        resistance = resistance * 10;
    } else if ((inputMultiplier == 'r') || (inputMultiplier == 'R')){
        printf(" Red");
        resistance = resistance * 100;
    } else if ((inputMultiplier == 'o') || (inputMultiplier == 'O')){
        printf(" Orange");
        resistance = resistance * 1000;
    } else if ((inputMultiplier == 'e') || (inputMultiplier == 'E')){
        printf(" Yellow");
        resistance = resistance * 10000;
    } else if ((inputMultiplier == 'g') || (inputMultiplier == 'G')){
        printf(" Green");
        resistance = resistance * 100000;
    } else if ((inputMultiplier == 'u') || (inputMultiplier == 'U')){
        printf(" Blue");
        resistance = resistance * 1000000;
    } else if ((inputMultiplier == 'v') || (inputMultiplier == 'V')){
        printf(" Violet");
        resistance = resistance * 10000000;
    } else if ((inputMultiplier == 'l') || (inputMultiplier == 'L')){
        printf(" Gold");
        resistance = resistance * 0.1;
    } else if ((inputMultiplier == 's') || (inputMultiplier == 'S')){
        printf(" Silver");
        resistance = resistance * 0.01;
    }
    // tolerance band output
    if ((inputTolerance == 'b') || (inputTolerance == 'B')){
        printf(" Brown\n");
        tolerance = 1;
    } else if ((inputTolerance == 'r') || (inputTolerance == 'R')){
        printf(" Red\n");
        tolerance = 2;    
    } else if ((inputTolerance == 'g') || (inputTolerance == 'G')){
        printf(" Green\n");
        tolerance = 0.5;
    } else if ((inputTolerance == 'u') || (inputTolerance == 'U')){
        printf(" Blue\n");
        tolerance = 0.25;
    } else if ((inputTolerance == 'v') || (inputTolerance == 'V')){
        printf(" Violet\n");
        tolerance = 0.10;
    } else if ((inputTolerance == 'y') || (inputTolerance == 'Y')){
        printf(" Grey\n");
        tolerance = 0.05;
    } else if ((inputTolerance == 'l') || (inputTolerance == 'L')){
        printf(" Gold\n");
        tolerance = 5;
    } else if ((inputTolerance == 's') || (inputTolerance == 'S')){
        printf(" Silver\n");
        tolerance = 10;
    }
    
    // Outputting results
    if (resistance >= 1000000){
        newResistance = resistance / 1000000;
        printf("Resistance: %.2lf MOhms +/- %.2lf%%", newResistance, tolerance);
    } else if ((resistance >= 1000) && (resistance < 1000000)) {
        newResistance = resistance / 1000;
        printf("Resistance: %.2lf KOhms +/- %.2lf%%", newResistance, tolerance);
    } else if (resistance < 1000) {
        newResistance = resistance;
        printf("Resistance: %.2lf Ohms +/- %.2lf%%", newResistance, tolerance);
    }
    
    
    return 0;
}
