// final project
// apartments_list.h
// Name: Bar Vilenski 
// I.D : 204519854
// Name: Shira Yad Shalom
// I.D : 315780486
// Date: 04.06.18

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <time.h>

typedef struct apartment {
	short int id;
	int price;
	char* address;
	short int rooms;
	short int entry_day;
	short int entry_month;
	short int entry_year;
	short int created_day;
	short int created_month;
	short int created_year;
}Apartment;

typedef struct apartment_node {
	Apartment data;
	struct apartment_node*  next;
	struct apartment_node*  previous;
}ApartmentNode;

typedef struct apartments_list {
	ApartmentNode* head;
	ApartmentNode* tail;
}ApartmentsList;

/*
This function initializes an apartments list.
*/
void initializeApartmentsList(ApartmentsList* lst);
/*
This function checks if an apartments list is empty.
*/
int isEmptyApartmentsList(ApartmentsList* lst);
/*
This function gets apartment data.
It generates and returns an apartment node.
*/
ApartmentNode* createNewApartmentNode(Apartment data, ApartmentNode* previous, ApartmentNode* next);
/*
This function inserts an apartment into the list according to the sort type.
*/
void insertApartmentToList(Apartment data, int sort_type, ApartmentsList* lst);
/*
This function removes an apartment from the list according to the input id.
*/
void removeApartmentFromList(int id, ApartmentsList* lst);
/*
This function frees an apartments list.
*/
void freeApartmentsList(ApartmentsList* lst);
/*
This function filters an apartments list according to the input parameters.
*/
ApartmentsList* filterApartmentsList(ApartmentsList* apartments, int min_rooms, int max_rooms, int max_price, int max_date, int sort_type);
/*
This function checks if a specific apartment complies with the input parameters.
*/
int apartmentComplyWithFilters(ApartmentNode* apt, int min_rooms, int max_rooms, int max_price, int max_date);
/*
This function checks if the entry date of the apartment is valid.
*/
int checkApartmentEntryDate(ApartmentNode* apt, int date);
/*
This function checks if the creation date of an apartment is valid.
*/
int checkApartmentCreationDate(ApartmentNode* apt, int last_days);
