/**
     main.c

     Program supplied as a starting point for
     Assignment 1: Student record manager

     COMP9024 17s2
**/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "studentRecord.h"
#include "studentLL.h"

int studentID;
int credit_points;
float WAM;
float total_wam = 0;
float total_weighted_wam = 0;
float average_wam;
float average_weighted_wam;
int number_students = 0;

void printHelp();
void StudentLinkedListProcessing();

int main(int argc, char *argv[]) {
   if (argc == 2) {

     int i;
     int n;
     float total_credits = 0;

     // Allocate HEAP memory
     n = atoi(argv[1]);
     studentRecordT* records = malloc(n*sizeof(studentRecordT));
     assert(records != NULL);

     // Store values in memory
     for (i = 0; i < n; i++) {
       studentID = readValidID();
       credit_points = readValidCredits();
       WAM = readValidWAM();

       records[i].zID = studentID;
       records[i].credits = credit_points;
       records[i].WAM = WAM;
     }

     // Print values in memory
    for (i = 0; i < n; i++) {
      printStudentData(records[i].zID, records[i].credits, records[i].WAM);
      total_wam += records[i].WAM;
      total_weighted_wam += records[i].WAM * records[i].credits;
      total_credits += records[i].credits;
    }
    average_wam = total_wam / n;
    average_weighted_wam = total_weighted_wam / total_credits;
    printf("Average WAM: %.3f\n", average_wam);
    printf("Weighted average WAM: %.3f\n", average_weighted_wam);
    free(records);

   } else {
      StudentLinkedListProcessing();
   }
   return 0;
}

/* Code for Stages 2 and 3 starts here */
void StudentLinkedListProcessing() {
   int op, ch;

   List list = newLL();   // create a new linked list

   while (1) {
      printf("Enter command (a,f,g,p,q, h for Help)> ");

      do {
	 ch = getchar();
      } while (!isalpha(ch) && ch != '\n');  // isalpha() defined in ctype.h
      op = ch;
      // skip the rest of the line until newline is encountered
      while (ch != '\n') {
	 ch = getchar();
      }

      switch (op) {

         case 'a':
         case 'A':
            studentID = readValidID();
            credit_points = readValidCredits();
            WAM = readValidWAM();
            insertLL(list, studentID, credit_points, WAM);
            /*** Insert your code for adding a student record ***/

	    break;

         case 'f':
         case 'F':
            studentID = readValidID();
            inLL(list, studentID);
            /*** Insert your code for finding a student record ***/

	    break;

         case 'g':
         case 'G':
            getStatLL(list, &number_students, &total_wam, &total_weighted_wam);
            printf("Number of records: %d\n", number_students);
            printf("Average WAM: %.3f\n", total_wam);
            printf("Average weighted WAM: %.3f\n", total_weighted_wam);

      break;

         case 'h':
         case 'H':
            printHelp();
	    break;

         case 'p':
         case 'P':
            showLL(list);
            /*** Insert your code for printing all student records ***/
	    break;

	       case 'q':
         case 'Q':
            dropLL(list);       // destroy linked list before returning
	    printf("Bye.\n");
	    return;
      }
   }
}

void printHelp() {
   printf("\n");
   printf(" A - Add student record\n" );
   printf(" F - Find student record\n" );
   printf(" G - Get statistics\n" );
   printf(" H - Help\n");
   printf(" P - Print all records\n" );
   printf(" Q - Quit\n");
   printf("\n");
}
