#include <stdio.h>
#include <string.h>
#include <math.h>
#include "linked_list_struct.h"


void Display(int shape, LinkedList *ll, LinkedListEx *ex);

void Graphical(int type, float* value_D1, float* value_D2, float* value_D3, float* value_C1, float* value_C2, 
	int num_values, float SD_C1, float SD_C2, float mean_C1, float mean_C2);

void DrawGraph(float *values, int num_values);

void Divider(char* type_D2, char* type_D3, int type);

void DrawTable(char* type_D1, char* type_D2, char* type_D3, char* type_C1, char* type_C2, float *value_D1, float* value_D2, 
	float* value_D3, float* value_C1, float* value_C2, int num_values, float SD_C1, float SD_C2, float mean_C1, float mean_C2);

void ConvertListEx(LinkedListEx* ll, int num_values, float *temp_list);

void CopyList(float* value, int num_values, float* temp_list);