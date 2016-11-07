#ifndef CLEANUP_H_
#define CLEANUP_H_

void destroyBoard(GameBoard *board) {
	free(board);
}

void destroyLinkedList(LinkedList **list) {
	LinkedList *temp = NULL;

	while((*list) != NULL) {
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
}

#endif /* CLEANUP_H_ */
