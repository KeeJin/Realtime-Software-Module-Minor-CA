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
void SaveCurrentDB(char filepath[], LinkedList *ll);

void LoadRequest(LinkedList* ll);
LinkedList* LoadDB(char filepath[]);

#endif /* MENU_COMPONENTS */
