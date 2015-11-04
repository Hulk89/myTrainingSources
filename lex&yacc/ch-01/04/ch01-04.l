%{
    enum {
            LOOKUP = 0,
            VERB,
            ADJ,
            ADV,
            NOUN,
            PREP,
            PRON,
            CONJ
    };
    int state;
    int addWord( int aType, char *aWord );
    int lookupWord( char *aWord );
%}

%%

\n      { state = LOOKUP; }
^verb   { state = VERB; }
^adj    { state = ADJ; }
^adv    { state = ADV; }
^noun   { state = NOUN; }
^prep   { state = PREP; }
^pron   { state = PRON; }
^conj   { state = CONJ; }

[a-zA-Z]+   {
    if ( state != LOOKUP )
    {
        addWord( state, yytext );
    }
    else
    {
        switch( lookupWord( yytext ) )
        {
            case VERB:
                printf( "%s: verb.\n", yytext );
                break;
            case ADJ:
                printf( "%s: adjective.\n", yytext );
                break;
            case ADV:
                printf( "%s: adverb.\n", yytext );
                break;           
            case NOUN:
                printf( "%s: noun.\n", yytext );
                break;          
            case PREP:
                printf( "%s: preposition.\n", yytext );
                break;           
            case PRON:
                printf( "%s: pronoun.\n", yytext );
                break;           
            case CONJ:
                printf( "%s: conjunction.\n", yytext );
                break;           
            default:
                printf( "%s: cannot recognize.\n", yytext );
                break;
        }
    }
}

%%
 /* user subroutine section */
int main()
{
    yylex(); /* return이 존재하지 않는 경우 주어진 입력 전체를 처리할 때 까지 return하지 않는다. */
    return 0;
}

typedef struct wordNode {
    char*               mWordName;
    int                 mWordType;
    struct wordNode*    mNext;
} wordNode;

wordNode* gWordList;

//extern void *malloc();

int addWord( int aType, char* aWord )
{
    wordNode* ptr;
    if ( lookupWord( aWord ) != LOOKUP )
    {
        printf( "!!! warning: word %s is already defined \n", aWord );
        return 0;
    }

    ptr = (wordNode*)malloc( sizeof( wordNode ) );
    ptr->mNext = gWordList;

    ptr->mWordName = (char*)malloc( strlen( aWord ) + 1 );
    strcpy( ptr->mWordName, aWord );
    ptr->mWordType = aType;
    gWordList = ptr;
    
    return 1;
}

int lookupWord( char* aWord )
{
    wordNode * ptr = gWordList;

    for ( ; ptr ; ptr = ptr->mNext )
    {
        if ( strcmp( ptr->mWordName, aWord ) == 0 )
        {
            return ptr->mWordType;
        }
    }
    return LOOKUP;
}

