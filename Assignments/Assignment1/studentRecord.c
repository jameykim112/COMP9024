// Student record implementation ... Assignment 1 COMP9024 17s2
#include <stdio.h>
#include <string.h>

#define LINE_LENGTH 1024

// scan input for a positive integer, returns -1 if none
int readInt(void) {
   char line[LINE_LENGTH];
   int  n;

   fgets(line, LINE_LENGTH, stdin);
   if ( (sscanf(line, "%d", &n) != 1) || n <= 0 )
      return -1;
   else
      return n;
}

// scan input for a positive floating point number, returns -1 if none
float readFloat(void) {
   char  line[LINE_LENGTH];
   float f;

   fgets(line, LINE_LENGTH, stdin);
   if ( (sscanf(line, "%f", &f) != 1) || f <= 0.0 )
      return -1;
   else
      return f;
}

/*** Your code for stage 1 starts here ***/

int readValidID(void) {
  printf("Enter student ID: ");
  int studentID = readInt();
  while (studentID == -1 || studentID < 1000000 || studentID > 999999999) {
    printf("Not valid. Enter a valid value: ");
    studentID = readInt();
  }
  return studentID;
}

int readValidCredits(void) {
  printf("Enter credit points: ");
  int credit_points = readInt();
  while (credit_points == -1 || credit_points < 2 || credit_points > 480) {
    printf("Not valid. Enter a valid value: ");
    credit_points = readInt();
  }
  return credit_points;
}

float readValidWAM(void) {
  printf("Enter WAM: ");
  float WAM = readFloat();
  while (WAM == -1 || WAM < 50 || WAM > 100) {
    printf("Not valid. Enter a valid value: ");
    WAM = readFloat();
  }
  return WAM;
}

void printStudentData(int zID, int credits, float WAM) {
  char grade[3];
  // Calculation of WAM
  if (WAM >= 85 && WAM <= 100) {
    strcpy(grade, "HD");
  }
  else if (WAM >= 75 && WAM < 85) {
    strcpy(grade, "DN");
  }
  else if (WAM >= 65 && WAM < 75) {
    strcpy(grade, "CR");
  }
  else if (WAM >= 50 && WAM < 65) {
    strcpy(grade, "PS");
  }

  printf("------------------------\n");
  printf("Student zID: z%d\n", zID);
  printf("Credits: %d\n", credits);
  printf("Level of performance: %s\n", grade);
  printf("------------------------\n");

   return;
}
