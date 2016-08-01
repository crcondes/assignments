/**
 * Name:		Cecilia Condes
 * ID:			ccondes
 * Class: 		CMPS 101
 * Date:		8.8.15
 * Filename: 	Graph.h
 * Description:	Graph ADT for pa5
 */

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"

#ifndef INF
#define INF -1000000
#endif
#ifndef NIL
#define NIL 0
#endif

// Graph
typedef struct GraphObj* Graph;

// Constructors-Destructors----------------------------------------------------
Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access fns------------------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); // Pre: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u); // Pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u); // Pre: 1 <= u <= n = getOrder(G)

// Manipulation procedures-----------------------------------------------------
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S); // Pre: length(S) == getOrder(G)

// Other-----------------------------------------------------------------------
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif
