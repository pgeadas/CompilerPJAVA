%{
#include "structures.h"
#include "y.tab.h"
%}

%S COMENTARIOS

stringAspas 			\"[^\"]*\"
floatNumber			[0-9]+"."[0-9]*
comentariosLinha		"//".*\n


%%

{comentariosLinha}	{linha++;}
"/*"			{BEGIN COMENTARIOS;}

<COMENTARIOS>[^"*/"\n]* {;}
<COMENTARIOS>\n		{linha++;}
<COMENTARIOS>"*/"	{BEGIN 0;}
"="			{return EQUAL;}
"%"			{return MOD;}
"-"			{return MINUS;}
"*"			{return MULT;}
"/"			{return DIV;}
"+"			{return PLUS;}
"--"			{return MINUSMINUS;}
"++"			{return PLUSPLUS;}
"!"			{return NOT;}
"-="			{return MINUSEQUAL;}
"+="			{return PLUSEQUAL;}
"^"			{return POT;}
"=="			{return EQUALEQUAL;}
"!="			{return NOTEQUAL;}
"<="			{return LESSEQUAL;}
">="			{return GREATEREQUAL;}
">"			{return GREATER;}
"<"			{return LESS;}
"&&"			{return AND;}
"||"			{return OR;}



"int"			{return INTSYMB;}
"float"			{return FLOATSYMB;}
"double"		{return DOUBLESYMB;}
"String"		{return STRINGSYMB;}
"void"			{return VOIDSYMB;}
"boolean"		{return BOOLSYMB;}

"True"			{yylval.boolValue=true; return BOOL;}
"False"			{yylval.boolValue=false; return BOOL;}

"public static "	{return FUNCSYMB;}
"public class "         {return CLASSSYMB;}
"return"		{return RETURNSYMB;}

"if"			{return IF;}
"while"			{return WHILE;}
"else"			{return ELSE;}
"else if"		{return ELSEIF;}			
"for"			{return FOR;}
"System.out.print"	{return PRINT;}
"System.out.println"	{return PRINTLN;}
"System.in.read"	{return READ;}
"System.in.readln"      {return READLINE;}
"System.concat"		{return CONCATSYMB;}
"break"			{return BREAK;}
"continue"		{return CONTINUE;}

{stringAspas}	  	{yylval.string= (char *)strdup(yytext); return STRING;}
[A-Za-z][A-Za-z0-9_]*  	{yylval.id=(is_id*)malloc(sizeof(is_id)); yylval.id->id= (char *)strdup(yytext); yylval.id->codeLine=linha; return ID;}
{floatNumber}		{yylval.floatValue=atof(yytext);return FLOAT;}
[0-9]+			{yylval.intValue=atoi(yytext); return INT;}
[ \t]			;
\n			{linha++;}
[^\"\n] 		{return yytext[0];}


%%

int yywrap()
{
	return 1;
}


