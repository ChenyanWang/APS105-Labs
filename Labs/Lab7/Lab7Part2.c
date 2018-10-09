#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
//#include "lab7part2lib.h"

// Prototypes to declare functions
void initializeBoard(char board[][26], int n);
void printBoard(char board[][26], int n);
bool positionInBounds(int n, char row, char col);
char opponentColour(char colour);
bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
bool moveValid(char board[][26], int n, char colour, char row, char col);
void flipPieces(char board[][26], int n, char colour, char rowMove, char colMove);
int numValidMoves(char board[][26], int n, char colour);
bool colourValidMoves(char board[][26], int n, char colour);
bool gameOn(char board[][26], int n);
int scoreColour(char board[][26], int n, char colour);
void copyBoard(char destBoard[][26], char initBoard[][26], int n);
int colourCorners(char board[][26], int n, char colour);
int scoreSpot (char board[][26], int n, char colour, char testRow, char testCol);
int returnBestScore(char board[][26], int n, char colour);
void computerMove(char board[][26], int n, char comColour);
bool humanMove(char board[][26], int n, char humColour);
char returnWinner(char board[][26], int n);

// Main program which asks user for board size & allows user to enter a move
int main(int argc, char **argv)
{
	// Declaring/initializing local variables
    int boardDimension;
	char board[26][26];
	char humColour, comColour;
	char currentTurn = 'B';
	bool gameOver = false;
	bool humanInvalidMove = false;
	
    // Prompts user for board size and computer colour
    printf("Enter the board dimension: ");
    scanf("%d", &boardDimension);
    printf("Computer plays (B/W): ");
	scanf(" %c", &comColour);
	
	// Determines human colour
	humColour = opponentColour(comColour);
	
	// Initializes original board and displays it
    initializeBoard(board, boardDimension);
    printBoard(board, boardDimension);
	
	// Continues while there is a valid move for either colour and player has not made an invalid move
	while (gameOn(board, boardDimension) && !gameOver){
		//Runs while there is valid moves
		if (colourValidMoves(board, boardDimension, currentTurn)){
			if (comColour == currentTurn){
				// Computer turn
				computerMove(board, boardDimension, comColour);
				printBoard(board, boardDimension);
				currentTurn = opponentColour(currentTurn);
			}
			else if (humColour == currentTurn){
				// Human turn
				if (humanMove(board, boardDimension, humColour)){
					// Human move is performed and colour changes
					currentTurn = opponentColour(currentTurn);
				    printBoard(board, boardDimension);
				} else {
					// Human move is invalid, game ends
					printf("Invalid move.\n");
					humanInvalidMove = true;
					gameOver = true;
				}
			}
		}
		// Checks if other colour has valid moves
		else if (colourValidMoves(board, boardDimension, opponentColour(currentTurn))){
			// Current colour has no vaild moves, opponent colour has valid moves, switches colour
			printf("%c player has no valid move.\n", currentTurn);
			currentTurn = opponentColour(currentTurn);
		}
		else {
			// No valid moves available
			gameOver = true;
		}	
	}
	
	// Displays winner
	if (!humanInvalidMove){
		// Human move was valid
		if (returnWinner(board, boardDimension) != 'T'){
			// Game is not a tie
			printf("%c player wins.\n", returnWinner(board, boardDimension));
		}
		else {
			// Game is a tie
			printf("Draw!\n");
		}
	}
	else {
		// Human made an invalid move, computer wins
		printf("%c player wins.\n", comColour);
	}
	
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

// Checks whether input move is valid for colour
bool moveValid(char board[][26], int n, char colour, char row, char col){
	// Declaring and initializing variables
	int cRow, cCol;
	int isLegal = 0;
	
	// Legal when legal in one direction or more
	isLegal = 0;
	
	// Checks all directions
	for (cRow = -1; cRow <= 1; cRow++){
		for (cCol = -1; cCol <= 1; cCol++){
			if (((cRow != 0) || (cCol != 0)) && (checkLegalInDirection(board, n, row, col, colour, cRow, cCol))){
				isLegal++;
			}
		}
	}
			
	// Move position is valid if there is one or more legal directions
	if (isLegal > 0){
		return true;
	}
	// If the spot is not empty, or is illegal in all directions, then move is false
	else {
		return false;
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
		
		// If move is valid, flips piece
		if (isValid){
			// Flips current piece
			board[rowMove - 'a'][colMove - 'a'] = colour;
		}
	}
}

// Returns number of valid moves on board
int numValidMoves(char board[][26], int n, char colour){
	// Declaring/initializing variables
	int i, j;
	int validMoves = 0;
	
	// Traverse board to check if there are any moves valid for current colour
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			if (moveValid(board, n, colour, i + 'a', j + 'a')){
				// Move is valid
				validMoves++;
			}
		}
	}
	return validMoves;
}

// Returns true if specified colour has any valid moves on board
bool colourValidMoves(char board[][26], int n, char colour){
	// Initializing variable
	int validMoves = 0;
	
	// To calculate # of valid moves
	validMoves = (numValidMoves(board, n, colour));
	
	// Returns true if there is a valid move for colour
	if (validMoves > 0){
		// Game is not over
		return true;
	}
	else {
		return false;
	}
}

// Returns true if either colour has a valid move
bool gameOn(char board[][26], int n){
	// Game over if both colours have no moves
	// If move is invalid, then game is also over (checked in moveValid function)
	
	if ((colourValidMoves(board, n, 'B')) || (colourValidMoves(board, n, 'W'))){
		// Game is not over if either colour has valid moves
		return true;
	}
	else {
		return false;
	}
}

// Counts number of colour on board
int scoreColour(char board[][26], int n, char colour){
	// Traverses board and counts specified colour
	// Declaring/initializing variables
	int i, j;
	int colourCount = 0;
	
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			if (board[i][j] == colour){
				colourCount++;
			}
		}
	}
	
	// Returns number of colour
	return colourCount;
}

// Copies board from initial to destination
void copyBoard(char destBoard[][26], char initBoard[][26], int n){
	// Declaring variables
	int i, j;
	
	// Copying current board into test board
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			destBoard[i][j] = initBoard [i][j];
		}
	}
}

// Scores spot based off of # of tiles flipped if placed there
int scoreSpot (char board[][26], int n, char colour, char testRow, char testCol){
	// Declaring/initializing variables;
	// Score is # of other colour tiles flipped
	int score, preMoveTiles, postMoveTiles;
	char testBoard[26][26];
	
	// Calculating # of tiles before move and copying current board into test board
	preMoveTiles = scoreColour(board, n, colour);
	copyBoard(testBoard, board, n);

	// Performing move in test board if valid, and calculating # of tiles after move
	if (moveValid(testBoard, n, colour, testRow, testCol)){
		flipPieces(testBoard, n, colour, testRow, testCol);
	}
	postMoveTiles = scoreColour(testBoard, n, colour);
	
	// Calculates and returns score
	score = postMoveTiles - preMoveTiles;
	
	return score;
}


int returnBestScore1(char board[][26], int n, char colour){
	int testRow, testCol;
	int tempScore = 0;
	int bestScore = 0;
		
	// Traverse through board
	for (testRow = 0; testRow < n; testRow ++){
		for (testCol = 0; testCol < n; testCol ++){
			// Checks if move is valid for computer
			if (moveValid(board, n, colour, testRow + 'a', testCol + 'a')){
				tempScore = scoreSpot(board, n, colour, testRow + 'a', testCol + 'a');
				// Checks if current spot score is better than the current "best spot" score
				if (tempScore > bestScore){
					// Test spot is better than the current best spot, update the best spot
					bestScore = tempScore;
				}
			}
		}
	}
	
	return bestScore;
}

// Recursive function to return best score after first level
int returnBestScoreRecursive(char board[][26], int n, char colour, int level){
	int testRow, testCol;
	int tempScore;
	int bestScore = -999999;
	char testBoard[26][26];
	
	if (level == 0){
		return returnBestScore1(board, n, colour);
	}
	
	// Copies board
	copyBoard(testBoard, board, n);
	
	// Traverse through board
	for (testRow = 0; testRow < n; testRow ++){
		for (testCol = 0; testCol < n; testCol ++){
			// Checks if move is valid for computer
			if (moveValid(testBoard, n, colour, testRow + 'a', testCol + 'a')){
				// Makes move then calculates score
				tempScore = scoreSpot(testBoard, n, colour, testRow + 'a', testCol + 'a');
				flipPieces(testBoard, n, colour, testRow + 'a', testCol + 'a');
				tempScore = tempScore - returnBestScoreRecursive(testBoard, n, opponentColour(colour), level - 1);
				
				// Copies board
				copyBoard(testBoard, board, n);
				
				// Checks if current spot score is better than the current "best spot" score
				if (tempScore > bestScore){
					// Test spot is better than the current best spot, update the best spot
					bestScore = tempScore;
				}
			}
		}
	}
	if (bestScore == -999999) {
		return 0;
	}
	return bestScore;
}


// Performs best move for computer (in terms of most tiles turned)
// Function only called when there is a valid move for computer
void computerMove(char board[][26], int n, char comColour){
	// Traverses through all spots, and plays spot with highest score
	// Declares/initializes variables
	int testRow, testCol, bestRow, bestCol;
	int tempScore;
	int bestScore = -999999;
	char testBoard[26][26];
	
	// Copies board onto test board
	copyBoard(testBoard, board, n);
	
	// Traverse through board
	for (testRow = 0; testRow < n; testRow ++){
		for (testCol = 0; testCol < n; testCol ++){
			// Checks if move is valid for computer
			if (moveValid(testBoard, n, comColour, testRow + 'a', testCol + 'a')){
				// Makes move then calculates score
				tempScore = scoreSpot(testBoard, n, comColour, testRow + 'a', testCol + 'a');
				flipPieces(testBoard, n, comColour, testRow + 'a', testCol + 'a');
				tempScore = tempScore - returnBestScoreRecursive(testBoard, n, opponentColour(comColour), 3);
				
				// Copies board
				copyBoard(testBoard, board, n);
				
				// Checks if current spot score is better than the current "best spot" score
				if (tempScore > bestScore){
					// Test spot is better than the current best spot, update the best spot
					bestScore = tempScore;
					bestRow = testRow;
					bestCol = testCol;
				}
			}
		}
	}
		
	// If "best position" is a valid spot on board, performs move
	if (moveValid(board, n, comColour, bestRow + 'a', bestCol + 'a')){
		printf("Computer places %c at %c%c.\n", comColour, bestRow + 'a', bestCol + 'a');
		flipPieces(board, n, comColour, bestRow + 'a', bestCol + 'a');
	}
	
}

// Asks and performs human move if valid, if move is invalid, returns false
bool humanMove(char board[][26], int n, char humColour){
	// Declaring variables
	char inputRow, inputCol;
	
	printf("Enter move for colour %c (RowCol): ", humColour);
	scanf(" %c%c", &inputRow, &inputCol);

/*
	// Used to test with liblab7part2.a
	int row, col;
	findSmartestMove(board, n, humColour, &row, &col);
	inputRow = row + 'a'; inputCol = col + 'a';
	printf("%c%c\n", inputRow, inputCol);
*/
	if (moveValid(board, n, humColour, inputRow, inputCol)){
		// Performs move if valid
		flipPieces(board, n, humColour, inputRow, inputCol);
		return true;
	}
	else {
		// Move is invalid
		return false;
	}
	
}

// Determines winner of game
char returnWinner(char board[][26], int n){
	if (scoreColour(board, n, 'B') > scoreColour(board, n, 'W')){
		// Black wins
		return 'B';
	}
	else if (scoreColour(board, n, 'W') > scoreColour(board, n, 'B')){
		// White wins
		return 'W';
	}
	else {
		// Tie
		return 'T';
	}
}