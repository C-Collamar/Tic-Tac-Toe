#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "headers/macros.h"

typedef struct Player {
	unsigned int turn : 1;
	char symbol;
} Player;

/*[NEEDS IMROVEMENT] I did this "workaround" to pass the board by value to avoid modifying the actual board state
 * To make more sense - for some functions, I wanted to pass the board of type 'char **' by value (passing it as of type 'char **', and
 * the parameter expecting it is of type 'char **'), the board still gets modified :(
 */
 typedef struct GameBoard {
	char state[BOARD_HEIGHT][BOARD_WIDTH]; //this represents the state of the board (i.e. the positions of each piece on the board)
} GameBoard;

typedef struct LinkedList {
	int coordinate[2]; //the values stored in this array are the row and column positions of legal moves
	int score; //this will serve as a basis on whether the legal move (defined by the coordinates above) is good or bad
	struct LinkedList *next; //this points to another legal action/move
} LinkedList;

#include "headers/Processing Functions/update.h"
#include "headers/IO Functions/IO.h"
#include "headers/Processing Functions/assess.h"
#include "headers/Memory Management/init.h"
#include "headers/Memory Management/cleanup.h"

int main(void) {
	//due to an eclipse bug...
	setvbuf(stdout, NULL, _IONBF, 0);

	//variable declarations
	Player computer;
	Player user;
	GameBoard board;
	LinkedList *legalMoves = NULL;
	int latestMove[2] = { 0, 0 };
	int turn = 1;

	printf("hello");

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
		if((turn & 1) == user.turn) {
			printf("\nUSER'S TURN:\n");
			//get user's move and update the board
			getPlayersMove(latestMove,&legalMoves);
			updateBoard(&board, latestMove, user.symbol);
		}
		//else if it's computer's turn
		else {
			printf("\nCOMPUTER'S TURN:\n");
			//here's where things get crazy
			findBestMove(latestMove, legalMoves, board, 0);
			updateBoard(&board, latestMove, computer.symbol);
		}

		//display the board to the screen
		printf("\nUPDATED BOARD STATE:\n");
		displayBoard(board);

		if(checkForWinner(board, latestMove) == 1) {
			congratulatePlayer(((turn & 1) == computer.turn)? computer.symbol : user.symbol);
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
