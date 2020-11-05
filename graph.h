#ifndef _GRAPH_H
#define _GRAPH_H

typedef struct 
{
	void *destination_node;
	int weight;
} Edge_t;

typedef struct
{
	int num_edges;
	Edge_t * edge_list;
} GraphNode_t;

typedef struct
{
	int num_nodes;
	
	GraphNode_t head;
} Graph_t;

#endif
