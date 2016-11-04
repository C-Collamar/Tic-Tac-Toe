#ifndef UPDATE_H_
#define UPDATE_H_

//This function updates an element value of the board
void updateBoard(GameBoard *board, int *coordinate, char symbol) {
	board->state[coordinate[0]][coordinate[1]] = symbol;
}

//This function inserts the x and y coordinates into the list of legal moves; which will be used later on
void addLegalMove(LinkedList ***legalMoves, int row, int column) {
	LinkedList *newNode = NULL;

	//allocate memory to the new node
	newNode = malloc(sizeof(LinkedList));

	//check if allocation failed
	if(!newNode) {
		printf("ERROR: Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}

	newNode->coordinate[0] = row;
	newNode->coordinate[1] = column;

	//if the list is currently empty
	if(**legalMoves == NULL) {
		newNode->next = NULL;
		**legalMoves = newNode;
		return;
	}

	//else, connect the new node to the list
	newNode->next = **legalMoves;
	**legalMoves = newNode;
}

void removeLegalMove(LinkedList ***head, LinkedList **curr, LinkedList **prev) {
	//if the node to be removed is the head in the list
	if(*prev == NULL) {
		*prev = (*curr)->next;
		free(*curr);
		//*curr = *prev;
		**head = *prev;
		return;
	}

	//else...
	(*prev)->next = (*curr)->next;
	free(*curr);
}

#endif /* UPDATE_H_ */
