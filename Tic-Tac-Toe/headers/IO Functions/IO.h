#ifndef IO_H_
#define IO_H_

void displayBoard(char **board) {
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
			printf("| %c ", board[x][y]);

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

void getPlayersMove(int *coordinates, LinkedList **legalMoves) {
	LinkedList *currentNode = *legalMoves;
	LinkedList *previousNode = NULL;

	//keep asking for user's move (via coordinates) until he enters a valid move
	while(1) {
		printf("Enter row coordinate: ");
		scanf("%i", &coordinates[0]);
		printf("Enter column coordinate: ");
		scanf("%i", &coordinates[1]);

		// if the user entered a location within the board
		if( (coordinates[0] >= 0 && coordinates[0] < BOARD_HEIGHT) &&
			(coordinates[1] >= 0 && coordinates[1] < BOARD_WIDTH))
		{
			//check if the user entered a non-occupied board location
			while(currentNode != NULL) {
				//if the input move is a legal move
				if( (coordinates[0] == currentNode->coordinate[0]) &&
					(coordinates[1] == currentNode->coordinate[1]))
				{
					/* remove this move from the 'legal moves' list to make it invalid if the user re-enters that move.
					 * For some reason though, I cannot properly delete the head node using only 'currentNode' and 'previousNode' as parameters
					 * so I'm forced to messily include the head node itself. I'll see if I can work around this on my spare time...
					 */
					removeLegalMove(&legalMoves, &currentNode, &previousNode);

					return;
				}

				previousNode = currentNode;
				currentNode = currentNode->next;
			}

			printf("Invalid move. The location has already been occupied.\n");
		}

		//otherwise, inform the user that his/her move is invalid
		printf("Invalid move. The location is out of bounds.\n");
	}
}

void congratulatePlayer(char player) {
	printf("%c won the game.\n", (player == 'o')? 'o' : 'x');
}

#endif /* IO_H_ */
