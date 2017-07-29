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
	//variable declarations
	GameBoard board;
	int turn = 1;

	//initializations
	InitPlayer(&computer);
	InitPlayer(&user);
	InitBoard(&board);
	InitGame(&computer, &user);

	//clear the screen and display the initial board state
	system("cls");
	printf("BOARD STATE:\n");
	displayBoard(board);

	//while there's no winner, increment turn
	while(turn <= BOARD_HEIGHT * BOARD_WIDTH) {
		//if it's user's turn
		if((turn & 1) == user.turn) {
			printf("\nYOUR TURN:\n");

			//get user's move
			getPlayersMove(user.move, board);

			//update the board with the user's move
			updateBoard(&board, user.move, user.symbol);

			//check if the user wins
			if(checkForWinner(board, user.move) == 1) {
				printf("Congratulaions, you won the game.\n");
				break;
			}
		}
		//if it's computer's turn
		else {
			//let the minimax algorithm do its thing
			findBestMove(computer.move, board);

			//update the board with the computer's move
			updateBoard(&board, computer.move, computer.symbol);

			//clear the screen and display the current board state
			system("cls");
			printf("BOARD STATE:\n");
			displayBoard(board);

			//display the computer's move
			printf("Computer's move: [%i, %i]\n", computer.move[0], computer.move[1]);

			//see if the computer wins
			if(checkForWinner(board, computer.move) == 1) {
				printf("Game over. Computer has won the game.\n");
				break;
			}
		}

		//increment each turn
		++turn;
	}

	//if it's a tie
	if(turn > BOARD_HEIGHT * BOARD_WIDTH) {
		system("cls");
		printf("BOARD STATE:\n");
		displayBoard(board);
		printf("Computer's move: [%i, %i]\n", computer.move[0], computer.move[1]);
		printf("It's a tie!\n");
	}

	//properly deallocate pointer variables
	destroyBoard(&board);

	//...and exit
	return EXIT_SUCCESS;
}
