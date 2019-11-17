// final project
// apartments_list.c
// Name: Bar Vilenski 
// I.D : 204519854
// Name: Shira Yad Shalom
// I.D : 315780486
// Date: 04.06.18

#include "apartments_list.h"

#define DEFAULT_FILTER -200
#define SORT_LOW_TO_HIGH 205
#define SORT_HIGH_TO_LOW 206

void initializeApartmentsList(ApartmentsList* lst) {
	lst->head = NULL;
	lst->tail = NULL;
}

int isEmptyApartmentsList(ApartmentsList* lst) {
	return lst->head == NULL;
}

ApartmentNode* createNewApartmentNode(Apartment data, ApartmentNode* previous, ApartmentNode* next) {
	ApartmentNode* new_node = (ApartmentNode*)malloc(sizeof(ApartmentNode));

	new_node->data = data;
	new_node->previous = previous;
	new_node->next = next;

	return new_node;
}

void insertApartmentToList(Apartment data, int sort_type, ApartmentsList* lst) {
	ApartmentNode* new_node = createNewApartmentNode(data, NULL, NULL);
	ApartmentNode* temp = lst->head;

	if (isEmptyApartmentsList(lst)) {
		lst->head = new_node;
		lst->tail = new_node;
	}
	else {
		switch (sort_type) {
		case SORT_LOW_TO_HIGH:
			while (temp != NULL && temp->data.price <= new_node->data.price)
				temp = temp->next;
			break;
		case SORT_HIGH_TO_LOW:
			while (temp != NULL && temp->data.price >= new_node->data.price)
				temp = temp->next;
			break;
		default:
			temp = NULL;
			break;
		}

		if (temp == lst->head) {
			new_node->next = lst->head;
			lst->head->previous = new_node;
			lst->head = new_node;
		}
		else if (temp == NULL) {
			new_node->previous = lst->tail;
			lst->tail->next = new_node;
			lst->tail = new_node;
		}
		else {
			new_node->previous = temp->previous;
			new_node->next = temp;
			temp->previous->next = new_node;
			temp->previous = new_node;
		}
	}
}

void removeApartmentFromList(int id, ApartmentsList* lst) {
	ApartmentNode *current = lst->tail;

	while (current != NULL && current->data.id != id) {
		current = current->previous;
	}

	if (current != NULL) {
		if (current == lst->tail) {
			current->previous->next = NULL;
			lst->tail = current->previous;
		}
		else if (current == lst->head) {
			current->next->previous = NULL;
			lst->head = current->next;
		}
		else {
			current->previous->next = current->next;
			current->next->previous = current->previous;
		}

		free(current);
	}
}

void freeApartmentsList(ApartmentsList* lst) {
	ApartmentNode* current = lst->head;
	ApartmentNode* next;

	while (current) {
		next = current->next;
		free(current);
		current = next;
	}

	lst->head = NULL;
}

ApartmentsList* filterApartmentsList(ApartmentsList* apartments, int min_rooms, int max_rooms, int max_price, int max_date, int sort_type) {
	ApartmentsList* new_list = (ApartmentsList*)malloc(sizeof(ApartmentsList));
	ApartmentNode* current = apartments->head;

	initializeApartmentsList(new_list);

	while (current != NULL) {
		if (apartmentComplyWithFilters(current, min_rooms, max_rooms, max_price, max_date)) {
			insertApartmentToList(current->data, sort_type, new_list);
		}
		current = current->next;
	}

	return new_list;
}

int apartmentComplyWithFilters(ApartmentNode* apt, int min_rooms, int max_rooms, int max_price, int max_date) {
	int is_complying = 1;

	if (min_rooms != DEFAULT_FILTER)
		if (apt->data.rooms < min_rooms)
			is_complying = 0;
	if (max_rooms != DEFAULT_FILTER)
		if (apt->data.rooms > max_rooms)
			is_complying = 0;
	if (max_price != DEFAULT_FILTER)
		if (apt->data.price > max_price)
			is_complying = 0;
	if (max_date != DEFAULT_FILTER)
		if (!checkApartmentEntryDate(apt, max_date))
			is_complying = 0;


	return is_complying;
}

int checkApartmentEntryDate(ApartmentNode* apt, int date) {
	short int max_day, max_month, max_year;

	max_year = date % 10000;
	date /= 10000;
	max_month = date % 100;
	date /= 100;
	max_day = date % 100;

	if (max_year < apt->data.entry_year + 2000) return 0;
	else if (max_year > apt->data.entry_year + 2000) return 1;
	else {
		if (max_month < apt->data.entry_month) return 0;
		else if (max_month > apt->data.entry_month) return 1;
		else {
			if (max_day < apt->data.entry_day) return 0;
			else return 1;
		}
	}
}

int checkApartmentCreationDate(ApartmentNode* apt, int last_days) {
	time_t last_date;
	struct tm* last_date_formatted;
	int last_seconds = last_days * 24 * 60 * 60;

	time(&last_date);
	last_date -= last_seconds;
	last_date_formatted = localtime(&last_date);

	if (last_date_formatted->tm_year - 100 > apt->data.created_year) return 0;
	else if (last_date_formatted->tm_year - 100 < apt->data.created_year) return 1;
	else {
		if (last_date_formatted->tm_mon + 1 > apt->data.created_month) return 0;
		else if (last_date_formatted->tm_mon + 1 < apt->data.created_month) return 1;
		else {
			if (last_date_formatted->tm_mday > apt->data.created_day) return 0;
			else return 1;
		}
	}
}
