/**
 * Name:		Cecilia Condes
 * ID:			ccondes
 * Class: 		CMPS 101
 * Date:		8.8.15
 * Filename: 	Graph.c
 * Description:	Graph ADT for pa5
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"
#include "Graph.h"

/* TEST
 * newGraph		PASS
 * freeGraph
 * getOrder		PASS
 * getSize		PASS
 * getParent	PASS
 * getDiscover	PASS
 * getFinish	PASS
 * addEdge		PASS
 * addArc		PASS
 * DFS			PASS 
 * Visit 		PASS
 * transpose	
 * copyGraph	PASS
 * printGraph	PASS
 */

// #ifndef DEBUG
// #define DEBUG(ERR, MSG) { 
//  // fprintf(stderr, ERR+": "+__FILE__+":"+__LINE__+" %s\n", MSG);
//  printf("%s:%d: %s: %s\n", __FILE__, __LINE__, ERR, MSG);
// }
// #endif

#ifndef TRACE
#define TRACE(err, msg) (fprintf(stderr, err+": "+__FILE__+":"+__LINE__+" %s\n", msg)) 
#endif

#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef INF
#define INF -1
#endif
#ifndef NIL
#define NIL 0
#endif
#ifndef WHITE
#define WHITE 0
#endif
#ifndef GRAY
#define GRAY 1
#endif
#ifndef BLACK
#define BLACK 2
#endif
#ifndef BULLSHIT
#define BULLSHIT 0
#endif

void throwException(char* msg);

// :)
// Graph
typedef struct GraphObj{
	List* adj;
	int* color;
	int* discover;
	int* finish;
	int* parent;
	int order; // number of vertices
	int size; // number of edges
} GraphObj;

// Constructors-Destructors----------------------------------------------------
// :)
Graph newGraph(int n){
	Graph G 	= malloc(sizeof(GraphObj));
	assert(G!=NULL);
	G->adj 		= calloc(n+1, sizeof(List)); // initialize space for n+1 vertices
	assert(G->adj != NULL);
	G->color	= calloc(n+1, sizeof(int)); // the colors
	assert(G->color != NULL);
	G->discover = calloc(n+1, sizeof(int)); // discooer time
	assert(G->discover != NULL);
	G->finish 	= calloc(n+1, sizeof(int)); // finish times
	assert(G->finish != NULL);
	G->parent 	= calloc(n+1, sizeof(int)); // parents
	assert(G->parent != NULL);

	// make empty adjacency lists
	for(int i = 1; i <= n; ++i) G->adj[i] = newList();

	G->order = n;
	G->size = 0;

	return G;
}

// :)
Graph transpose(Graph G){
	Graph T = newGraph(getOrder(G));
	List G_L; // G's adjacency lists

	for(int i = 1; i <= T->order; ++i){
		G_L = G->adj[i];
		for(moveFront(G_L); index(G_L) > -1; moveNext(G_L) ){
			// G(i, get(GL)) --> T(get(GL), i)
			if(DEBUG) printf("adding new arc\n");
			addArc(T, get(G_L), i);
		}
	}

	return T;
}

// :)
Graph copyGraph(Graph G){
	Graph C 	= malloc(sizeof(GraphObj));
	assert(C!=NULL);
	memcpy(C, G, sizeof(GraphObj));
	return C;
}

void freeGraph(Graph* pG){
	if(pG!=NULL || *pG!=NULL){
		if(*pG!=NULL){

			// for(int i = 1; i <= (*pG)->size; ++i){
			// 	// List L = *((*pG)->adj[i]);
			// 	if((*pG)->adj[i] != NULL) freeList((*pG)->adj[i]);
			// }

			for(int i = 0; i <= (*pG)->order; ++i){ // free all lists, even 0
				freeList( &((*pG)->adj[i]) );
			}

			free((*pG)->adj);
			(*pG)->adj = NULL;

			free((*pG)->color);
			(*pG)->color = NULL;
			free((*pG)->parent);
			(*pG)->parent = NULL;
			free((*pG)->discover);
			(*pG)->discover = NULL;
			free((*pG)->finish);
			(*pG)->finish = NULL;
		}
		free(*pG);
		*pG = NULL;
	}
}

// Access fns------------------------------------------------------------------
// :) - number of vertices
int getOrder(Graph G){
	if(NULL==G)
		throwException("Graph Exception: calling getOrder on NULL Graph");

	return G->order;
}

// :) - number of edges
int getSize(Graph G){
	if(NULL==G) 
		throwException("Graph Error: calling getSize on NULL Graph");
	
	return G->size;
}

// :)
// Pre: 1 <= u <= n = getOrder(G)
int getParent(Graph G, int u){
	if(u < 1 || u > getOrder(G))
		throwException("Graph.c: calling getParent() on nonexistent vertex");

	return G->parent[u];
}

// :)
// Pre: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u){
	if(u < 1 || u > getOrder(G))
		throwException("Graph.c: calling getDiscover() on nonexistent vertex");

	return G->discover[u];
}

// :)
// Pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u){
	if(u < 1 || u > getOrder(G))
		throwException("Graph.c: calling getFinish() on nonexistent vertex");

	return G->finish[u];
}


// Manipulation procedures-----------------------------------------------------

// :)
// addEdge()
void addEdge(Graph G, int u, int v){
	List L = G->adj[u];
	if(NULL!=L && length(L) > 0){
		if(DEBUG) printf("moving to the front\n");
		moveFront(L);
		while(index(L) >= 0 && get(L) < v) {
			if(DEBUG) printf("searching for the next node...\n");
			moveNext(L);
		}
		if(index(L) >= 0) {
			insertBefore(L, v);
			if(DEBUG) printf("appending the node\n");
			}
		else append(L, v);
	}
	else append(L, v);

	List M = G->adj[v];
	if(NULL!=M && length(M) > 0){
		if(DEBUG) printf("moving to the front\n");
		moveFront(M);
		while(index(M) >= 0 && get(M) < u) {
			if(DEBUG) printf("searching for the next node...\n");
			moveNext(M);
		}
		if(index(M) >= 0) {
			insertBefore(M, u);
			if(DEBUG) printf("appending the node\n");
			}
		else append(M, u);
	}
	else append(M, u);

	G->size++;
}

// :)
// addArc()
void addArc(Graph G, int u, int v){
	List L = G->adj[u];
	if(NULL!=L && length(L) > 0){
		if(DEBUG) printf("moving to the front\n");
		moveFront(L);
		while(index(L) >= 0 && get(L) < v) {
			if(DEBUG) printf("searching for the next node...\n");
			moveNext(L);
		}
		if(index(L) >= 0) {
			insertBefore(L, v);
			if(DEBUG) printf("appending the node\n");
			}
		else append(L, v);
	}
	else append(L, v);

	G->size++;
}

// :)
// private helper fn
void Visit(Graph G, int x, int* t, List Q){
	if(DEBUG) printf("visiting vertex %d\n", x);

	// append(Q, x);
	G->color[x] = GRAY;
	G->discover[x] = (int)(++(*t));

	List LX = (G->adj[x]);

	moveFront(LX);
	for(; index(LX) > -1; moveNext(LX)) {
		if(G->color[get(LX)] == WHITE) {
			G->parent[get(LX)] = x;
			// append(Q, x);
			if(BULLSHIT) printf("parent of %d is %d\n", get(LX), x);
			Visit(G, get(LX), t, Q);
		}
	}

	G->color[x] = BLACK;
	G->finish[x] = (int)(++(*t));
	
	if(index(Q) > -1){
		if(length(Q) > getOrder(G)){	
			insertBefore(Q, x);
			movePrev(Q);
		}
		else{
			append(Q, x);
			moveNext(Q);
			append(Q, INF); // append dummy node so that after this executes
							// once, the if condition will always be true
							// (this node must be removed in DFS)
		}
		if(BULLSHIT) {
			printf("%d finished, stack = ", x);
			printList(stdout, Q);
		}
	}
	else{
		prepend(Q, x);
		if(BULLSHIT) {
			printf("%d finished, stack = \n", x);
			printList(stdout, Q);
		}
	}
}

// :)
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S){
	if(length(S) != getOrder(G)) 
		throwException("wrong lengths");

	int* _time = malloc(sizeof(int));
	for(int i = 1; i <= getOrder(G); ++i){
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->discover[i] = INF;
		G->finish[i] = INF;
	}

	*_time = 0;

	moveBack(S);
	for(int i = 1; i <= getOrder(G); ++i){
		// moveFront(S);
		if(G->color[front(S)] == WHITE) Visit(G, front(S), _time, S);
		deleteFront(S);
	}
	
	deleteBack(S);

	if(DEBUG || BULLSHIT) {
		printf("  x:   c   d   f   p\n");
		for(int i = 1; i <= getOrder(G); ++i){
			printf("%3d: %3d %3d %3d %3d\n", i, G->color[i], 
										G->discover[i], 
										G->finish[i], G->parent[i]);
		}
	}

	free(_time);
}

// Other-----------------------------------------------------------------------

void printGraph(FILE* out, Graph G){
	List L = NULL;
	for(int i = 1; i <= G->order; ++i){
		L = G->adj[i];
		fprintf(out, "%d:", i);
		if(length(L) < 1) fprintf(out, " ");
		printList(out, L);
	}
}
