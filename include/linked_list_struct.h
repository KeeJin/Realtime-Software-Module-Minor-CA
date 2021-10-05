#ifndef LINKED_LIST_STRUCT
#define LINKED_LIST_STRUCT

#define PI 3.14159265359

#include <stdlib.h>
#include <stdio.h>
// #include <stddef.h>
// const float pi = 3.14159265359;


/* ---------- structures for actual data storage ------------- */
typedef struct _listnode {
  int type;                // shape and 2/3D
  float d1;                // first dimension
  float d2;                // second dimension
  float d3;                // third dimension
  float c1;                // area for 2D, surface area for 3D
  float c2;                // perimeter for 2D, volume for 3D
  struct _listnode *next;  // address to next node
} ListNode;

typedef struct _linkedlist {
  int size;
  ListNode *head;
  ListNode *tail;
  float SD_c1[9];  // 9 for 9 different shapes in the order:
                   // 11,21,31,41,12,22,32,42,52
  float SD_c2[9];
  float mean_c1[9];
  float mean_c2[9];
  int count[9];
} LinkedList;


/* ----------- structures for data extraction ------------- */
typedef struct _listnodeEx {
  float item;
  struct _listnodeEx *next;
} ListNodeEx;

typedef struct _linkedlistEx {
  int size;
  ListNodeEx *head;
  ListNodeEx *tail;
} LinkedListEx;


/* ----------------------- helper functions ---------------------------- */
int Calculate(LinkedList *ll, int type, float d1, float d2, float d3,
               float *c1, float *c2);
int Extract(LinkedList *ll, LinkedListEx *ex, int t1, int selector);
void PrintList(LinkedList *ll);
void PrintListEx(LinkedListEx *ll);
ListNode *FindNode(LinkedList *ll, int index);
int InsertNodeForMainLL(LinkedList *ll, int index, int t1, float d1, float d2,
                        float d3);
int RemoveNode(LinkedList *ll, int index);
int InsertNodeEx(LinkedListEx *ll, int index, int value);
int FreeMem(LinkedList *ll);
int FreeMemEx(LinkedListEx *ll);

#endif /* LINKED_LIST_STRUCT */
