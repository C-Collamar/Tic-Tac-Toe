#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct Player {
	unsigned int turn : 1;
	char symbol;
} Player;

#include "headers/macros.h"
#include "headers/IO Functions/IO.h"
#include "headers/Memory Management/init.h"
#include "headers/Memory Management/cleanup.h"
#include "headers/Processing Functions/process.h"

int main(void) {
	//variable declarations
	Player *computer = NULL;
	Player *user = NULL;
	char **board = NULL;
	int move[2] = { 0, 0 };
	int turn = 1;

	//initializations
	InitPlayer(&computer);
	InitPlayer(&user);
	InitBoard(&board);
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
			getPlayersMove(move, board);
			updateBoard(&board, move, user->symbol);
		}
		//else if it's computer's turn
		else {
			//get computer's move and update the board
			//getComputersMove(move, board);
			printf("\nCOMPUTER'S TURN:\n");
			//updateBoard(&board, move, computer->symbol);
		}

		//display the board to the screen
		displayBoard(board);

		if(checkForWinner(board, move) == 1) {
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

	return EXIT_SUCCESS;
}
