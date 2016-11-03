#ifndef CLEANUP_H_
#define CLEANUP_H_

void destroyPlayer(Player **player) {
	free(*player);
	player = NULL;
}

void destroyBoard(char ***board) {
	int x;

	for(x = 0; x < BOARD_WIDTH; ++x) {
		free((*board)[x]);
	}

	free(*board);
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
