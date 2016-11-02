/*
 * process.h
 *
 *  Created on: Nob 2, 2016
 *      Author: Collamar PC
 */

#ifndef PROCESS_H_
#define PROCESS_H_

//This function updates an element value board
void updateBoard(char ***board, int *coordinate, char symbol) {
	(*board)[coordinate[0]][coordinate[1]] = symbol;
}

// This function checks if the last move results to a win-situation
int checkForWinner(char **board, int *lastMove) {
	int terminator; // 'terminator' will serve as the mark of the last
					//  horizontal/vertical/diagonal element to check
	int count;	// 'count'  counts the number of same consecutive symbols
	char symbol = board[lastMove[0]][lastMove[1]]; // 'symbol' is the symbol that 'count' counts
	int column;
	int row;

	//check for horizontal alignment
	count = 0;
	terminator = lastMove[1] + ALIGNMENT_NUMBER;
	column = lastMove[1] - ALIGNMENT_NUMBER;

	while(column < 0) { ++column; } // the next line seems pointless until we consider an arbitrary board dimensions

	for(row = lastMove[0] ; column < ALIGNMENT_NUMBER && column < terminator; ++column)
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
	terminator = lastMove[0] + ALIGNMENT_NUMBER;
	row = lastMove[0] - ALIGNMENT_NUMBER;

	while(row < 0) { ++row; }	//just like what I stated above, I intentionally used this instead of
								//"row = (lastMove[0] - ALIGNMENT_NUMBER < 0) 0 : lastMove[0] - ALIGNMENT_NUMBER;"

	for(column = lastMove[1] ; row < ALIGNMENT_NUMBER && row < terminator; ++row)
	{
		//increment 'count' if the control reads in the same symbol
		//else, reset 'count' to zero
		count = (board[row][column] == symbol)? count + 1 : 0;

		//if the winning alignment is detected
		if(count == ALIGNMENT_NUMBER) {
			printf("Vertical alignment detected.\n");
			return 1;
		}
	}

	//WARNING: I don't know how to explain the following codes in words

	//check for positively sloped diagonal alignment
	count = 0;
	row = lastMove[0] + ALIGNMENT_NUMBER;
	column = lastMove[1] + ALIGNMENT_NUMBER;

	while(row >= ALIGNMENT_NUMBER || column >= ALIGNMENT_NUMBER) {
		--row;
		--column;
	}

	for( ; (row >= 0 && row > lastMove[0] - ALIGNMENT_NUMBER) && (column >= 0 && column > lastMove[1] - ALIGNMENT_NUMBER); --row, --column) {
		printf("\t\tchecking board[%i]{%i] = %c\n", row, column, board[row][column]);
		count = (board[row][column] == symbol)? count + 1 : 0;

		//if the winning alignment is detected
		if(count == ALIGNMENT_NUMBER) {
			printf("/ alignment detected.\n");
			printf("\t\tcount = %i\n", count);
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

#endif /* PROCESS_H_ */
