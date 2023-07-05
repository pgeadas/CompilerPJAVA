#ifndef PJAVA_TRANSLATE_H
#define PJAVA_TRANSLATE_H

#include "structures.h"
#include "symbol_table.h"
#include <stdio.h>


void translate(is_program *ip);

void translate_header(FILE *dest);

void translate_global(FILE *dest, prog_env *pe);

void translate_global_dec_type(FILE *dest, disc_type type, int offset);

void translate_class(FILE *dest, is_class *iclass, prog_env *pe);

void translate_func_list(FILE *dest, is_func_list *ifl, prog_env *pe);

void translate_func_def(FILE *dest, is_func_def *ifdef, environment_list *el, prog_env *pe);

void translate_main(FILE *dest, is_func_def *main, environment_list *el, prog_env *pe);

void translate_arg_list(FILE *dest, is_arg_list *ial, environment_list *el, prog_env *pe);

void translate_cont_func(FILE *dest, is_cont_func *icf, environment_list *el, prog_env *pe);

void translate_statement_list(FILE *dest, is_statement_list *isl, environment_list *el, prog_env *pe);

void translate_statement(FILE *dest, is_statement *ist, environment_list *el, prog_env *pe);

void translate_declare_locals(FILE *dest, environment_list *el, prog_env *pe);

void translate_local_dec_type(FILE *dest, table_element *t, disc_type dt);

void translate_instruction(FILE *dest, is_instruction *iinstr, environment_list *el, prog_env *pe);

void translate_atribution(FILE *dest, is_atribution *ia, environment_list *el, prog_env *pe);

void translate_expression(FILE *dest, is_expression *iexp, environment_list *el, prog_env *pe);

void translate_logic_exp_not(FILE *dest, is_logic_exp_not *ilen, environment_list *el, prog_env *pe);

void translate_logic_exp_or_and(FILE *dest, is_logic_exp_or_and *ileoa, environment_list *el, prog_env *pe);

void translate_relac_exp(FILE *dest, is_relac_exp *ire, environment_list *el, prog_env *pe);

void translate_declaration(FILE *dest, environment_list *el, prog_env *pe, is_declaration *decl);

void translate_return_statement(FILE *dest, is_return_statement *irs, environment_list *el, prog_env *pe);

void translate_println_statement(FILE *dest, is_println_statement *ips, environment_list *el, prog_env *pe);

void translate_dec_list(FILE *dest, environment_list *el, prog_env *pe, is_dec_list *idl);

void translate_args_outgoing(FILE *dest, table_element *isy, prog_env *pe);

void translate_args(FILE *dest, disc_type type);

void translate_type(FILE *dest, is_type *ity, environment_list *el, prog_env *pe);

void translate_aritmetic_exp(FILE *dest, is_aritmetic_exp *iae, environment_list *el, prog_env *pe);

void translate_atrib_list(FILE *dest, prog_env *pe, environment_list *el, is_atribution_list *ial);

void translate_function(FILE *dest, is_func_def *ifdef, environment_list *el, prog_env *pe);

void translate_cont_func(FILE *dest, is_cont_func *icf, environment_list *el, prog_env *pe);

void translate_symbols(FILE *dest, is_symbols *isy, is_id *id, environment_list *el, prog_env *pe);

void translate_var_print(FILE *dest, disc_type type);

void translate_is_func_call(FILE *dest, environment_list *el, prog_env *pe, is_func_call *ifc);

void
translate_call_list(FILE *dest, environment_list *el, environment_list *funcDest, prog_env *pe, is_call_list *list);

void translate_ourgoing_dec_type(FILE *dest, table_element *t, disc_type dt);

void translate_redirector(FILE *dest);

void translate_atr(FILE *dest, environment_list *el, prog_env *pe, is_atr *ia);

void translate_expression_first(FILE *dest, is_expression *ie, environment_list *el, prog_env *pe);

void translate_type_first(FILE *dest, is_type *ity, environment_list *el, prog_env *pe);

void translate_plusminus(FILE *dest, is_plusminus *ipm, environment_list *el, prog_env *pe);

void translate_if_statement(FILE *dest, is_if_statement *iis, environment_list *el, prog_env *pe);

void translate_compound_statement(FILE *dest, is_compound_statement *ics, environment_list *el, prog_env *pe);

void translate_else_statement(FILE *dest, is_else_statement *ise, environment_list *el, prog_env *pe);

void translate_cont_statement(FILE *dest, is_cont_statement *ics, environment_list *el, prog_env *pe);

void translate_elseif_statement_list(FILE *dest, is_elseif_statement_list *ieisl, environment_list *el, prog_env *pe);

void translate_elseif_statement(FILE *dest, is_elseif_statement *ieis, environment_list *el, prog_env *pe);

void translate_while_statement(FILE *dest, is_while_statement *iws, environment_list *el, prog_env *pe);

void translate_for_statement(FILE *dest, is_for_statement *ifs, environment_list *el, prog_env *pe);

void translate_for_args(FILE *dest, is_for_args *ifa, environment_list *el, prog_env *pe);

void translate_exp_minus_plus(FILE *dest, is_exp_minus_plus *exp, environment_list *el, prog_env *pe);

void create_return_value(FILE *dest, disc_type ty);

void translate_read_statement(FILE *dest, environment_list *el, prog_env *pe, is_read_statement *irs);

void translate_readln_statement(FILE *dest, table_element *newel, int flag);

void translate_type_print(FILE *dest, is_type *ity, environment_list *el, prog_env *pe);

void translate_println_args(FILE *dest, is_println_args *ipa, environment_list *el, prog_env *pe);

void translate_atrib_list_globals(FILE *dest, prog_env *pe, is_atribution_list *ial);

void translate_atr_globals(FILE *dest, prog_env *pe, is_atr *idec);

void translate_break_cont(FILE *dest, environment_list *el, prog_env *pe, is_break_cont *ibc);

void find_expression(FILE *dest, is_instruction *instr, environment_list *el, prog_env *pe);

void translate_concat(FILE *dest, environment_list *el, prog_env *pe, is_concat *ic);

void translate_concat_args(FILE *dest, environment_list *el, prog_env *pe, is_concat_args *icargs);

int translate_type_concat(FILE *dest, environment_list *el, prog_env *pe, is_type *ity, int operacao);

void translate_footer(FILE *dest);

#endif
