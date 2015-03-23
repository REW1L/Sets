//cell of linkedList

struct linkedList
{
    char name[24];
    void* data;
    struct linkedList *next;
    struct linkedList *prev;
};
//external functions
int compare(char*, char*);
int strcopy(char*, char*);

//functions for working with linkedList

struct linkedList *createLinkedList(char*, int); 
struct linkedList *getLinkedList(char*, int, int); 
struct linkedList *getElementById(struct linkedList*, int); 
struct linkedList *getElementByValue(struct linkedList*, void*); 
int addElement(char*, char*, int); 
int deleteElementByValue(char*, char*, int); 
int deleteList(char* listname, int); 
int countElements(struct linkedList*); 
int printList(char*, int); 


//boolean functions

//main function for boolean
struct linkedList* logics(void (*)(struct linkedList*, struct linkedList*, struct linkedList*),char*,char*, char*, char*, int);

//union
struct linkedList *uniLists(char*, char*, char*, int); 

//check whether list 1 is in list 2
///@return 1 if in, 0 if not in
int isin(char*, char*, int); 

//intersec (list, list, rez)
struct linkedList* intersec(char*, char*, char*, int); 

//diff (list, list, rez)

struct linkedList* diff(char*, char*, char*, int); 

//simmdiff (list, list, rez)
struct linkedList* simmdiff(char*, char*, char*, int); 

//showAll
int showAll();

#include "LinkedList.c"