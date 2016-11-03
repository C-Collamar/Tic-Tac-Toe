#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct LinkedList {
	int coordinate[2]; //the values stored in this array are the row and column positions of legal moves
	int score; //this will serve as a basis on whether the legal move (defined by the coordinates above) is good or bad
	struct LinkedList *next; //this points to another legal action/move
} LinkedList;

typedef struct Player {
	unsigned int turn : 1;
	char symbol;
} Player;

Player *computer = NULL;
Player *user = NULL;

#include "headers/macros.h"
#include "headers/Processing Functions/update.h"
#include "headers/IO Functions/IO.h"
#include "headers/Processing Functions/assess.h"
#include "headers/Memory Management/init.h"
#include "headers/Memory Management/cleanup.h"

int main(void) {
	//due to an eclipse bug...
	setvbuf(stdout, NULL, _IONBF, 0);

	//variable declarations
	LinkedList *legalMoves = NULL;
	char **board = NULL;
	int latestMove[2] = { 0, 0 };
	int turn = 1;

	//initializations
	InitPlayer(&computer);
	InitPlayer(&user);
	InitBoard(&board);
	InitLegalMoves(&legalMoves);
	InitGame(&computer, &user);

	//display the initial state of the board
	printf("\nINITIAL BOARD STATE:\n");
	displayBoard(board);

	//while there's no winner, increment turn
	while(turn <= BOARD_HEIGHT * BOARD_WIDTH) {
		//if it's user's turn
		if((turn & 1) == user->turn) {
			printf("\nUSER'S TURN:\n");
			//get user's move and update the board
			getPlayersMove(latestMove,&legalMoves);
			updateBoard(&board, latestMove, user->symbol);
		}
		//else if it's computer's turn
		else {
			printf("\nCOMPUTER'S TURN:\n");
			//here's where things get crazy
			findBestMove(latestMove, legalMoves, board, 0);
			updateBoard(&board, latestMove, computer->symbol);
		}

		//display the board to the screen
		displayBoard(board);

		if(checkForWinner(board, latestMove) == 1) {
			congratulatePlayer(((turn & 1) == computer->turn)? computer->symbol : user->symbol);
			break;
		}

		//and of course,increment each turn
		++turn;
	}

	//properly deallocate variables
	destroyPlayer(&computer);
	destroyPlayer(&user);
	destroyBoard(&board);
	destroyLinkedList(&legalMoves);

	//...and exit
	return EXIT_SUCCESS;
}
