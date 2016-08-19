//****************************************************************************
//****************************************************************************
//*************   A       S        T   ***************************************
//  ESTRUTURA DA ARVORE DE SINTAXE ABSTRACTA  [AST]

#include "symbol_table.h"


#ifndef _STRUCTURES_
#define _STRUCTURES_

int linha;

prog_env *pe;

typedef struct _statement_list is_statement_list;
typedef struct _type is_type;
typedef struct _expression is_expression;
typedef struct _instruction is_instruction;
typedef struct _statement is_statement;
typedef struct _compound_statement is_compound_statement;
typedef struct _if_statement is_if_statement;
typedef struct _while_statement is_while_statement;
typedef struct _elseif_statement is_elseif_statement;
typedef struct _cont_statement is_cont_statement;
typedef struct _else_statement is_else_statement;
typedef struct _elseif_statement_list is_elseif_statement_list;
typedef struct _println_statement is_println_statement;
typedef struct _declaration is_declaration;
typedef struct _dec_list is_dec_list;
typedef struct _atr is_atr;
typedef struct _atribution is_atribution;
typedef struct _id is_id;
typedef struct _relac_exp is_relac_exp;
typedef struct _for_statement is_for_statement;
typedef struct _for_args is_for_args;
typedef struct _func_def is_func_def;
typedef struct _cont_func is_cont_func;
typedef struct _arg_list is_arg_list;
typedef struct _symbols is_symbols;
typedef struct _call_list is_call_list;
typedef struct _func_call is_func_call;
typedef struct _program is_program;
typedef struct _class is_class;
typedef struct _func_list is_func_list;
typedef struct _return_statement is_return_statement;
typedef struct _plusminus is_plusminus;
typedef struct _read_statement is_read_statement;
typedef struct _concat_args is_concat_args;
typedef struct _concat is_concat;
typedef struct _println_args is_println_args;
typedef struct _break_cont is_break_cont;


// is_statement --> is_instruction V is_compound_statement V is_println_statement V is_declaration V is_return_statement V is_func_call
typedef enum {d_instruction, d_compound_statement, d_println_statement, d_declaration, d_return_statement, d_func_call, d_read_statement, d_concat, d_break_cont} disc_statement;

//is_instruction --> is_atribution V is_expression
typedef enum { d_atribution,  d_expression, d_plusminus } disc_instr;

//break e continue
typedef enum { is_BREAK, is_CONTINUE } disc_bc;


typedef enum { d_PRINTLN,  d_PRINT } disc_print;

typedef enum { d_PLUSPLUS,  d_MINUSMINUS } disc_plusminus;

typedef enum { d_READ,  d_READLINE } disc_read;

typedef enum { d_EQUAL,  d_MINUSEQUAL, d_PLUSEQUAL } disc_atr_lis;

//is_expression --> is_logic_oper_or_and V is_logic_oper_not V is_aritmetic_oper V is_relac_oper
typedef enum {d_logic_exp_or_and, d_logic_exp_not, d_exp_minus_plus, d_aritmetic_exp, d_relac_exp, d_type, d_expression_exp} disc_expr;

//is_oper_a --> is_PLUS ∨ is_MINUS v is_MULT v is_DIV v is_MOD v is_POT
typedef enum {is_PLUS, is_MINUS, is_MULT, is_DIV, is_MOD , is_POT} is_oper_a;

//is_oper_l --> is_AND v is_OR v is_NOT
typedef enum {is_AND, is_OR} is_oper_l;

//is_oper_r --> is_GREATER v is_GREATEREQUAL v is_LESS v is_LESSEQUAL v is_EQUAL v is_NOTEQUAL
typedef enum {is_GREATER, is_GREATEREQUAL, is_LESS, is_LESSEQUAL, is_EQUAL, is_NOTEQUAL} is_oper_r;

// is_compound_statement --> is_if_statement V is_while_statement V is_stmt_for 
typedef enum {d_if_statement, d_while_statement, d_for_statement} disc_compound_statement;

typedef enum {d_statement, d_statement_list} disc_cont_statement;

typedef enum {d_atribution_atr, d_ID} disc_atr;

typedef enum {d_for_dec_list, d_for_declaration, d_for_plusminus} disc_for_args;

//CLASS
struct _class{
	is_declaration *idecl;
	is_class *icla;
	is_func_list *ifl;
};

//LISTA DE FUNCOES
struct _func_list {
	is_func_def *ifdef;
	struct _func_list* next;
};

//RETURN
struct _return_statement {
	is_instruction *instr;
};

//CONCAT
struct _concat {
	int codeLine;
	is_concat_args *icargs;
};

//CONCAT ARGS
struct _concat_args {
	int codeLine;
	is_type *ity1;
	is_type *ity2;
	struct _concat_args* next;
};

//PRINTLN ARGS
struct _println_args {
	int codeLine;
	is_type *ity;
	struct _println_args* next;
};

//FOR
struct _for_statement{
	is_for_args *ifarg1;
	is_relac_exp *ire;
	is_for_args *ifarg2;
	is_cont_statement *ics;
};

//ARGUMENTOS FOR
struct _for_args{
	disc_for_args disc_n;	
	union{
		is_dec_list *u_dec_list;
		is_declaration *u_declaration;
		is_plusminus *u_plusminus;
	}data_for_args;
};

//CHAMADA DE FUNCTIONS
struct _func_call{
	is_id *id;
	is_call_list *icl;
	int codeLine;
};

//LISTA DE ARGUMENTOS DE CHAMADA
struct _call_list {
	int codeLine;
	is_type *ty;
	struct _call_list* next;
};


//DEFINICAO DE FUNCTIONS
struct _func_def{
	is_symbols *isym;
	is_id *id;
	is_arg_list *ial;
	is_cont_func *icf;
	int codeLine;
};


//CONTINUACAO DAS FUNCTIONS
struct _cont_func {
	is_statement_list* u_stmt_list;
};

//SYMBOLOS DE DECLARACAO
struct _symbols{
	int codeLine;
	disc_type disc_d;
};

//LISTA DE ARGUMENTOS
struct _arg_list {
	is_symbols *sym;
	is_id *id;
	struct _arg_list* next;
};

//LISTA DE DECLARACOES
struct _dec_list {
	int codeLine;
	is_atr *atr;
	struct _dec_list* next;
};

//DECLARATION
struct _declaration {
	disc_type disc_d;
	is_dec_list *dec_list;
};

//ATR
struct _atr {
	int codeLine;
	disc_atr disc_n;	
	union{
		is_atribution *u_atribution;
		is_id *u_id;
	}data_atr;
};

//TYPE
struct _type {
	int codeLine;
	disc_type disc_n;	
	union{
		int integer;
		float fl;
		double db;
		char* string;
		bool boolean;
		is_id *id;
		is_func_call *fcall;
	}data_type;
};

//is_aritmetic_exp --> (<exp1: is_expression><oper:is_oper_a><exp2:is_expression>)
typedef struct _aritmetic_exp {
	is_expression *exp1;
	is_oper_a oper;
	is_expression *exp2;
}is_aritmetic_exp;

//ID
struct _id {
	char* id;
	int codeLine;
};

//PLUSMINUS
struct _plusminus {
	is_id* id;
	int codeLine;
	disc_plusminus disc_d;
};

// is_id_list
typedef struct _id_list {
	is_id* id;
	struct _id_list* next;
} is_id_list;


// ATRIBUTION LIST
typedef struct _atribution_list {
	is_id* id;
	disc_atr_lis disc_d;
	struct _atribution_list* next;
}is_atribution_list;

//is_exp_minus_plus --> ( <exp:is_expression><oper:is_oper_a> )
typedef struct _exp_minus_plus {
	is_expression *exp;
	is_oper_a oper;
}is_exp_minus_plus;


//is_relac_exp --> (<exp1: is_expression><oper:is_oper_r><exp2:is_expression>)
struct _relac_exp {
	is_expression *exp1;
	is_oper_r oper;
	is_expression *exp2;
};

//is_logic_exp_or_and --> ( <exp1:is_expression><oper:is_oper_l><exp2:is_expression> )
typedef struct _logic_exp_or_and {
	is_expression *exp1;
	is_oper_l oper;
	is_expression *exp2;
}is_logic_exp_or_and;

//is_logic_exp_not --> ( <exp:is_expression>)
typedef struct _logic_exp_not {
	is_expression *exp1;
}is_logic_exp_not;

//EXPRESSION
struct _expression {
	disc_expr disc_d;
	union{
		is_expression* u_expression;
		is_logic_exp_or_and *u_logic_exp_or_and;
		is_logic_exp_not *u_logic_exp_not;
		is_exp_minus_plus *u_exp_minus_plus;
		is_aritmetic_exp *u_aritm_exp;
		is_relac_exp *u_relac_exp;
		is_type *u_type;
	}data_expr;
};


//ATRIBUTION
struct _atribution {
	is_atribution_list *atrib_list;
	is_expression *expression;
};

//INSTRUCTION
struct _instruction {
	disc_instr disc_d;
	union{
		is_atribution *u_atribution;
		is_expression *u_expression;
		is_plusminus *u_plusminus;
	}data_instr;
};

//PRINTLN
struct _println_statement {
	int codeLine;
	disc_print disc_d;
	is_println_args* ipargs;
};

//READ TYPE
struct _read_statement {
	is_id* id;
	disc_read disc_d;
	int codeLine;
};

//BREAK CONTINUE
struct _break_cont {
	int codeLine;
	disc_bc disc_bc;
};

//STATEMENT
struct _statement {
	int codeLine;
	disc_statement disc_d;
	union{
		is_instruction *u_instruction;
		is_compound_statement * u_compound_statement;
		is_println_statement * u_println_statement;
		is_declaration* u_declaration;
		is_return_statement* u_return_statement;
		is_func_call* u_func_call;
		is_read_statement* u_read_statement;
		is_concat* u_concat;
		is_break_cont* u_break_cont;
	}data_statement;
};

//CICLOS
struct _compound_statement {
	disc_compound_statement disc_cs;
	union{
		is_if_statement * u_stmt_if;
		is_while_statement * u_stmt_while;
		is_for_statement * u_stmt_for;
	}data_compound_statement;
};

//CONTINUACAO DE CICLOS
struct _cont_statement {
	disc_cont_statement disc_cts;
	union{
		is_statement* u_stmt;
		is_statement_list* u_stmt_list;
	}data_cont_statement;
	
};

//IF
struct _if_statement {
	is_instruction* instr;
	is_cont_statement* iconts;
	is_elseif_statement_list* ieisl;
	is_else_statement* ielses;
};

//ELSE IF LIST
struct _elseif_statement_list {
	is_elseif_statement* ielseifs;
	struct _elseif_statement_list* next;
};

//ELSE IF
struct _elseif_statement {
	is_instruction* instr;
	is_cont_statement* iconts;
};

//ELSE
struct _else_statement {
	is_cont_statement* iconts;

};

//WHILE
struct _while_statement {
	is_instruction * instr;
	is_cont_statement* iconts;
};

//STATEMENT LIST
struct _statement_list {
	is_statement *statement;
	struct _statement_list* next;
};

//PROGRAM
struct _program {
	is_class *iclass;
	is_id *iid;
}; 


#endif

