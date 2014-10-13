#ifndef __GRAPH_H
#define __GRAPH_H

typedef struct graph *Graph;

Graph initGraph(unsigned int(calculateEdgeWeight)(void* fromNode, void* toNode));

int addNode(Graph g, void *node);

int addEdge(Graph g, void *fromNode, void *toNode, void *Edge);

/* Result must be freed */
void **calculatePath(Graph g, void *fromNode, void *toNode);

/*if searchfb returns 1 on any node nodeSearch reurns the pointer to that node else NULL */
void *nodeSearch(Graph g, int(searchfn)(void *node, void *extData), void *data);

void printGraph(Graph g, void(printNode)(void *node), void(printEdge)(void *node, void*toNode));

#endif 

