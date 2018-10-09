#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Prototypes to declare functions
void initializeBoard(char board[][26], int n);
void printBoard(char board[][26], int n);
bool positionInBounds(int n, char row, char col);
char opponentColour(char colour);
bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
void printAllLegalSpots(char board[][26], int n, char colour);
void flipPieces(char board[][26], int n, char colour, char rowMove, char colMove);

// Main program which asks user for board size & allows user to enter a move
int main(int argc, char **argv)
{
    // Declaring/initializing local variables
    int boardDimension;
    char inputColour, inputRow, inputCol;
	char board[26][26];
    
    // Prompts user for board size
    printf("Enter the board dimension: ");
    scanf("%d", &boardDimension);
    
	// Initializes original board and displays it
    initializeBoard(board, boardDimension);
    printBoard(board, boardDimension);
	
	// Prompts user for board configuration
	printf("Enter board configuration:\n");
	do {
		scanf(" %c%c%c", &inputColour, &inputRow, &inputCol);
		board[inputRow - 'a'][inputCol - 'a'] = inputColour;
	} while ((inputColour != '!') && (inputRow != '!') && (inputCol != '!'));
	
	// Displays current board configuration
	printBoard(board, boardDimension);

	// Printing moves in all 8 directions for white
	printf("Available moves for W:\n");
	inputColour = 'W';
	printAllLegalSpots(board, boardDimension, inputColour);
	
	// Printing moves in all 8 directions for black
	printf("Available moves for B:\n");
	inputColour = 'B';
	printAllLegalSpots(board, boardDimension, inputColour);
	
	// Prompts user for move
	printf("Enter a move:\n");
	scanf(" %c%c%c", &inputColour, &inputRow, &inputCol);
	
	// Performs move if valid, otherwise prints invalid move
	flipPieces(board, boardDimension, inputColour, inputRow, inputCol);
	
	// Prints current state of board after move
	printBoard(board, boardDimension);

    return 0;
}


// Determines initial positions of pieces when board is first initialized
void initializeBoard(char board[][26], int n){
    // Initializing variables
    int topLeft = n / 2 - 1;
    int bottomRight = n / 2;
    int i = 0;
    int j = 0;
    
    // To make board initially empty
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            board[i][j] = 'U';
        }
    }
    
    // To place center pieces
    board [topLeft][topLeft] = 'W';
    board [topLeft][bottomRight] = 'B';
    board [bottomRight][topLeft] = 'B';
    board [bottomRight][bottomRight] = 'W';
}

// Prints board
void printBoard(char board[][26], int n){
    // Initializing variables
    int i = 0;
    int j = 0;
    
    // Printing first row
    printf("  ");
    for (i = 0; i < n; i++){
        printf("%c", ('a' + i));
    }
    
    // Printing rows after first header row
    // To traverse down each row
    for (i = 0; i < n; i++){
        printf("\n%c ", ('a'+i));
        // To traverse across each row
        for (j = 0; j < n; j++){
            printf("%c", board[i][j]);
        }
    }
	printf ("\n");
}


// Checks whether specific location (row, col) is in bounds of the board
bool positionInBounds(int n, char row, char col){
    if ((row < 'a' + n) && (col < 'a' + n) && (row >= 'a') && (col >= 'a')){
        return true;
    }
	// If not in bounds, returns false
    return false;
}

// Returns opponent colour
char opponentColour(char colour){
	if (colour == 'B'){
		return 'W';
	}
	else if (colour == 'W'){
		return 'B';
	}
	// Returns blank if empty
	else {
		return 'U';
	}
}

// Checks whether (row, col) is a legal position for the given tile colour
bool checkLegalInDirection(char board[][26], int n, char row, char col,
                           char colour, int deltaRow, int deltaCol){
		
	// Initializing variables used to check if direction is legal and count # of opponents
	int r = row - 'a' + deltaRow;
	int c = col - 'a' + deltaCol;
	int opponentNum = 0;
	
	while ((positionInBounds(n, r + 'a', c + 'a')) && (board[r][c] == opponentColour(colour))){
		r = r + deltaRow;
		c = c + deltaCol;
		opponentNum++;
	}
	
	// Legal move in direction if more than 1 opponent in that direction and ends on own square
	if (opponentNum > 0){
		// Check if next space is in bounds and same colour and board is empty at current position
		if ((positionInBounds(n, r + 'a', c + 'a')) && (board[r][c] == colour) && (board[row - 'a'][col - 'a'] == 'U')){
			return true;
		}
	}
	
	// Otherwise illegal move in direction
	return false;
}


// Prints legal moves for a given colour
void printAllLegalSpots(char board[][26], int n, char colour){
	// Declaring and initializing variables
	int r, c, cRow, cCol;
	int isLegal = 0;
	
	// Traverses through board checking if each spot is valid
	for (r = 0; r < n; r++){
		for (c = 0; c < n; c++){
			
			// Legal when legal in one direction or more
			isLegal = 0;
			for (cRow = -1; cRow <= 1; cRow++){
				for (cCol = -1; cCol <= 1; cCol++){
					if (((cRow != 0) || (cCol != 0)) && (checkLegalInDirection(board, n, r + 'a', c + 'a', colour, cRow, cCol))){
						isLegal++;
					}
				}
			}
			
			// Prints position if there is one or more legal directions
			if (isLegal > 0){
				printf("%c%c\n", r + 'a', c + 'a');
			}
		}
	}
}

// Function to flip pieces on board when given a valid row and column to place the piece
void flipPieces(char board[][26], int n, char colour, char rowMove, char colMove){
	// Declaring variables for use in for loops
	int cRow, cCol;
	
	// Initializing temporary row and column positions for flipping and whether move is valid
	int tempRow = 0;
	int tempCol = 0;
	bool isValid = false;
	
	// Only valid move if spot is empty and is legal in a direction
	// Only enters if spot is empty
	if (board[rowMove - 'a'][colMove - 'a'] == 'U'){
		
		// Checks all direction for legal moves
		for (cRow = -1; cRow <= 1; cRow++){
			for (cCol = -1; cCol <= 1; cCol++){
				
				// Checks if legal in direction, if so flips pieces in direction
				if (((cRow != 0) || (cCol != 0)) && (checkLegalInDirection(board, n, rowMove, colMove, colour, cRow, cCol))){
					// Is legal in a direction
					isValid = true;
					
					// Sets temporary position
					tempRow = rowMove - 'a' + cRow;
					tempCol = colMove - 'a' + cCol;
					
					// Flips pieces in the direction
					while ((positionInBounds(n, tempRow + 'a', tempCol + 'a')) && (board[tempRow][tempCol] == opponentColour(colour))){
						// Flips current piece
						board[tempRow][tempCol] = colour;
						
						// Increments temporary positions to traverse direction
						tempRow = tempRow + cRow;
						tempCol = tempCol + cCol;
					}
				}
			}
		}
		
		// Prints whether move is valid or not
		if (isValid){
			// Flips current piece
			board[rowMove - 'a'][colMove - 'a'] = colour;
			
			printf("Valid move.\n");
		}
		// Move is not valid
		else if (isValid == false){
			printf("Invalid move.\n");
		}
	}
}