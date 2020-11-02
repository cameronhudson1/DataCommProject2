#ifndef _GRAPH_H
#define _GRAPH_H

// A structure to represent an adjacency list node 
struct AdjListNode 
{ 
    int dest; 
    struct AdjListNode* next; 
}; 
  
// A structure to represent an adjacency list 
struct AdjList 
{ 
    struct AdjListNode *head;  
}; 
  
// A structure to represent a graph. A graph 
// is an array of adjacency lists. 
// Size of array will be V (number of vertices  
// in graph) 
struct Graph 
{ 
    int V; 
    struct AdjList* array; 
}; 

#endif
