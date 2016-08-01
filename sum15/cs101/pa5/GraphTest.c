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

int main(int argc, char const *argv[]){
	printf("compiled\n");
	Graph G = newGraph(8);

	printf("getOrder(): 8\n");
	printf("            %d\n", getOrder(G));
	printf("getSize(): 0\n");
	printf("           %d\n", getSize(G));

	// addArc(G, 1, 4);
	// addArc(G, 1, 2);
	// addArc(G, 3, 4);
	// addArc(G, 4, 5);
	// addArc(G, 1, 3);
	// addArc(G, 6, 2);
	// addArc(G, 4, 6);
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
	
	printGraph(stdout, G);

	printf("getOrder(): 8\n");
	printf("            %d\n", getOrder(G));
	printf("getSize(): 14\n");
	printf("           %d\n", getSize(G));

	// Graph H = copyGraph(G);
	// printf("copyGraph(G)\n");
	// printGraph(stdout, H);

	List stack = newList();
	// DFS(G, stack);

	// printf("Node 4: discovered at %d, finished at %d, child of %d\n", 
	// 		getDiscover(G, 4), getFinish(G, 4), getParent(G, 4));

	Graph H = transpose(G);
	printf("transpose():\n");
	printGraph(stdout, H);
	printf("getOrder(): 8\n");
	printf("            %d\n", getOrder(H));
	printf("getSize(): 14\n");
	printf("           %d\n", getSize(H));

	freeGraph(&H);
	freeList(&stack);
	freeGraph(&G);
	return 0;
}