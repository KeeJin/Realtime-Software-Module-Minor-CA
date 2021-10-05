#include "menu_components.h"

int main(int argc, char* argv[]) {
  char* file_path;
  file_path = (char*)"test";
  LinkedList main_list;
  main_list.head = NULL;
  main_list.tail = 0;
  main_list.size = 0;

  for(int i = 0; i<9; i++)
  {
    main_list.SD_c1[i] = 0;
    main_list.SD_c2[i] = 0;
    main_list.mean_c1[i] = 0;
    main_list.mean_c2[i] = 0;
  }




  while (MainMenu(&main_list, file_path));

  if (!FreeMem(&main_list)) {
    printf("Warning: memory free failed.\n");
  }
  return 1;
}