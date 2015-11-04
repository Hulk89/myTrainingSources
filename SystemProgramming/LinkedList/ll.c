#include "ll.h"


/* return : if exist, return pointer of LL object.
            else, return NULL
*/
struct Node* findObj ( struct LinkedList* root , void* aObj )
{
    struct Node* ptr = root->head;

    while ( ptr != NULL )
    {
        if ( ptr->mObj == aObj )
        {
            break;
        }
        ptr = ptr->next;
    }
    return ptr;
}

/* return : the end of LinkedList.
*/
struct Node* end ( struct LinkedList* root )
{
    struct Node* ptr = root->head;
    struct Node* prevPtr = root->head;

    while ( ptr != NULL )
    {
        prevPtr = ptr;
        ptr = ptr->next;
    }
    return prevPtr;
}

void printLinkedList ( struct LinkedList* root )
{
    struct Node* ptr = root->head;

    while ( ptr != NULL && ptr->next != NULL )
    {
        printf( "%d -> ", *((int*)(ptr->mObj)) );
    
        ptr = ptr->next;
    }
    if ( ptr != NULL )
        printf( "%d\n", *((int*)(ptr->mObj)) );
    else
    {
        printf("There are no objects in LinkedList\n");
    }
}

int insertObj ( struct LinkedList* root, void* aObj )
{
    struct Node* ptr = end( root );
    struct Node* newNode = ( Node* ) malloc( sizeof( Node ) );

    newNode->next = NULL;
    newNode->mObj = aObj;

    if ( ptr == NULL )
    {
        root->head = newNode;
    }
    else
    {
        ptr->next = newNode;
    }
    return 1;
}

int insertAfterIndex ( LinkedList* root, int idx, void* aObj )
{
    Node* ptr = root->head;
    Node* newNode;

    int i = 0;

    for ( i = 0 ; i < idx-1 ; i++ )
    {
        if ( ptr == NULL )
        {
            return -1;
        }
        ptr = ptr->next;
    }
    
    newNode = ( Node* ) malloc( sizeof( Node ) );
    
    newNode->next = ptr->next;
    newNode->mObj = aObj;
    ptr->next = newNode;
    
    return 1;
}

int deleteAtIndex ( LinkedList* root, int idx )
{
    Node* ptr = root->head;
    Node* prevPtr = NULL;
    int i = 0;

    for ( i = 0 ; i < idx-1 ; i++ )
    {
        if ( ptr == NULL )
        {
            return -1;
        }
        prevPtr = ptr;
        ptr = ptr->next;
    }
    prevPtr->next = ptr->next;

    free(ptr->mObj);
    free(ptr);
    
    return 1;
}

int insertAtFirst ( LinkedList* root, void* aObj )
{
    Node* ptr = root->head;
    Node* newNode;
    
    newNode = ( Node* ) malloc( sizeof( Node ) );
    
    newNode->next = ptr;
    newNode->mObj = aObj;
    root->head = newNode; 
    return 1;
}

void deleteAll ( LinkedList* root )
{
    deleteRecursive( root->head );
    root->head = NULL;
}

void deleteRecursive ( Node* aNode )
{
    Node* ptr = aNode;

    if( ptr == NULL )
    {
        /* fall through */
    }
    else
    {
        deleteRecursive( ptr->next );
        free( ptr->mObj );
        ptr->mObj = NULL;
        free( ptr );
        ptr = NULL;
    }
    return;
}
