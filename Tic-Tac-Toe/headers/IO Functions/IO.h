#ifndef IO_H_
#define IO_H_

void displayBoard(GameBoard board) {
	int x, y, z;

	printf("  ");
	for(z = 0; z < BOARD_WIDTH; ++z) {
		printf("  %i ", z);
	}

	printf("\n");

	for(z = 0, x = 0; x < BOARD_HEIGHT; ++z, ++x) {
		printf("  ");
		for(y = BOARD_WIDTH * 4; y; --y)
			printf("%c", !(y % 4)? '+' : '-');

		printf("-\n%i ", z);

		for(y = 0; y < BOARD_WIDTH; ++y)
			printf("| %c ", board.state[x][y]);

		printf("|\n");
	}

	printf("  ");
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

void getPlayersMove(int *coordinates, GameBoard board) {
	//keep asking for user's move (via coordinates) until he enters a valid move
	while(1) {
		printf("Enter row coordinate: ");
		scanf("%i", &coordinates[0]);
		printf("Enter column coordinate: ");
		scanf("%i", &coordinates[1]);

		// if the user entered a vacant location within the board
		if( (coordinates[0] >= 0 && coordinates[0] < BOARD_HEIGHT) &&
			(coordinates[1] >= 0 && coordinates[1] < BOARD_WIDTH) &&
			board.state[coordinates[0]][coordinates[1]] == BLANK_CHARACTER)
		{
			return;
		}

		//otherwise, inform the user that his/her move is invalid
		printf("Invalid move. Either the input coordinate is occupied or out of bounds.\n\n");
	}
}

#endif /* IO_H_ */
