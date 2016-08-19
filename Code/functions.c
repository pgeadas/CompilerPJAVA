#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>


//PROGRAMA
is_program* insert_program(is_id *id, is_class *isl)
{
	is_program* ip = (is_program*)malloc(sizeof(is_program));

	ip->iclass = isl;
	ip->iid=id;

	return ip;
}

//CLASS
is_class* insert_class(is_declaration *idecl, is_class *icla, is_func_list *ifl)
{
	
	is_class *ic = (is_class*) malloc (sizeof(is_class*));
	if(ifl==NULL){
		ic->idecl=idecl;
		ic->icla=icla;
		ic->ifl=NULL;
		return ic;	
	}

	ic->idecl=NULL;
	ic->icla=NULL;
	ic->ifl=ifl;
	return ic;
}

//LISTA DE FUNCOES
is_func_list* insert_func_list(is_func_list *list, is_func_def *st)
{
	is_func_list* istl=(is_func_list*)malloc(sizeof(is_func_list));	//Cria novo nó na lista
	
	istl->ifdef=st;				//Preenche-o
	istl->next=NULL;
	
	if(list==NULL){		//Se a lista estiver vazia
		return istl;	//Devolve o nó criado
	}

	is_func_list* aux;
			
	for(aux=list; aux->next!=NULL; aux=aux->next);	//procura pelo final da lista
		aux->next=istl;					//adiciona no final da lista
	
	return list;
}

//RETURN
is_return_statement* insert_return_statement(is_instruction *instr)
{
	is_return_statement* irs = (is_return_statement*)malloc(sizeof(is_return_statement));	
	irs->instr = instr;

	return irs;
}

// is_statement --> is_instruction V comp_stat
is_statement* insert_statement(disc_statement ds, void* stmt)
{
	is_statement* is = (is_statement*)malloc(sizeof(is_statement));
	is->disc_d = ds;
	is->codeLine=linha;
	switch (ds)
	{
		case d_instruction:
			is->data_statement.u_instruction = (is_instruction*) stmt;
			break;
		case d_compound_statement:
			is->data_statement.u_compound_statement = (is_compound_statement*) stmt;
			break;
		case d_println_statement:
			is->data_statement.u_println_statement = (is_println_statement*) stmt;
			break;
		case d_declaration:
			is->data_statement.u_declaration = (is_declaration*) stmt;
			break;
		case d_func_call:
			is->data_statement.u_func_call = (is_func_call*) stmt;
			break;
		case d_return_statement:
			is->data_statement.u_return_statement = (is_return_statement*) stmt;
			break;
		case d_read_statement:
			is->data_statement.u_read_statement = (is_read_statement*) stmt;
			break;
		case d_concat:
			is->data_statement.u_concat = (is_concat*) stmt;
			break;
		case d_break_cont:
			is->data_statement.u_break_cont = (is_break_cont*) stmt;
			break;
		default:
			printf("ERRO na inserção de um statement!\n");	
	}

	return is;
}

//BREAK CONT
is_break_cont* insert_break_cont(disc_bc bc)
{
	is_break_cont* ibc = (is_break_cont*)malloc(sizeof(is_break_cont));
	ibc->disc_bc = bc;
	ibc->codeLine=linha;

	return ibc;
}

//CONCAT
is_concat* insert_concat(is_concat_args* ica){
	
	is_concat* ips = (is_concat*)malloc(sizeof(is_concat));
	ips->icargs = ica;
	ips->codeLine=linha;
	return ips;
}

//CONCAT ARGS
is_concat_args* insert_concat_args(is_type* i1, is_type* i2, is_concat_args* n){

	is_concat_args* ips = (is_concat_args*)malloc(sizeof(is_concat_args));
	ips->codeLine=linha;
	ips->next=NULL;

	ips->ity1=i1;



	if(i2==NULL){
		ips->ity2=NULL;
		ips->next=n;
		return ips;	
	}

	ips->ity2=i2;
	ips->next=NULL;
	return ips;

}

//LISTA DE STATEMENTS
is_statement_list* insert_statement_list(is_statement_list* list, is_statement* st)
{
	is_statement_list* istl=(is_statement_list*)malloc(sizeof(is_statement_list));	//Cria novo nó na lista
	
	istl->statement=st;				//Preenche-o
	istl->next=NULL;
	if(list==NULL)		//Se a lista estiver vazia
		return istl;	//Devolve o nó criado

	is_statement_list* aux;
			
	for(aux=list; aux->next!=NULL; aux=aux->next);	//procura pelo final da lista
		aux->next=istl;					//adiciona no final da lista
	
	return list;
}

//SYMBOLS
is_symbols* insert_symbols(disc_type dn)
{
	is_symbols* s = (is_symbols*)malloc(sizeof(is_symbols));
	s->disc_d = dn;
	s->codeLine=linha;

	return s;
}

//DECLARATION
is_declaration* insert_declaration(disc_type dn, is_dec_list* decl)
{
	is_declaration* in = (is_declaration*)malloc(sizeof(is_declaration));
	in->disc_d = dn;
	in->dec_list=decl;

	return in;
}

//DECLIST
is_dec_list* insert_dec_list(is_dec_list* list, is_atr* st)
{
	is_dec_list* istl=(is_dec_list*)malloc(sizeof(is_dec_list));	//Cria novo nó na lista
	
	istl->atr=st;				//Preenche-o
	
	if(list==NULL)		//Se a lista estiver vazia
		return istl;	//Devolve o nó criado

	is_dec_list* aux;
			
	for(aux=list; aux->next!=NULL; aux=aux->next);	//procura pelo final da lista
	aux->next=istl;					//adiciona no final da lista
	
	return list;
}

//arg_list
is_arg_list* insert_arg_list(is_arg_list* list, is_symbols* st, is_id* id)
{
	is_arg_list* isal=(is_arg_list*)malloc(sizeof(is_arg_list));	//Cria novo nó na lista
	
	isal->sym=st;				//Preenche-o
	isal->id=id;
	
	if(list==NULL)		//Se a lista estiver vazia
		return isal;	//Devolve o nó criado

	is_arg_list* aux;
			
	for(aux=list; aux->next!=NULL; aux=aux->next);	//procura pelo final da lista
	aux->next=isal;					//adiciona no final da lista
	
	return list;
}

is_atr* insert_atr(disc_atr cts, void* cont)
{
	is_atr* ics = (is_atr*)malloc(sizeof(is_atr));
	ics->codeLine=linha;
	ics->disc_n= cts;
	switch(cts){
		case d_ID:
			ics->data_atr.u_id = (is_id*) cont;
			ics->data_atr.u_id->codeLine=linha;
			break;
		case d_atribution_atr:
			ics->data_atr.u_atribution = (is_atribution*) cont;
			break;
		default:
			printf("ERRO na inserção de um atr!\n");
			break;
	}

	return ics;
}

is_compound_statement* insert_compound_statement(disc_compound_statement cs, void* cmp)
{
	is_compound_statement* is = (is_compound_statement*)malloc(sizeof(is_compound_statement));
	is->disc_cs = cs;

	switch (cs)
	{
		case d_if_statement:
			is->data_compound_statement.u_stmt_if = (is_if_statement*) cmp;
			break;

		case d_while_statement:
			is->data_compound_statement.u_stmt_while = (is_while_statement*) cmp;
			break;

		case d_for_statement:
			is->data_compound_statement.u_stmt_for = (is_for_statement*) cmp;
			break;
		default:
			printf("ERRO na inserção de um compound statement!\n");	
	}

	return is;
}

//PRINTLN
is_println_statement* insert_println_statement(disc_print d, is_println_args* ii)
{
	is_println_statement* ips = (is_println_statement*)malloc(sizeof(is_println_statement));
	ips->ipargs = ii;
	ips->disc_d=d;
	ips->codeLine=linha;
	return ips;
}

//PRINTLN ARGS
is_println_args* insert_println_args(is_type* it, is_println_args* ipa){

	is_println_args* ips = (is_println_args*)malloc(sizeof(is_println_args));
	ips->codeLine=linha;
	ips->next=NULL;

	ips->ity=it;

	if(ipa==NULL){
		ips->next=NULL;
		return ips;	
	}

	ips->next=ipa;
	return ips;
}

//READ
is_read_statement* insert_read_statement(disc_read d, is_id* id)
{
	is_read_statement* irs = (is_read_statement*)malloc(sizeof(is_read_statement));
	irs->id = id;
	irs->codeLine = linha;
	irs->disc_d=d;
	return irs;
}

//FOR
is_for_statement* insert_for_statement(is_for_args *args1, is_relac_exp *ire, is_for_args *args2, is_cont_statement *icsta)
{
	is_for_statement* in = (is_for_statement*)malloc(sizeof(is_for_statement));
	in->ifarg1 = args1;
	in->ifarg2 = args2;
	in->ire=ire;
	in->ics= icsta;

	return in;
}

//FOR ARGS
is_for_args* insert_for_args(disc_for_args cts, void* cont)
{
	is_for_args* ics = (is_for_args*)malloc(sizeof(is_for_args));
	ics->disc_n= cts;
	switch(cts){
		case d_for_declaration:
			ics->data_for_args.u_declaration = (is_declaration*) cont;
			break;
		case d_for_dec_list:
			ics->data_for_args.u_dec_list = (is_dec_list*) cont;
			break;
		case d_for_plusminus:
			ics->data_for_args.u_plusminus = (is_plusminus*) cont;
			break;
		default:
			printf("ERRO na inserção de ARGUMENTOS DO FOR!\n");
			break;
	}

	return ics;
}

//WHILE
is_while_statement* insert_while_statement(is_instruction* ii, is_cont_statement* iconts)
{
	is_while_statement* iws = (is_while_statement*)malloc(sizeof(is_while_statement));
	iws->instr = ii;
	iws->iconts = iconts;

	return iws;
}

//IF
is_if_statement* insert_if_statement(is_instruction* ii, is_cont_statement* iconts, is_elseif_statement_list* ieisl, is_else_statement* ielses)
{
	is_if_statement* iifs = (is_if_statement*)malloc(sizeof(is_if_statement));
	iifs->instr = ii;
	iifs->iconts = iconts;
	iifs->ieisl = ieisl;
	iifs->ielses = ielses;

	return iifs;
}

//ELSE
is_else_statement* insert_else_statement(is_cont_statement* iconts)
{
	is_else_statement* ielses = (is_else_statement*)malloc(sizeof(is_else_statement));	
	ielses->iconts = iconts;

	return ielses;
}

//ELSE IF
is_elseif_statement* insert_elseif_statement(is_instruction* instr, is_cont_statement* iconts)
{
	is_elseif_statement* ielseifs = (is_elseif_statement*)malloc(sizeof(is_elseif_statement));
	ielseifs->instr = instr;	
	ielseifs->iconts = iconts;

	return ielseifs;
}

//ELSE IF LISTA
is_elseif_statement_list* insert_elseif_statement_list(is_elseif_statement_list* list_head, is_elseif_statement* ielseifs)
{
	is_elseif_statement_list* aux;
	is_elseif_statement_list* ieisl = (is_elseif_statement_list*)malloc(sizeof(is_elseif_statement_list));
	ieisl->ielseifs = ielseifs;
	ieisl->next=NULL;

	// Se não for o primeiro elemento da lista, adiciona-o ao fim da lista
	if (list_head != NULL)
	{
		for (aux = list_head; aux->next; aux = aux->next);
		aux->next = ieisl;
		return list_head;
	}
	

	return ieisl;
}


//CONTINUACAO
is_cont_statement* insert_cont_statement(disc_cont_statement cts, void* cont)
{
	is_cont_statement* ics = (is_cont_statement*)malloc(sizeof(is_cont_statement));
	ics->disc_cts= cts;
	switch(cts){
		case d_statement:
			ics->data_cont_statement.u_stmt = (is_statement*) cont;
			break;
		case d_statement_list:
			ics->data_cont_statement.u_stmt_list = (is_statement_list*) cont;
			break;
		default:
			printf("ERRO na inserção de um continuation statement!\n");
			break;
	}

	return ics;
}

//DEFINICAO DE FUNCAO
is_func_def* insert_func_def(is_symbols* is, is_id* id, is_arg_list* ial, is_cont_func* icf)
{
	is_func_def* ifd = (is_func_def*)malloc(sizeof(is_func_def));
	ifd->isym = is;
	ifd->id = id;
	ifd->ial = ial;
	ifd->icf = icf;
	ifd->codeLine=linha;
	return ifd;
}

//CONTINUACAO de FUNCAO
is_cont_func* insert_cont_func(is_statement_list* isl)
{
	is_cont_func* icf = (is_cont_func*)malloc(sizeof(is_cont_func));
	icf->u_stmt_list = isl;
		
	
	return icf;
}

//PLUSMINUS
is_plusminus* insert_plusminus(disc_plusminus d, is_id* id)
{
	is_plusminus* ifcall = (is_plusminus*)malloc(sizeof(is_plusminus));
	ifcall->codeLine=linha;
	ifcall->disc_d = d;
	ifcall->id = id;

	return ifcall;
}

//CHAMADA DE FUNCAO
is_func_call* insert_func_call(is_id* id, is_call_list* icl)
{
	is_func_call* ifcall = (is_func_call*)malloc(sizeof(is_func_call));
	ifcall->codeLine=linha;
	ifcall->icl = icl;
	ifcall->id = id;

	return ifcall;
}

//LISTA DE ARGUMENTOS DE CAHAMADA DE FUNCAO
is_call_list* insert_call_list(is_call_list* list, is_type* ty)
{
	is_call_list* icl=(is_call_list*)malloc(sizeof(is_call_list));	//Cria novo nó na lista
	
	icl->ty=ty;				//Preenche-o
	icl->codeLine=linha;
	
	if(list==NULL)		//Se a lista estiver vazia
		return icl;	//Devolve o nó criado

	is_call_list* aux;
			
	for(aux=list; aux->next!=NULL; aux=aux->next);	//procura pelo final da lista
	aux->next=icl;					//adiciona no final da lista
	
	return list;
}

//INSTRUCTION
is_instruction* insert_instruction(disc_instr di, void* instruction)
{
	is_instruction* ii=(is_instruction*)malloc(sizeof(is_instruction));
	ii->disc_d = di;
	
	switch (di)
	{
		case d_atribution:
			ii->data_instr.u_atribution= (is_atribution*) instruction;
			break;
		case d_expression:
			ii->data_instr.u_expression = (is_expression*) instruction;
			break;
		case d_plusminus:
			ii->data_instr.u_plusminus = (is_plusminus*) instruction;
			break;
		default:
			printf("ERRO na inserção de uma instruction!\n");	
	}	
	return ii;		
}

//se é expressao, dizer qual o tipo
is_expression* insert_expression(disc_expr de, void* expression)
{
	is_expression* ie=(is_expression*)malloc(sizeof(is_expression));
	ie->disc_d = de;
	
	switch (de)
	{
		case d_expression_exp:
			ie->data_expr.u_expression= (is_expression*) expression;
			break;
		case d_logic_exp_or_and:
			ie->data_expr.u_logic_exp_or_and= (is_logic_exp_or_and*) expression;
			break;
		case d_logic_exp_not:
			ie->data_expr.u_logic_exp_not = (is_logic_exp_not*) expression;
			break;
		case d_exp_minus_plus:
			ie->data_expr.u_exp_minus_plus = (is_exp_minus_plus*) expression;
			break;	
		case d_aritmetic_exp:
			ie->data_expr.u_aritm_exp = (is_aritmetic_exp*) expression;
			break;
		case d_relac_exp:
			ie->data_expr.u_relac_exp = (is_relac_exp*) expression;
			break;
		case d_type:
			ie->data_expr.u_type = (is_type*) expression;
			break;	
		default:
			printf("ERRO na inserção de uma expression!\n");	
	}	
	return ie;		
}


//is_logic_exp_or_and --> ( <exp1:is_expression><oper:is_oper_l><exp2:is_expression> )
is_logic_exp_or_and *insert_logic_exp_or_and(is_expression *exp1, is_oper_l oper, is_expression *exp2)
{
        is_logic_exp_or_and *ileoa=(is_logic_exp_or_and*)malloc(sizeof(is_logic_exp_or_and));
        ileoa->exp1 = exp1;			//Guarda operando 1
        ileoa->oper = oper;			//Guarda operador
        ileoa->exp2 = exp2;			//Guarda operando 2

        return ileoa;
}

//is_logic_exp_not --> ( <exp:is_expression>)
is_logic_exp_not* insert_logic_exp_not(is_expression *exp)
{
        is_logic_exp_not *ilen=(is_logic_exp_not*)malloc(sizeof(is_logic_exp_not));
        ilen->exp1 = exp;			//Guarda operando 1

        return ilen;
}

//is_exp_minus_plus --> ( <exp:is_expression><oper_a:is_oper_a> )
is_exp_minus_plus* insert_exp_minus_plus(is_expression *exp, is_oper_a oper)
{
        is_exp_minus_plus *iemp=(is_exp_minus_plus*)malloc(sizeof(is_exp_minus_plus));
        iemp->exp = exp;			//Guarda operando 1
	iemp->oper = oper;
        return iemp;
}

//is_aritmetic_exp
is_aritmetic_exp *insert_aritmetic_exp(is_expression *exp1, is_oper_a oper, is_expression *exp2)
{
        is_aritmetic_exp *iae=(is_aritmetic_exp*)malloc(sizeof(is_aritmetic_exp));
        iae->exp1 = exp1;			//Guarda operando 1
        iae->oper = oper;			//Guarda operador
        iae->exp2 = exp2;			//Guarda operando 2

        return iae;
}

//is_relac_exp
is_relac_exp *insert_relac_exp(is_expression *exp1, is_oper_r oper, is_expression *exp2)
{
        is_relac_exp *ire=(is_relac_exp*)malloc(sizeof(is_relac_exp));
        ire->exp1 = exp1;			//Guarda operando 1
        ire->oper = oper;			//Guarda operador
        ire->exp2 = exp2;			//Guarda operando 2

        return ire;
}

//ATRIBUTION LIST
is_atribution_list* insert_atribution_list(disc_atr_lis d, is_atribution_list* head, is_id* id)
{
	is_atribution_list* aux;
	is_atribution_list* ial = (is_atribution_list*)malloc(sizeof(is_atribution_list));
	ial->next = NULL;
	ial->id = id;
	ial->disc_d= d;

	
	// Se não for o primeiro elemento da lista, adiciona-o ao fim da lista
	if (head != NULL)
	{
		for (aux = head; aux->next; aux = aux->next){
			printf("LETRA: %s\n", aux->id->id);
		}
		aux->next = ial;
		return head;
	}

	return ial;
}

is_atribution* insert_atribution(is_atribution_list* ial, is_expression* ie)
{
	is_atribution* ia = (is_atribution*)malloc(sizeof(is_atribution));
	ia->atrib_list = ial;
	ia->expression = ie;

	return ia;
}

//TYPE
is_type* insert_type(disc_type dn, void* type)
{
	is_type* in = (is_type*)malloc(sizeof(is_type));
	in->codeLine=linha;
	in->disc_n = dn;
	
	switch (dn)
	{
		case d_INTEGER:
			in->data_type.integer = *((int*)type);
			break;
		case d_FLOAT:
			in->data_type.fl = *((float*)type);
			break;
		case d_DOUBLE:
			in->data_type.db = *((double*)type);
			break;
		case d_STRING:
			in->data_type.string = ((char*)type);
			break;
		case d_type_ID:
			in->data_type.id = ((is_id*) type);
			break;
		case d_type_func_call:
			in->data_type.fcall = ((is_func_call*) type);
			break;
		case d_BOOL:
			in->data_type.boolean = *((bool*) type);
			break;
		default:
			printf("ERRO na inserção de um type!\n");
	}

	return in;
}

is_id_list* insert_id_list(is_id_list* i_list, is_id* id)
{
	is_id_list* aux;
	is_id_list* iil = (is_id_list*)malloc(sizeof(is_id_list));
	iil->next = NULL;
	iil->id = id;

	// Se não for o primeiro elemento da lista, adiciona-o ao fim da lista
	if (i_list != NULL)
	{
		for (aux=i_list; aux->next; aux = aux->next);
		aux->next = iil;
		return i_list;
	}

	return iil;
}

