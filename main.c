// Final Project
// main.c
// Name: Bar Vilenski 
// I.D : 204519854
// Name: Shira Yad Shalom
// I.D : 315780486
// Date: 04.06.18

#include "action.h"

#define N 7

/*
This function initializes the array of short term history commands, the list of long term history commands and the list of apartments.
*/
void initializeEnvironment(char* short_term_history[], int short_history_size, CommandsList* long_term_history, ApartmentsList* apartments);

void main() {
	char* command;
	char* short_term_history[N];
	CommandsList long_term_history;
	ApartmentsList apartments;

	initializeEnvironment(short_term_history, N, &long_term_history, &apartments);
	printStartMessage();

	command = getCommandFromInput();
	while (parseCommandAction(command) != EXIT) {
		executeAndSaveCommand(command, short_term_history, N, &long_term_history, &apartments);
		free(command);
		command = getCommandFromInput();
	}

	saveDataToFiles(short_term_history, N, &long_term_history, &apartments);
	printEndMessage();

	free(command);
	freeCommandsList(&long_term_history);
	freeApartmentsList(&apartments);
}


void initializeEnvironment(char* short_term_history[], int short_history_size, CommandsList* long_term_history, ApartmentsList* apartments) {
	int i;

	// initialize the array of short term history commands
	for (i = 0; i < short_history_size; i++) {
		short_term_history[i] = NULL;
	}

	// initialize the list of long term history commands
	initializeCommandsList(long_term_history);

	// initialize the list of apartments
	initializeApartmentsList(apartments);

	getDataFromFiles(short_term_history, short_history_size, long_term_history, apartments);
}
