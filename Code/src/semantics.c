#include "../headers/symbol_table.h"
#include "../headers/semantics.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum {
    LOCALSCOPE, GLOBALSCOPE
};

prog_env *pe;
int linha;
int totalErros = 0;
int concat = 0;
int global_offset = 0;
int maincount;
int debugPrints = 0; //Ligar os prints de debug 0-desliga, 1-liga
int aritm = 0;//para sabermos que estamos numa operacao aritmetica (impedir a soma de booleans por exemplo)
disc_type tipoActual = -1;//guarda o tipo para comparar se nas atribuicoes os tipos sao iguais!
int bc_flag = 1; //flag que nos diz se tamos dentro de um for ou while, caso em que se pode fazer break ou continue

//Procura um identificador, devolve 0 caso nao exista
table_element *lookup(table_element *table, char *str) {
    if (table == NULL)
        return 0;
    if (debugPrints == 1)
        printf("ENTROU| NOME->%s\n", str);
    table_element *aux;

    for (aux = table; aux; aux = aux->next) {
        if (strcmp(aux->name, str) == 0) {
            return aux;
        }
    }

    if (debugPrints == 1)
        printf("SAIU DO FOR\n");
    return 0;
}


//PLOOKUP
environment_list *plookup(environment_list *procs, char *procname) {
    environment_list *aux;

    for (aux = procs; aux; aux = aux->next)
        if (strcmp(aux->name, procname) == 0)
            return aux;

    return NULL;
}

//Criação de um identificador retornando a table element dele
table_element *create_symbol(int offset, char *name, disc_type type) {
    table_element *el = (table_element *) malloc(sizeof(table_element));
    strcpy(el->name, name);
    el->type = type;
    el->next = NULL;
    el->offset = offset;
    return el;
}

//ANALISE SEMANTICA:

//PROGRAM
int semantic_analysis(is_program *p) //analise semantica da lista de blocos, ou seja do nosso programa
{
    pe = (prog_env *) malloc(
            sizeof(prog_env));  //criação do program_environment, que contera todas os símbolos (globais, locais, procedimentos)

    semantic_analysis_class(pe, p->iclass);

    return totalErros;
}

//CLASS
void semantic_analysis_class(prog_env *pe, is_class *iclass) {
    is_class *aux = iclass;
    pe->global = (table_element *) malloc(sizeof(table_element)); //CRIACAO DA TABELA DE ELEMENTOS GLOBAIS

    //faz a triagem do bloco a analisar
    for (; aux->icla; aux = aux->icla) {
        semantic_analysis_declaration(0, GLOBALSCOPE, pe, pe->global, aux->idecl);
    }

    semantic_analysis_func_list(pe, aux->ifl);
}


//DECLARATION
int semantic_analysis_declaration(int offset, int scope, prog_env *pe, table_element *te, is_declaration *isd) {
    offset = semantic_analysis_dec_list(offset, scope, pe, te, isd->dec_list, isd->disc_d, 1);
    return offset;
}

//DEC LIST
int semantic_analysis_dec_list(int offset, int scope, prog_env *pe, table_element *te, is_dec_list *idl, disc_type dt,
                               int caller) {
    is_dec_list *tmp;

    if (idl == NULL) {
        return offset;
    }

    for (tmp = idl; tmp; tmp = tmp->next) {
        if (debugPrints == 1)
            printf("DECLIST VAI CHAMAR ATR!\n");

        if (scope == LOCALSCOPE) {
            offset = semantic_analysis_atr(offset, scope, pe, te, tmp->atr, dt, caller);
            offset++;
        } else {
            semantic_analysis_atr(global_offset, scope, pe, te, tmp->atr, dt, caller);
            global_offset++;
        }

        if (debugPrints == 1)
            printf("SAIU DO DECLIST - ATR!\n");
    }
    return offset;
}

//ATR
int
semantic_analysis_atr(int offset, int scope, prog_env *pe, table_element *te, is_atr *ics, disc_type dt, int caller) {
    table_element *newel;
    table_element *aux = te;
    is_id *id_tmp = ics->data_atr.u_id;

    switch (ics->disc_n) {
        case d_ID:
            if (caller == 1) {
                if (te == NULL) {
                    newel = create_symbol(offset, id_tmp->id, dt);
                    te = newel;
                    te->next = NULL;
                } else {
                    if (debugPrints == 1)
                        printf("ATR-ID-> te nao e' null OFFSET->%d\n", offset);
                    newel = lookup(te, id_tmp->id);
                    if (newel == 0) {
                        if (scope == GLOBALSCOPE)
                            newel = create_symbol(global_offset, id_tmp->id, dt);
                        else
                            newel = create_symbol(offset, id_tmp->id, dt);
                        for (; aux->next; aux = aux->next);
                        aux->next = newel;
                        newel->next = NULL;
                    } else {
                        printf("ERRO NA LINHA %d | (ATR) Symbol %s already defined!\n", id_tmp->codeLine, id_tmp->id);
                        totalErros++;
                    }
                }
            } else {
                newel = lookup(te, id_tmp->id);
                if (newel == 0) {
                    printf("ERRO NA LINHA %d | (ATR) Symbol %s is not defined!\n", id_tmp->codeLine, id_tmp->id);
                    totalErros++;
                }
            }
            break;

        case d_atribution_atr:
            if (scope == GLOBALSCOPE)
                global_offset--;
            else
                offset--;

            ////caller 1 - e' para adicionar 0- para procurar
            offset = semantic_analysis_is_atribution(caller, offset, scope, pe, te, dt, ics->data_atr.u_atribution);
            break;
    }
    return offset;
}

//ATRIBUTION
int semantic_analysis_is_atribution(int caller, int offset, int scope, prog_env *pe, table_element *te, disc_type dt,
                                    is_atribution *ia) {
    tipoActual = -1;
    semantic_analysis_is_expression(pe, te, ia->expression);
    offset = semantic_analysis_is_atrib_list(scope, pe, te, dt, ia->atrib_list, caller, offset);
    return offset;
}

//ATRIB LIST
int semantic_analysis_is_atrib_list(int scope, prog_env *pe, table_element *te, disc_type dt, is_atribution_list *ia,
                                    int caller, int offset) {

    table_element *newel;
    table_element *aux = te;
    is_id *id_tmp = ia->id;
    is_atribution_list *atrib_aux;

    for (atrib_aux = ia; atrib_aux; atrib_aux = atrib_aux->next) {


        if (caller == 0) {//int que diz se a variavel e pa adicionar ou procurar (neste caso para procurar)
            newel = lookup(te, id_tmp->id);
            if (newel == NULL) {
                newel = lookup(pe->global, id_tmp->id);
                if (newel == NULL) {
                    printf("ERRO NA LINHA %d | (ATRIB_LIST) Symbol %s is not defined!\n", id_tmp->codeLine, id_tmp->id);
                    totalErros++;
                } else {
                    if (newel->type != tipoActual) {
                        printf("ERRO NA LINHA %d | (ATRIB_LIST) Types mismatch (%s<->%s)!\n", id_tmp->codeLine,
                               typeToString(newel->type), typeToString(tipoActual));
                        totalErros++;
                    }

                }
            } else {
                if (newel->type != tipoActual) {
                    printf("ERRO NA LINHA %d | (ATRIB_LIST) Types mismatch (%s<->%s)!\n", id_tmp->codeLine,
                           typeToString(newel->type), typeToString(tipoActual));
                    totalErros++;
                }
            }
        } else//adicionar
        {
            if (dt != tipoActual && (dt != d_INTEGER && dt != d_DOUBLE && dt != d_FLOAT) &&
                (tipoActual != d_INTEGER && tipoActual != d_DOUBLE && tipoActual != d_FLOAT)) {
                printf("ERRO NA LINHA %d | (ATRIB_LIST) Types mismatch (%s<->%s)!\n", id_tmp->codeLine,
                       typeToString(dt), typeToString(tipoActual));
                totalErros++;
                if (scope == GLOBALSCOPE)
                    global_offset--;
                else
                    offset--;
            } else {
                if (te == NULL) {
                    offset++;
                    newel = create_symbol(offset, id_tmp->id, dt);
                    te = newel;
                    te->next = NULL;
                } else {
                    if (debugPrints == 1)
                        printf("ATRIB_LIST-ID-> te nao e' null OFFSET->%d\n", offset);
                    newel = lookup(te, id_tmp->id);
                    if (newel == 0) {
                        if (scope == GLOBALSCOPE) {
                            global_offset++;
                            newel = create_symbol(global_offset, id_tmp->id, dt);
                        } else {
                            offset++;
                            newel = create_symbol(offset, id_tmp->id, dt);
                        }
                        for (; aux->next; aux = aux->next);
                        aux->next = newel;
                        newel->next = NULL;
                    } else {
                        printf("ERRO NA LINHA %d | (ATRIB_LIST) Symbol %s already defined!\n", id_tmp->codeLine,
                               id_tmp->id);
                        totalErros++;
                        if (scope == GLOBALSCOPE)
                            global_offset--;
                        else
                            offset--;
                    }
                }
            }
        }
    }

    return offset;

}

//READ STATEMENT
void semantic_analysis_is_read_statement(prog_env *pe, table_element *te, is_read_statement *irs) {
    table_element *newel, *newel2;


    newel = lookup(te, irs->id->id);
    newel2 = lookup(pe->global, irs->id->id);


    if (newel == 0 && newel2 == 0) {
        printf("ERRO NA LINHA %d | (READ) Variable %s not defined!\n", irs->codeLine, irs->id->id);
        totalErros++;
        return;
    }

    if (newel == 0) {
        if (newel2->type == d_BOOL) {
            printf("ERRO NA LINHA %d | (READ) Read do not supports variables type boolean!\n", irs->codeLine);
            totalErros++;
            return;
        }
    } else {
        if (newel->type == d_BOOL) {
            printf("ERRO NA LINHA %d | (READ) Read do not supports variables type boolean!\n", irs->codeLine);
            totalErros++;
            return;
        }
    }

    if (irs->disc_d == d_READLINE) {
        if (newel == 0) {
            if (newel2->type != d_STRING) {
                printf("ERRO NA LINHA %d | (READ) READ only supports variables type string!\n", irs->codeLine);
                totalErros++;
                return;

            }
        } else {
            if (newel->type != d_STRING) {
                printf("ERRO NA LINHA %d | (READ) READ only accepts variables type string!\n", irs->codeLine);
                totalErros++;
                return;

            }
        }
    }
}

//CONVERTE O d_type para facilitar na apresentacao de erros!
char *typeToString(disc_type type) {
    switch (type) {
        case d_INTEGER:
            return "Integer";
        case d_STRING:
            return "String";
        case d_DOUBLE:
            return "Double";
        case d_FLOAT:
            return "Float";
        case d_type_ID:
            return "ID";
        case d_type_func_call:
            return "Func";
        case d_VOID:
            return "Void";
        case d_BOOL:
            return "Boolean";
    }
    totalErros++;
    return "Unknown Type";
}

//FUNC LIST
void semantic_analysis_func_list(prog_env *pe, is_func_list *ifl) {
    is_func_list *aux;
    environment_list *env_aux;

    //vamos fazer analise semantica de cada funcao
    for (aux = ifl; aux; aux = aux->next) {
        semantic_analysis_func_def(pe, aux->ifdef);
    }



    //verificacao se existe uma main e se tem os correctos parametros
    for (env_aux = pe->procs; env_aux; env_aux = env_aux->next) {
        if (strcmp(env_aux->name, "main") == 0 && env_aux->type == d_INTEGER) {
            return;
        }
    }

    printf("ERRO NA LINHA %d | (FUNC LIST) Function main not found or is not correctly defined!\n", linha);
    totalErros++;

}

//FUNC DEF
void semantic_analysis_func_def(prog_env *pe, is_func_def *ifd) {
    environment_list *aux;
    environment_list *pl;
    table_element *aux_te;
    int numeroArgs = 0;

    for (aux = pe->procs; aux; aux = aux->next) {
        if (strcmp(aux->name, ifd->id->id) == 0) {
            printf("ERRO NA LINHA %d | (FUNC DEF) Function %s already defined!\n", ifd->codeLine, ifd->id->id);
            totalErros++;
            return;
        }
    }

    pl = (environment_list *) malloc(sizeof(environment_list)); //cria um nodo para a lista de ambientes

    //preenche entrada para o procedimento na lista de ambientes
    pl->name = (char *) strdup(ifd->id->id);
    pl->type = ifd->isym->disc_d;
    pl->locals = (table_element *) malloc(sizeof(table_element));
    pl->arguments = (table_element *) malloc(sizeof(table_element));
    pl->next = NULL;
    pl->offset = 0;

    pl->offset = semantic_analysis_arg_list(pl->offset, LOCALSCOPE, pe, pl->locals, pl->arguments, ifd->ial);
    if (strcmp(pl->arguments->name, "") == 0) {
        aux_te = pl->arguments->next;
    } else {
        aux_te = pl->arguments;
    }
    for (; aux_te; aux_te = aux_te->next) {
        numeroArgs++;
    }


    pl->total_args = numeroArgs;

    if (debugPrints == 1)
        printf("SAIU DO ARG LIST!\n");

//INICIO
    //Adiciona ao program environment
    if (pe->procs == NULL) {    //Caso seja o primeiro procedimento, fica na cabeca
        pe->procs = pl;
    } else {    //senao, fica na cauda
        for (aux = pe->procs; aux->next; aux = aux->next);
        aux->next = pl;
    }
//FIM


    if (ifd->icf != NULL) {
        if (debugPrints == 1)
            printf("VAI ENTRAR CONT FUNC!\n");
        semantic_analysis_is_cont_func(pl, pe, pl->locals, ifd->icf);
        if (debugPrints == 1)
            printf("SAIU DO CONT FUNC!\n");
    }


//AQUI

    if (pl->type != d_VOID) { //SE NAO FOR DO TIPO VOID TEM QUE VIR UM RETURN NO FIM OBRIGATORIAMENTE
        if (ifd->icf->u_stmt_list == NULL) {
            printf("ERRO NA LINHA %d | (RET STA L) Missing return statement!\n", ifd->codeLine + 1);
            totalErros++;
        } else
            semantic_analysis_return_statement_list(ifd->icf->u_stmt_list);

    }

}


//STATEMENT LIST PARA PROCURAR O RETURN
void semantic_analysis_return_statement_list(is_statement_list *isl) {
    is_statement_list *tmp;

    for (tmp = isl; tmp->next; tmp = tmp->next);

    switch (tmp->statement->disc_d) {
        case d_return_statement:
            break;

        default:
            printf("ERRO NA LINHA %d | (RET STA L) Missing return statement!\n", tmp->statement->codeLine + 1);
            totalErros++;
            break;
    }
}


//ARG LIST
int semantic_analysis_arg_list(int offset, int scope, prog_env *pe, table_element *locals, table_element *arguments,
                               is_arg_list *ial) {
    is_arg_list *tmp;

    if (ial == NULL) {
        return offset;
    }

    for (tmp = ial; tmp; tmp = tmp->next) {
        semantic_analysis_symbols((scope == LOCALSCOPE ? offset++ : global_offset++), pe, locals, arguments, tmp->sym,
                                  tmp->id);
    }

    return offset;
}

//CONT FUNC
void
semantic_analysis_is_cont_func(environment_list *actualFunc, prog_env *pe, table_element *locals, is_cont_func *icf) {
    if (icf == NULL) {
        return;
    }

    if (debugPrints == 1)
        printf("VAI ENTRAR NO STATEMENT LIST DO CONT FUNC!\n");
    semantic_analysis_is_statement_list(actualFunc, pe, locals, icf->u_stmt_list);
    if (debugPrints == 1)
        printf("SAIU DO STATEMENT LIST DO CONT FUNC!\n");
}

//STATEMENT LIST
void semantic_analysis_is_statement_list(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                         is_statement_list *isl) {
    is_statement_list *tmp;

    for (tmp = isl; tmp; tmp = tmp->next) {
        semantic_analysis_is_statement(actualFunc, pe, locals, tmp->statement);
    }
}


//STATEMENT
void
semantic_analysis_is_statement(environment_list *actualFunc, prog_env *pe, table_element *locals, is_statement *is) {
    aritm = 0;
    switch (is->disc_d) {
        case d_instruction:
            semantic_analysis_is_instruction(pe, locals, is->data_statement.u_instruction);
            break;

        case d_compound_statement:
            semantic_analysis_is_compound_statement(actualFunc, pe, locals, is->data_statement.u_compound_statement);
            break;

        case d_println_statement:
            semantic_analysis_is_println_statement(pe, locals, is->data_statement.u_println_statement);
            break;

        case d_declaration:
            if (debugPrints == 1)
                printf("STATEMENT VAI CHAMAR O DECLARATION!\n");

            actualFunc->offset = semantic_analysis_declaration(actualFunc->offset, LOCALSCOPE, pe, locals,
                                                               is->data_statement.u_declaration);

            if (debugPrints == 1)
                printf("SAIU DO STATEMENT - DECLARATION!\n");
            break;

        case d_return_statement:
            semantic_analysis_is_return_statement(pe, locals, is->data_statement.u_return_statement);

            if (actualFunc->type != tipoActual) {
                printf("ERRO NA LINHA %d | (RETURN) Function %s returns an unexpected type!\n", is->codeLine,
                       actualFunc->name);
                totalErros++;

            }
            break;

        case d_func_call:
            semantic_analysis_is_func_call(actualFunc, pe, locals, is->data_statement.u_func_call);
            break;

        case d_read_statement:
            semantic_analysis_is_read_statement(pe, locals, is->data_statement.u_read_statement);
            break;
        case d_concat:
            semantic_analysis_is_concat(pe, locals, is->data_statement.u_concat);
            break;
        case d_break_cont:
            semantic_analysis_is_break_cont(pe, locals, is->data_statement.u_break_cont);
            break;
    }
}

//BREAK CONT
void semantic_analysis_is_break_cont(prog_env *pe, table_element *te, is_break_cont *ibc) {
    switch (ibc->disc_bc) {
        case is_BREAK:
            if (bc_flag >= 1) {
                printf("ERRO NA LINHA %d | (BREAK) Cannot use break outside cicles!!!\n", ibc->codeLine);
                totalErros++;
            }

            break;
        case is_CONTINUE:
            if (bc_flag >= 1) {
                printf("ERRO NA LINHA %d | (CONTINUE) Cannot use continue outside cicles!!!\n", ibc->codeLine);
                totalErros++;
            }
            break;
    }

}


//CONCAT STATEMENT
void semantic_analysis_is_concat(prog_env *pe, table_element *te, is_concat *irs) {
    semantic_analysis_is_concat_args(pe, te, irs->icargs);
}

//CONCAT ARGS
void semantic_analysis_is_concat_args(prog_env *pe, table_element *te, is_concat_args *irs) {
    is_concat_args *aux;
    if (irs->next == NULL) {
        concat = 1;
        semantic_analysis_is_type(pe, te, irs->ity1);
        concat = 0;
        semantic_analysis_is_type(pe, te, irs->ity2);
        return;
    }

    aux = irs;
    concat = 1;
    semantic_analysis_is_type(pe, te, irs->ity1);
    concat = 0;
    aux = aux->next;

    if (aux->next == NULL) {

        semantic_analysis_is_type(pe, te, aux->ity1);
        semantic_analysis_is_type(pe, te, aux->ity2);
    } else {

        for (; aux->next; aux = aux->next) {
            semantic_analysis_is_type(pe, te, aux->ity1);
        }

        semantic_analysis_is_type(pe, te, aux->ity1);
        semantic_analysis_is_type(pe, te, aux->ity2);
    }
}


//PRINTLN STATEMENT
void semantic_analysis_is_println_statement(prog_env *pe, table_element *locals, is_println_statement *ips) {

    semantic_analysis_is_println_args(pe, locals, ips->ipargs);

}

//PRINTLN ARGS
void semantic_analysis_is_println_args(prog_env *pe, table_element *locals, is_println_args *irs) {
    is_println_args *aux;
    if (irs->next == NULL) {
        semantic_analysis_is_type(pe, locals, irs->ity);
        return;
    }


    for (aux = irs; aux; aux = aux->next) {
        semantic_analysis_is_type(pe, locals, aux->ity);
    }
}

//FUNC CALL
void semantic_analysis_is_func_call(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                    is_func_call *ifcall) {
    int encontrou = 0;
    environment_list *aux;
    for (aux = pe->procs; aux; aux = aux->next) {
        if (strcmp(aux->name, ifcall->id->id) == 0) {
            encontrou = 1;
            break;
        }
    }

    if (encontrou == 1) {
        if (ifcall->icl != NULL) {
            semantic_analysis_is_call_list(aux, pe, locals, ifcall->icl);
        } else {
            if (aux->total_args != 0) {
                printf("ERRO NA LINHA %d | (FUNC CALL) Function call %s missing arguments!\n", ifcall->codeLine,
                       ifcall->id->id);
                totalErros++;
            }
        }

    } else {
        printf("ERRO NA LINHA %d | (FUNC CALL) Function %s is not defined!\n", ifcall->codeLine, ifcall->id->id);
        totalErros++;
    }
}

//CALL LIST
void
semantic_analysis_is_call_list(environment_list *actualFunc, prog_env *pe, table_element *locals, is_call_list *icl) {
    is_call_list *tmp;
    table_element *aux;
    table_element *aux2;
    aux = actualFunc->arguments;
    int argsSent = 0;
    int argsNeed = 0;

    for (; aux; aux = aux->next) {
        if (strcmp(aux->name, "") != 0) {
            argsNeed++;
        }
    }

    if (strcmp(actualFunc->arguments->name, "") == 0) {
        aux2 = actualFunc->arguments->next;
    } else
        aux2 = actualFunc->arguments;

    for (tmp = icl; tmp; tmp = tmp->next) {
        tipoActual = -1;
        argsSent++;
        semantic_analysis_is_type(pe, locals, tmp->ty);
        if (argsSent <= argsNeed) {
            semantic_analysis_arguments_are_correct(aux2, argsSent, icl->codeLine);
            aux2 = aux2->next;
        }
    }


    if (argsNeed != argsSent) {
        printf("ERRO NA LINHA %d | (CALL LIST) %d Arguments Needed ---- %d Arguments Sent!\n", icl->codeLine, argsNeed,
               argsSent);
        totalErros++;
    }
}

//VERIFICA ARGUMENTO A ARGUMENTO PARA COMPARAR COM OS QUE ESTAO A SER PASSADOS 'A FUNCAO
void semantic_analysis_arguments_are_correct(table_element *argument, int i, int errorLine) {
    if (argument->type == d_INTEGER || argument->type == d_FLOAT || argument->type == d_DOUBLE) {
        if (tipoActual == d_INTEGER || tipoActual == d_FLOAT || tipoActual == d_DOUBLE) {
            return;
        }
    }

    if (argument->type != tipoActual) {
        printf("ERRO NA LINHA %d | (CALL LIST) Argumento %d passado 'a funcao nao e' do tipo esperado!\n", errorLine,
               i);
        totalErros++;
    }

}

//TYPE
void semantic_analysis_is_type(prog_env *pe, table_element *locals, is_type *ity) {
    table_element *aux;
    table_element *aux_globals;
    environment_list *env_aux;
    char *functionName;
    int flagFuncCall = 0, tmp = 0;
    disc_type typeTmp;

    switch (ity->disc_n) {
        case d_type_ID:
            typeTmp = d_type_ID;
            aux = lookup(locals, ity->data_type.id->id);
            aux_globals = lookup(pe->global, ity->data_type.id->id);
            if (aux == 0 && aux_globals == 0) {
                printf("ERRO NA LINHA %d | (TYPE) Symbol %s is not defined!\n", ity->codeLine, ity->data_type.id->id);
                totalErros++;
                tipoActual = -1;
            } else {
                if (aux != NULL)
                    tipoActual = aux->type;
                else
                    tipoActual = aux_globals->type;
            }
            break;

        case d_type_func_call:
            functionName = ity->data_type.fcall->id->id;
            flagFuncCall = 0;
            for (env_aux = pe->procs; env_aux; env_aux = env_aux->next) {
                if (strcmp(functionName, env_aux->name) == 0) {
                    tmp = tipoActual = env_aux->type;
                    flagFuncCall = 1;
                    break;
                }
            }
            if (flagFuncCall == 0) {
                tmp = tipoActual = -1;
                printf("ERRO NA LINHA %d | (TYPE) Function %s is not defined!\n", ity->codeLine, functionName);
                totalErros++;
            } else {
                semantic_analysis_is_func_call(env_aux, pe, locals, ity->data_type.fcall);
            }
            tipoActual = tmp;
            break;

        case d_INTEGER:
            tipoActual = d_INTEGER;
            break;

        case d_DOUBLE:
            tipoActual = d_DOUBLE;
            break;

        case d_FLOAT:
            tipoActual = d_FLOAT;
            break;

        case d_STRING:
            tipoActual = d_STRING;
            break;
        case d_VOID:
            tipoActual = d_VOID;
            break;
        case d_BOOL:
            tipoActual = d_BOOL;
            break;
        default:
            break;
    }
    if (aritm == 1 && (tipoActual == d_BOOL)) {
        printf("ERRO NA LINHA %d | (TYPE) Operation aritmetic do not supports boolean type!\n", ity->codeLine);
        totalErros++;
    }
    if (aritm == 1 && (tipoActual == d_STRING)) {
        printf("ERRO NA LINHA %d | (TYPE) Operation aritmetic do not supports string type!\nTip: Use System.concat();\n",
               ity->codeLine);
        totalErros++;
    }
    if (concat == 1 && typeTmp != d_type_ID) {
        printf("ERRO NA LINHA %d | (TYPE-CONCAT) First argument needs to be a String variable to store the concat!\n",
               ity->codeLine);
        totalErros++;

    } else if (concat == 1 && typeTmp == d_type_ID && tipoActual != d_STRING) {
        printf("ERRO NA LINHA %d | (TYPE-CONCAT) First argument needs to be a String variable to store the concat!\n",
               ity->codeLine);
        totalErros++;

    }

}


//RETURN STATEMENT
void semantic_analysis_is_return_statement(prog_env *pe, table_element *locals, is_return_statement *irs) {

    //Caso em que nao retorna nada
    if (irs->instr == NULL) {
        tipoActual = d_VOID;
        return;
    }
    semantic_analysis_is_instruction(pe, locals, irs->instr);

}

//COMPOUND STATEMENT
void semantic_analysis_is_compound_statement(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                             is_compound_statement *ics) {
    switch (ics->disc_cs) {
        case d_if_statement:
            semantic_analysis_is_if_statement(actualFunc, pe, locals, ics->data_compound_statement.u_stmt_if);
            break;
        case d_while_statement:
            semantic_analysis_is_while_statement(actualFunc, pe, locals, ics->data_compound_statement.u_stmt_while);
            break;
        case d_for_statement:
            semantic_analysis_is_for_statement(actualFunc, pe, locals, ics->data_compound_statement.u_stmt_for);
            break;
    }
}

//FOR STATEMENT
void semantic_analysis_is_for_statement(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                        is_for_statement *ifs) {
    semantic_analysis_is_for_args(actualFunc, pe, locals, ifs->ifarg1);
    semantic_analysis_is_relac_exp(pe, locals, ifs->ire);
    semantic_analysis_is_for_args(actualFunc, pe, locals, ifs->ifarg2);
    bc_flag--;
    semantic_analysis_is_cont_statement(actualFunc, pe, locals, ifs->ics);
    bc_flag++;
}

//FOR ARGS
void
semantic_analysis_is_for_args(environment_list *actualFunc, prog_env *pe, table_element *locals, is_for_args *ifa) {
    //Caso em que o argumento seja NULL
    if (ifa == NULL) {
        return;
    }

    switch (ifa->disc_n) {
        case d_for_declaration:
            actualFunc->offset = semantic_analysis_declaration(actualFunc->offset++, LOCALSCOPE, pe, locals,
                                                               ifa->data_for_args.u_declaration);
            break;

        case d_for_dec_list:
            semantic_analysis_dec_list(actualFunc->offset, LOCALSCOPE, pe, locals, ifa->data_for_args.u_dec_list, 1, 0);
            break;
        case d_for_plusminus:
            semantic_analysis_is_plusminus(pe, locals, ifa->data_for_args.u_plusminus);
            break;
    }
    return;
}


//WHILE STATEMENT
void semantic_analysis_is_while_statement(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                          is_while_statement *iws) {
    semantic_analysis_is_instruction(pe, locals, iws->instr);
    bc_flag--; //pode usar breaks e continues dentro do while
    semantic_analysis_is_cont_statement(actualFunc, pe, locals, iws->iconts);
    bc_flag++;
}


//IF STATEMENT
void semantic_analysis_is_if_statement(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                       is_if_statement *iifs) {
    semantic_analysis_is_instruction(pe, locals, iifs->instr);
    semantic_analysis_is_cont_statement(actualFunc, pe, locals, iifs->iconts);
    semantic_analysis_is_elseif_statement_list(actualFunc, pe, locals, iifs->ieisl);
    semantic_analysis_is_else_statement(actualFunc, pe, locals, iifs->ielses);
}

//ELSE STATEMENT
void semantic_analysis_is_else_statement(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                         is_else_statement *ies) {
    //Caso em que nao ha else
    if (ies == NULL) {
        return;
    }

    semantic_analysis_is_cont_statement(actualFunc, pe, locals, ies->iconts);
    return;
}

//ELSE IF STATMT LIST
void semantic_analysis_is_elseif_statement_list(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                                is_elseif_statement_list *ieisl) {
    is_elseif_statement_list *tmp;

    //Caso em que nao ha lista de else if
    if (ieisl == NULL) {
        return;
    }

    for (tmp = ieisl; tmp; tmp = tmp->next) {
        semantic_analysis_is_elseif_statement(actualFunc, pe, locals, tmp->ielseifs);
    }
    return;
}

//ELSE IF STATMT
void semantic_analysis_is_elseif_statement(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                           is_elseif_statement *ieis) {
    //Caso em que nao ha else if
    if (ieis == NULL) {
        return;
    }

    semantic_analysis_is_instruction(pe, locals, ieis->instr);
    semantic_analysis_is_cont_statement(actualFunc, pe, locals, ieis->iconts);
    return;
}

//CONT_STATEMENT
void semantic_analysis_is_cont_statement(environment_list *actualFunc, prog_env *pe, table_element *locals,
                                         is_cont_statement *ics) {
    if (ics == NULL) {
        return;
    }

    switch (ics->disc_cts) {
        case d_statement:
            semantic_analysis_is_statement(actualFunc, pe, locals, ics->data_cont_statement.u_stmt);
            break;

        case d_statement_list:
            semantic_analysis_is_statement_list(actualFunc, pe, locals, ics->data_cont_statement.u_stmt_list);
            break;
    }

    return;
}

//INSTRUCTION
void semantic_analysis_is_instruction(prog_env *pe, table_element *locals, is_instruction *iinstr) {
    switch (iinstr->disc_d) {
        case d_atribution: //caller 0 - e' para verificar existencia
            semantic_analysis_is_atribution(0, 0, LOCALSCOPE, pe, locals, 0, iinstr->data_instr.u_atribution);
            break;
        case d_expression:
            semantic_analysis_is_expression(pe, locals, iinstr->data_instr.u_expression);
            break;
        case d_plusminus:
            semantic_analysis_is_plusminus(pe, locals, iinstr->data_instr.u_plusminus);
            break;
    }
}

//PLUSMINUS
void semantic_analysis_is_plusminus(prog_env *pe, table_element *te, is_plusminus *ia) {

    table_element *newel;
    is_id *id_tmp = ia->id;


    newel = lookup(te, id_tmp->id);
    if (newel == NULL) {
        newel = lookup(pe->global, id_tmp->id);
        if (newel == NULL) {
            printf("ERRO NA LINHA %d | (PLUSMINUS) Symbol %s is not defined!\n", id_tmp->codeLine, id_tmp->id);
            totalErros++;
        } else {
            if (newel->type == d_VOID || newel->type == d_STRING || newel->type == d_type_ID ||
                newel->type == d_type_func_call) {
                printf("ERRO NA LINHA %d | (PLUSMINUS) Type is invalid for that kind of operation!\n",
                       id_tmp->codeLine);
                totalErros++;
            }
        }
    } else {
        if (newel->type == d_VOID || newel->type == d_STRING || newel->type == d_type_ID ||
            newel->type == d_type_func_call) {
            printf("ERRO NA LINHA %d | (PLUSMINUS) Type is invalid for that kind of operation!\n", id_tmp->codeLine);
            totalErros++;
        }
    }
}


//EXPRESSION
void semantic_analysis_is_expression(prog_env *pe, table_element *locals, is_expression *ie) {
    switch (ie->disc_d) {
        case d_expression_exp:
            semantic_analysis_is_expression(pe, locals, ie->data_expr.u_expression);
            break;

        case d_logic_exp_or_and:
            semantic_analysis_is_logic_exp_or_and(pe, locals, ie->data_expr.u_logic_exp_or_and);
            break;

        case d_logic_exp_not:
            semantic_analysis_is_logic_exp_not(pe, locals, ie->data_expr.u_logic_exp_not);
            break;

        case d_exp_minus_plus:
            semantic_analysis_is_exp_minus_plus(pe, locals, ie->data_expr.u_exp_minus_plus);
            break;

        case d_aritmetic_exp:
            semantic_analysis_is_aritmetic_exp(pe, locals, ie->data_expr.u_aritm_exp);
            break;

        case d_relac_exp:
            semantic_analysis_is_relac_exp(pe, locals, ie->data_expr.u_relac_exp);
            break;

        case d_type:
            semantic_analysis_is_type(pe, locals, ie->data_expr.u_type);
            break;
    }
}

void semantic_analysis_is_exp_minus_plus(prog_env *pe, table_element *locals, is_exp_minus_plus *iemp) {
    semantic_analysis_is_expression(pe, locals, iemp->exp);
}

//LOGIC EXP OR AND
void semantic_analysis_is_logic_exp_or_and(prog_env *pe, table_element *locals, is_logic_exp_or_and *ileoa) {
    //is_oper_l oper  |||  ileoa->oper------> NAO SEI SE E' PRECISO VERIFICAR ALGUMA COISA NO OPERADOR!!!!!

    semantic_analysis_is_expression(pe, locals, ileoa->exp1);
    semantic_analysis_is_expression(pe, locals, ileoa->exp2);
}

//LOGIC EXP NOT
void semantic_analysis_is_logic_exp_not(prog_env *pe, table_element *locals, is_logic_exp_not *ilen) {
    semantic_analysis_is_expression(pe, locals, ilen->exp1);
}

//RELAC EXP
void semantic_analysis_is_relac_exp(prog_env *pe, table_element *locals, is_relac_exp *ire) {
    semantic_analysis_is_expression(pe, locals, ire->exp1);
    semantic_analysis_is_expression(pe, locals, ire->exp2);
}

//ARITMETIC EXP
void semantic_analysis_is_aritmetic_exp(prog_env *pe, table_element *locals, is_aritmetic_exp *iae) {
    aritm = 1;
    semantic_analysis_is_expression(pe, locals, iae->exp1);
    semantic_analysis_is_expression(pe, locals, iae->exp2);
}

//SYMBOLS
void
semantic_analysis_symbols(int offset, prog_env *pe, table_element *locals, table_element *arguments, is_symbols *isy,
                          is_id *id) {

    table_element *newel;
    table_element *newel2;
    table_element *aux = locals;
    table_element *aux2 = arguments;

    if (locals == NULL) {
        newel = create_symbol(offset, id->id, isy->disc_d);
        newel->next = NULL;
        locals = newel;
        arguments = newel;
    } else {
        newel = lookup(locals, id->id);
        if (newel == 0) {
            newel = create_symbol(offset, id->id, isy->disc_d);
            newel->next = NULL;
            newel2 = create_symbol(offset, id->id, isy->disc_d);
            newel2->next = NULL;
            for (; aux->next; aux = aux->next);
            aux->next = newel;
            for (; aux2->next; aux2 = aux2->next);
            aux2->next = newel2;
        } else {
            printf("ERRO NA LINHA %d | (SYMBOLS) Symbol %s already defined!\n", id->codeLine, id->id);
            totalErros++;
        }
    }
}