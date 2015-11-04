
%{

%}

%%

[\t ] ;
is  { printf("is\n"); return 1; }


%%

int main()
{
    yylex();
}
