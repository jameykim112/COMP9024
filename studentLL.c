#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "studentLL.h"
#include "studentRecord.h"

// linked list node type
// DO NOT CHANGE
typedef struct node {
  studentRecordT data;
  struct node    *next;
} NodeT;

// linked list type
typedef struct ListRep {
  int count;
  NodeT *head;
} ListRep;

/*** Your code for stages 2 & 3 starts here ***/

// Time complexity: O(1)
// Explanation: take constant time and indifferent of the input size
List newLL() {
  List L = malloc(sizeof(ListRep));
  assert(L != NULL);
  L->head = NULL;
  return L;
}

// Time complexity: O(N)
// Explanation: Will systematically iterate through Linked List from start to end, thus time
//              complexity increases linearly in relation to number of elements.
void dropLL(List listp) {
  NodeT *current = listp->head;
  NodeT *temp;
  while (current != NULL) {
    temp = current;
    current = current->next;
    free(temp);
  }
  listp->head = NULL;
  free(listp);
  return;
}

// Time complexity: O(N)
// Explanation: Will systematically iterate through Linked List from start to end, thus time
//              complexity increases linearly in relation to number of elements.
void inLL(List listp, int zid) {
  NodeT *curr; // Creating node pointer
  curr = listp->head; //Pointer starting at the first node

  // Iterate through LL until find zid input
  while (curr != NULL) {
    if (curr->data.zID == zid) {
      printStudentData(curr->data.zID, curr->data.credits, curr->data.WAM);
      break;
    }
    else {
      curr = curr->next;
    }
  }
  // Get to end of LL and can't find value
  if (curr == NULL) {
    printf("No record found.\n");
  }
  return;
}

// Time complexity: O(1) when inserting new records into the start of the linked list.
//                  O(N) when inserting new records in ascending order
// Explanation:     O(1) take constant time and indifferent of the input size
//                  O(N) Will systematically iterate through Linked List from start to end, thus time
//                       complexity increases linearly in relation to number of elements.
void insertLL(List listp, int zid, int cr, float wam) {
  //Creating Pointer
  NodeT *curr;

  //Allocating memory to create a new node
  NodeT *new = malloc(sizeof(NodeT));
  assert(new != NULL);

  //Assigning values zID, credits and WAM to new node
  new->data.zID = zid;
  new->data.credits = cr;
  new->data.WAM = wam;
  new->next = NULL; //Initialise link to next node

  // Check whether values exist in linked list
  curr = listp->head;
  while (curr != NULL) {
    if (curr->data.zID == zid) {
      curr->data.zID = zid;
      curr->data.credits = cr;
      curr->data.WAM = wam;
      printf("Student record updated.\n");
      free(new);
      return;
    }
    else {
      curr = curr->next;
    }
  }

  // Assigning new head value if no previous value exists or head >= new
  if (listp->head == NULL || listp->head->data.zID >= new->data.zID) {
    new->next = listp->head;
    listp->head = new;
  }
  // Iterate through list until find point where existing value < new, then update values
  else {
    curr = listp->head;
    while (curr->next != NULL && curr->next->data.zID < new->data.zID) {
      curr = curr->next;
    }
    new->next = curr->next;
    curr->next = new;
  }
  printf("Student record added.\n");
  return;
}

// Time complexity: O(N)
// Explanation: Will systematically iterate through Linked List from start to end, thus time
//              complexity increases linearly in relation to number of elements.
void getStatLL(List listp, int *n, float *wam, float *w_wam) {
  float total_wam = 0;
  int total_credits = 0;
  float total_weighted_wam = 0;

  NodeT *curr;
  curr = listp->head;

  while (curr != NULL) {
    *n += 1;
    total_credits += curr->data.credits;
    total_wam += curr->data.WAM;
    total_weighted_wam += curr->data.WAM * curr->data.credits;
    curr = curr->next;
  }
  *wam = total_wam / *n;
  *w_wam = total_weighted_wam / total_credits;
  return;
}

// Time complexity: O(N)
// Explanation: Will systematically iterate through Linked List from start to end, thus time
//              complexity increases linearly in relation to number of elements.
void showLL(List listp) {
  NodeT *curr;
  curr = listp->head;
  while (curr != NULL) {
    printStudentData(curr->data.zID, curr->data.credits, curr->data.WAM);
    curr = curr->next;
  }
return;
}
