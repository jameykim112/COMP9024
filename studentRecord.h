// Student record header file ... Assignment 1 COMP9024 17s2
// DO NOT CHANGE

typedef struct {
   int   zID;
   int   credits;
   float WAM;
} studentRecordT;

int   readValidID(void);
int   readValidCredits(void);
float readValidWAM(void);
void  printStudentData(int, int, float);
