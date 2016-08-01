/**
 * Name:		Cecilia Condes
 * ID:			ccondes
 * Class: 		CMPS 101
 * Date:		8.8.15
 * Filename: 	List.h
 * Description:	List module for pa2: defines a doubly linked list with a cursor
 *				that points to one (or none) elements in a list
 */

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// #ifndef DEBUG
// #define DEBUG(ERR, MSG) { 
//  // fprintf(stderr, ERR+": "+__FILE__+":"+__LINE__+" %s\n", MSG);
//  // printf("%s:%d: %s: %s\n", __FILE__, __LINE__, ERR, MSG);
//  fprintf(stderr, __FILE__+":"+__LINE__+": "+ERR+": "+MSG+"\n");
// }
// #endif

#ifndef TRACE
#define TRACE __FILE__+':'+__LINE__
#endif

// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------
List newList(void);
void freeList(List* pL);

// Access functions -----------------------------------------------------------
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int equals(List A, List B);
int get(List L);

// Manipulation procedures ----------------------------------------------------
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void moveNext(List L);
void movePrev(List L);
void append(List L, int data);
void prepend(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);


// Other Functions ------------------------------------------------------------
void printList(FILE* out, List L);
List copyList(List L);

#endif
