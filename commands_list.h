// Final Project
// commands_list.h
// Name: Bar Vilenski 
// I.D : 204519854
// Name: Shira Yad Shalom
// I.D : 315780486
// Date: 04.06.18

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>

typedef struct command_node {
	char*  data;
	struct command_node*  next;
	struct command_node*  previous;
}CommandNode;

typedef struct commands_list {
	CommandNode* head;
	CommandNode* tail;
	int size;
}CommandsList;

/*
This function initializes a commands list.
*/
void initializeCommandsList(CommandsList* lst);
/*
This function checks if a commands list is empty.
*/
int isEmptyCommandsList(CommandsList* lst);
/*
This function gets the command string and returns a command node generated out of that data.
*/
CommandNode* createNewCommandNode(char* data, CommandNode* previous, CommandNode* next);
/*
This function inserts a command into the start of the commands list.
*/
void insertToStartOfCommandsList(char* command, CommandsList* lst);
/*
This function inserts a command into the end of the commands list.
*/
void insertToEndOfCommandsList(char* command, CommandsList* lst);
/*
This function frees a commands list.
*/
void freeCommandsList(CommandsList* lst);
/*
This function checks of the array of commands is full or not.
*/
int isFullArray(char* arr[], int size);
/*
This function inserts a commnand to the start of the array.
*/
void addToStartOfArray(char* command, char* arr[], int size);
/*
This function inserts a commnand to the end of the array.
*/
void addToEndOfArray(char* command, char* arr[], int size);
/*
This functionn saves the input command into the start of the array or list as needed.
*/
void saveCommand(char* command, char* short_term_history[], int short_history_size, CommandsList* long_term_history);
/*
This functionn saves the input command into the end of the array or list as needed.
*/
void saveCommandToEnd(char* command, char* short_term_history[], int short_history_size, CommandsList* long_term_history);
