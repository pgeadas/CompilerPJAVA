#include "structures.h"

/*PROGRAMA*/
void show_program(is_program* ip);

/*CLASS*/
void show_class(is_class *iclass);

/*FUNC LIST*/
void show_func_list(is_func_list* ifl);

/*STATMENTS*/
void show_statement_list(is_statement_list* isl);
void show_statement(is_statement* is);

/*ARG LIST*/
void show_arg_list(is_arg_list* iargl);
void show_for_args(is_for_args* ifa);

/*CONT FUNCTION*/
void show_cont_func(is_cont_func* icf);

/*func call*/
void show_func_call(is_func_call* ifcall);
void show_call_list(is_call_list* icall);

/*STATMENT*/
void show_compound_statement(is_compound_statement* ics);
void show_cont_statement(is_cont_statement* icts);
void show_instruction(is_instruction* ii);
void show_println_statement(is_println_statement* ips);
void show_return_statement(is_return_statement *ireturn);

void show_func_def(is_func_def* ifd);

/*INSTRUCOES*/
void show_atribution(is_atribution* ia);
void show_expression(is_expression* ie);
void show_plusminus(is_plusminus* ia);

/*ATRIBUICAO*/
void show_atribution_list(is_atribution_list* ial);

/*OPERACOES*/
void show_logic_exp_or_and(is_logic_exp_or_and* ileoa);
void show_aritmetic_exp(is_aritmetic_exp* iae);
void show_relac_exp(is_relac_exp* ire);
void show_logic_exp_not(is_logic_exp_not* ilen);

/*OPERADORES*/
void show_operator_a(is_oper_a);
void show_operator_r(is_oper_r oper);
void show_operator_l_o_a(is_oper_l oper);

/*NUMERO*/
void show_type(is_type* in);

/*SYMBOLOS*/
void show_symbols(is_symbols* s);

/*ID*/
void show_id(is_id* id);

/*DECLARATION*/
void show_declaration(is_declaration* decl);
void show_dec_list(is_dec_list* idl);
void show_atr(is_atr* ics);

/*COMPOUND*/
void show_if_statement(is_if_statement* iifs);
void show_else_statement(is_else_statement* ielses);
void show_elseif_statement(is_elseif_statement* ielseifs);
void show_elseif_statement_list(is_elseif_statement_list* iesl);
void show_while_statement(is_while_statement* iws);
void show_for_statement(is_for_statement *ifs);

/*READ*/
void show_read_statement(is_read_statement* irs);
