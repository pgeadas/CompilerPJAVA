#ifndef PJAVA_SEMANTICS_H
#define PJAVA_SEMANTICS_H

#include "structures.h"

char *typeToString(disc_type type);

void semantic_analysis_arguments_are_correct(table_element *argument, int i, int errorLine);

environment_list *plookup(environment_list *procs, char *procname);

table_element *lookup(table_element *table, char *str);

table_element *create_symbol(int offset, char *name, disc_type type);

int semantic_analysis(is_program *p);

void semantic_analysis_class(prog_env *pe, is_class *iclass);

int semantic_analysis_declaration(int offset, int scope, prog_env *pe, table_element *te, is_declaration *isd);

int semantic_analysis_dec_list(int offset, int scope, prog_env *pe, table_element *te, is_dec_list *idl, disc_type dt,
                               int caller);

int
semantic_analysis_atr(int offset, int scope, prog_env *pe, table_element *te, is_atr *ics, disc_type dt, int caller);

int semantic_analysis_is_atribution(int caller, int offset, int scope, prog_env *pe, table_element *te, disc_type dt,
                                    is_atribution *ia);

void semantic_analysis_func_list(prog_env *pe, is_func_list *ifl);

void semantic_analysis_func_def(prog_env *pe, is_func_def *ifd);

void
semantic_analysis_is_cont_func(environment_list *actualFunc, prog_env *pe, table_element *locals, is_cont_func *icf);

void semantic_analysis_is_statement_list(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                         is_statement_list *isl);

void
semantic_analysis_is_statement(environment_list *actualFunc, prog_env *pe, table_element *locals, is_statement *is);

void
semantic_analysis_is_func_call(environment_list *actualFunc, prog_env *pe, table_element *locals, is_func_call *ifcall);

void
semantic_analysis_is_call_list(environment_list *actualFunc, prog_env *pe, table_element *locals, is_call_list *icl);

void semantic_analysis_is_type(prog_env *pe, table_element *locals, is_type *ity);

void semantic_analysis_is_return_statement(prog_env *pe, table_element *locals, is_return_statement *irs);

void semantic_analysis_is_compound_statement(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                             is_compound_statement *ics);

void semantic_analysis_is_for_statement(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                        is_for_statement *ifs);

void semantic_analysis_is_for_args(environment_list *actualFunc, prog_env *pe, table_element *locals, is_for_args *ifa);

void semantic_analysis_is_while_statement(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                          is_while_statement *iws);

void semantic_analysis_is_if_statement(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                       is_if_statement *iifs);

void semantic_analysis_is_else_statement(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                         is_else_statement *ies);

void semantic_analysis_is_elseif_statement_list(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                                is_elseif_statement_list *ieisl);

void semantic_analysis_is_elseif_statement(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                           is_elseif_statement *ieis);

void semantic_analysis_is_cont_statement(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                         is_cont_statement *ics);

void semantic_analysis_is_instruction(prog_env *pe, table_element *locals, is_instruction *iinstr);

void semantic_analysis_is_expression(prog_env *pe, table_element *locals, is_expression *ie);

void semantic_analysis_is_logic_exp_or_and(prog_env *pe, table_element *locals, is_logic_exp_or_and *ileoa);

void semantic_analysis_is_println_statement(prog_env *pe, table_element *locals, is_println_statement *ips);

void semantic_analysis_is_logic_exp_not(prog_env *pe, table_element *locals, is_logic_exp_not *ilen);

void semantic_analysis_is_relac_exp(prog_env *pe, table_element *locals, is_relac_exp *ire);

void semantic_analysis_is_aritmetic_exp(prog_env *pe, table_element *locals, is_aritmetic_exp *iae);

int semantic_analysis_arg_list(int offset, int scope, prog_env *pe, table_element *locals, table_element *arguments,
                               is_arg_list *ial);

void
semantic_analysis_symbols(int offset, prog_env *pe, table_element *locals, table_element *arguments, is_symbols *isy,
                          is_id *id);

int semantic_analysis_is_atrib_list(int scope, prog_env *pe, table_element *te, disc_type dt, is_atribution_list *ia,
                                    int caller, int offset);

void semantic_analysis_is_plusminus(prog_env *pe, table_element *te, is_plusminus *ia);

void semantic_analysis_return_statement_list(is_statement_list *isl);

void semantic_analysis_is_exp_minus_plus(prog_env *pe, table_element *locals, is_exp_minus_plus *iemp);

void semantic_analysis_is_concat(prog_env *pe, table_element *te, is_concat *irs);

void semantic_analysis_is_concat_args(prog_env *pe, table_element *te, is_concat_args *irs);

void semantic_analysis_is_read_statement(prog_env *pe, table_element *te, is_read_statement *irs);

void semantic_analysis_is_break_cont(prog_env *pe, table_element *te, is_break_cont *ibc);

void semantic_analysis_is_println_args(prog_env *pe, table_element *locals, is_println_args *irs);

#endif
