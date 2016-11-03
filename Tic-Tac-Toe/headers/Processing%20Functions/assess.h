#ifndef ASSESS_H_
#define ASSESS_H_

/* This function checks if the last move results to a win-situation;
 * returns 1 if the winning alignment is detected, otherwise, zero.
 */
int checkForWinner(char **board, int *lastMove) {
	int terminator; // 'terminator' will serve as the mark of the last horizontal/vertical/diagonal element to check
	int count;	// 'count'  counts the number of same consecutive symbols
	char symbol = board[lastMove[0]][lastMove[1]]; // 'symbol' is the symbol that 'count' counts
	int column;
	int row;

	//check for horizontal alignment
	count = 0;
	terminator = lastMove[1] + ALIGNMENT_NUMBER;
	row = lastMove[0];
	column = (lastMove[1] - ALIGNMENT_NUMBER <= 0)? 0 : lastMove[1] - ALIGNMENT_NUMBER + 1;

	for( ; column < terminator; ++column)
	{
		//increment 'count' if the control reads in the same symbol
		//else, reset 'count' to zero
		count = (board[row][column] == symbol)? count + 1 : 0;

		//if the winning alignment is detected
		if(count == ALIGNMENT_NUMBER) {
			printf("Horizontal alignment detected.\n");
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
		count = (board[row][column] == symbol)? count + 1 : 0;

		//if the winning alignment is detected
		if(count == ALIGNMENT_NUMBER) {
			printf("Vertical alignment detected.\n");
			return 1;
		}
	}

	//I don't know how to explain the following codes in words

	//check for positively sloped diagonal alignment
	count = 0;
	row = lastMove[0] + ALIGNMENT_NUMBER - 1;
	column = lastMove[1] - ALIGNMENT_NUMBER + 1;

	while(row >= BOARD_HEIGHT || column < 0) {
		--row;
		++column;
	}

	for( ; (row >= 0 && row > lastMove[0] - ALIGNMENT_NUMBER) && (column < BOARD_WIDTH && column < lastMove[1] + ALIGNMENT_NUMBER); --row, ++column) {
		count = (board[row][column] == symbol)? count + 1 : 0;

		//if the winning alignment is detected
		if(count == ALIGNMENT_NUMBER) {
			printf("/ alignment detected.\n");
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
		count = (board[row][column] == symbol)? count + 1 : 0;

		//if the winning alignment is detected
		if(count == ALIGNMENT_NUMBER) {
			printf("\\ alignment detected.\n");
			return 1;
		}
	}

	return 0;
}

/* PARAMETERS:
 * move - an array of 2 elements defining the AI's move - row and column
 * legalMoves - a collection of all possible moves and scoring values for those moves
 * board - the board used for analyzing the current game state
 * depthCount - keeps track on the current depth of the game tree
 */
void findBestMove(int *move, LinkedList *legalMoves, char **board, int depthCount) {
	printf("(Under development)\n");
}

#endif /* ASSESS_H_ */