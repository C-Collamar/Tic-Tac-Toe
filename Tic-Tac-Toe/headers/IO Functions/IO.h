#ifndef IO_H_
#define IO_H_

void displayBoard(char **board) {
	int x, y;

	for(x = 0; x < BOARD_HEIGHT; ++x) {
		for(y = BOARD_WIDTH * 4; y; --y)
			printf("%c", !(y % 4)? '+' : '-');

		printf("-\n");

		for(y = 0; y < BOARD_WIDTH; ++y)
			printf("| %c ", board[x][y]);

		printf("|\n");
	}

	for(y = BOARD_WIDTH * 4; y; --y)
		printf("%c", !(y % 4)? '+' : '-');

	printf("-\n");
}

int userPlaysFirst(void) {
	char choice;

	while(1) {
		printf("Do you want to play first (y/n)? ");
		scanf(" %c", &choice);

		choice = tolower(choice);

		if(choice == 'y' || choice == 'n')
			break;

		printf("Invalid choice. Enter 'y' or 'n' only.\n\n");
	}

	return (choice == 'y')? 1 : 0;
}

void getPlayersMove(int *coordinates, char **board) {
	//keep asking for user's move (via coordinates) until he enters a valid move
	while(1) {
		printf("Enter row coordinate: ");
		scanf("%i", &coordinates[0]);
		printf("Enter column coordinate: ");
		scanf("%i", &coordinates[1]);

		/* verifies if the user's move is legal
		 * by checking on weather that position is already occupied
		 */
		if( (coordinates[0] >= 0 && coordinates[0] < BOARD_HEIGHT) &&
			(coordinates[1] >= 0 && coordinates[1] < BOARD_WIDTH) &&
			(board[coordinates[0]][coordinates[1]] == BLANK_CHARACTER))
		{
			break;
		}

		//otherwise, inform the user that his/her move is invalid
		printf("Invalid move. The location is either out of bounds or has been occupied.\n");
	}
}

void congratulatePlayer(char player) {
	printf("%c won the game.\n", (player == 'o')? 'o' : 'x');
}

#endif /* IO_H_ */
