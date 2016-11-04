#ifndef INIT_H_
#define INIT_H_

// This function allocates memory for 'Player'-type objects
void InitPlayer(Player *player) {
	player = malloc(sizeof(Player));
	if(player == NULL) {
		printf("ERROR: Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
}

//this function initializes the board elements to BLANK_CHARACTER
void InitBoard(GameBoard *board) {
	int x, y;

	for(x = 0; x < BOARD_HEIGHT; ++x)
		for(y = 0; y < BOARD_WIDTH; ++y)
			board->state[x][y] = BLANK_CHARACTER;
}

void InitGame(Player *computer, Player *user) {
	/* the following lines initialize the numeric representation
	 * for distinguishing user's turn from computer's turn
	 */
	computer->turn = (userPlaysFirst())? 0 : 1;
	user->turn = (computer->turn == 1)? 0 : 1;

	computer->symbol = 'x';
	user->symbol = 'o';
}

// This function initializes the initial possible moves both players can make
void InitLegalMoves(LinkedList **legalMoves) {
	int x = -1, y;

	while(++x < BOARD_HEIGHT) {
		y = -1;
		while(++y < BOARD_WIDTH) {
			addLegalMove(&legalMoves, x, y);
		}
	}
}

#endif /* INIT_H_ */
