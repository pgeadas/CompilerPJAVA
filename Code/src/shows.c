#include "../headers/shows.h"
#include <stdlib.h>
#include <stdio.h>

//PROGRAMA
void show_program(is_program* ip)
{
    printf("PROGRAM:\n\n");
    if((ip->iclass)==NULL){
        printf("NULL");
        return;
    }
    printf("CLASS %s {\n", ip->iid->id);
    show_class(ip->iclass);
    printf("\n}\n\n");
}

//CLASS
void show_class(is_class *ic)
{
    for(; ic->icla; ic=ic->icla){
        show_declaration(ic->idecl);
    }
    show_func_list(ic->ifl);
}

//FUNC LIST
void show_func_list(is_func_list* ifl)
{
    for(; ifl != NULL; ifl = ifl->next)
    {
        printf("\nFUNC_LIST(");
        if((ifl->ifdef)==NULL){
            printf("NULL");
        }
        else{
            show_func_def(ifl->ifdef);
        }
        printf(")");
    }
}

//RETURN
void show_return_statement(is_return_statement *ireturn)
{
    printf("RETURN(");
    if((ireturn->instr)==NULL){
        printf("NULL");
    }
    else{
        show_instruction(ireturn->instr);
    }
    printf(")");

}

//STATEMENT LIST
void show_statement_list(is_statement_list* isl)
{
    for(; isl != NULL; isl = isl->next)
    {
        printf("\nstatement(");
        if((isl->statement)==NULL){
            printf("NULL");
        }
        else{
            show_statement(isl->statement);
        }
        printf(")");
    }
}

//STATEMENT
void show_statement(is_statement* is)
{
    switch(is->disc_d)
    {
        case d_instruction:
            printf("Instruction(");
            show_instruction((is_instruction*)is->data_statement.u_instruction);
            printf(")");
            break;

        case d_compound_statement:
            printf("Compound Statement(");
            show_compound_statement((is_compound_statement*)is->data_statement.u_compound_statement);
            printf(")");
            break;
        case d_println_statement:
            printf("Println Statement(");
            show_println_statement((is_println_statement*)is->data_statement.u_println_statement);
            printf(")");
            break;
        case d_declaration:
            printf("Declaration(");
            show_declaration((is_declaration*)is->data_statement.u_declaration);
            printf(")");
            break;
        case d_return_statement:
            show_return_statement((is_return_statement*) is->data_statement.u_return_statement);
            break;
        case d_func_call:
            printf("Function Call(");
            show_func_call((is_func_call*) is->data_statement.u_func_call);
            printf(")");
            break;
        case d_read_statement:
            printf("read from keypad(");
            show_read_statement((is_read_statement*)is->data_statement.u_read_statement);
            break;
        case d_concat:
            printf("CONCAT()");
            break;

        case d_break_cont:
            printf("BREAK_CONT()");
            break;

    }
}

void show_read_statement(is_read_statement* irs)
{
    printf("READ FROM KeyBoard and saved in %s))",irs->id->id);


}

//CHAMADA FUNC
void show_func_call(is_func_call* ifcall)
{
    printf("FUNCTION CALL(");
    if((ifcall->id)==NULL)
        printf(" NULL ");
    else
        show_id(ifcall->id);


    if((ifcall->icl)==NULL)
        printf(" NULL, ");
    else{
        printf("lista_chamada: ");
        show_call_list(ifcall->icl);
    }

    printf(")");
}


//LISTA DE CHAMADA
void show_call_list(is_call_list* icall){
    for(; icall != NULL; icall = icall->next)
    {
        show_type(icall->ty);
        printf(", ");
    }

}

//DEFINE FUNC
void show_func_def(is_func_def* ifd)
{
    printf("func_def(");

    show_symbols(ifd->isym);
    show_id(ifd->id);
    printf("argumentos: ");
    show_arg_list(ifd->ial);
    if((ifd->icf)==NULL){
        printf(" NULL, ");
    }
    else{
        show_cont_func(ifd->icf);
    }

    printf(")");
}

//SYMBOLS
void show_symbols(is_symbols* s)
{
    switch(s->disc_d)
    {
        case d_INTEGER:
            printf("INT ");
            break;

        case d_FLOAT:
            printf("FLOAT ");
            break;
        case d_DOUBLE:
            printf("DOUBLE ");
            break;
        case d_STRING:
            printf("STRING ");
            break;
        case d_type_ID:
            printf("ID ");
            break;
        case d_type_func_call:
            printf("FUNCTION CALL ");
            break;
        case d_VOID:
            printf("VOID ");
            break;
        case d_BOOL:
            printf("BOOL ");
            break;
    }
}

//LISTA DE ARGUMENTOS
void show_arg_list(is_arg_list* iargl)
{
    for(; iargl != NULL; iargl = iargl->next)
    {
        show_symbols(iargl->sym);
        show_id(iargl->id);
        printf(", ");
    }
}

//CONTINUACAO DA FUNC
void show_cont_func(is_cont_func* icf){

    printf("CONT_FUNC(");
    show_statement_list((is_statement_list*)icf->u_stmt_list);
    printf(")");
}


//DECLARATION
void show_declaration(is_declaration* decl)
{
    switch(decl->disc_d)
    {
        case d_INTEGER:
            printf("INT ");
            break;

        case d_FLOAT:
            printf("FLOAT ");
            break;
        case d_DOUBLE:
            printf("DOUBLE ");
            break;
        case d_STRING:
            printf("STRING ");
            break;
        case d_type_ID:
            printf("ID ");
            break;
        case d_type_func_call:
            printf("FUNCTION CALL ");
            break;
        case d_VOID:
            printf("VOID ");
            break;
        case d_BOOL:
            printf("BOOL ");
            break;
    }


    show_dec_list( (is_dec_list*) decl->dec_list);
}

//LISTA DE DECLARATION
void show_dec_list(is_dec_list* idl)
{
    for(; idl != NULL; idl = idl->next)
    {
        show_atr(idl->atr);
        printf(", ");
    }
}

//ATRIBUICAO NAS DECLARATIONS
void show_atr(is_atr* ics)
{
    switch(ics->disc_n)
    {
        case d_ID:
            show_id((is_id*)ics->data_atr.u_id);
            break;

        case d_atribution:
            show_atribution((is_atribution*)ics->data_atr.u_atribution);
            break;
    }
}


void show_compound_statement(is_compound_statement* ics)
{
    switch(ics->disc_cs)
    {
        case d_if_statement:
            show_if_statement((is_if_statement*)ics->data_compound_statement.u_stmt_if);
            break;

        case d_while_statement:
            show_while_statement((is_while_statement*)ics->data_compound_statement.u_stmt_while);
            break;
        case d_for_statement:
            show_for_statement((is_for_statement*)ics->data_compound_statement.u_stmt_for);
            break;
    }
}

//PRINTLN
void show_println_statement(is_println_statement* ips)
{
    printf("PRINT");
}

//WHILE
void show_while_statement(is_while_statement* iws)
{
    printf("WHILE(");
    show_instruction(iws->instr);
    printf(")");
    if((iws->iconts)==NULL){
        printf(" NULL, ");
    }
    else{
        show_cont_statement(iws->iconts);
    }
}

//IF
void show_if_statement(is_if_statement* iifs)
{
    printf("IF(");
    show_instruction(iifs->instr);
    printf(")");

    if((iifs->iconts)==NULL){
        printf(" NULL, ");
    }
    else{
        show_cont_statement(iifs->iconts);
    }

    if((iifs->ieisl)==NULL){
        printf(" NULL, ");
    }
    else{
        show_elseif_statement_list(iifs->ieisl);
    }

    if((iifs->ielses)==NULL){
        printf(" NULL, ");
    }
    else{
        show_else_statement(iifs->ielses);
    }
}

//ELSE
void show_else_statement(is_else_statement* ielses)
{
    printf("ELSE(");
    if((ielses->iconts)==NULL){
        printf(" NULL, ");
    }
    else{
        show_cont_statement(ielses->iconts);
    }
    printf(")");

}


//ELSE IF
void show_elseif_statement(is_elseif_statement* ielseifs)
{
    printf("ELSE IF(");
    show_instruction(ielseifs->instr);

    if((ielseifs->iconts)==NULL){
        printf(" NULL ");
    }
    else{
        show_cont_statement(ielseifs->iconts);
    }
    printf(")");


}

//LISTA DE ELSES
void show_elseif_statement_list(is_elseif_statement_list* iesl)
{
    if(iesl==NULL)
        return;
    is_elseif_statement_list* aux;

    for(aux=iesl; aux!=NULL; aux=aux->next){
        if((aux->ielseifs)!=NULL)
            show_elseif_statement(aux->ielseifs);
    }
}

//CONTINUACAO
void show_cont_statement(is_cont_statement* icts){

    printf("CONT_STATEMENT(");
    switch(icts->disc_cts)
    {
        case d_statement:
            if((icts->data_cont_statement.u_stmt)==NULL){
                printf(" NULL ");
            }
            else{
                show_statement((is_statement*)icts->data_cont_statement.u_stmt);
            }
            break;
        case d_statement_list:
            if((icts->data_cont_statement.u_stmt_list)==NULL){
                printf(" NULL ");
            }
            else{
                show_statement_list((is_statement_list*)icts->data_cont_statement.u_stmt_list);
            }
            break;

        default:
            printf("È NULLLLLL\n");
            break;
    }


    printf(")");
}


//INSTRUCTION
void show_instruction(is_instruction* ii)
{
    switch(ii->disc_d)
    {
        case d_expression:
            printf("expression(");
            show_expression((is_expression*)ii->data_instr.u_expression);
            printf(")");
            break;

        case d_atribution:
            printf("atribution(");
            show_atribution((is_atribution*)ii->data_instr.u_atribution);
            printf(")");
            break;
        case d_plusminus:
            show_plusminus((is_plusminus*)ii->data_instr.u_plusminus);
            break;
    }
}

//PLUSMINUS
void show_plusminus(is_plusminus* ia)
{

    printf("( ID(%s)",ia->id->id);
    switch(ia->disc_d){

        case d_PLUSPLUS:
            printf("++ )");
            break;
        case d_MINUSMINUS:
            printf("-- )");
            break;

    }

}


void show_atribution(is_atribution* ia)
{

    show_atribution_list(ia->atrib_list);
    printf(", ");
    show_expression(ia->expression);
}

void show_atribution_list(is_atribution_list* ial){

    for(; ial!=NULL; ial=ial->next)
        show_id(ial->id);

}

void show_id(is_id* id)
{
    printf("ID(%s)",id->id);
}

void show_expression(is_expression* ie)
{
    switch(ie->disc_d)
    {
        case d_expression_exp:
            printf("PRIORIDADE(");
            show_expression((is_expression*)ie->data_expr.u_expression);
            printf(")");
            break;
        case d_aritmetic_exp:
            printf("aritmetic(");
            show_aritmetic_exp((is_aritmetic_exp*)ie->data_expr.u_aritm_exp);
            printf(")");
            break;

        case d_type:
            printf("type(");
            show_type((is_type*) ie->data_expr.u_type);
            printf(")");
            break;

        case d_relac_exp:
            printf("relac_exp(");
            show_relac_exp((is_relac_exp*) ie->data_expr.u_relac_exp);
            printf(")");
            break;

        case d_logic_exp_or_and:
            printf("logic_exp_or_and(");
            show_logic_exp_or_and((is_logic_exp_or_and*) ie->data_expr.u_logic_exp_or_and);
            printf(")");
            break;
        case d_logic_exp_not:
            printf("NOT(");
            show_logic_exp_not((is_logic_exp_not*) ie->data_expr.u_logic_exp_not);
            printf(")");
            break;
        case d_exp_minus_plus:
            printf("FALTA FAZER ISTO!");
            //FALTA FAZERRRRRRRRRRRRRRRRRR!
            break;

    }
}

void show_logic_exp_not(is_logic_exp_not* ilen){

    show_expression(ilen->exp1);
}

void show_logic_exp_or_and(is_logic_exp_or_and* ileoa){

    show_expression(ileoa->exp1);
    printf(", ");
    show_operator_l_o_a(ileoa->oper);
    printf(", ");
    show_expression(ileoa->exp2);

}

void show_relac_exp(is_relac_exp* ire){

    show_expression(ire->exp1);
    printf(", ");
    show_operator_r(ire->oper);
    printf(", ");
    show_expression(ire->exp2);

}

void show_aritmetic_exp(is_aritmetic_exp* iae)
{
    show_expression(iae->exp1);
    printf(", ");
    show_operator_a(iae->oper);
    printf(", ");
    show_expression(iae->exp2);
}

void show_type(is_type* in)
{
    switch(in->disc_n)
    {
        case d_INTEGER: printf("int(%d)", in->data_type.integer);
            break;
        case d_FLOAT:	printf("float(%f)", in->data_type.fl);
            break;
        case d_DOUBLE:	printf("double(%f)", in->data_type.db);
            break;
        case d_STRING:	printf("string(%s)", in->data_type.string);
            break;
        case d_type_ID:
            printf("ID( ");
            show_id(in->data_type.id);
            printf(")");
            break;
        case d_type_func_call:
            show_func_call(in->data_type.fcall);
            break;
        case d_BOOL:
            if(in->data_type.boolean)
                printf("BOOL(%s)", "True");
            else
                printf("BOOL(%s)", "False");
            break;

        default:	break;
    }
}


void show_operator_l_o_a(is_oper_l oper)
{
    if(oper==is_AND)
        printf("&&");
    else
        printf("||");
}

void show_operator_a(is_oper_a oper)
{
    if(oper==is_PLUS)
        printf("+");
    else if(oper==is_MINUS)
        printf("-");
    else if(oper==is_DIV)
        printf("/");
    else if(oper==is_MULT)
        printf("*");
    else if(oper==is_POT)
        printf("^");
    else
        printf("MOD");
}

void show_operator_r(is_oper_r oper)
{
    if(oper==is_GREATER)
        printf(">");
    else if(oper==is_LESS)
        printf("<");
    else if(oper==is_EQUAL)
        printf("==");
    else if(oper==is_NOTEQUAL)
        printf("!=");
    else if(oper==is_GREATEREQUAL)
        printf(">=");
    else
        printf("<=");
}

void show_for_statement(is_for_statement *ifs){

    printf("FOR STATEMENT(");
    if((ifs->ifarg1)==NULL){
        printf("NULL ,");
    }
    else{
        show_for_args(ifs->ifarg1);
        printf(" ,");
    }
    printf("relac_exp(");
    show_relac_exp(ifs->ire);
    printf(") ");

    if((ifs->ifarg2)==NULL){
        printf("NULL ,");
    }
    else{
        show_for_args(ifs->ifarg2);
        printf(" , ");
    }

    if((ifs->ics)==NULL){
        printf("NULL");
    }
    else{
        show_cont_statement(ifs->ics);
    }

    printf(")");

}

//ARGUMENTOS FOR
void show_for_args(is_for_args* ifa)
{
    switch(ifa->disc_n)
    {
        case d_for_dec_list:
            printf("for_dec_list(");
            show_dec_list((is_dec_list*)ifa->data_for_args.u_dec_list);
            printf(")");
            break;

        case d_for_declaration:
            printf("for_declaration(");
            show_declaration((is_declaration*)ifa->data_for_args.u_declaration);
            printf(")");
            break;
        case d_for_plusminus:
            show_plusminus((is_plusminus*)ifa->data_for_args.u_plusminus);
            break;

    }
}