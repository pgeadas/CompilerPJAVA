%{
#include "structures.h"
#include "functions.h"
#include "symbol_table.h"
#include "semantics.h"
#include "shows.h"
#include "translate.h"
#include <stdio.h>

int ERROS=0;
int showShows=1;	 	//1 - Ligar os Shows | 0 - Desligar os Shows
int checkSemantic=1; 		//1 - Ligar a verificacao da semantica | 0 - Desligar
int showTable=1; 		//1 - Ligar o show Table | 0 - Desligar

table_element *symtab=NULL;


is_program * PJAVAPROGRAM;

%}

%union{
	int intValue;
	float floatValue;
	double doubleValue;
	char* string;
	bool boolValue;

	is_statement_list* isl;
	is_instruction* ii;
	is_expression* ie;
	is_relac_exp* ire;
	is_logic_exp_or_and* ileoa;
	is_logic_exp_not* ilen;
	is_aritmetic_exp* iae;
	is_atribution_list* ial;
	is_atribution* ia;
	is_id* id;
	is_statement* is;
	is_type* ity;
	is_program* iprogram;
	is_compound_statement* ics;
	is_if_statement* iifs;
	is_while_statement* iws;
	is_else_statement* ielses;
	is_elseif_statement* ielseifs;
	is_elseif_statement_list* ieisl;
	is_cont_statement* iconts;
	is_println_statement* iprints;
	is_declaration* idecl;
	is_atr* iatr;
	is_dec_list* ideclist;
	is_func_def* ifd;
	is_arg_list* iargl;
	is_cont_func* icf;
	is_symbols* isymb;
	is_func_call* ifcall;
	is_call_list* icall;
	is_for_statement* ifors;
	is_for_args* ifa;
	is_exp_minus_plus* impe;	
	is_return_statement* ireturn;
	is_class* iclass;
	is_func_list* iflist;
	is_plusminus* ipm;
	is_read_statement* irs;
	is_concat* iconcat;
	is_concat_args* icargs;
	is_println_args* ipargs;
	is_break_cont* ibc;
}

%right EQUAL PLUSEQUAL MINUSEQUAL
%left GREATER LESS GREATEREQUAL LESSEQUAL NOTEQUAL EQUALEQUAL AND OR
%left PLUS MINUS PLUSPLUS MINUSMINUS
%left MULT DIV
%left POT MOD
%left NOT IF WHILE ELSE ELSEIF FUNCSYMB RETURNSYMB
%left '(' ')'
%left CLASSSYMB


%token INTSYMB FLOATSYMB STRINGSYMB DOUBLESYMB FUNCSYMB CLASSSYMB RETURNSYMB VOIDSYMB BOOLSYMB CONCATSYMB
%token <intValue> INT
%token <floatValue> FLOAT
%token <string> STRING
%token <boolValue> BOOL

%token NOT POT
%token MINUS PLUS MOD MULT DIV MINUSMINUS PLUSPLUS //ARITMETICA
%token GREATER LESS GREATEREQUAL LESSEQUAL NOTEQUAL EQUALEQUAL EQUAL PLUSEQUAL MINUSEQUAL //RELACIONAL
%token AND OR //LOGICA
%token <id> ID //VARIAVEIS
%token IF WHILE ELSE ELSEIF FOR 
%token BREAK CONTINUE //break e continue
%token PRINTLN PRINT 
%token READ READLINE//ler do teclado

%type <ipargs> println_args
%type <icargs> concat_args
%type <iconcat> concat
%type <ireturn> return_statement
%type <iclass> class
%type <iflist> func_list
%type <ity> type
%type <iae> aritmetic_exp
%type <ire> relac_exp
%type <impe> exp_minus_plus	
%type <ileoa> logic_exp_or_and
%type <ilen> logic_exp_not
%type <ie> expression
%type <isl> statement_list
%type <ial> atribution_list
%type <ia> atribution
%type <is> statement
%type <ii> instruction
%type <iprogram> program
%type <ics> compound_statement
%type <iifs> if_statement
%type <iws> while_statement
%type <ielses> else_statement
%type <ielseifs> elseif_statement
%type <ieisl> elseif_statement_list
%type <iconts> cont_statement
%type <iprints> println_statement
%type <idecl> declaration
%type <iatr> atr
%type <ideclist> dec_list
%type <ifors> for_statement
%type <ifa> for_args
%type <ipm> plusminus
%type <ifd> func_def
%type <iargl> arg_list
%type <icf> cont_func
%type <isymb> symbols
%type <ifcall> func_call
%type <icall> call_list
%type <irs> read_statement
%type <ibc> break_cont


%% 

program:	CLASSSYMB ID '{' class '}'		{$$ = PJAVAPROGRAM = insert_program($2, $4); return 0;}
	;

//GERIR AS VARIAVEIS GLOBAIS E A SEGUI VAI PARA A FUNCOES
class:		declaration ';' class			{$$=insert_class($1, $3, NULL);}
	|       func_list				{$$=insert_class(NULL, NULL, $1);}
	;

//GERIR AS DECLARACOES DE FUNCOES
func_list:	func_list func_def			{$$=insert_func_list($1, $2);}
	|	func_def				{$$=insert_func_list(NULL, $1);}	
	;
		
//TUDO O QUE FOR DECLARADO A PARTIR DAQUI SERA LOCAL
statement_list: statement_list	statement 		{$$=insert_statement_list($1, $2);}
	|	statement				{$$=insert_statement_list(NULL, $1);}				
	;

statement:  	instruction ';'				{$$=insert_statement(d_instruction, $1);}
	| 	compound_statement			{$$=insert_statement(d_compound_statement, $1);}
	|	println_statement ';'			{$$=insert_statement(d_println_statement, $1);}
	|	declaration ';'				{$$=insert_statement(d_declaration, $1);}
	|	func_call ';'				{$$=insert_statement(d_func_call, $1);}
	|	return_statement ';'			{$$=insert_statement(d_return_statement, $1);}
	|	read_statement	';'			{$$=insert_statement(d_read_statement, $1);}
	|	concat ';'				{$$=insert_statement(d_concat, $1);}
	|	break_cont ';'				{$$=insert_statement(d_break_cont, $1);}
	;
	
break_cont: BREAK					{$$=insert_break_cont(is_BREAK);}
	|   CONTINUE					{$$=insert_break_cont(is_CONTINUE);}
	;

concat:		CONCATSYMB '(' concat_args ')'		{$$=insert_concat($3);}
	;

concat_args: 	type ',' concat_args			{$$=insert_concat_args($1, NULL, $3);}
	|	type ',' type				{$$=insert_concat_args($1,$3, NULL);}
	;
	
read_statement: READ '(' ID ')'				{$$=insert_read_statement(d_READ, $3);}
	|	READLINE '(' ID ')'			{$$=insert_read_statement(d_READLINE, $3);}

	;			

instruction:	expression				{$$=insert_instruction(d_expression, $1);}
	|	atribution				{$$=insert_instruction(d_atribution, $1);}
	|	plusminus				{$$=insert_instruction(d_plusminus, $1);}
	;

plusminus:	ID PLUSPLUS				{$$=insert_plusminus(d_PLUSPLUS, $1);}
	|	ID MINUSMINUS				{$$=insert_plusminus(d_MINUSMINUS, $1);}
	;
	
compound_statement:	if_statement			{$$=insert_compound_statement(d_if_statement,$1);}
	|		while_statement			{$$=insert_compound_statement(d_while_statement,$1);}
	|		for_statement			{$$=insert_compound_statement(d_for_statement,$1);}	
	;

println_statement:	PRINTLN '(' println_args ')' 	{$$=insert_println_statement(d_PRINTLN, $3);}
	|		PRINT '(' println_args ')'	{$$=insert_println_statement(d_PRINT, $3);}
	;

println_args:		type PLUS println_args		{$$=insert_println_args($1, $3);}
	|		type				{$$=insert_println_args($1, NULL);}
	;

return_statement:	RETURNSYMB			{$$=insert_return_statement(NULL);}
	| 		RETURNSYMB instruction		{$$=insert_return_statement($2);}
	;
	
for_statement: 	FOR '(' for_args ';' relac_exp ';' for_args ')' cont_statement	{$$=insert_for_statement($3,$5,$7, $9);}
	;

for_args:  	dec_list					{$$=insert_for_args(d_for_dec_list,$1);}
        | 	declaration					{$$=insert_for_args(d_for_declaration,$1);}
	|	plusminus					{$$=insert_for_args(d_for_plusminus,$1);}
        | 							{$$=NULL;}
        ;
	
if_statement:	IF '(' instruction ')' cont_statement elseif_statement_list else_statement			{$$=insert_if_statement($3, $5, $6, $7);}
	;

while_statement: WHILE '(' instruction ')' cont_statement	{$$=insert_while_statement($3, $5);}
	;

else_statement: ELSE cont_statement			{$$=insert_else_statement($2);}
	| /*n ha else*/					{$$=NULL;}
	; 

elseif_statement_list: elseif_statement_list elseif_statement  {$$=insert_elseif_statement_list($1,$2);}
	|							{$$=NULL;}
	; 

elseif_statement: ELSEIF '(' instruction ')' cont_statement	{$$=insert_elseif_statement($3,$5);}
	; 
cont_statement:	 statement/*if so cm 1 statement*/		{$$=insert_cont_statement(d_statement,$1);}
	|	'{' statement_list '}'/*varios*/		{$$=insert_cont_statement(d_statement_list,$2);}
	|	'{' '}'						{$$=NULL;}
	| 	';'						{$$=NULL;}	
	;

func_def:	FUNCSYMB symbols ID '(' arg_list ')' cont_func	{$$=insert_func_def($2, $3, $5, $7);}
	;
func_call:	ID '(' call_list ')' 				{$$=insert_func_call($1, $3);}
	;
	
call_list:	call_list ',' type				{$$=insert_call_list($1, $3);}
	|	type						{$$=insert_call_list(NULL, $1);}
	|							{$$=NULL;}
	;
	
cont_func:	'{' statement_list '}'				{$$=insert_cont_func($2);}
	|	'{' '}'						{$$=NULL;}
	;

arg_list:	arg_list ',' symbols ID				{$$=insert_arg_list($1, $3, $4);}
	|	symbols ID					{$$=insert_arg_list(NULL, $1, $2);}
	|							{$$=NULL;}
	;


symbols:	INTSYMB						{$$=insert_symbols(d_INTEGER);}
	|	DOUBLESYMB					{$$=insert_symbols(d_DOUBLE);}
	|	FLOATSYMB					{$$=insert_symbols(d_FLOAT);}
	|	STRINGSYMB					{$$=insert_symbols(d_STRING);}
	|	VOIDSYMB					{$$=insert_symbols(d_VOID);}
	|	BOOLSYMB					{$$=insert_symbols(d_BOOL);}
	;
		

declaration:  	INTSYMB dec_list				{$$=insert_declaration(d_INTEGER, $2);}
	|	DOUBLESYMB dec_list				{$$=insert_declaration(d_DOUBLE, $2);}
	|	FLOATSYMB dec_list				{$$=insert_declaration(d_FLOAT, $2);}
	|	STRINGSYMB dec_list				{$$=insert_declaration(d_STRING, $2);}
	|	BOOLSYMB dec_list				{$$=insert_declaration(d_BOOL, $2);}
	;

dec_list:	atr						{$$=insert_dec_list(NULL, $1);}
	|	dec_list ','  atr				{$$=insert_dec_list($1, $3);}
	;

atr:		ID					{$$=insert_atr(d_ID, $1);}
	|	atribution				{$$=insert_atr(d_atribution_atr, $1);}
	;
		
atribution: 	atribution_list expression		{$$=insert_atribution($1,$2);}
	;
	
atribution_list: atribution_list ID EQUAL		{$$= insert_atribution_list(d_EQUAL, $1,$2);}
	|	 atribution_list ID PLUSEQUAL		{$$= insert_atribution_list(d_PLUSEQUAL, $1,$2);}
	|	 atribution_list ID MINUSEQUAL		{$$= insert_atribution_list(d_MINUSEQUAL, $1,$2);}
	|	 ID EQUAL				{$$= insert_atribution_list(d_EQUAL, NULL,$1);}
	|	 ID MINUSEQUAL				{$$= insert_atribution_list(d_MINUSEQUAL, NULL,$1);}
	|	 ID PLUSEQUAL				{$$= insert_atribution_list(d_PLUSEQUAL, NULL,$1);}
	;
	
expression: 	exp_minus_plus				{$$=insert_expression(d_exp_minus_plus, $1);}
	|	'(' expression ')'			{$$=insert_expression(d_expression_exp, $2);}
	|	logic_exp_or_and			{$$=insert_expression(d_logic_exp_or_and, $1);}
	|	relac_exp				{$$=insert_expression(d_relac_exp, $1);}
	|	aritmetic_exp 				{$$=insert_expression(d_aritmetic_exp, $1);}
	|	logic_exp_not				{$$=insert_expression(d_logic_exp_not, $1);}
	|	type					{$$=insert_expression(d_type, $1);}	
	;
	
exp_minus_plus:  MINUS expression				{$$=insert_exp_minus_plus($2,is_MINUS);}
	| 	 PLUS expression				{$$=insert_exp_minus_plus($2,is_PLUS);}
	;

logic_exp_not:	NOT expression				{$$=insert_logic_exp_not($2);}	
	;
	
logic_exp_or_and: expression AND expression		{$$=insert_logic_exp_or_and($1, is_AND, $3);}
	|	expression OR expression		{$$=insert_logic_exp_or_and($1, is_OR, $3);}
	;

relac_exp: 	expression EQUALEQUAL expression		{$$=insert_relac_exp($1, is_EQUAL, $3);}
	|	expression NOTEQUAL expression			{$$=insert_relac_exp($1, is_NOTEQUAL, $3);}
	|	expression GREATEREQUAL expression		{$$=insert_relac_exp($1, is_GREATEREQUAL, $3);}
	|	expression LESSEQUAL expression			{$$=insert_relac_exp($1, is_LESSEQUAL, $3);}
	|	expression LESS expression			{$$=insert_relac_exp($1, is_LESS, $3);}
	|	expression GREATER expression			{$$=insert_relac_exp($1, is_GREATER, $3);}
	;

aritmetic_exp:	expression PLUS expression		{$$=insert_aritmetic_exp($1, is_PLUS, $3);}
	|	expression MINUS expression		{$$=insert_aritmetic_exp($1, is_MINUS, $3);}
	|	expression MULT expression		{$$=insert_aritmetic_exp($1, is_MULT, $3);}
	|	expression DIV expression		{$$=insert_aritmetic_exp($1, is_DIV, $3);}
	|	expression MOD expression		{$$=insert_aritmetic_exp($1, is_MOD, $3);}
	|	expression POT expression		{$$=insert_aritmetic_exp($1, is_POT, $3);}
	;

type:		INT					{$$=insert_type(d_INTEGER, &$1);}
	|	FLOAT					{$$=insert_type(d_FLOAT, &$1);}
	|	STRING					{$$=insert_type(d_STRING, $1);}
	|	ID					{$$=insert_type(d_type_ID, $1);}
	|	func_call   				{$$=insert_type(d_type_func_call, $1);}
	|	BOOL					{$$=insert_type(d_BOOL, &$1);}
	;		



%%
int main()
{
	int parsingOK=0;
	
	linha=1;

	parsingOK=yyparse();

	if(parsingOK==0){
		
		if(showShows==1){
			printf("\n\nSTRUCTURES SHOW:\n\n");
			show_program(PJAVAPROGRAM);
			printf("-------------------\n");
		}

		if(checkSemantic==1){
			printf("\n\nSEMANTIC CHECK:\n\n");
			ERROS=semantic_analysis(PJAVAPROGRAM);
			if(ERROS>0){
				printf("-------------------\n");
				printf("\nTOTAL DE ERROS DE SEMANTICA:\n%d\n", ERROS);
				printf("-------------------\n");
			}
			else{
				printf("-->!SEMANTIC IS CORRECT!<--\n\n");
				printf("-------------------\n");
			}
		}

		
		if(showTable==1 && checkSemantic==1){
			printf("\n\nTABELAS:\n");
			show_table();
			printf("-------------------\n");
		}


		if(checkSemantic==1 && ERROS==0){
			printf("\n\nVAI FAZER O TRANSLATE\n\n");
			translate(PJAVAPROGRAM);
			printf("\n\nTRANSLATE FINALIZADO COM SUCESSO!\n\n");

		}
	}
	else
	{
		printf("linha %d: Erro de Sintaxe!\n", linha);
		
		return -1;
	}

	return 0;
}


int yyerror(char* s)
{
	printf("%s\n", s);
	return 1;
}
