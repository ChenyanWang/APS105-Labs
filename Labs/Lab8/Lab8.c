/*
 * APS105 Lab 8 Lab8.c
 * 
 * This is a program written to maintain a personal music library, 
 * using a linked list to hold the songs in the library.
 * 
 * Author: Chen Yan Wang
 * 
 * Student Number: 1004101777
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
    char *artist ;
    char *songName ;
    char *genre ;
    struct node *nextNode ;
} Node;

// Declarations of linked list functions
Node* insertSong (Node *listHead);
void printSong(Node *songPrinted);
void printMusicLibrary (Node *listHead);
void searchMusicLibrary (Node *listHead, char *inputName);
Node *deleteSong (Node *listHead, char *songToDelete);
Node *deleteLibrary (Node *listHead);

// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser( char prompt[], char s[], int arraySize ) ;
void songNameDuplicate( char songName[] ) ;
void songNameFound( char songName[] ) ;
void songNameNotFound( char songName[] ) ;
void songNameDeleted( char songName[] ) ;
void artistFound( char artist[] ) ;
void artistNotFound( char artist[] ) ;
void printMusicLibraryEmpty( void ) ;
void printMusicLibraryTitle( void ) ;

const int MAX_LENGTH = 1024;

int main( void ) {
    // Declare the head of the linked list.
    Node *listHead = NULL;

    // Announce the start of the program
    printf( "Personal Music Library.\n\n" ) ;
    printf( "%s", "Commands are I (insert), D (delete), S (search by song name),\n"
         "P (print), Q (quit).\n" ) ;
    
    char response ;
    char input[ MAX_LENGTH + 1 ] ;

    do {
        inputStringFromUser( "\nCommand", input, MAX_LENGTH ) ;

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper( input[0] ) ;

        if( response == 'I' ) {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
			listHead = insertSong(listHead);

        }
        else if( response == 'D' ) {
            // Delete a song from the list.

            char *prompt = "\nEnter the name of the song to be deleted" ;
			inputStringFromUser(prompt, input, MAX_LENGTH);
            //   Deletes song
			listHead = deleteSong(listHead, input);
        }
        else if( response == 'S' ) {
            // Search for a song by its name.
			
			// Prompts for song name
            char *prompt = "\nEnter the name of the song to search for" ;
			inputStringFromUser(prompt, input, MAX_LENGTH);
			// Searches for song
			searchMusicLibrary(listHead, input);

        }
        else if( response == 'P' ) {
            // Print the music library.

			printMusicLibrary(listHead);

        }
        else if( response == 'Q' ) {
            ; // do nothing, we'll catch this below
        }
        else {
            // do this if no command matched ...
            printf( "\nInvalid command.\n" ) ;
        }
    } while( response != 'Q' ) ;
  
    // Delete the entire linked list.
    listHead = deleteLibrary(listHead);

    // Print the linked list to confirm deletion.
    printMusicLibrary(listHead);

    return 0 ;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char prompt[], char s[], int maxStrLength) {
    int i = 0;
    char c;
    
    printf( "%s --> ", prompt ) ;
    while( i < maxStrLength && (c = getchar()) != '\n' )
        s[i++] = c ;
    s[i] = '\0' ;
}

// Function to call when the user is trying to insert a song name 
// that is already in the personal music library.
void songNameDuplicate( char songName[] ) {
    printf( "\nA song with the name '%s' is already in the music library.\n"
            "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound( char songName[] ) {
    printf( "\nThe song name '%s' was found in the music library.\n",
           songName ) ;
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound( char songName[] ) {
    printf( "\nThe song name '%s' was not found in the music library.\n",
           songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted( char songName[] ) {
    printf( "\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf( "\nThe music library is empty.\n" ) ;
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) {
    printf( "\nMy Personal Music Library: \n" ) ;
}

// Add your functions below this line.
// Function for inserting a song
Node *insertSong (Node *listHead){
	char *promptName = "Song name";
    char *promptArtist =  "Artist";
	char *promptGenre = "Genre";
	char inputName[MAX_LENGTH + 1];
	char inputArtist[MAX_LENGTH + 1];
	char inputGenre[MAX_LENGTH + 1];
	Node *tempNode = malloc(sizeof(Node));
	Node *tempPointer = listHead;
	
	// Getting song info
	printf("\n");
	inputStringFromUser(promptName, inputName, MAX_LENGTH);
	inputStringFromUser(promptArtist, inputArtist, MAX_LENGTH);
	inputStringFromUser(promptGenre, inputGenre, MAX_LENGTH);
	
	// Putting song info into tempNode
	tempNode -> songName = strcpy(malloc(strlen(inputName + 1)), inputName);
	tempNode -> artist = strcpy(malloc(strlen(inputArtist + 1)), inputArtist);
	tempNode -> genre = strcpy(malloc(strlen(inputGenre + 1)), inputGenre);
	tempNode -> nextNode = NULL;
	
	// Checks if list is empty
	if (tempPointer == NULL){
		return tempNode;
	}
	// List is not empty; checks if first song is a duplicate
	else if (strcmp(tempPointer -> songName, tempNode -> songName) == 0){
		// Duplicate song
		songNameDuplicate(tempNode -> songName);
		return listHead;
	}
	// Checks if song should be inserted before first song
	else if (strcmp(tempNode -> songName, tempPointer -> songName) < 0){
		tempNode -> nextNode = tempPointer;
		return tempNode;
	}
	// Song should be inserted into the middle/end of list
	else {
		while (tempPointer != NULL){
			// Checks if duplicate
			if (strcmp(tempPointer -> songName, tempNode -> songName) == 0){
				songNameDuplicate(tempNode -> songName);
				return listHead;
			}
			
			// Checks if the temp song is in between the current pointer song and the song after the current pointer
			if ((tempPointer -> nextNode != NULL) &&
				(strcmp(tempPointer -> songName, tempNode -> songName) < 0) &&
				(strcmp(tempPointer -> nextNode -> songName, tempNode -> songName) > 0)){
				// Temp node song name is greater than current tempPointer song name and less than following song name
				tempNode -> nextNode = tempPointer -> nextNode;
				tempPointer -> nextNode = tempNode;
				return listHead;
			}
			
			// Checks if next node is null (if so sticks at end of list)
			if (tempPointer -> nextNode == NULL){
				tempPointer -> nextNode = tempNode;
				return listHead;
			}
			
			// moves temphead to the next node
			tempPointer = tempPointer -> nextNode;
		}
		
		return listHead;
	}
}

// Function for printing a single song
void printSong(Node *songPrinted){
	// Prints song name, artist, and genre
	printf("%s\n", songPrinted -> songName);
	printf("%s\n", songPrinted -> artist);
	printf("%s\n", songPrinted -> genre);
	
}

// Function for printing song library
void printMusicLibrary (Node *listHead){
	Node *tempPointer = listHead;

	// Checks if list is empty
	if (listHead == NULL){
		printMusicLibraryEmpty();
	}
	// Searches music library
	else {
		printMusicLibraryTitle();
		while (tempPointer != NULL){
			printf("\n");
			printSong(tempPointer);
			tempPointer = tempPointer -> nextNode;
		}
	}
}

// Function to search for song in library
void searchMusicLibrary (Node *listHead, char *inputName){
	
	// Declaring/initializing variables
	Node *tempPointer = listHead;
	int foundSong = 0;
	
	// Searches music library (and prints if found)
	while ((tempPointer != NULL) && (foundSong == 0)){
		if (strcmp(tempPointer -> songName, inputName) == 0){
			foundSong++;
			songNameFound(inputName);
			printf("\n");
			printSong(tempPointer);
		}
		tempPointer = tempPointer -> nextNode;
	}
	
	// Song not found or list is empty
	if ((tempPointer == NULL) && (foundSong == 0)){
		songNameNotFound(inputName);
	}
}

// Function to delete a specified song in the library
Node *deleteSong (Node *listHead, char *songToDelete){
	// Search for song
	// Declaring/initializing variables
	Node *tempPointer = listHead;
	Node *tempNode = malloc(sizeof(Node));
	int foundSong = 0;
	
	// Checks if list is empty
	if (listHead == NULL){
		songNameNotFound(songToDelete);
		return listHead;
	}
	
	// Checks if listHead is the song to delete
	if (strcmp(listHead -> songName, songToDelete) == 0){
		foundSong ++;
		tempNode = listHead -> nextNode;
		songNameDeleted(songToDelete);
		free(listHead -> songName);
		free(listHead -> artist);
		free(listHead -> genre);
		free(listHead);
		return tempNode;
	}
	
	// Searches music library (and prints if found)
	while ((tempPointer != NULL) && (foundSong == 0)){
		
		// Checks if next song is the one to be deleted
		if (strcmp(tempPointer -> nextNode -> songName, songToDelete) == 0){
			// Song is found, and will be deleted (memory freed)
			foundSong++;
			// Temp node stores the next next song
			tempNode = tempPointer -> nextNode -> nextNode;
			songNameDeleted(songToDelete);
			free(tempPointer -> nextNode -> songName);
			free(tempPointer -> nextNode -> artist);
			free(tempPointer -> nextNode -> genre);
			free(tempPointer -> nextNode);
			tempPointer -> nextNode = tempNode;
			return listHead;
		}
		tempPointer = tempPointer -> nextNode;
	}
	
	// Song not found or list is empty -> displays error not found
	if ((tempPointer == NULL) && (foundSong == 0)){
		songNameNotFound(songToDelete);
		return listHead;
	}
}

// Called when quitting, deletes whole library
Node *deleteLibrary (Node *listHead){
	// Deletes whole list
	while (listHead != NULL){
		listHead = deleteSong(listHead, listHead -> songName);
	}
	return listHead;
}
