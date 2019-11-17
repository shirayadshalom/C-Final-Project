// final project
// action.c
// Name: Bar Vilenski 
// I.D : 204519854
// Name: Shira Yad Shalom
// I.D : 315780486
// Date: 04.06.18

#include "action.h"

void executeAndSaveCommand(char* command, char* short_term_history[], int short_history_size, CommandsList* long_term_history, ApartmentsList* apartments) {
	char* command_copy = (char*)calloc(strlen(command) + 1, sizeof(char));
	strcpy(command_copy, command);//copy the command

	switch (parseCommandAction(command_copy)) {
	case ADD_APT:
		addApartment(command_copy, apartments); 
		saveCommand(command, short_term_history, short_history_size, long_term_history);
		break;
	case GET_APT:
		getApartment(command_copy, apartments);
		saveCommand(command, short_term_history, short_history_size, long_term_history);
		break;
	case BUY_APT:
		buyApartment(command_copy, apartments);
		saveCommand(command, short_term_history, short_history_size, long_term_history);
		break;
	case DELETE_APT:
		deleteApartment(command_copy, apartments);
		saveCommand(command, short_term_history, short_history_size, long_term_history);
		break;
	case RECONSTRUCTION:
		reconstructCommand(command_copy, short_term_history, short_history_size, long_term_history, apartments);
		break;
	case SHORT_TERM_HISTORY:
		printShortTermHistory(short_term_history, short_history_size, long_term_history->size);
		break;
	case LONG_TERM_HISTORY:
		printLongTermHistory(long_term_history);
		printShortTermHistory(short_term_history, short_history_size, long_term_history->size);
		break;
	case EXIT:
		break;
	default:
		break;
	}

	free(command_copy);
}

void addApartment(char* command, ApartmentsList* apartments) {
	Apartment new_apartment = parseAddCommand(command, apartments);

	insertApartmentToList(new_apartment, DEFAULT_FILTER, apartments);
}

void getApartment(char* command, ApartmentsList* apartments) {
	int minimum_rooms = DEFAULT_FILTER, maximum_rooms = DEFAULT_FILTER, maximum_price = DEFAULT_FILTER, date = DEFAULT_FILTER, sort = DEFAULT_FILTER;
	ApartmentsList* filtered_apartments;

	parseGetCommand(command, &minimum_rooms, &maximum_rooms, &maximum_price, &date, &sort);

	filtered_apartments = filterApartmentsList(apartments, minimum_rooms, maximum_rooms, maximum_price, date, sort);

	printApartmentsList(filtered_apartments);
	freeApartmentsList(filtered_apartments);
}

void buyApartment(char* command, ApartmentsList* apartments) {
	int apartment_id;

	sscanf(command, "%*s %d", &apartment_id);

	removeApartmentFromList(apartment_id, apartments);
}

void deleteApartment(char* command, ApartmentsList* apartments) {
	ApartmentNode *apt = apartments->tail, *previous;
	int last_days;

	sscanf(command, "%*s %*s %d", &last_days);

	while (apt != NULL && checkApartmentCreationDate(apt, last_days)) {
		previous = apt->previous;
		removeApartmentFromList(apt->data.id, apartments);
		apt = previous;
	}
}

void reconstructCommand(char* command, char* short_term_history[], int short_history_size, CommandsList* long_term_history, ApartmentsList* apartments) {
	char *new_command = NULL, *old_string = NULL, *new_string = NULL;

	new_command = parseReconstructionGetOriginalCommand(command[1], short_term_history, short_history_size, long_term_history);

	if (strlen(command) <= 2) {
		executeAndSaveCommand(new_command, short_term_history, short_history_size, long_term_history, apartments);
	}
	else {
		parseReconstructionGetStrings(command, &old_string, &new_string);
		new_command = parseReconstructionReplaceStrings(new_command, old_string, new_string);
		executeAndSaveCommand(new_command, short_term_history, short_history_size, long_term_history, apartments);

		free(old_string);
		free(new_string);
		free(new_command);
	}
}
