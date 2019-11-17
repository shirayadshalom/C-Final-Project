// Final Project
// commands_list.c
// Name: Bar Vilenski 
// I.D : 204519854
// Name: Shira Yad Shalom
// I.D : 315780486
// Date: 04.06.18

#include "commands_list.h"

void initializeCommandsList(CommandsList* lst) {
	lst->head = NULL;
	lst->tail = NULL;
	lst->size = 0;
}

int isEmptyCommandsList(CommandsList* lst) {
	return lst->size == 0;
}

CommandNode* createNewCommandNode(char* data, CommandNode* previous, CommandNode* next) {
	CommandNode* new_node = (CommandNode*)malloc(sizeof(CommandNode));
	new_node->data = (char*)calloc(strlen(data) + 1, sizeof(char));

	strcpy(new_node->data, data);
	new_node->previous = previous;
	new_node->next = next;

	return new_node;
}

void insertToStartOfCommandsList(char* command, CommandsList* lst) {
	CommandNode* new_node = createNewCommandNode(command, NULL, lst->head);

	if (isEmptyCommandsList(lst)) {
		lst->tail = new_node;
		lst->head = new_node;
	}
	else {
		lst->head->previous = new_node;
		lst->head = new_node;
	}

	lst->size++;
}

void insertToEndOfCommandsList(char* command, CommandsList* lst) {
	CommandNode* new_node = createNewCommandNode(command, lst->tail, NULL);

	if (isEmptyCommandsList(lst)) {
		lst->tail = new_node;
		lst->head = new_node;
	}
	else {
		lst->tail->next = new_node;
		lst->tail = new_node;
	}

	lst->size++;
}

void freeCommandsList(CommandsList* lst) {
	CommandNode* current = lst->head;
	CommandNode* next;

	while (current) {
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}

	lst->head = NULL;
	lst->size = 0;
}

int isFullArray(char* arr[], int size) {
	return arr[size - 1] != NULL;
}

void addToStartOfArray(char* command, char* arr[], int size) {
	int i;
	// shift the elements of the array by one position
	for (i = size - 1; i >= 1; i--) {
		arr[i] = arr[i - 1];
	}
	arr[0] = NULL;

	// copy the command into the first position
	arr[0] = (char*)calloc(strlen(command) + 1, sizeof(char));
	strcpy(arr[0], command);
}

void addToEndOfArray(char* command, char* arr[], int size) {
	int i = 0;

	while (arr[i] != NULL) {
		i++;
	}

	arr[i] = (char*)calloc(strlen(command) + 1, sizeof(char));
	strcpy(arr[i], command);
}

void saveCommand(char* command, char* short_term_history[], int short_history_size, CommandsList* long_term_history) {
	if (isFullArray(short_term_history, short_history_size)) {
		insertToStartOfCommandsList(short_term_history[short_history_size - 1], long_term_history);
		free(short_term_history[short_history_size - 1]);
	}

	addToStartOfArray(command, short_term_history, short_history_size);
}

void saveCommandToEnd(char* command, char* short_term_history[], int short_history_size, CommandsList* long_term_history) {
	if (isFullArray(short_term_history, short_history_size)) {
		insertToEndOfCommandsList(command, long_term_history);
	}
	else {
		addToEndOfArray(command, short_term_history, short_history_size);
	}
}
