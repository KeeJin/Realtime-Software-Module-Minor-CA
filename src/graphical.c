
#include <stdio.h>
#include <stdlib.h>
#include "graphical.h"



//default: "-"; 1: "_", 2: "=", 3: " " 
void Divider(char* type_D2, char* type_D3, int type)
{
	switch (type)
	{
	case 1: //Top (Underscore)
		printf(" ______________");
		if (type_D2[0]) printf("_______________");
		if (type_D3[0]) printf("_______________");
		printf("_______________");
		printf("_______________\n");
		break;

	case 2: // "=" divider
		printf("|==============|");
		if (type_D2[0]) printf("==============|");
		if (type_D3[0]) printf("==============|");
		printf("==============|");
		printf("==============|\n");
		break;

	case 3: //Bot 
		printf("|______________|");
		if (type_D2[0]) printf("______________|");
		if (type_D3[0]) printf("______________|");
		printf("______________|");
		printf("______________|\n");
		break;

	default: // "-" divider
		printf("|--------------|");
		if (type_D2[0]) printf("--------------|");
		if (type_D3[0]) printf("--------------|");
		printf("--------------|");
		printf("--------------|\n");
		break;

	}
}

void DrawGraph(float *values, int num_values)
{
	int scale = 10;
	int i, j;
	int max_val = 0;
	int max_count = 0;
	int max_width = 180; // CHANGE THIS ACCORDING TO SCREEN SIZE or preference. Max 180 (for 1980x1080 res)


	for (i = 0; i < num_values; i++)
	{
		if ((int)values[i] > max_val) max_val = (int)values[i];
	}
	

	int min_val = max_val;

	for (i = 0; i < num_values; i++)
	{
		if ((int)values[i] < min_val) min_val = (int)values[i];
	}



	int freq_size = max_val - min_val;
	int step = ceil((float)freq_size / (float)scale);
	if (step < 1) step = 1;


	freq_size = freq_size / step + 1;


	int frequency[freq_size];
	for (i = 0; i < freq_size; i++)
	{
		frequency[i] = 0;
	}

	for (i = 0; i < num_values; i++)
	{
		int index = (int)(values[i] / step) - min_val / step;
		frequency[index]++;
		if (frequency[index] > max_count) max_count = frequency[index];
	}

	int spacer_size = max_width / max_count;
	if (!spacer_size) spacer_size = 1;
	char spacer[spacer_size];

	for (i = 0; i < spacer_size; i++)
	{
		spacer[i] = '_';
	}
	spacer[spacer_size] = '\0';


	for (i = 0; i < freq_size; i++)
	{
		if (i) printf("                 |");
		else printf("                  ");

		for (j = 0; j < frequency[i]; j++)
		{
			printf("%s", spacer);
		}

		printf("\n");

		printf("%4d <= x < %4d |", min_val + i * step, min_val + i * step + step);
		for (j = 0; j < frequency[i]; j++)
		{
			printf("%s", spacer);
		}

		if (frequency[i]) printf("|");
		printf("\n");
		if (freq_size - i - 1) printf("                 |\n");

	}

}

void DrawTable(char* type_D1, char* type_D2, char* type_D3, char* type_C1, char* type_C2, float *value_D1, float* value_D2, 
	float* value_D3, float* value_C1, float* value_C2, int num_values, float SD_C1, float SD_C2, float mean_C1, float mean_C2)
{
	//Header

	Divider(type_D2, type_D3, 1);

	printf("|%13s |", type_D1);
	if (type_D2[0]) printf("%13s |", type_D2);
	if (type_D3[0]) printf("%13s |", type_D3);
	printf("%13s |", type_C1);
	printf("%13s |\n", type_C2);

	Divider(type_D2, type_D3, 2);

	//Body

	for (int i = 0; i < num_values; i++)
	{
		printf("|%13.2f |", value_D1[i]);
		if (type_D2[0]) printf("%13.2f |", value_D2[i]);
		if (type_D3[0]) printf("%13.2f |", value_D3[i]);
		printf("%13.2f |", value_C1[i]);
		printf("%13.2f |\n", value_C2[i]);

		Divider(type_D2, type_D3, 0);
	}

	//Mean
	printf("|     MEAN     |");
	if (type_D2[0]) printf("     MEAN     |");
	if (type_D3[0]) printf("     MEAN     |");
	printf("%13.2f |", mean_C1);
	printf("%13.2f |\n", mean_C2);

	//SD
	Divider(type_D2, type_D3, 0);
	printf("|      SD      |");
	if (type_D2[0]) printf("      SD      |");
	if (type_D3[0]) printf("      SD      |");
	printf("%13.2f |", SD_C1);
	printf("%13.2f |\n", SD_C2);

	//END
	Divider(type_D2, type_D3, 3);

}

void Graphical(int type, float* value_D1, float* value_D2, float* value_D3, float* value_C1, float* value_C2, 
	int num_values, float SD_C1, float SD_C2, float mean_C1, float mean_C2)

{
	char c1_2D[] = "Area";
	char c2_2D[] = "Perimeter";
	char c1_3D[] = "Volume";
	char c2_3D[] = "Surface Area";
	char type_C1[13];
	char type_C2[7];

	char length[] = "Length";
	char width[] = "Width";
	char height[] = "Height";
	char base[] = "Base";
	char radius[] = "Radius";

	char type_D1[7] = "";
	char type_D2[7] = "";
	char type_D3[7] = "";



	switch (type)
	{
	case 11: //2D rectangle
		printf("2D Rectangle\n");
		strcpy(type_D1, length);
		strcpy(type_D2, width);
		break;

	case 21: //2D Square
		printf("2D Square\n");
		strcpy(type_D1, length);
		break;

	case 31: //2D circle
		printf("2D Circle\n");
		strcpy(type_D1, radius);
		break;

	case 41: //2D right angle triangle
		printf("2D Triangle\n");
		strcpy(type_D1, base);
		strcpy(type_D2, height);
		break;

	case 12: //3D cude
		printf("3D Cube\n");
		strcpy(type_D1, length);
		break;

	case 22: //3D block
		printf("3D Block\n");
		strcpy(type_D1, length);
		strcpy(type_D2, width);
		strcpy(type_D3, height);
		break;

	case 32: //3D cylinder
		printf("3D Cylinder\n");
		strcpy(type_D1, radius);
		strcpy(type_D2, height);
		break;

	case 42: //3D sphere
		printf("3D Sphere\n");
		strcpy(type_D1, radius);
		break;

	case 52: //3D cone
		printf("3D Cone\n");
		strcpy(type_D1, radius);
		strcpy(type_D2, height);
		break;

	default:
		printf("Error: none of type matches pre programmed types\n");
		break;

	}


	if (type % 10 == 1)
	{
		// 2D
		strcpy(type_C1, c1_2D);
		strcpy(type_C2, c2_2D);
	}

	else
	{
		//3D
		strcpy(type_C1, c1_3D);
		strcpy(type_C2, c2_3D);
	}



	printf("\n==============\n");
	printf("Histogram Plot\n");
	printf("==============\n");


	printf("%s:\n", type_C1);
	DrawGraph(value_C1, num_values);
	printf("\n\n");


	printf("%s:\n", type_C2);
	DrawGraph(value_C2, num_values);
	printf("\n\n");

	printf("\n==============\n");
	printf("     Table\n");
	printf("==============\n");

	DrawTable(type_D1, type_D2, type_D3, type_C1, type_C2, value_D1, value_D2, value_D3, value_C1, value_C2, num_values, SD_C1, SD_C2, mean_C1, mean_C2);
}


void Display(int shape, LinkedList *ll, LinkedListEx *ex)
{	
	//D1
	Extract(ll, ex, shape, 1); 
	int num_values = ex -> size;
	float temp_list[num_values];
	float value_D1[num_values], value_D2[num_values], value_D3[num_values], value_C1[num_values], value_C2[num_values];

	ConvertListEx(ex, num_values, temp_list);
	CopyList(value_D1, num_values, temp_list);
	
	
	//D2
	Extract(ll, ex, shape, 2);
	ConvertListEx(ex, num_values, temp_list);
	CopyList(value_D2, num_values, temp_list);

	//D3
	Extract(ll, ex, shape, 3);
	ConvertListEx(ex, num_values, temp_list);
	CopyList(value_D3, num_values, temp_list);

	//C1
	Extract(ll, ex, shape, 4);
	ConvertListEx(ex, num_values, temp_list);
	CopyList(value_C1, num_values, temp_list);

	//C2
	Extract(ll, ex, shape, 5);
	ConvertListEx(ex, num_values, temp_list);
	CopyList(value_C2, num_values, temp_list);

	//meanC1, SDC1, meanC2, SDC2, have not been extracted yet.

	float mean_C1 = ll -> mean_c1[shape];
	float SD_C1 = ll -> SD_c1[shape];
	float mean_C2 = ll -> mean_c2[shape];
	float SD_C2 = ll -> SD_c2[shape];


	// cant get actual to work yet
	mean_C1 = 10;
	SD_C1 = 20;
	mean_C2 = 30;
	SD_C2 = 40;


	Graphical(21, value_D1, value_D2, value_D3, value_C1, value_C2, num_values, SD_C1, SD_C2, mean_C1, mean_C2);
}


void ConvertListEx(LinkedListEx* ll, int num_values, float *temp_list)
{
	ListNodeEx* cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	int i = 0;
	while (cur != NULL)
	{
		temp_list[i] =  cur->item;
		cur = cur->next;
		i++;
	}
}

void CopyList(float* value, int num_values, float* temp_list) 
{
	int i;
	for (i = 0; i < num_values; i++) 
	{
		value[i] = temp_list[i];
	}
}




