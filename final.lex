%{
    #include "expr.tab.h"

    #define YY_SKIP_YYWRAP
    int yywrap() { return 1; }
%}

ID [a-z]+ 
ASSIGNOP [=] 
WEBOBJECT [https:\/\/www\.[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}] 
FUNC1GETHTML [\.GETHTML] 
FUNC2FINDWEBIMAGES [\.FINDWEBIMAGES]
FUNC3ORGANIZEWEBINFO [\.ORGANIZEWEBINFO]

%% 

{ID} {
    yylval.id = (char*) strdup(yytext);
    return (ID);
}

"=" {
    return (ASSIGNOP);  
}

{FUNC1GETHTML} {
    yylval.val = (char*) strdup(yytext);
    return (FUNC1GETHTML); 
}

 {FUNC2FINDWEBIMAGES} { 
    yylval.val = (char*) strdup(yytext);
    return (FUNC2FINDWEBIMAGES); 
}

{FUNC3ORGANIZEWEBINFO} {
    yylval.val = (char*) strdup(yytext);
    return (FUNC3ORGANIZEWEBINFO); 
}

"$$" {
    return (END);
}

[ \t\n\r]+ /* eat up whitespace */
. { printf( "Unknown: '%s'\n", yytext ); }

%%