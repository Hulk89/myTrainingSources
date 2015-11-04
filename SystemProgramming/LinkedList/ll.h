#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    void* mObj;
    struct Node* next;
} Node;

typedef struct LinkedList
{
    struct Node* head;
} LinkedList;


/* return : if exist, return pointer of LL object.
            else, return NULL
*/
struct Node* findObj ( struct LinkedList* root , void* aObj );
/* return : the end of LinkedList.
*/
struct Node* end ( struct LinkedList* root );

void printLinkedList ( struct LinkedList* root );

int insertObj ( struct LinkedList* root, void* aObj );

int insertAfterIndex ( LinkedList* root, int idx, void* aObj );

int deleteAtIndex ( LinkedList* root, int idx );

int insertAtFirst ( LinkedList* root, void* aObj );

void deleteAll( LinkedList* root );

void deleteRecursive ( Node* aNode );

