#include "menu_components.h"

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
// #define QNX

void PrintMenuHeader() {
  printf("===============================\n");
  printf("SHAPE DATABASE SEARCH ENGINE\n");
  printf("===============================\n");
}
void PrintMenuOptions() {
  PrintMenuHeader();
  printf("\n-------------------------------\n");
  printf("MENU OPTIONS\n");
  printf("-------------------------------\n");
  printf("1. New Object\n");
  printf("2. Object Query\n");
  printf("3. Save Current Database\n");
  printf("4. Load a Database\n");
  printf("5. Exit Program\n");
  printf("-------------------------------\n\n");
}

void GetUserMenuOption(char* user_input_ptr) {
  int temp;
  int c;
  system("clear"); // comment this line for easy reading of error
  /*
  PrintMenuOptions();
  printf("Hello user, what would you like to do today? (1/2/3/4/5)\nOption: ");
  scanf("%c", user_input_ptr);
  while (getchar() != '\n')
    ;  // clear buffer
  */
  // below code to only allow 1 character input.
  printf("\n\n");  // to allow space for error printing.
  while (1) {
    PrintMenuOptions();
    printf("Hello user, what would you like to do today? (1/2/3/4/5)\n");
    // printf("Option: ");
    scanf("%d", &temp);
    while ((c = getchar()) != '\n' && c != EOF);

    if ((temp == 1) || (temp == 2) || (temp == 3) || (temp == 4) || (temp == 5))
      break;
    else {
      system("clear");
      printf("Invalid input! Please choose only 1, 2, 3, 4 or 5!\n\n");
    }
  }

  *user_input_ptr = (char)(temp + 48);
}

void DataEntry(LinkedList* ll) {
  int t1 = 0;
  float d1, d2, d3;

  char message[] = "Adding new object";
  t1 = ObjectType(&message[0]);

  d1 = ShapeChecker(t1, 1);
  d2 = ShapeChecker(t1, 2);
  d3 = ShapeChecker(t1, 3);

  if (InsertNodeForMainLL(ll, 0, t1, d1, d2, d3) == 0)
    printf("data entry failed.");

  else {
    printf("\n\nObject added successfully!\n");
    ShapeChecker(t1, 4);
    ShapeChecker(t1, 5);
    printf("%.5f\n", d1);
    if (d2) {
      ShapeChecker(t1, 6);
      printf("%.5f\n", d2);
    }
    if (d3) {
      ShapeChecker(t1, 7);
      printf("%.5f\n", d3);
    }
  }
  // uncomment this for debugging purposes.
  // printf("Current database contains the following: \n");
  // PrintList(ll);

  /* debgugging
        LinkedListEx extracted_list;
        extracted_list.head=NULL;
        extracted_list.tail=NULL;
        extracted_list.size=0;
  Extract(ll, &extracted_list, 11, 1);
  PrintListEx(&extracted_list);
  PrintList(ll);
  */

  /*
#ifdef QNX
  delay(1000);
#else
  sleep(1);
#endif
  printf("==========================================\n\n\n\n");*/
  printf("\n\n");
}

void DataQuery(LinkedList* ll) {
  // can comment this out later on if we dont want!!
  // printf("Current database contains the following: \n");
  // PrintList(ll);

  LinkedListEx extracted_list;
  extracted_list.head = NULL;
  extracted_list.tail = NULL;
  extracted_list.size = 0;

  LinkedListEx validity_check;
  validity_check.head = NULL;
  validity_check.tail = NULL;
  validity_check.size = 0;

  int t1;
  char message[] = "Object query selected.";
  t1 = ObjectType(&message[0]);

  Extract(ll, &validity_check, t1, 1);
  if (validity_check.size) {
    printf("\n\nData Query for: ");
    Display(t1, ll, &extracted_list);
  } else
    printf("\n\nItem does not exist yet!\n");
  printf("\n\n");
}

void SaveRequest(LinkedList* ll) {
  char filename[20];
  size_t len = 0;
  ssize_t line_size = 0;
  printf(
      "Enter your desired filename for this database (Hit enter to abort): ");
  // line_size = getline(&filename, &len, stdin);
  if (fgets(filename, 20, stdin) == NULL) {
    printf("Invalid filename entered. Aborting save...\n");
  } else {
    printf("This is what is being saved: \n");
    PrintList(ll);
    SaveCurrentDB(ll, filename);
  }
}
// function to save linked list to a file
void SaveCurrentDB(LinkedList* ll, char filepath[]) {
  ListNode* cached_node;

  FILE* file;
  file = fopen(filepath, "w");
  if (file == NULL) {
    printf("Couldn't write to file! Skipping save...\n");
    return;
  }

  // check if LinkedList is empty
  if (ll == NULL) {
    printf("Linked List is empty! Skipping save...\n");
    return;
  }

  // write LinkedList struct to file
  fwrite(ll, sizeof(LinkedList), 1, file);

  // write all the ListNodes of the linked list to the file
  cached_node = ll->head;
  while (cached_node != NULL) {
    if (fwrite(cached_node, sizeof(ListNode), 1, file) != 1) {
      printf("Error saving ListNode to file. \n");
      break;
    }
    printf("cached_node: \nd1 - %.3f, d2 - %.3f, d3 - %.3f", cached_node->d1,
           cached_node->d2, cached_node->d3);
    cached_node = cached_node->next;
  }
  printf("Database stored in the file successfully!\n");
  fclose(file);
}

void LoadRequest(LinkedList* ll) {
  char filename[20];
  size_t len = 0;
  ssize_t line_size = 0;
  char confirmation;
  printf(
      "Warning!! This will wipe out your current database. Do you wish to "
      "proceed? (Y/N)\n");
  scanf("%c", &confirmation);
  while (getchar() != '\n')
    ;  // clear buffer
  if (confirmation != 'y' && confirmation != 'Y') return;

  printf(
      "Enter the filename of the database you wish to load (Hit enter to "
      "abort): ");
  // line_size = getline(&filename, &len, stdin);
  if (fgets(filename, 20, stdin) == NULL) {
    printf("Invalid filename entered. Aborting save...\n");
  } else {
    FreeMem(ll);
    LoadDB(ll, filename);
  }
  // can comment this out later on if we dont want!!
  printf("Current database contains the following: \n");
  PrintList(ll);
  printf("==========================================\n\n\n\n");
}

// function to load linked list from a file
void LoadDB(LinkedList* ll, char filepath[]) {
  ListNode* cached_node = (ListNode*)malloc(sizeof(ListNode));
  // LinkedList* loaded_db = (LinkedList*)malloc(sizeof(LinkedList));
  ListNode* head;  // points to the first node of the linked list in the file
  ListNode* tail;  // points to the last node of the linked list in the file
  tail = head = NULL;

  // initialise linked list
  ll->head = NULL;
  ll->tail = 0;
  ll->size = 0;

  // try to open file
  FILE* file;
  file = fopen(filepath, "r");
  if (file == NULL) {
    printf("Couldn't load database. Defaulting to an empty one.\n");
    return;
  }

  // extract LinkedList struct
  if (!fread(ll, sizeof(LinkedList), 1, file)) {
    printf("Couldn't load database. Defaulting to an empty one.\n");
    return;
  }

  // reading nodes from the file
  // nodes are read in the same order as they were stored
  // we are using the data stored in the file to create a new linked list
  while (fread(cached_node, sizeof(ListNode), 1, file)) {
    if (head == NULL) {
      head = tail = (ListNode*)malloc(sizeof(ListNode));
    } else {
      tail->next = (ListNode*)malloc(sizeof(ListNode));
      tail = tail->next;
    }
    printf("cached_node: \nd1 - %.3f, d2 - %.3f, d3 - %.3f\n", cached_node->d1,
           cached_node->d2, cached_node->d3);
    tail->type = cached_node->type;
    tail->d1 = cached_node->d1;
    tail->d2 = cached_node->d2;
    tail->d3 = cached_node->d3;
    tail->c1 = cached_node->c1;
    tail->c2 = cached_node->c2;
    tail->next = NULL;
  }

  fclose(file);
  ll->head = head;
  ll->tail = tail;
  // PrintList(ll);
}

int MainMenu(LinkedList* ll, const char* file_path) {
  int c;
  PrintMenuHeader();
  while (1) {
    char user_option;
    GetUserMenuOption(&user_option);
    int error = 0;
    switch (user_option) {
      case '1':
        DataEntry(ll);
        printf("Press 'Enter' to continue...\n");
        while ((c = getchar()) != '\n' && c != EOF);
        break;
      case '2':
        DataQuery(ll);
        printf("Press 'Enter' to continue...\n");
        while ((c = getchar()) != '\n' && c != EOF);
        break;
      case '3':
        SaveRequest(ll);
        printf("Press 'Enter' to continue...\n");
        while ((c = getchar()) != '\n' && c != EOF);
        break;
      case '4':
        LoadRequest(ll);
        printf("Press 'Enter' to continue...\n");
        while ((c = getchar()) != '\n' && c != EOF);
        break;
      case '5':
        printf("Exiting program now. Goodbye!\n");
        printf("Press 'Enter' to continue...\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
        break;
      default:
        printf("Invalid option! Please try again.\n");
        printf("Press 'Enter' to continue...\n");
        while ((c = getchar()) != '\n' && c != EOF);
        error = 1;
        break;
    }
    if (error == 0) break;
  }
  // everything went smoothly, we can return true here
  return 1;
}

float ShapeChecker(int type, int dimension) {
  int c;
  float input_dimension = 0;
  char length[] = "Length";
  char width[] = "Width";
  char height[] = "Height";
  char base[] = "Base";
  char radius[] = "Radius";

  char type_D1[7] = "";
  char type_D2[7] = "";
  char type_D3[7] = "";
  char object_type[27];

  //Limits for input --> lower_limit <= x <= upper_limit
  const float upper_limit = 99.99999;
  const float lower_limit = 0.1;

  switch (type) {
    case 11:  // 2D rectangle
      strcpy(object_type, "2D Rectangle");
      strcpy(type_D1, length);
      strcpy(type_D2, width);
      break;

    case 21:  // 2D Square
      strcpy(object_type, "2D Square");
      strcpy(type_D1, length);
      break;

    case 31:  // 2D circle
      strcpy(object_type, "2D Circle");
      strcpy(type_D1, radius);
      break;

    case 41:  // 2D right angle triangle
      strcpy(object_type, "2D Right Angled Triangle");
      strcpy(type_D1, base);
      strcpy(type_D2, height);
      break;

    case 12:  // 3D cude
      strcpy(object_type, "3D Cube");
      strcpy(type_D1, length);
      break;

    case 22:  // 3D block
      strcpy(object_type, "3D Block");
      strcpy(type_D1, length);
      strcpy(type_D2, width);
      strcpy(type_D3, height);
      break;

    case 32:  // 3D cylinder
      strcpy(object_type, "3D Cylinder");
      strcpy(type_D1, radius);
      strcpy(type_D2, height);
      break;

    case 42:  // 3D sphere
      strcpy(object_type, "3D Sphere");
      strcpy(type_D1, radius);
      break;

    case 52:  // 3D cone
      strcpy(object_type, "3D Right Circular Cone");
      strcpy(type_D1, radius);
      strcpy(type_D2, height);
      break;

    default:
      printf("Error: none of type matches pre programmed types\n");
      break;
  }

  if ((dimension == 1) && type_D1[0]) {
    system("clear");
    printf("\n\n");
    while (1) {
      printf("Object Selected: %s\n", object_type);
      printf("Please enter object's %s (0 < x < 100, in m):\n", type_D1);
      scanf("%f", &input_dimension);  
      while ((c = getchar()) != '\n' && c != EOF);

      if ((lower_limit <= input_dimension) && (input_dimension <= upper_limit))
        break;
      else {
        system("clear");
        printf("Invalid input! Please enter a float value between 0 and 100!\n\n");
      }
    }
    system("clear");
    return input_dimension;
  }

  if ((dimension == 2) && type_D2[0]) {
    system("clear");
    printf("\n\n");
    while (1) {
      printf("Object Selected: %s\n", object_type);
      printf("Please enter object's %s (0 < x < 100, in m):\n", type_D2);
      scanf("%f", &input_dimension);
      while ((c = getchar()) != '\n' && c != EOF);

      if ((lower_limit <= input_dimension) && (input_dimension <= upper_limit))
        break;
      else {
        system("clear");
        printf("Invalid input! Please enter a float value between 0 and 100!\n\n");
      }
    }
    system("clear");
    return input_dimension;
  }

  if ((dimension == 3) && type_D3[0]) {
    system("clear");
    printf("\n\n");
    while (1) {
      printf("Object Selected: %s\n", object_type);
      printf("Please enter object's %s (0 < x < 100, in m):\n", type_D3);
      scanf("%f", &input_dimension);
      while ((c = getchar()) != '\n' && c != EOF);

      if ((lower_limit <= input_dimension) && (input_dimension <= upper_limit))
        break;
      else {
        system("clear");
        printf("Invalid input! Please enter a float value between 0 and 100!\n\n");
      }
    }
    system("clear");
    return input_dimension;
  }

  if (dimension == 4) {
    printf("Object Selected: %s\n\nDimensions Input:\n", object_type);
  }

  if (dimension == 5) {
    printf("%-7s = ", type_D1);
  }

  if (dimension == 6) {
    printf("%-7s = ", type_D2);
  }

  if (dimension == 7) {
    printf("%-7s = ", type_D3);
  }
}

int ObjectType(char* message) {
  system("clear");

  printf("\n\n");  // to allow space for error printing.

  int c;
  int t1_1 = 0;
  int t1_2 = 0;
  int t1 = 0;

  while (1) {
    printf("%s\n", message);
    printf("Please select object type:\n");
    printf("1. 2D\n");
    printf("2. 3D\n");
    // printf("Option: ");
    scanf("%d", &t1_1);
    while ((c = getchar()) != '\n' && c != EOF);

    if ((t1_1 == 1) || (t1_1 == 2))
      break;
    else {
      system("clear");
      printf("Invalid input! Please choose only 1 or 2!\n\n");
    }
  }

  system("clear");
  printf("\n\n");  // to allow space for error printing.

  if (t1_1 == 1)  // 2D
  {
    while (1) {
      printf("%s\n", message);
      printf("Please select object shape for 2D:\n");
      printf("1. Rectangle\n");
      printf("2. Square\n");
      printf("3. Circle\n");
      printf("4. Right Angled Triangle\n");
      // printf("Option: ");
      scanf("%d", &t1_2);
      while ((c = getchar()) != '\n' && c != EOF);

      if ((t1_2 == 1) || (t1_2 == 2) || (t1_2 == 3) || (t1_2 == 4))
        break;
      else {
        system("clear");
        printf("Invalid input! Please choose only 1, 2, 3 or 4!\n\n");
      }
    }
  }

  else  // 2D
  {
    while (1) {
      printf("%s\n", message);
      printf("Please select object shape for 3D:\n");
      printf("1. Cube\n");
      printf("2. Block\n");
      printf("3. Cylinder\n");
      printf("4. Sphere\n");
      printf("5. Right Circular Cone\n");
      // printf("Option: ");
      scanf("%d", &t1_2);
      while ((c = getchar()) != '\n' && c != EOF);

      if ((t1_2 == 1) || (t1_2 == 2) || (t1_2 == 3) || (t1_2 == 4) ||
          (t1_2 == 5))
        break;
      else {
        system("clear");
        printf("Invalid input! Please choose only 1, 2, 3, 4 or 5!\n\n");
      }
    }
  }

  system("clear");

  t1 = t1_1 + t1_2 * 10;
  return t1;
}
