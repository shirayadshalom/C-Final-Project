// Final Project
// input_output.h
// Name: Bar Vilenski 
// I.D : 204519854
// Name: Shira Yad Shalom
// I.D : 315780486
// Date: 04.06.18

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "commands_list.h"
#include "apartments_list.h"

#define COMMANDS_FILE "commands_db.txt"
#define APARTMENTS_FILE "apartments_db.bin"

#define ADD_APT 100
#define GET_APT 101
#define BUY_APT 102
#define DELETE_APT 103
#define RECONSTRUCTION 104
#define SHORT_TERM_HISTORY 105
#define LONG_TERM_HISTORY 106
#define EXIT 107
#define ERROR_ACTION -100

#define DEFAULT_FILTER -200
#define MINIMUM_ROOMS 201
#define MAXIMUM_ROOMS 202
#define MAXIMUM_PRICE 203
#define DATE 204
#define SORT_LOW_TO_HIGH 205
#define SORT_HIGH_TO_LOW 206


/*
This function prints the start message.
*/
void printStartMessage();
/*
This function prints the end message.
*/
void printEndMessage();
/*
This function prints the commands in the short term history array.
*/
void printShortTermHistory(char* short_term_history[], int short_history_size, int long_history_size);
/*
This function prints the commands in the long term history list.
*/
void printLongTermHistory(CommandsList* long_term_history);
/*
This function gets a pointer to an apartment and prints the data of the apartment.
*/
void printApartment(ApartmentNode* apt);
/*
This function gets a list of apartments and prints the data of all of the apartments.
*/
void printApartmentsList(ApartmentsList* apartments);
/*
This function gets the command from the input,
it creates a string out of it and retruns a pointer to it.
*/
char* getCommandFromInput();
/*
This function gets a command string and returns an integer which represents the type of the command.
*/
int parseCommandAction(char* command);
/*
This function gets a command string and the apartments list.
It generates and returns a new apartment according to the data in the command string and the apartments list.
*/
Apartment parseAddCommand(char* command, ApartmentsList* apartments);
/*
This function gets a command string and output parameters.
It updates the output parameters according to the data in the command string.
*/
void parseGetCommand(char* command, int* minimum_rooms, int* maximum_rooms, int* maximum_price, int* date, int* sort);
/*
This function gets a command number character, short term history array, its size and a long term history list.
It gets and returns the command with the id that matches the command number.
*/
char* parseReconstructionGetOriginalCommand(char command_number, char* short_term_history[], int short_history_size, CommandsList* long_term_history);
/*
This function gets a command string and output parameters.
It updates the output parameters with the string to replace and the replacing string accoirding to the data in the command string.
*/
void parseReconstructionGetStrings(char* command, char** old_string, char** new_string);
/*
This function gets a command string and two other strings.
It replaces the occurrences of the old_string in the command string with the new_string.
*/
char* parseReconstructionReplaceStrings(const char* command, const char* old_string, const char* new_string);
/*
This function compresses the number of rooms and the entry date of an apartment into 3 bytes.
*/
void compressRoomsAndEntryDate(unsigned char* arr, Apartment* apartment);
/*
This function compresses the creation date of an apartment into 2 bytes.
*/
void compressCreatedDate(unsigned char* arr, Apartment* apartment);
/*
This function saves the commands to a text file and the apartments to a binary file.
*/
void saveDataToFiles(char* short_term_history[], int short_history_size, CommandsList* long_term_history, ApartmentsList* apartments);
/*
This function reads the data of the commands and apartments from the files and populates it into the matching array and lists.
*/
void getDataFromFiles(char* short_term_history[], int short_history_size, CommandsList* long_term_history, ApartmentsList* apartments);
