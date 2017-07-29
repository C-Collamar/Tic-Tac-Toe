#ifndef ASSESS_H_
#define ASSESS_H_

/* This function checks if the last move results to a win-situation;
 * returns 1 if the winning alignment is detected, otherwise, zero.
 */
int checkForWinner(GameBoard board, int *lastMove) {
	int terminator; // 'terminator' will serve as the mark of the last horizontal/vertical/diagonal element to check
	int count;	// 'count'  counts the number of same consecutive symbols
	char symbol = board.state[lastMove[0]][lastMove[1]]; // 'symbol' is the symbol that 'count' counts
	int column;
	int row;

	//check for horizontal alignment
	count = 0;
	terminator = (lastMove[1] + ALIGNMENT_NUMBER >= BOARD_WIDTH)? BOARD_WIDTH : lastMove[1] + ALIGNMENT_NUMBER;
	row = lastMove[0];
	column = (lastMove[1] - ALIGNMENT_NUMBER <= 0)? 0 : lastMove[1] - ALIGNMENT_NUMBER + 1;

	for( ; column < terminator; ++column)
	{
		//increment 'count' if the control reads in the same symbol
		//else, reset 'count' to zero
		count = (board.state[row][column] == symbol)? count + 1 : 0;

		//if the winning alignment is detected
		if(count == ALIGNMENT_NUMBER) {
			//printf("Horizontal alignment detected\n");
			return 1;
		}
	}

	//check for vertical alignment
	count = 0;
	terminator = (lastMove[0] + ALIGNMENT_NUMBER >= BOARD_HEIGHT)? BOARD_HEIGHT: lastMove[0] + ALIGNMENT_NUMBER + 1;
	row = (lastMove[0] - ALIGNMENT_NUMBER <= 0)? 0 : lastMove[0] - ALIGNMENT_NUMBER + 1;
	column = lastMove[1];

	for( ; row < terminator; ++row)
	{
		/* increment 'count' if the same symbol has been read in
		 * else, reset 'count' to zero
		 */
		count = (board.state[row][column] == symbol)? count + 1 : 0;

		//if the winning alignment is detected
		if(count == ALIGNMENT_NUMBER) {
			//printf("Vertical alignment detected\n");
			return 1;
		}
	}

	//check for positively sloped diagonal alignment
	count = 0;
	row = lastMove[0] + ALIGNMENT_NUMBER - 1;
	column = lastMove[1] - ALIGNMENT_NUMBER + 1;

	while(row >= BOARD_HEIGHT || column < 0) {
		--row;
		++column;
	}

	for( ; (row >= 0 && row > lastMove[0] - ALIGNMENT_NUMBER) && (column < BOARD_WIDTH && column < lastMove[1] + ALIGNMENT_NUMBER); --row, ++column) {
		count = (board.state[row][column] == symbol)? count + 1 : 0;

		//if the winning alignment is detected
		if(count == ALIGNMENT_NUMBER) {
			//printf("'/' alignment detected\n");
			return 1;
		}
	}

	//check negatively slopped diagonal alignment
	count = 0;
	row = lastMove[0] + ALIGNMENT_NUMBER - 1;
	column = lastMove[1] + ALIGNMENT_NUMBER - 1;

	while(row >= BOARD_HEIGHT || column >= BOARD_WIDTH) {
		--row;
		--column;
	}

	for( ; (row >= 0 && row > lastMove[0] - ALIGNMENT_NUMBER) && (column >= 0 && column > lastMove[1] - ALIGNMENT_NUMBER); --row, --column) {
		count = (board.state[row][column] == symbol)? count + 1 : 0;

		//if the winning alignment is detected
		if(count == ALIGNMENT_NUMBER) {
			//printf("'\' alignment detected\n");
			return 1;
		}
	}

	return 0;
}

/* This function checks if a tie has occurred. It checks every square on the board if
 * there is still a blank character. Return 0 if there is, or 1 meaning there isn't
 */
int tie(GameBoard board) {
	int x = -1, y;

	while(++x < BOARD_HEIGHT) {
		y = -1;
		while(++y < BOARD_WIDTH)
			if(board.state[x][y] == BLANK_CHARACTER)
				return 0;
	}

	//if it reaches to this point where every square in the board is filled up
	return 1;
}

int minimax(GameBoard board, int *move, int treeDepth) {
	//check if computer reaches its level of thinking
	if(treeDepth > TREE_DEPTH) {
		return 0;
	}

	//apply the input move to the current board state
	updateBoard(&board, move, ((treeDepth & 1) == 0)? computer.symbol : user.symbol);

	//if executing that move results to a win
	if(checkForWinner(board, move) == 1) {
		/* return 1 if it's the computer was the one who won in this scenario.
		 * Otherwise, return -1, which tells the computer that this was a bad move
		 */
		return (((treeDepth & 1) == 0)? 10 : -10) - treeDepth;
	}

	//also check if that move resulted in a tie
	if(tie(board)) {
		return 0;
	}
	//if not, create a list of possible moves
	LinkedList *legalMoves = getPossibleMoves(board);

	//assign a a pointer to point at each node of legal moves
	LinkedList *currentLegalMove = legalMoves;

	//get the scores for every possible move
	while(currentLegalMove != NULL) {
		currentLegalMove->score = minimax(board, currentLegalMove->coordinate, treeDepth + 1);
		currentLegalMove = currentLegalMove->next;
	}

	currentLegalMove = legalMoves;
	int finalScore = legalMoves->score;

	//if it's computer's turn that the computer thinks of
	if((treeDepth & 1) == 1) {
		//get the highest score among the scores, since the computer wants to maximize its chance of winning
		while(currentLegalMove != NULL) {
			if(currentLegalMove->score > finalScore)
				finalScore = currentLegalMove->score;
			currentLegalMove = currentLegalMove->next;
		}
	}
	//else if it's the user's turn that the computer thinks of
	else {
		//get the lowest score, since the user wants to minimize the computer's chances of winning
		while(currentLegalMove != NULL) {
			if(currentLegalMove->score < finalScore)
				finalScore = currentLegalMove->score;
			currentLegalMove = currentLegalMove->next;
		}
	}

	//properly deallocate the list and return the final score for the node which this function was called
	destroyLinkedList(&legalMoves);
	return finalScore;
}

/* PARAMETERS:
 * - move: an array of 2 elements defining the AI's move - row and column
 * - legalMoves: a collection of all possible moves and scoring values for those moves
 * - board: the board used for analyzing the current game state
 * - depthCount: keeps track on the current depth of the game tree
 */
void findBestMove(int *move, GameBoard board) {
	//create a list of legal moves
	LinkedList *legalMoves = getPossibleMoves(board);

	//create a pointer to each legal-move node
	LinkedList *currentLegalMove = legalMoves;

	//for each legal moves, determine their score. Higher score indicates better move
	while(currentLegalMove != NULL) {
		//the minimax function rates the move based on the board and the number of turns it takes to win or not lose
		currentLegalMove->score = minimax(board, currentLegalMove->coordinate, 0);

		//do the same for the next move
		currentLegalMove = currentLegalMove->next;
	}

	//declare a variable to compare scores and initialize it to the score of the fist legal move
	int highestScore = legalMoves->score;

	//initially set the chosen move to the first legal move (actually it should be assigned a vacant location)
	move[0] = legalMoves->coordinate[0];
	move[1] = legalMoves->coordinate[1];

	//reset 'currentLegalMove' to point to the next legal move
	currentLegalMove = legalMoves->next;

	//find the best move among the rated legal moves by finding the highest score among them
	while(currentLegalMove != NULL) {
		if(currentLegalMove->score > highestScore) {
			highestScore = currentLegalMove->score;
			move[0] = currentLegalMove->coordinate[0];
			move[1] = currentLegalMove->coordinate[1];
		}
		currentLegalMove = currentLegalMove->next;
	}

	destroyLinkedList(&legalMoves);
}

#endif /* ASSESS_H_ */
