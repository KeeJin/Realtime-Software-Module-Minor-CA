#include "linked_list_struct.h"
#include <math.h>

int Calculate(LinkedList *ll, int type, float d1, float d2, float d3, float *c1,
              float *c2) {
  int t1, shape, total_c1, total_c2, type_index, old_unique_count,
      new_unique_count;
  float variance, old_mean_c1, old_mean_c2, old_sd_c1, old_sd_c2;
  if (type == 0 || d1 == 0) {
    perror("Initialising error in Calculation\n");
    return 0;
  }
  switch (type) {
    case 11:  // 2D rectangle
      *c1 = (d1) * (d2);
      *c2 = 2 * (d1 + d2);
      type_index = 0;
      break;
    case 21:  // 2D Square
      *c1 = d1 * d1;
      *c2 = 4 * d1;
      type_index = 1;
      break;
    case 31:  // 2D circle
      *c1 = PI * d1 * d1;
      *c2 = PI * d1 * 2;
      type_index = 2;
      break;
    case 41:  // 2D right angle triangle
      *c1 = 0.5 * d1 * d2;
      *c2 = d1 + d2 + sqrt(d1 * d1 + d2 * d2);
      type_index = 3;
      break;
    case 12:  // 3D cude
      *c1 = pow(d1, 3);
      *c2 = 6 * d1 * d1;
      type_index = 4;
      break;
    case 22:  // 3D block
      *c1 = d1 * d2 * d3;
      *c2 = 2 * (d1 * d2 + d2 * d3 + d1 * d3);
      type_index = 5;
      break;
    case 32:  // 3D cylinder
      *c1 = PI * d1 * d1 * d2;
      *c2 = 2 * PI * d1 * d1 + 2 * PI * d1 * d2;
      type_index = 6;
      break;
    case 42:  // 3D sphere
      *c1 = PI * pow(d1, 3);
      *c2 = 4 * PI * d1 * d1;
      type_index = 7;
      break;
    case 52:  // 3D cone
      *c1 = PI * d1 * d1 * d2 * 1 / 3;
      *c2 = PI * d1 * (d1 + sqrt(d2 * d2 + d1 * d1));
      type_index = 8;
      break;
    default:
      printf(
          "Error: none of type matches pre-programmed types. Terminating this "
          "object entry...\n");
      return 0;
  }

  // calculate mean_c1 and sd_c1
  old_mean_c1 = ll->mean_c1[type_index];
  old_sd_c1 = ll->SD_c1[type_index];
  old_unique_count = ll->count[type_index];
  new_unique_count = old_unique_count + 1;
  total_c1 = old_mean_c1 * old_unique_count;
  total_c1 += *c1;
  variance = (((new_unique_count - 2) * old_sd_c1 +
               ((*c1 - old_mean_c1) * (*c1 - old_mean_c1))) /
              (new_unique_count - 1));

  // update with new values
  ll->mean_c1[type_index] = total_c1 / new_unique_count;
  ll->SD_c1[type_index] = sqrt(variance);

  // calculate mean_c2 and sd_c2
  old_mean_c2 = ll->mean_c2[type_index];
  old_sd_c2 = ll->SD_c2[type_index];
  total_c2 = old_mean_c2 * old_unique_count;
  total_c2 += *c2;
  variance = (((new_unique_count - 2) * old_sd_c2 +
               ((*c1 - old_mean_c2) * (*c1 - old_mean_c2))) /
              (new_unique_count - 1));

  // update with new values
  ll->mean_c2[type_index] = total_c2 / new_unique_count;
  ll->SD_c2[type_index] = sqrt(variance);
  ll->count[type_index] += 1;

  return 1;
}

int Extract(LinkedList *ll, LinkedListEx *ex, int t1, int selector) {
  // ll is main linked list. t1 is type, 01 for 2D,
  // 02 for 3D. selector is for d1---c2

  ListNode *mov;  // cursor to move down the inserted ll
  int i;          // for error catching in insertnodeEx.
  i = 0;
  if (ll == NULL) return 0;

  mov = ll->head;
  while (mov != NULL) {
    if (((t1 / 10 == 0) && ((mov->type) % 10 == t1 % 10)) ||
        (mov->type == t1)) {
      switch (selector) {
        case 1:  // extract d1
          i = InsertNodeEx(ex, 0, mov->d1);
          break;
        case 2:  // extract d2
          i = InsertNodeEx(ex, 0, mov->d2);
          break;
        case 3:  // extract d3
          if (t1 % 10 != 2) {
            printf("No third dimension in 2D shapes. Exiting function....");
            return 0;
          }
          i = InsertNodeEx(ex, 0, mov->d3);
          break;
        case 4:  // extract c1
          i = InsertNodeEx(ex, 0, mov->c1);
          break;
        case 5:  // extract c2
          i = InsertNodeEx(ex, 0, mov->c2);
          break;
        default:
          printf("Selector error. Exiting function....");
          return 0;
      }
      if (i == 0) {
        printf("Insert node error. Exiting function....");
        return 0;
      }
      if (i == 0) printf("InsertNodeEx fail.\n");
    }
    mov = mov->next;
  }
  if (i == 1) printf("Extraction complete");
  return 1;
}

void PrintList(LinkedList *ll) {
  ListNode *cur;
  int i;
  if (ll == 0) return;

  printf("count: %d, mean_c1: %.3f, sd_c1: %.3f, mean_c2: %.3f, sd_c2: %.3f\n",
         *ll->count, *ll->mean_c1, *ll->SD_c1, *ll->mean_c2, *ll->SD_c2);

  cur = ll->head;

  if (cur == 0) printf("Empty");
  while (cur != NULL) {
    printf(
        "type = %d, d1 = %.3f, d2 = %.3f, d3 = %.3f, c1 = %.3f, c2 = %.3f \n",
        cur->type, cur->d1, cur->d2, cur->d3, cur->c1, cur->c2);
    // fflush(stdout);

    cur = cur->next;
  }
  printf("Print Complete\n");
}

void PrintListEx(LinkedListEx *ll) {
  ListNodeEx *cur;
  if (ll == NULL) return;
  cur = ll->head;

  if (cur == NULL) printf("Empty");
  while (cur != NULL) {
    printf("%f\n", cur->item);
    cur = cur->next;
  }
  printf("\n");
}

ListNode *FindNode(LinkedList *ll, int index) {
  ListNode *temp;

  if (ll == NULL || index < 0 || index >= ll->size) return NULL;

  temp = ll->head;

  if (temp == NULL || index < 0) return NULL;

  while (index > 0) {
    temp = temp->next;
    if (temp == NULL) return NULL;
    index--;
  }

  return temp;
}

// set index to 0 for inserting at the start of the list
int InsertNodeForMainLL(LinkedList *ll, int index, int t1, float d1, float d2,
                        float d3) {
  ListNode *pre, *cur;
  float c1, c2;

  // calculate c1 and c2 values, then update the mean and SD
  if (!Calculate(ll, t1, d1, d2, d3, &c1, &c2)) return 0;

  if (ll == NULL || index < 0 || index > ll->size + 1) return 0;

  // If empty list or inserting first node, need to update head pointer
  if (ll->head == NULL || index == 0) {
    cur = ll->head;
    ll->head = malloc(sizeof(ListNode));
    ll->head->type = t1;
    ll->head->d1 = d1;
    ll->head->d2 = d2;
    ll->head->d3 = d3;
    ll->head->c1 = c1;
    ll->head->c2 = c2;
    ll->head->next = cur;
    ll->size++;
    return 1;
  }

  // Find the nodes before and at the target position
  // Create a new node and reconnect the links
  if ((pre = FindNode(ll, index - 1)) != NULL) {
    cur = pre->next;
    pre->next = malloc(sizeof(ListNode));
    pre->next->type = t1;
    pre->next->d1 = d1;
    pre->next->d2 = d2;
    pre->next->d3 = d3;
    pre->next->c1 = c1;
    pre->next->c2 = c2;
    pre->next->next = cur;
    ll->size++;
    return 1;
  }

  return 0;
}

// set index to 0 for removing at the start of the list
int RemoveNode(LinkedList *ll, int index) {
  ListNode *pre, *cur;

  // Highest index we can remove is size-1
  if (ll == NULL || index < 0 || index >= ll->size) return 0;

  // If removing first node, need to update head pointer
  if (index == 0) {
    cur = ll->head->next;
    free(ll->head);
    ll->head = cur;
    ll->size--;

    return 1;
  }

  // Find the nodes before and after the target position
  // Free the target node and reconnect the links
  if ((pre = FindNode(ll, index - 1)) != NULL) {
    if (pre->next == NULL) return 0;

    cur = pre->next;
    pre->next = cur->next;
    free(cur);
    ll->size--;
    return 1;
  }

  return 0;
}

int InsertNodeEx(LinkedListEx *ll, int index, int value) {
  ListNodeEx *pre, *cur;

  if (ll == NULL || index < 0 || index > ll->size + 1) return 0;

  // If empty list or inserting first node, need to update head pointer
  if (ll->head == NULL || index == 0) {
    cur = ll->head;
    ll->head = malloc(sizeof(ListNodeEx));
    if (ll->head == NULL) {
      exit(0);
    }
    ll->head->item = value;
    ll->head->next = cur;
    ll->size++;
    return 1;
  }
}

int FreeMem(LinkedList *ll) {
  ListNode *cur, *nex;
  printf("Freeing memory for main list......\n");
  if (ll == NULL) return 0;
  cur = ll->head;
  while (cur != NULL) {
    nex = cur;
    cur = cur->next;
    free(nex);
  }
  // free(ll);
  printf("Memory is freed successfully.\n");
  return 1;
}

int FreeMemEx(LinkedListEx *ll) {
  ListNodeEx *cur, *nex;
  printf("Freeing memory for extracted list......");
  if (ll == NULL) return 0;
  cur = ll->head;
  while (cur != NULL) {
    nex = cur;
    cur = cur->next;
    free(nex);
  }
  // free(ll);
  printf("Memory is free.\n");
  return 1;
}
