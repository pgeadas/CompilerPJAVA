#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include "structures.h"


is_program* insert_program(is_id *id, is_class* isl);
is_class* insert_class(is_declaration *idecl, is_class *icla, is_func_list *ifl);
is_func_list* insert_func_list(is_func_list* list, is_func_def* st);
is_return_statement* insert_return_statement(is_instruction* instr);

is_type* insert_type(disc_type dn, void* type);
is_statement_list* insert_statement_list(is_statement_list* list, is_statement* st);
is_statement* insert_statement(disc_statement ds, void* stmt);
is_instruction* insert_instruction(disc_instr di, void* instruction);
is_expression* insert_expression(disc_expr de, void* expression);
is_logic_exp_or_and *insert_logic_exp_or_and(is_expression *exp1, is_oper_l oper, is_expression *exp2);
is_logic_exp_not* insert_logic_exp_not(is_expression *exp);
is_exp_minus_plus* insert_exp_minus_plus(is_expression *exp, is_oper_a oper);
is_aritmetic_exp *insert_aritmetic_exp(is_expression *exp1, is_oper_a oper, is_expression *exp2);
is_relac_exp *insert_relac_exp(is_expression *exp1, is_oper_r oper, is_expression *exp2);
is_atribution_list* insert_atribution_list(disc_atr_lis d, is_atribution_list* head, is_id* id);
is_atribution* insert_atribution(is_atribution_list* ial, is_expression* ie);
is_id_list* insert_id_list(is_id_list* i_list, is_id* id);
is_compound_statement* insert_compound_statement(disc_compound_statement cs, void* cmp);
is_if_statement* insert_if_statement(is_instruction* ii, is_cont_statement* iconts, is_elseif_statement_list* ieisl, is_else_statement* ielses);
is_while_statement* insert_while_statement(is_instruction* ii, is_cont_statement* iconts);
is_else_statement* insert_else_statement(is_cont_statement* iconts);
is_elseif_statement* insert_elseif_statement(is_instruction* instr, is_cont_statement* iconts);
is_elseif_statement_list* insert_elseif_statement_list(is_elseif_statement_list* list_head, is_elseif_statement* ielseifs);
is_cont_statement* insert_cont_statement(disc_cont_statement cts, void* cont);
is_println_statement* insert_println_statement(disc_print d, is_println_args* ii);
is_declaration* insert_declaration(disc_type dn, is_dec_list* decl);
is_dec_list* insert_dec_list(is_dec_list* list, is_atr* st);
is_atr* insert_atr(disc_atr cts, void* cont);
is_symbols* insert_symbols(disc_type dn);
is_arg_list* insert_arg_list(is_arg_list* list, is_symbols* st, is_id* id);
is_func_def* insert_func_def(is_symbols* is, is_id* id, is_arg_list* ial, is_cont_func* icf);
is_cont_func* insert_cont_func(is_statement_list* isl);
is_call_list* insert_call_list(is_call_list* list, is_type* ty);
is_func_call* insert_func_call(is_id* id, is_call_list* icl);
is_for_statement* insert_for_statement(is_for_args *args1, is_relac_exp *ire, is_for_args *args2, is_cont_statement *icsta);
is_for_args* insert_for_args(disc_for_args cts, void* cont);
is_plusminus* insert_plusminus(disc_plusminus d, is_id* id);
is_read_statement* insert_read_statement(disc_read d, is_id* id);
is_concat* insert_concat(is_concat_args* ica);
is_concat_args* insert_concat_args(is_type* i1, is_type* i2, is_concat_args* n);
is_println_args* insert_println_args(is_type* it, is_println_args* ipa);
is_break_cont* insert_break_cont(disc_bc bc);
#endif

