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

LinkedList * getPossibleMoves(GameBoard board) {
	//create a pointer to the head of the list of legal moves
	LinkedList *head = NULL;

	//create a new node to connect to the list
	LinkedList *legalMove = NULL;

	//check each squares in the board for vacant squares
	int x = -1, y;

	while(++x < BOARD_HEIGHT) {
		y = -1;
		while(++y < BOARD_WIDTH) {
			//if a vacant position is found
			if(board.state[x][y] == BLANK_CHARACTER) {

				//check if memory allocation failed
				if((legalMove = malloc(sizeof(LinkedList))) == NULL) {
					printf("ERROR: Memory allocation failed.\n");
					exit(EXIT_FAILURE);
				}

				//else, add that board coordinate to that node
				legalMove->coordinate[0] = x;
				legalMove->coordinate[1] = y;

				//connect that node to the list
				legalMove->next = head;
				head = legalMove;
			}
		}
	}

	return head;
}

#endif /* INIT_H_ */
