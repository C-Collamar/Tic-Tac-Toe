#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "headers/macros.h"

typedef struct Player {
	int move[2]; //represents what the player's move/action is
	unsigned int turn : 1; //this determines if it's the player's turn
	char symbol; //this represents the symbol for the players' pieces ('X' and 'O' by default)
} Player;

Player computer;
Player user;

/*[NEEDS IMROVEMENT] I did this "workaround" to pass the board by value to avoid modifying the actual board state
 * To make more sense - for some functions, I wanted to pass the board of type 'char **' by value (passing it as of type 'char **', and
 * the parameter expecting it is of type 'char **'), but the board still gets modified :(
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
#include "headers/Memory Management/init.h"
#include "headers/Memory Management/cleanup.h"
#include "headers/Processing Functions/assess.h"

int main(void) {
	//due to an eclipse bug...
	setvbuf(stdout, NULL, _IONBF, 0);

	//variable declarations
	GameBoard board;
	int turn = 1;

	printf("hello");

	//initializations
	InitPlayer(&computer);
	InitPlayer(&user);
	InitBoard(&board);
	InitGame(&computer, &user);

//	LinkedList *temp;

	//display the initial state of the board
	printf("\nINITIAL BOARD STATE:\n");
	displayBoard(board);

	//while there's no winner, increment turn
	while(turn <= BOARD_HEIGHT * BOARD_WIDTH) {
/*		temp = legalMoves;
		while(temp != NULL) {
			printf("\t[%i, %i]\n", temp->coordinate[0], temp->coordinate[1]);
			temp = temp->next;
*/
		//if it's user's turn
		if((turn & 1) == user.turn) {
			printf("\nUSER'S TURN:\n");

			//get user's move
			getPlayersMove(user.move, board);

			//update the board
			updateBoard(&board, user.move, user.symbol);

			//display the board on the screen
			printf("\nUPDATED BOARD STATE:\n");
			displayBoard(board);

			//check if the user wins
			if(checkForWinner(board, user.move) == 1) {
				congratulatePlayer(user.symbol);
				break;
			}
		}
		//else if it's computer's turn
		else {
			printf("\nCOMPUTER'S TURN:\n");

			//let the A.I. do its thing
			findBestMove(computer.move, board);

			//update the board
			updateBoard(&board, computer.move, computer.symbol);

			//display it on the screen
			printf("\nUPDATED BOARD STATE:\n");
			displayBoard(board);

			//see if the computer wins
			if(checkForWinner(board, computer.move) == 1) {
				congratulatePlayer(computer.symbol);
				break;
			}
		}

		//increment each turn
		++turn;
	}

	//properly deallocate pointer variables
	destroyBoard(&board);

	//...and exit
	return EXIT_SUCCESS;
}
