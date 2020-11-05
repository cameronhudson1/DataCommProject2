#ifndef _GRAPH_H
#define _GRAPH_H

// C / C++ program for Dijkstra's 
// shortest path algorithm for adjacency
// list representation of graph
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// A structure to represent a 
// node in adjacency list
struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode* next;
};

// A structure to represent 
// an adjacency list
struct AdjList
{
    
// Pointer to head node of list
struct AdjListNode *head; 
};

// A structure to represent a graph. 
// A graph is an array of adjacency lists.
// Size of array will be V (number of 
// vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};

// Structure to represent a min heap node
struct MinHeapNode
{
    int v;
    int dist;
};

// Structure to represent a min heap
struct MinHeap
{
    
    // Number of heap nodes present currently
    int size;    

    // Capacity of min heap
    int capacity; 

    // This is needed for decreaseKey()
    int *pos; 
    struct MinHeapNode **array;
};

struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int dest, int weight);
void dijkstra(struct Graph* graph, int src);

#endif
