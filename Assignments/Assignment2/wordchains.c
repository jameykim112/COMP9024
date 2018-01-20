// COMP9024 - Data Structures and Algorithms //
// Assignment 2: Word Chain //
// By Jamey Kim z3251762 //

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "Graph.h"

#define MAX_WORD_LENGTH 20
#define FORMAT_STRING "%19s"
#define MAX_NODES 1000


int maxDistance[MAX_NODES]; // Array storing longest lengths to nodes
int visited[MAX_NODES]; // Track visited nodes in list matrix
int path[MAX_NODES]; // Array storing current path
int max_path_length = 0;
int indx = 0;


int findNeighbour(char *word, char *word_set, int nV);
int findMaxlength(Graph g, int nV);
void findPathDFS(Graph g, int nV, char **word_set, int src, int dest);
void findPath(Graph g, int nV, char **word_set, int src, int dest, int length);
void checkStack();


int main() {
  /*
  Task 1:
  Time Complexity: O(n^2*m)
  Explanation: First loop which incrementally iterates from the first
  user entered word to the last entered word, with each word assumed
  entered in alphabetical order is O(n), with the second loop also
  being O(n). This results in a time complexity of O(n^2)

  In the findNeighbour function, time complexity when changing a
  letter is O(26m) where 26 is number of letters in alphabet, when
  adding a letter O(26m) and when removing a letter O(m) as each
  letter is incrementally removed. This results in a time complexity of
  O(m)

  Overall, the time complexity for Task 1 is O(n^2) * O(m) = O(n^2*m)

  Task 2:
  Time Complexity: O(n^2)
  Explanation: The maximum path length is first calculated using a
  modification of the Dijkstra algorithm to find the possible longest
  path in the Directed Acyclic Graph (DAG). The first loop iterates from
  the first user entered word to the last entered word and is O(n). The
  second loop iterates from the n – 1 word to n thus is O(n-1). This
  results in a time complexity of O(n^2)

  To find all word chains of maximum path length, the first loop iterates
  through all words in alphabetical order thus is O(n). The second loop
  iterates from the first word to all words which have a length of maximum
  path length found through the modified Dijkstra algorithm, thus has a
  time complexity of O(n) and calculates whether there is a path through
  Depth First Search which has a time complexity of O(n). This results in
  a time complexity of O(n^2) + O(n)

  Overall, the time complexity for Task 2 is O(n^2)
  */

  // Prompt user to input a positive number n
  int nV = 0;
  int i, j;
  printf("Enter a number: ");
  scanf("%i", &nV);
  //Check whether user input is a integer

  //char word[MAX_WORD_LENGTH];
  char *word_set[nV];
  for (i = 0; i < nV; i++) {
    printf("Enter word: ");
    word_set[i] = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
    assert(word_set[i] != NULL);
    scanf(FORMAT_STRING, word_set[i]);
  }

  //Initialise a new Graph
  Graph g = newGraph(nV);
  Edge e;

  /*
  Task 1: For each word compute and output all words that could
  immediately folllow word in a word chains
  */
  for (i = 0; i < nV; i++) {
    for (j = i; j < nV; j++) {
      int neighbour = findNeighbour(word_set[i], word_set[j], nV);
      if (neighbour == 1) {
        e.v = i;
        e.w = j;
        insertEdge(g, e);
      }
    }
  }

  // Print all word chains
  showGraph(g, word_set);

  /*
  Task 2a: Compute and output the maximum length of a word chain that
  can be built from the given words
  */
  max_path_length = findMaxlength(g, nV);

  /*
  Task 2b: Compute and output all word chains of maximum length that
  can be built from the given words
  */
  for (i = 0; i < nV; i++) {
    findPathDFS(g, nV, word_set, i, nV-1);
  }

  freeGraph(g, nV, word_set);

  return 0;
}

// FUNCTIONS //
// Find max distance array
int findMaxlength(Graph g, int nV) {
  int i, j;

  for (i = 0; i < nV; i++) {
    for (j = i + 1; j < nV; j++) {
      if (adjacent(g, i, j) && maxDistance[j] <= maxDistance[i] + 1) {
        maxDistance[j] = maxDistance[i] + 1;
        if (maxDistance[j] > max_path_length) {
          max_path_length = maxDistance[j];
        }
      }
    }
  }

  int max_path = max_path_length + 1; // Addition of 1 to include base node

  printf("Maximum chain length: %d\n", max_path);
  printf("Maximal chains:\n");
  return max_path_length;
}

void findPathDFS(Graph g, int nV, char **word_set, int src, int dest) {
    Vertex v;

    // init unvisited
    for (v = 0; v < nV; v++)
        visited[v] = -1;

    visited[src] = src;
    findPath(g, nV, word_set, src, dest,0);
}


void findPath(Graph g, int nV, char **word_set, int src, int dest, int length) {
  int i;

  visited[src] = 1; // Set visited node to 1
  path[indx] = src;
  indx++;

  for (i = 0; i < nV; i++) {
    if (visited[i] == -1 && adjacent(g, src, i)) {
      findPath(g, nV, word_set, i, dest, length + 1);
    }
  }

  if (length == max_path_length) {
    checkStack(word_set, length);
  }
  length --;
  visited[src] = -1; // Backtrack set node as unvisited
  indx--; // Decrement indx value
}

void checkStack(char **word_set, int length) {
  int i;
  if (length == max_path_length) {
    for (i = 0; i < indx; i++) {
      if (i == indx - 1) {
        printf ("%s", word_set[path[i]]);
      }
      else {
        printf ("%s -> ", word_set[path[i]]);
      }
    }
    printf ("\n");
  }
}

// Word = Word being compared
// word_set = Dictionary of word_set
// num = Number of user  input word_set
int findNeighbour(char *word, char *word2, int num) {
  //int i = 0;
  int j = 0;
  char c;
  char new_word[MAX_WORD_LENGTH]; //Statically allocate memory
  int length = strlen(word);

  //REPLACE A LETTER//
  strcpy(new_word, "");
  //printf("Change a letter\n");
  for (j = 0; j < length; j++) {
    for (c = 'a'; c <= 'z'; ++c) {
      strncat(new_word, word, j);
      strncat(new_word, &c, 1);
      strncat(new_word, &word[j+1], length-j);

      //Compare based on inputs ie. alphabetically
      if (strcmp(new_word, word2) == 0) {
        //printf("Match found %s %s\n", word2, new_word);
        return 1;
      }
      else {
        strcpy(new_word, "");
      }
    }
  }

  //ADD A LETTER//
  strcpy(new_word, "");
  //printf("Add a letter\n");
  for (j = 0; j < length + 1; j++) {
    for (c = 'a'; c <= 'z'; ++c) {
      strncat(new_word, word, j);
      strncat(new_word, &c, 1);
      strncat(new_word, &word[j], length-j);
      //printf("%s\n", new_word);

      //Compare based on inputs ie. alphabetically
      if (strcmp(new_word, word2) == 0) {
        //printf("Match found %s\n", word2);
        return 1;
      }
      else {
        strcpy(new_word, "");
      }
    }
  }

  //REMOVE A LETTER//
  strcpy(new_word, "");
  //printf("Remove a letter\n");
  for (j = 0; j < length + 1; j++) {
    strncat(new_word, word, j);
    strncat(new_word, &word[j+1], length-j);

    //Compare based on inputs ie. alphabetically
    if (strcmp(new_word, word2) == 0) {
      //printf("Match found %s\n", word2);
      return 1;
    }
    else {
      strcpy(new_word, "");
    }
  }
  return 0;
}
