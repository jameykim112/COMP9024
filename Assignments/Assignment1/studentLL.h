// Linked lists of student records header file ... Ass 1 COMP9024 17s2
// DO NOT CHANGE

typedef struct ListRep *List;

List newLL();          // set up empty list
void dropLL(List);     // remove unwanted list
void showLL(List);     // display all student records in list
void inLL(List, int);  // find and display student record

// given a studentID, #credits, WAM ...
// ... Stage 2: insert new record at the beginning of the list
// ... Stage 3: insert in ascending order (if studentID new) else update record
void insertLL(List, int, int, float);

// get statistical information: #records, average WAM, average weighted WAM
void getStatLL(List, int *, float *, float *);
