#include "graph.h"
#include <stdlib.h>

typedef struct node *Node;
typedef struct edgeList *EdgeList;

struct node {
  void *nodeData;
  unsigned int distance;
  EdgeList edges;
  Node next;
  void** path;
};

struct edgeList{
  void *edgeData;
  Node to;
  EdgeList next;
};

struct graph{
  Node node;
  unsigned int (*calculateEdgeWeight)(void* fromNode, void* toNode);
}; 


static Node findNodeFromNodedata(Graph g, void *nodeData){
  Node cursor = g->node;
  while(cursor != NULL){
    if(nodeData == cursor->nodeData){
      return cursor;
    }
    cursor = cursor->next;
  }
  return NULL;
};

Graph initGraph (unsigned int(calculateEdgeWeight)(void* fromNode, void* toNode)){
  Graph newGraph = malloc(sizeof(struct graph));
  newGraph->node = NULL;
  newGraph->calculateEdgeWeight = calculateEdgeWeight;
  return newGraph;

}

int addNode(Graph g, void *node){
  Node newNode = malloc(sizeof(struct node));
  if(newNode == NULL) return 0;
  newNode->nodeData = node;
  newNode->distance = -1;
  newNode->edges = NULL;
  newNode->next = g->node;
  g->node = newNode;
  return 1;
}

int addEdge(Graph g, void *fromNode, void *toNode, void *Edge){
  Node from = findNodeFromNodedata(g, fromNode);
  Node to = findNodeFromNodedata(g, toNode);
  EdgeList newEdgeList = malloc(sizeof(struct edgeList));
  newEdgeList->edgeData = Edge;
  newEdgeList->to=to;
  newEdgeList->next = from->edges;
  from->edges = newEdgeList;
  return 1;				 
}

void **calculatePath(Graph g, void *fromNode, void *toNode){
  return NULL;

  /* Int pathsize = sizeof(void*)*((g->numberOfNodes*2)+1); */
  /* Node cursor = g->node; */
  /* while(cursor != NULL){ */
  /*   cursor->path = malloc(pathsize); */
  /*   memset(cursor->path, (int)NULL, pathsize); */
  /* } */
  /* Node from = findNodeFromNodedata(g, fromNode );*/
}

void *nodeSearch(Graph g, int(searchfn)(void *node, void *extData), void *data){
  Node cursor = g->node;
  while(cursor != NULL){
    if(searchfn(cursor->nodeData, data)){
      return cursor->nodeData;
    }else {
      cursor = cursor->next;
    }
  }
  return NULL;
}

void printGraph(Graph g, void(printNode)(void *node), void(printEdge)(void *node, void *toNode)){
  Node nodecursor = g->node;
  while(nodecursor != NULL){
    printNode(nodecursor->nodeData);
    EdgeList edgelistcursor = nodecursor->edges;
    while(edgelistcursor != NULL){
      printEdge(edgelistcursor->edgeData, edgelistcursor->to->nodeData);
      edgelistcursor = edgelistcursor->next;
    }
    nodecursor = nodecursor->next;
  }
}


