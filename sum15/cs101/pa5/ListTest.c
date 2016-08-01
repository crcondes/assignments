/**
 * Name:		Cecilia Condes
 * ID:			ccondes
 * Class: 		CMPS 101
 * Date:		8.8.15
 * Filename: 	ListTest.c
 * Description:	test client for List.c
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include"List.h"

int main(int argc, char const *argv[]){
	printf("compiled\n");

	// List L = newList();

	// printf("length(): 0\n");
	// printf("          %d\n", length(L));
	// append(L, 55);
	// append(L, 42);

	// // 55 <--> 42

	// printf("length(): 2\n");
	// printf("          %d\n", length(L));
	// printList(stdout, L);

	// printf("index(): -1\n");
	// printf("         %d\n", index(L));

	// printf("moveFront()\n");
	// moveFront(L);
	// printf("get(): 55\n");
	// printf("       %d\n", get(L));
	// printf("moveBack(): 42\n");
	// moveBack(L);
	// printf("index(): 1\n");
	// printf("         %d\n", index(L));

	// append(L,0);
	// append(L,9);
	// // 55 <--> 42 <--> 0 <--> 9
	// printf("get(): 42\n");
	// printf("       %d\n", get(L));
	// printf("movePrev()\n");
	// movePrev(L);
	// printf("get(): 55\n");
	// printf("       %d\n", get(L));

	// printf("front(): 55\n");
	// printf("         %d\n", front(L));
	// printf("back(): 9\n");
	// printf("        %d\n", back(L));

	// printf("printList(): 55 42 0 9\n             ");
	// printList(stdout, L);

	// List X = copyList(L);
	// printf("printList(X): 55 42 0 9\n             ");
	// printList(stdout, X);
	// printf("equals(L,X): true\n");
	// printf("%d\n", equals(L,X));
	// append(X, -77);
	// // 55 <--> 42 <--> 0 <--> 9 <--> -77
	// printf("equals(L,X): false\n");
	// printf("%d\n", equals(L,X));
	// //clear(L);
	// //
	// printf("printList(): \n");
	// printList(stdout, L);


	// prepend(L, 22);
	// // 22 <--> 55 <--> 42 <--> 0 <--> 9
	// moveFront(L);
	// printf("index(): 0\n");
	// printf("         %d\n", index(L));
	// prepend(L, 11);
	// // 11 <--> 22 <--> 55 <--> 42 <--> 0 <--> 9
	// printf("index(): 1\n");
	// printf("         %d\n", index(L));
	// printf("printList(): 11 22 55 42 0 9\n             ");
	// printList(stdout, L);

	// insertBefore(L, 111);
	// // 11 <--> 111 <--> 22 <--> 55 <--> 42 <--> 0 <--> 9
	// printf("index(): 2\n");
	// printf("         %d\n", index(L));
	// printf("printList(): 11 111 22 55 42 0 9\n             ");
	// printList(stdout, L);
	// movePrev(L);
	// printf("movePrev(): 1, 111\n");
	// printf("            %d, %d\n", index(L), get(L));
	// moveNext(L);
	// printf("moveNext(): 2, 22\n");
	// printf("            %d, %d\n", index(L), get(L));
	// moveFront(L);
	// printf("moveFront(): 0, 11\n");
	// printf("            %d, %d\n", index(L), get(L));
	// movePrev(L);
	// printf("movePrev(): -1, -1000000\n");
	// printf("            %d, NULL\n", index(L));
	// // 11 <--> 111 <--> 22 <--> 55 <--> 42 <--> 0 <--> 9
	// printf("length(): 7\n");
	// printf("          %d\n", length(L));
	// printf("printList(): 11 111 22 55 42 0 9\n             ");
	// printList(stdout, L);

	// // printList(stdout, L);
	// deleteBack(L);
	// printf("deleteBack(L)\n             ");
	// printList(stdout, L);
	// deleteFront(L);
	// printf("deleteFront(L)\n             ");
	// printList(stdout, L);
	// clear(L);
	// printf("clear()\n");
	// printList(stdout, L);
	// prepend(L, 88);
	// printf("printList(): 88\n             ");
	// printList(stdout, L);

	// printf("moveBack(): 0, 88\n");
	// moveBack(L);
	// printf("            %d, %d\n", index(L), get(L));

	// moveNext(L);
	// printf("moveNext(): -1, -1000000\n");
	// printf("            %d, NULL\n", index(L));



	// freeList(&L);
	// freeList(&X);

	List L = newList();
	int n = 5;
	
	for (int i = 0; i < n; ++i) {
		append(L, i+1);
	}

	printList(stdout, L);
	moveBack(L);
	printf("L->cursor = %d\n", get(L));

	for (int i = 0; i < n; ++i) {
		deleteFront(L);
		// append(L, i);
		insertBefore(L, i);
		// if(index(L) > -1) 
		// 	insertAfter(L, i);
		// else
		// 	append(L, i);

		printList(stdout, L);

	}

	printf("after modification loop\n");

	printList(stdout, L);
	freeList(&L);

	return EXIT_SUCCESS;
}