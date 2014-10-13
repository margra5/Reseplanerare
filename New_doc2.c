#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "graph.h"

typedef struct edge *Edge;
typedef struct busstop *Busstop;

struct busstop{
  char name[50];
  int timeToNext;
  Busstop next;
};
 
struct edge {
  int lineNo;
  unsigned int time;
};

/* int busstopExists() */
unsigned int calculateEdgeweight(void* fromNode, void* toNode){
  return 1;
};

void printNode(void *node){
  Busstop b = (Busstop)node;
  printf("Busstop name -> %s\n", b->name);
}

void printEdge(void *edge, void *to){
  Edge e = (Edge)edge;
  printf("   %-30s Edge lineno -> %3dm time -> %3d\n", ((Busstop)to)->name, e->lineNo, e->time);
}

int searchfn(void *node, void *extData){
  Busstop b = (Busstop)node;
  char *Busstopname = (char *)extData;
  if(strcmp(b->name, Busstopname) == 0){
    return 1;
  } else {
    return 0;
  }
}


int main(int argc, char *argv[]){
  if (argc < 2){
    printf("Need filename\n");
    return 1;
  }
  /* Open the file*/
  FILE *network = fopen(argv[1], "r");

  /* Save each line from the file in these variables  */
  int line, time;
  char from[50], to[50];
  Graph g = initGraph(calculateEdgeweight);
  /* this char is to check for newline */
  void *fromNode;
  void *toNode;


  while(fscanf(network, "%d, %[^,], %[^,], %d", &line, from, to, &time) != EOF){
    fromNode = nodeSearch(g, searchfn, (void *)from);
    toNode = nodeSearch(g, searchfn, (void *)to);
    if(fromNode == NULL){
      /* Node does not exists */
      Busstop newBusstop = malloc(sizeof(struct busstop));
      strncpy(newBusstop->name, from, 50);
      addNode(g, (void *)newBusstop);
      fromNode = (void *)newBusstop;
    }
    if(toNode == NULL){
      /* Node does not exists */
      Busstop newBusstop = malloc(sizeof(struct busstop));
      strncpy(newBusstop->name, from, 50);
      addNode(g, (void *)newBusstop);
      toNode =  (void *)newBusstop;
    }
    Edge newEdge = malloc(sizeof(struct edge));
    newEdge->lineNo = line;
    newEdge->time = time;
    addEdge(g, fromNode, toNode, (void *)newEdge);

      /* Debug */
    printf("From -> %-30s To -> %-30s Line -> %3d Time -> %3d \n", from, to, line, time);
    
  }
  printGraph(g, printNode, printEdge);
  return 0;
}
