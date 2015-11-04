#include "ll.h"




int main(int argc, char* argv[] )
{
    int*  a[10];
    int   idx;
    int* x = (int*) malloc( sizeof(int) );
    int* y = (int*) malloc( sizeof(int) );
    
    for( idx = 0 ; idx < 10 ; idx++ )
    {
        a[idx] = (int*)malloc( sizeof(int) );
    }

    LinkedList* root = (LinkedList*)malloc(sizeof(LinkedList));
    root->head = NULL;
    
    printf("insert Test.\n");
    for ( idx = 0 ; idx < 10 ; idx++ )
    {
        *(a[idx]) = idx;
        insertObj( root, a[idx] );
    }
    printLinkedList(root);

    printf("delete linkedlist from index 3.\n");
    deleteAtIndex( root, 3 );

    printLinkedList(root);
    
    *x = 100;
    
    printf("insert 100 into after index 2.\n");
    insertAfterIndex( root, 2, x );

    printLinkedList(root);

    printf("insert 200 into at first.\n");
    *y = 200;
    insertAtFirst( root, y );

    printLinkedList(root);

    deleteAll(root);   

    printLinkedList(root);

    free( root );

    return 0;
}

