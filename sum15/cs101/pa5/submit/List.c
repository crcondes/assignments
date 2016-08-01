/**
 * Name:        Cecilia Condes
 * ID:          ccondes
 * Class:       CMPS 101
 * Date:        8.8.15
 * Filename:    List.c
 * Description: List module for pa5: defines a doubly linked list with a cursor
 *              that points to one (or none) elements in a list
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include"List.h"

/* TEST
 * newNode      PASS
 * freeNode
 * newList      PASS
 * freeList
 * length       PASS
 * index        PASS    
 * front        PASS
 * back         PASS
 * equals       PASS
 * get          PASS
 * clear        PASS
 * moveFront    PASS
 * moveBack     PASS
 * moveNext     PASS
 * movePrev     PASS
 * append       PASS
 * prepend      PASS
 * insertBefore PASS
 * insertAfter  PASS
 * deleteFront  PASS
 * deleteBack   PASS
 * printList    PASS
 * copyList     PASS
 */

// #ifndef TRACE
// #define TRACE(err, msg) (fprintf(stderr, err+": "+__FILE__+":"+__LINE__+" %s\n", msg)) 
// #endif

#ifndef TRACE
#define TRACE (__FILE__+":"+__LINE__)
#endif

void throwException(char* msg){
    printf("Runtime Exception: %s\n", msg);
    exit(EXIT_FAILURE);
}

// void throwException(char* trc, char* msg){
//     printf("%s: %s\n", trc, msg);
// }

// :)
// private NodeObj type
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

// :)
// private Node type
typedef NodeObj* Node;

// :)
// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int index;
    int numItems;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// :)
// newNode() - private
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return(N);
}

// :)
// freeNode() - private
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
    if( pN!=NULL && *pN!=NULL ){
        free(*pN);
        *pN = NULL;
    }
}

// :)
// newList()
// Returns reference to new empty List object.
List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->index = -1;
    L->numItems = 0;
    return(L);
}

// :)
// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL
void freeList(List* pL){
    if(pL!=NULL && *pL!=NULL) { 
    // if(*pL!=NULL){ 
        while( length(*pL) > 0 ) { 
            deleteFront(*pL); 
        }
        free(*pL);
        *pL = NULL;
    }
}


// Access functions -----------------------------------------------------------
// :)
// index()
// returns the value of the index
int index(List L){
    if(NULL==L)
        throwException("NullPointerException: List does not exist");

    return L->index;
}

// :)
// length()
// Returns the length of L.
int length(List L){
    if( L==NULL ){
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }
    return(L->numItems);
}

// :)
// get()
// returns the value of the Node pointed to by cursor
int get(List L){
    if(NULL == L)
        throwException("NullPointerException: Calling get() on null List");

    if(NULL == L->cursor)
        throwException("NullPointerException: Calling get() on null cursor");
        
    Node N = L->cursor;
    return N->data;
}

// :)
// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L){
    if( L==NULL ){
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }
    if( length(L) <= 0 ){
        printf("List Error: calling front() on an empty List\n");
        exit(1);
    }
    return(L->front->data);
}

// :)
// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L){
    if( L==NULL ){
        printf("List Error: calling back() on NULL List reference\n");
        exit(1);
    }
    if( length(L) <= 0 ){
        printf("List Error: calling back() on an empty List\n");
        exit(1);
    }
    return(L->back->data);
}

// :)
// currently only a private fn
// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L){
    if( L==NULL ){
        printf("List Error: calling isEmpty() on NULL List reference\n");
        exit(1);
    }
    return(L->numItems==0);
}

// :)
// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
    int eq = 0;
    Node N = NULL;
    Node M = NULL;

    if( A==NULL || B==NULL ){
        printf("List Error: calling equals() on NULL List reference\n");
        exit(1);
    }

    eq = ( A->numItems == B->numItems );
    N = A->front;
    M = B->front;
    while( eq && N!=NULL){
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// Manipulation procedures ----------------------------------------------------
// :)
// clear()
// sets the list to the empty state
void clear(List L){
    if(NULL != L) { 
        while( length(L) > 0 ) { 
            deleteFront(L); 
        }
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
        L->numItems = 0;
    }
}

// :)
// moveFront()
// moves the cursor to the first element of the list and sets index to 0
void moveFront(List L){
    // if(NULL == L)
    //     throwException("NullPointerException: calling moveFront() on (NULL)");

    // if(length(L) == 0)
    //     throwException("ListEmptyException: calling moveFront() on empty List");
    
    if(NULL != L && length(L) != 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}

// :)
// moveBack()
// moves the cursor to the last element of the list and sets index to size-1
void moveBack(List L){
    if(NULL == L)
        throwException("NullPointerException: calling moveBack() on (NULL)");
    
    if(length(L) == 0)
        throwException("ListEmptyException: calling moveBack() on empty List");
    
    L->cursor = L->back;
    L->index = L->numItems - 1;
}

// :)
// moveNext()
// moves the cursor to the next element, becomes undefined if already at end
void moveNext(List L){
    if(NULL == L)
        throwException("NullPointerException: calling moveNext() on (NULL)");
    
    if(length(L) == 0)
        throwException("ListEmptyException: calling moveNext() on empty List");
    
    // if(L->index == (L->numItems - 1)){ // cursor is at the end
    //     L->index = -1;
    //     L->cursor = NULL;
    // }

    // if(L->index > -1 && L->index < (L->numItems - 1)){ // cursor is internal
    //     L->index++;
    //     L->cursor = L->cursor->next;
    // }

	// if(L->cursor!=NULL){
	// 	if(L->index > 0){
	// 		L->cursor = L->cursor->next;
	// 		L->index++;
	// 	}
	// 	if(L->index == 0){
	// 		L->cursor = NULL;
	// 		L->index = -1;
	// 	}
	// }
	// else{
	// 	L->cursor = NULL;
	// 	L->index = -1;
	// }

    if(L->cursor->next == NULL){
        // printf("cursor->next == NULL\n");
        L->cursor = NULL;
        L->index = -1;
    }
    else{
        // printf("cursor->next != NULL\n");
        L->cursor = L->cursor->next;
        L->index++;
    }
}

// :)
// movePrev()
// moves the cursor to the previous element, becomes undf if already at begin
void movePrev(List L){
    if(NULL == L)
        throwException("NullPointerException: calling movePrev() on (NULL)");
    
    if(length(L) == 0)
        throwException("ListEmptyException: calling movePrev() on empty List");
    
    L->index -= 1; // covers both cases: 1 --> 0, 0 --> -1

    if(L->index < 0) L->cursor = NULL;
    else {
        L->cursor = L->cursor->prev;
    }
}

// :)
// append()
// Places new data element at the end of L
void append(List L, int data){
    Node N = newNode(data);

    if( L==NULL ){
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ) { 
        L->front = L->back = N; 
    }
    else{ 
        L->back->next = N; 
        N->prev = L->back;
        L->back = N; 
    }
    L->numItems++;
}

// :)
// prepend()
// places new data element at the beginning of L
void prepend(List L, int data){
    Node N = newNode(data);

    if( L==NULL ){
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ) { 
        L->front = L->back = N; 
    }
    else {
        L->front->prev = N;
        N->next = L->front;
        L->front = N;
        if(L->index > -1) L->index++;
    }
    L->numItems++;
}

// :)
// insertBefore()
// places new data element in L before the cursor
void insertBefore(List L, int data){
    if(length(L) <= 0)
        throwException("Cannot insert before cursor: empty list");

    if(L->index < 0)
        throwException("Cannot insert before undefined cursor");

    Node N = newNode(data);
    if(L->index > 0){
        L->cursor->prev->next = N;
        N->prev = L->cursor->prev;
    
        N->next = L->cursor;
        L->cursor->prev = N;

        L->numItems++;
        L->index++;
    }
    else prepend(L, data);
}

// :)
// insertAfter()
// places new data element in L after the cursor
void insertAfter(List L, int data){
    if(length(L) <= 0)
        throwException("Cannot insert before cursor: empty list");

    if(L->index < 0)
        throwException("Cannot insert before undefined cursor");

    Node N = newNode(data);
    if(L->index < (L->numItems - 1)){
        L->cursor->next->prev = N;
        N->next = L->cursor->next;
    }
    N->prev = L->cursor;
    L->cursor->next = N;

    L->numItems++;
}

// :)
// deleteFront()
// Deletes element at front of L
// Pre: !isEmpty(L)
void deleteFront(List L){
    Node N = NULL;

    if( L==NULL ){
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ){
        printf("List Error: calling deleteFront on an empty List\n");
        exit(1);
    }
    N = L->front;
    if( length(L)>1 ) { 
        L->front = L->front->next; 
    }else{ 
        L->front = L->back = NULL; 
    }
    L->numItems--;
    freeNode(&N);
}

// :)
// deleteBack()
// deletes element at the back of L
void deleteBack(List L){
    Node N = NULL;

    if( L==NULL ){
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    if( isEmpty(L) ){
        printf("List Error: calling deleteBack on an empty List\n");
        exit(1);
    }

    N = L->back;
    if(length(L) > 1) {
        L->back = L->back->prev;
        L->back->next = NULL;
    }
    else {
        L->back = L->front = NULL;
    }
    L->numItems--;
    freeNode(&N);

}


// Other Functions ------------------------------------------------------------

// :)
// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L){
    Node N = NULL;

    if( L==NULL ){
        printf("List Error: calling printList() on NULL List reference\n");
        exit(1);
    }

    for(N = L->front; N != NULL; N = N->next){
        fprintf(out, " %d", N->data);
    }
    fprintf(out, "\n");
}

// :)
// copyList()
// returns a copy of the list, with the cursor set to undefined
List copyList(List L){
    List C = newList();
    moveFront(L);
    while(NULL != L->cursor){
        append(C, get(L));
        moveNext(L);
    }

    return C;
}
