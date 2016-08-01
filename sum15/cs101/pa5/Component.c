/**
 * Name:		Cecilia Condes
 * ID:			ccondes
 * Class: 		CMPS 101
 * Date:		7/28/15
 * Filename: 	GraphTest.c
 * Description:	Test client for pa4
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"

#ifndef COMPDEBUG
#define COMPDEBUG 1
#endif

void printComponents(FILE* out, Graph G, List S){
	// int* forest = malloc(sizeof(int)*(length(S)+1));
	// moveFront(S);
	// if(COMPDEBUG) printf("%d\n", front(S));

	// if(COMPDEBUG) printf("entering foresting loop\n");
	// for(int i = 1; i <= getOrder(G); ++i){
	// 	if(COMPDEBUG) printf("%d\n", i);
	// 	forest[i] = getParent(G, i);
	// }

	// if(COMPDEBUG) printf("forest: \n");
	// for(int i = 0; i < length(S); ++i) printf("%d ", forest[i]);
	// printf("\n");

	///////////////////////////////////////////////////////
	int i = 1, scc = 0;
	List* strong = malloc(sizeof(List)*(getOrder(G)+1));

	moveBack(S);
	while(index(S) > -1){	
		strong[i] = newList();
		++scc;
		while(1) {	// infinite loop - this is just getting weird
			prepend(strong[i], get(S));
			if(NIL == getParent(G, get(S))){
				movePrev(S);
				break;
			}
			else movePrev(S);
		}
		++i;
	}

	//////////////////////////////////////////////////////

	fprintf(out, "G contains %d strongly connected components:\n", scc);
	for(int i = 1; i <= scc; ++i){
		fprintf(out, "Component %d: ", i);
		printList(out, strong[i]);
		// freeList(&strong[i]);
	}
	
}

int main(int argc, char const *argv[]){
	if(COMPDEBUG) printf("compiled\n");
	int n = 8;
	Graph G = newGraph(n);

	addArc(G, 1, 2);
	addArc(G, 2, 3);
	addArc(G, 2, 5);
	addArc(G, 2, 6);
	addArc(G, 3, 4);
	addArc(G, 3, 7);
	addArc(G, 4, 3);
	addArc(G, 4, 8);
	addArc(G, 5, 1);
	addArc(G, 5, 6);
	addArc(G, 6, 7);
	addArc(G, 7, 6);
	addArc(G, 7, 8);
	addArc(G, 8, 8);
	
	printf("G:\n");
	printGraph(stdout, G);

	List stack = newList();
	for(int i=1; i<=n; i++) append(stack, i);
	DFS(G, stack);

	printf("stack: ");
	printList(stdout, stack);
	printf("\n\n");


	printf("FINDING THE SCCS");

	Graph H = transpose(G);
	printf("H = transpose(G):\n");
	printGraph(stdout, H);

	DFS(H, stack);

	printf("\n\n");

	printf("after DFS(H, stack):\n");
	// for(int i = 1; i <= getOrder(H); ++i){
	// 	printf("%3d: %3d\n", i, getParent(H, i));
	// }

	printf("printList(stack):\n");
	printList(stdout, stack);

	// ACTUAL DESIRED OUTPUT
	printf("Adjacency list representation of G:\n");
	printGraph(stdout, G);
	printf("\n");
	printComponents(stdout, H, stack);

	// freeGraph(&H);
	// freeList(&stack);
	// freeGraph(&G);
	return 0;
}