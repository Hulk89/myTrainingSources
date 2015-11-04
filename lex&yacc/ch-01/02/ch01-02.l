%{
    /* definition section
     * 
     */
%}
 /* 한칸 뒤에 주석으로 해야 처리된다.
  * 밑의 %%는 definition section의 끝을 말한다.*/
%%

 /* rules section */
 /*
  * pattern & action으로 이루어진다. 
  * 1. lex pattern은 주어진 문자열에 대해 한번만 매치한다.
  * 2. longest possible match에 대한 동작을 수행한다.
  */

[\t ]+   /* 공백은 무시한다 */

is |
am |
are |
were |
was |
be |
being |
been |
do |
does |
did |
will |
would |
should |
can |
could |
has |
have |
had |
go  { printf( "%s: is a verb.\n", yytext ); }
[a-zA-Z]+    { printf( "%s: is not a verb.\n", yytext ); }
.|\n    { ECHO; /* 기본적으로 수행되는 동작 */ }

%%
 /* user subroutine section */
int main()
{
    yylex(); /* return이 존재하지 않는 경우 주어진 입력 전체를 처리할 때 까지 return하지 않는다. */
    return 0;
}

