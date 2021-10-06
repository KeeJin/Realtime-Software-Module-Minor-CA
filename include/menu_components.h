#ifndef MENU_COMPONENTS
#define MENU_COMPONENTS

#include "linked_list_struct.h"
#include "graphical.h"

int MainMenu(LinkedList *ll, const char* file_path);
void PrintMenuHeader();
void PrintMenuOptions();
void GetUserMenuOption(char* user_input_ptr);

void DataQuery(LinkedList *ll);
void DataEntry(LinkedList *ll);

void SaveRequest(LinkedList* ll);
void SaveCurrentDB(LinkedList *ll, char filepath[]);

void LoadRequest(LinkedList* ll);
void LoadDB(LinkedList* ll, char filepath[]);

float ShapeChecker(int type, int dimension);
int ObjectType(char *message);

#endif /* MENU_COMPONENTS */
