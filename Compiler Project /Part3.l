%{


	#include <string.h>
	#include <stdlib.h>
	#include <stdio.h> 
	#include "y.tab.h"
%}

%option yylineno
%x COMMENT

%%
"bool" 															{yylval.string = strdup(yytext); return BOOL;}
"real" 															{yylval.string = strdup(yytext); return REAL;}
"int"															{yylval.string = strdup(yytext); return INT;}
"char" 															{yylval.string = strdup(yytext); return CHAR;}
"int*"															{yylval.string = strdup(yytext); return INTP;}
"char*" 														{yylval.string = strdup(yytext); return CHARP;}
"real*"															{yylval.string = strdup(yytext); return REALP;}
"string"														{yylval.string = strdup(yytext); return STRING;}
"if"															{return IF;}
"else"															{return ELSE;}
"while"                                                 		{return WHILE;}
"do"                                                   			{return DO;}
"for"															{return FOR;}
"true"															{yylval.string = strdup(yytext); return TRUEE;}
"false"															{yylval.string = strdup(yytext); return FALSEE;}
"var"															{return VAR;}
"return"														{return RETURN;}
"null"															{return NULLP;}
"void"															{return VOID;}

"+"																{yylval.string = strdup(yytext); return PLUS;}
"-"																{yylval.string = strdup(yytext); return MINUS;}
"/"																{yylval.string = strdup(yytext); return DIV;}
"*"																{yylval.string = strdup(yytext); return MUL;}
"="																{yylval.string = strdup(yytext); return PLACEMENT;}
"&&"															{yylval.string = strdup(yytext); return AND;}
"=="															{yylval.string = strdup(yytext); return EQ;}
">"																{yylval.string = strdup(yytext); return G;}
">="															{yylval.string = strdup(yytext); return GE;}
"<"																{yylval.string = strdup(yytext); return L;}
"<="															{yylval.string = strdup(yytext); return LE;}
"!"																{yylval.string = strdup(yytext); return NOT;}
"!="															{yylval.string = strdup(yytext); return NOTEQ;}
"||"															{yylval.string = strdup(yytext); return OR;}
"&"																{yylval.string = strdup(yytext); return ADR;}
";"       														{yylval.string = strdup(yytext); return ENDSTATEMENT;}
"("																{yylval.string = strdup(yytext); return OPE_BRA;}
")"																{yylval.string = strdup(yytext); return CLS_BRA;}
"{"																{yylval.string = strdup(yytext); return OPE_BLOCK;}
"}"																{yylval.string = strdup(yytext); return CLS_BLOCK;}
"["																{yylval.string = strdup(yytext); return OPE_ARRAY;}
"]"																{yylval.string = strdup(yytext); return CLS_ARRAY;}
","  															{yylval.string = strdup(yytext); return PSIK;}



0|[1-9][0-9]*													{ yylval.string = strdup(yytext); return DEC; };
0[xX][A-F0-9]+													{ yylval.string = strdup(yytext); return HEX; };
[0-9]*[\.]?[0-9]+|[0-9]*[\.]?[0-9]+[eE][-+]?[0-9]+				{ yylval.string = strdup(yytext); return EXP; };
\"[^\"]*\"														{ yylval.string = strdup(yytext); return STR; };
[a-zA-Z][a-zA-Z0-9_]*											{yylval.string=strdup(yytext); return ID;}
'[^\']'															{yylval.string = strdup(yytext); return TAV;}

"\n"															{yylineno++;}
[ \t\r]															{;}
"/*"															{BEGIN(COMMENT);}
<COMMENT>"*/"													{BEGIN(INITIAL);}
<COMMENT>\n														{yylineno++;}
<COMMENT>.														{;}
.																{return yytext[0];}
%%
