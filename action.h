// final project
// action.h
// Name: Bar Vilenski 
// I.D : 204519854
// Name: Shira Yad Shalom
// I.D : 315780486
// Date: 04.06.18

#include "input_output.h"

/*
This function gets the command string, short term history array, its size and the long term history list.
It executes the matching action to the data in the command string and saves the command afterwards.
*/
void executeAndSaveCommand(char* command, char* short_term_history[], int short_history_size, CommandsList* long_term_history, ApartmentsList* apartments);
/*
This function adds an apartment to the list of apartments.
*/
void addApartment(char* command, ApartmentsList* apartments);
/*
This function gets a list of apartments and prints it.
(The list consist of only the apartments that comply with the filters in the command string).
*/
void getApartment(char* command, ApartmentsList* apartments);
/*
This function buys an apartment (which means to delete it from the list).
*/
void buyApartment(char* command, ApartmentsList* apartments);
/*
This function deletes apartments from the list (according to the filter in the command string).
*/
void deleteApartment(char* command, ApartmentsList* apartments);
/*
This function recreates a previous command,
it changes the data of the command (according to the desired changes of the user),
and finally it executes and saves the new command.
*/
void reconstructCommand(char* command, char* short_term_history[], int short_history_size, CommandsList* long_term_history, ApartmentsList* apartments);
