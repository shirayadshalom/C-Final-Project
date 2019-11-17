// Final Project
// input_output.c
// Name: Bar Vilenski 
// I.D : 204519854
// Name: Shira Yad Shalom
// I.D : 315780486
// Date: 04.06.18

#include "input_output.h"

void printStartMessage() {
	printf("Please enter one of the following commands:\n"
		"add-an-apt, get-an-apt, buy-an-apt or delete-an-apt\n"
		"For reconstruction commands, please enter:\n"
		"!!, !num, history, short_history or !num^str1^str2\n"
		"To exit, enter exit.\n");
}

void printEndMessage() {
	printf("Good Bye!\n");
}

void printShortTermHistory(char* short_term_history[], int short_history_size, int long_history_size) {
	int i, command_id = long_history_size + 1;

	for (i = short_history_size - 1; i >= 0; i--) {
		if (short_term_history[i] != NULL) {
			printf("%d: %s\n", command_id, short_term_history[i]);
			command_id++;
		}
	}
}

void printLongTermHistory(CommandsList* long_term_history) {
	CommandNode* current = long_term_history->tail;
	int i;

	for (i = 1; i <= long_term_history->size; i++, current = current->previous) {
		printf("%d: %s\n", i, current->data);
	}
}

void printApartment(ApartmentNode* apt) {
	printf("Apt details:\n");
	printf("Code: %d\n", apt->data.id);
	printf("Address: %s\n", apt->data.address);
	printf("Number of rooms: %d\n", apt->data.rooms);
	printf("Price: %d\n", apt->data.price);
	printf("Entry date: %d.%d.%d\n", apt->data.entry_day, apt->data.entry_month, apt->data.entry_year + 2000);
	printf("Database entry date: %d.%d.%d\n", apt->data.created_day, apt->data.created_month, apt->data.created_year + 2000);
}

void printApartmentsList(ApartmentsList* apartments) {
	ApartmentNode* current = apartments->head;

	while (current != NULL) {
		printApartment(current);
		current = current->next;
	}
}

char* getCommandFromInput() {
	char ch;
	int physical_size = 1, logical_size = 0;
	char* command = (char*)calloc(physical_size, sizeof(char));

	ch = getchar();
	while (ch != '\n') {
		if (physical_size == logical_size + 1) {
			physical_size *= 2;
			command = (char*)realloc(command, physical_size * sizeof(char));
		}

		command[logical_size] = ch;
		logical_size++;
		ch = getchar();
	}
	command[logical_size] = '\0';
	logical_size++;

	if (physical_size != logical_size)
		command = (char*)realloc(command, logical_size * sizeof(char));

	return command;
}

int parseCommandAction(char* command) {
	int res;
	char* action = (char*)calloc(strlen(command) + 1, sizeof(char));
	sscanf(command, "%s", action);
	action = (char*)realloc(action, (strlen(action) + 1) * sizeof(char));

	if (action[0] == '!') res = RECONSTRUCTION;
	else if (strcmp("add-an-apt", action) == 0) res = ADD_APT;
	else if (strcmp("get-an-apt", action) == 0) res = GET_APT;
	else if (strcmp("buy-an-apt", action) == 0) res = BUY_APT;
	else if (strcmp("delete-an-apt", action) == 0) res = DELETE_APT;
	else if (strcmp("short_history", action) == 0) res = SHORT_TERM_HISTORY;
	else if (strcmp("history", action) == 0) res = LONG_TERM_HISTORY;
	else if (strcmp("exit", action) == 0) res = EXIT;
	else res = ERROR_ACTION;

	free(action);
	return res;
}

Apartment parseAddCommand(char* command, ApartmentsList* apartments) {
	Apartment new_apartment;
	char* address = (char*)calloc(strlen(command) + 1, sizeof(char));
	char* params = (char*)calloc(strlen(command) + 1, sizeof(char));
	int i, counter = 0, address_index = 0, params_index = 0;
	time_t current_time;
	struct tm* current_time_formatted;

	for (i = 0; i < (int)strlen(command); i++) {
		if (command[i] == '"') counter++;

		if (counter == 1 && command[i] != '"') {
			address[address_index] = command[i];
			address_index++;
		}
		else if (counter == 2 && command[i] != '"') {
			params[params_index] = command[i];
			params_index++;
		}
	}
	address[address_index] = '\0';
	params[params_index] = '\0';

	address = (char*)realloc(address, (strlen(address) + 1) * sizeof(char));
	params = (char*)realloc(params, (strlen(params) + 1) * sizeof(char));

	if (apartments->tail == NULL) {
		new_apartment.id = 1;
	}
	else {
		new_apartment.id = apartments->tail->data.id + 1;
	}
	new_apartment.address = address;
	sscanf(params, "%d %hd %hd %hd %hd", &(new_apartment.price), &(new_apartment.rooms), &(new_apartment.entry_day), &(new_apartment.entry_month), &(new_apartment.entry_year));

	time(&current_time);
	current_time_formatted = localtime(&current_time);
	new_apartment.created_day = current_time_formatted->tm_mday;
	new_apartment.created_month = current_time_formatted->tm_mon + 1;
	new_apartment.created_year = current_time_formatted->tm_year - 100;

	free(params);
	return new_apartment;
}

void parseGetCommand(char* command, int* minimum_rooms, int* maximum_rooms, int* maximum_price, int* date, int* sort) {
	char* delimiters = " ";
	char* parameters = strtok(command, delimiters);

	parameters = strtok(NULL, delimiters);
	while (parameters != NULL) {
		if (strcmp("-MinimumNumRooms", parameters) == 0) {
			parameters = strtok(NULL, delimiters);
			sscanf(parameters, "%d", minimum_rooms);
		}
		else if (strcmp("-MaximumNumRooms", parameters) == 0) {
			parameters = strtok(NULL, delimiters);
			sscanf(parameters, "%d", maximum_rooms);
		}
		else if (strcmp("-MaximumPrice", parameters) == 0) {
			parameters = strtok(NULL, delimiters);
			sscanf(parameters, "%d", maximum_price);
		}
		else if (strcmp("-Date", parameters) == 0) {
			parameters = strtok(NULL, delimiters);
			sscanf(parameters, "%d", date);
		}
		else if (strcmp("-s", parameters) == 0) {
			*sort = SORT_LOW_TO_HIGH;
		}
		else if (strcmp("-sr", parameters) == 0) {
			*sort = SORT_HIGH_TO_LOW;
		}
		parameters = strtok(NULL, delimiters);
	}
}

char* parseReconstructionGetOriginalCommand(char command_number, char* short_term_history[], int short_history_size, CommandsList* long_term_history) {
	CommandNode* command_node;
	char* result;
	int command_id, i;

	if (command_number == '!') {
		result = (char*)calloc(strlen(short_term_history[0]) + 1, sizeof(char));
		strcpy(result, short_term_history[0]);
	}
	else {
		command_id = command_number - '0';
		if (command_id <= long_term_history->size) {
			command_node = long_term_history->tail;
			for (i = 1; i < command_id; i++) {
				command_node = command_node->previous;
			}
			result = (char*)calloc(strlen(command_node->data) + 1, sizeof(char));
			strcpy(result, command_node->data);
		}
		else {
			i = short_history_size - 1;
			while (short_term_history[i] == NULL) i--;
			i -= command_id - long_term_history->size - 1;
			result = (char*)calloc(strlen(short_term_history[i]) + 1, sizeof(char));
			strcpy(result, short_term_history[i]);
		}
	}

	return result;
}

void parseReconstructionGetStrings(char* command, char** old_string, char** new_string) {
	*old_string = (char*)calloc(strlen(command) + 1, sizeof(char));
	*new_string = (char*)calloc(strlen(command) + 1, sizeof(char));
	int i, count, old_index = 0, new_index = 0;

	for (i = 0, count = 0; command[i] != '\0'; i++) {
		if (command[i] == '^') count++;
		else if (count == 1) {
			(*old_string)[old_index] = command[i];
			old_index++;
		}
		else if (count == 2) {
			(*new_string)[new_index] = command[i];
			new_index++;
		}
	}
	(*old_string)[old_index] = '\0';
	(*new_string)[new_index] = '\0';

	*old_string = (char*)realloc(*old_string, (old_index + 1) * sizeof(char));
	*new_string = (char*)realloc(*new_string, (new_index + 1) * sizeof(char));
}

char* parseReconstructionReplaceStrings(const char* command, const char* old_string, const char* new_string) {
	char* result;
	int i, cnt = 0;
	int new_string_len = strlen(new_string);
	int old_string_len = strlen(old_string);

	for (i = 0; command[i] != '\0'; i++) {
		if (strstr(&command[i], old_string) == &command[i]) {
			cnt++;
			i += old_string_len - 1;
		}
	}

	result = (char *)malloc(i + cnt * (new_string_len - old_string_len) + 1);

	i = 0;
	while (*command) {
		if (strstr(command, old_string) == command) {
			strcpy(&result[i], new_string);
			i += new_string_len;
			command += old_string_len;
		}
		else
			result[i++] = *command++;
	}

	result[i] = '\0';
	return result;
}

void compressRoomsAndEntryDate(unsigned char* arr, Apartment* apartment) {

	arr[0] = apartment->rooms << 0x4;
	arr[0] |= apartment->entry_day >> 0x1;
	arr[1] = apartment->entry_day << 0x7;
	arr[1] |= apartment->entry_month << 0x3;
	arr[1] |= 0x7 & (apartment->entry_year >> 0x4);
	arr[2] = apartment->entry_year << 0x4;
}

void compressCreatedDate(unsigned char* arr, Apartment* apartment) {
	arr[0] = apartment->created_day << 0x3;
	arr[0] |= apartment->created_month >> 0x1;
	arr[1] = apartment->created_month << 0x7;
	arr[1] |= apartment->created_year;
}

void saveDataToFiles(char* short_term_history[], int short_history_size, CommandsList* long_term_history, ApartmentsList* apartments) {
	FILE* commands_file = fopen(COMMANDS_FILE, "w");
	CommandNode* current_command = long_term_history->head;

	FILE* apartments_file = fopen(APARTMENTS_FILE, "wb");
	ApartmentNode* current_apartment = apartments->head;
	short int address_length;
	unsigned char rooms_entry_date_bytes[3], created_date_bytes[2];


	// save commands to text file
	for (int i = 0; i < short_history_size; i++) {
		if (short_term_history[i] != NULL) {
			fprintf(commands_file, "%s\n", short_term_history[i]);
		}
	}
	while (current_command != NULL) {
		fprintf(commands_file, "%s\n", current_command->data);
		current_command = current_command->next;
	}
	fclose(commands_file);

	// save apartments to binary file
	while (current_apartment != NULL) {
		address_length = (short int)strlen(current_apartment->data.address);
		compressRoomsAndEntryDate(rooms_entry_date_bytes, &(current_apartment->data));
		compressCreatedDate(created_date_bytes, &(current_apartment->data));

		fwrite(&(current_apartment->data.id), sizeof(short int), 1, apartments_file);
		fwrite(&(address_length), sizeof(short int), 1, apartments_file);
		fwrite(current_apartment->data.address, sizeof(char), address_length, apartments_file);
		fwrite(&(current_apartment->data.price), sizeof(int), 1, apartments_file);
		fwrite(rooms_entry_date_bytes, sizeof(unsigned char), 3, apartments_file);
		fwrite(created_date_bytes, sizeof(unsigned char), 2, apartments_file);

		current_apartment = current_apartment->next;
	}

	fclose(apartments_file);
}

void getDataFromFiles(char* short_term_history[], int short_history_size, CommandsList* long_term_history, ApartmentsList* apartments) {
	FILE* commands_file = fopen(COMMANDS_FILE, "r");
	int physical_size, logical_size, commands_file_size;
	char* current_command;
	char ch;

	FILE* apartments_file = fopen(APARTMENTS_FILE, "rb");
	Apartment current_apartment;
	short int address_length;
	unsigned char bytes[5] = { 0,0,0,0,0 };
	unsigned char mask;
	int apartments_file_size;


	// get commands from text file
	if (commands_file != NULL) {
		fseek(commands_file, 0, SEEK_END);
		commands_file_size = ftell(commands_file);
		rewind(commands_file);


		while (ftell(commands_file) < commands_file_size) {
			physical_size = 1;
			logical_size = 0;
			current_command = (char*)calloc(physical_size, sizeof(char));

			ch = fgetc(commands_file);
			while (ch != '\n' && ch != EOF) {
				if (physical_size == logical_size + 1) {
					physical_size *= 2;
					current_command = (char*)realloc(current_command, physical_size * sizeof(char));
				}

				current_command[logical_size] = ch;
				logical_size++;
				ch = fgetc(commands_file);
			}
			current_command[logical_size] = '\0';
			logical_size++;

			if (physical_size != logical_size)
				current_command = (char*)realloc(current_command, logical_size * sizeof(char));

			saveCommandToEnd(current_command, short_term_history, short_history_size, long_term_history);
			free(current_command);
		}
		fclose(commands_file);
	}

	// get apartments from binary file
	if (apartments_file != NULL) {
		fseek(apartments_file, 0, SEEK_END);
		apartments_file_size = ftell(apartments_file);
		rewind(apartments_file);

		while (ftell(apartments_file) < apartments_file_size) {
			fread(&(current_apartment.id), sizeof(short int), 1, apartments_file);
			fread(&address_length, sizeof(short int), 1, apartments_file);
			current_apartment.address = (char*)calloc(address_length + 1, sizeof(char));
			fread(current_apartment.address, sizeof(char), address_length, apartments_file);
			current_apartment.address[address_length] = '\0';
			fread(&(current_apartment.price), sizeof(int), 1, apartments_file);
			fread(bytes, sizeof(unsigned char), 5, apartments_file);
			current_apartment.rooms = bytes[0] >> 4;
			mask = 0xF;
			mask = (mask & bytes[0]) << 1;
			mask = mask | (bytes[1] >> 7);
			current_apartment.entry_day = mask;
			mask = 0x78;
			mask = mask & bytes[1];
			mask = mask >> 3;
			current_apartment.entry_month = mask;
			mask = 0x7;
			mask = mask & bytes[1];
			mask = (mask << 4) | (bytes[2] >> 4);
			current_apartment.entry_year = mask;
			mask = bytes[3] >> 3;
			current_apartment.created_day = mask;
			mask = 0x7;
			mask = (mask & bytes[3]) << 1;
			mask = mask | (((bytes[4] & (unsigned char)0x80) >> 7));
			current_apartment.created_month = mask;
			current_apartment.created_year = (bytes[4] & (unsigned char)0x7F); //
			insertApartmentToList(current_apartment, DEFAULT_FILTER, apartments);
		}
		fclose(apartments_file);
	}
}
