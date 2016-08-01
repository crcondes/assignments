/**
 * Name:		Cecilia Condes
 * ID:			ccondes
 * Class: 		CMPS 101
 * Date:		8/10/15
 * Filename: 	FindComponents.c
 * Description:	Graph ADT client for pa5
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <assert.h>
#include <getopt.h>
#include "List.h"
#include "Graph.h"

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef debug
#define debug 0
#endif

void throwException(char* msg);

void printComponents(FILE* out, Graph G, List S){
	int i = 1, scc = 0;
	List* strong = malloc(sizeof(List)*(getOrder(G)+1));

	moveBack(S);
	while(index(S) > -1){	
		strong[i] = newList();
		++scc;
		while(1) {	// infinite loop - MUST have a break statement
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
		fprintf(out, "Component %d:", i);
		printList(out, strong[i]);
		freeList(&strong[i]);
	}

	free(strong);
	// strong = NULL;


	
}

int stoi(char* s){
	int result = 0;
	for(int i = 0; s[i] != '\0'; ++i)
		result = (result*10) + ((s[i]) - '0');
		if(debug) printf("stoi result = %d\n", result);

	return result;
}

int main(int argc, char *argv[]){

	FILE* in;
	FILE* out;
	int n = 0;
	int llen = 4; // line length (max expected, anyway) = 3???

	Graph G = NULL;

	// file i/o setup----------------------------------------------------------

	// check for correct number of command-line args
	if(argc != 3) throwException("Usage: FindComponents <input file> <output file> [options]\n");

	// open input file
	if((in=fopen(argv[1], "r"))==NULL) throwException("Unable to read from file\n");

	// open output file for writing
	if((out=fopen(argv[2], "w"))==NULL) throwException("Unable to write to file\n");

	if(debug) printf("file i/o setup complete\n");

	// line scanning----------------------------------------------------------
	char* line = malloc((sizeof(char)*llen)+1); 
	assert(line!=NULL);

	// set n, the number of vertices
	if(fgets(line, llen, in)!=NULL) n = atoi(line); 
	if(debug) printf("n = %d\n", n);
	G = newGraph(n);
	if(debug) printGraph(out, G);

	int u = -1, v = -1;
	if(debug) printf("creating adjacency list:\n");

	fscanf(in, "%d %d\n", &u, &v);
	while(0 != u || 0 != v){
		addArc(G, u, v);
		fscanf(in, "%d %d\n", &u, &v);
	}
	// DFS-ing-----------------------------------------------------------------

	List stack = newList();
	for(int i=1; i<=n; i++) append(stack, i);
	DFS(G, stack);

	Graph T = transpose(G);
	DFS(T, stack);

	// output------------------------------------------------------------------
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");
	printComponents(out, T, stack);


	fclose(in);
	fclose(out);
	free(line);
	freeList(&stack);
	freeGraph(&G);
	freeGraph(&T);
	return EXIT_SUCCESS;
}