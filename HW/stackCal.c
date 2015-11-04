#include <stdio.h>
#include <string.h>
#define MAX 100
#define TRUE 1
#define FALSE 0
char OperatorStack[100];
char OperandStack[100];
int OperatorTop = 0;
int OperandTop = 0;
void InitializeStack(void);
void OperatorPush(char);
void OperandPush(int);
char OperatorPop(void);
int OperandPop(void);
int IsEmptyOperatorStack(void);
int IsEmptyOperandStack(void);
int GreaterOpr(char, char);
int Calculate(int, int, char);

int main(void)
{
	char buf[800];
	char buf2[800] = { 0, };

    int len, i, j;
	int opn1, opn2;
	char opr,c;
	char tmpopr;

	printf("Enter any expression :");
	fgets(buf,MAX,stdin);
	printf("\n");

	if(buf[0] == 'e') // input??exit ?대㈃醫낅즺?섍쾶 
		return 0;
	len = strlen(buf);
	i = j = 0;

	while(i < len){
		c = buf[i++];
		if(c <='9' && c >='0')		// 숫자일 경우
			buf2[j++] = c;
		else if( c == '+' || c == '-' || c == '*' || c == '/'){		//연산자인 경우
			if(IsEmptyOperatorStack())
				OperatorPush(c);
			else
			{
				while( !IsEmptyOperatorStack() )
                {
                    opr = OperatorPop();
                    if( GreaterOpr(opr,c) )
                        buf2[j++] = opr;
                    else
                    {
                        OperatorPush(opr);
                        break;
                    }
				}
				OperatorPush(c);
			}
		}	
		else if(c == '('){							//괄호 시작
			OperatorPush(c);
		}else if(c == ')'){							//괄호 끝
			do {
				tmpopr = OperatorPop();
                if ( tmpopr != '(' )
                    buf2[j++] = tmpopr;
                else
                {
                    printf("%c\n",tmpopr );
                    break;
                }
			} while ( 1 );
		}
		else if( c == '\n' )
 		{
            while ( !IsEmptyOperatorStack() )
            {
                opr = OperatorPop();
                buf2[j++] = opr;
            }
 		}
        else
        {
            printf( "%c\n",c );
        }

	}
	// printf("OperandStack: %d, OperatorStack: %s", OperandStack[0],OperatorStack); 

	printf("%s\n",buf2);


	return 0;
}
void OperatorPush(char opr){
	OperatorStack[OperatorTop++] = opr;
}
void OperandPush(int opn){
	OperandStack[OperandTop++] = opn;
}
char OperatorPop(void){
	return OperatorStack[--OperatorTop];
}
int OperandPop(void){
	return OperandStack[--OperandTop];
}
int IsEmptyOperandStack(void)
{
	if(OperandTop == 0)
		return TRUE;
	else
		return FALSE;
}
int IsEmptyOperatorStack(void)
{
	if(OperatorTop == 0)
		return TRUE;
	else
		return FALSE;
}
int GreaterOpr(char opr1, char opr2)
{
	if(opr2 == '*' || opr2 == '/'){
		if(opr1 == '+' || opr1 == '-' || opr1 == '(' )
			return FALSE;
		else
			return TRUE;
	}
	else if( opr2 == '+' || opr2 == '-')
    {    
        if( opr1 == '(' )
		    return FALSE;
        else
            return TRUE;
    }
    else
        return FALSE;
}
int Calculate(int opn1, int opn2, char opr)
{
	switch(opr){
		case'+':
		opn1 = opn1 + opn2;
		break;
		case'-':
		opn1 = opn2 - opn1;
		break;
		case'*':
		opn1 = opn1 * opn2;
		break;
		case'/':
		opn1 = opn2 / opn1;
		break;
	}
	return opn1;
}
