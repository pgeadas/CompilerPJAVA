
#include "translate.h"
#include "structures.h"
#include "semantics.h"
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int returncounter=0;
int ifcounter=0;
int printState=0;
int returnState=-1;
int func_calls=-1;
int printType=-1;
int varAmbConcat=0;
int flag=1;
int pass=0;

int declare=0;

int num_if=0;
int num_elseif=0;
int num_while=0;
int num_for=0;
int flag_bc=0;

//pilhas para tratamento dos breaks e continues 
Pilha *pilha_w;
Pilha *pilha_f;
Pilha2 *pilha_ciclos;


//PROGRAM
void translate(is_program* ip)
{
	FILE *dest;
	
	pilha_w=(Pilha*)malloc(sizeof(Pilha));
	pilha_f=(Pilha*)malloc(sizeof(Pilha));
	pilha_ciclos=(Pilha2*)malloc(sizeof(Pilha2));
	
	No_pilha* element = (No_pilha*)malloc(sizeof(No_pilha));
	No_pilha* element2 = (No_pilha*)malloc(sizeof(No_pilha));
	No_pilha2* element3 = (No_pilha2*)malloc(sizeof(No_pilha2));
	
	element->num=-1;
	element->next=NULL;
	
	pilha_w->header=element;
	pilha_w->tail=element;
	pilha_w->size=0;
	
	pilha_f->header=element2;
	pilha_f->tail=element2;
	pilha_f->size=0;
	
	pilha_ciclos->header=element3;
	pilha_ciclos->tail=element3;
	pilha_ciclos->size=0;
	
	
	dest=fopen("result.c", "w");		//Ficheiro de saida sera': "result.c"

	translate_header(dest);
	translate_global(dest, pe);
	translate_class(dest, ip->iclass, pe);
	translate_footer(dest);

	fclose(dest);
	
}

//HEADER
void translate_header(FILE* dest)
{
	fprintf(dest, "#include \"frame.h\"\n");
	fprintf(dest, "#include <stdlib.h>\n");
	fprintf(dest, "#include <stdio.h>\n");
	fprintf(dest, "#include <string.h>\n");
	fprintf(dest, "#include <math.h>\n\n\n");
	fprintf(dest, "#define LINE_MAX 1024\n\n\n"); //TAMANHO MAXIMO PARA LER STRING
	fprintf(dest, "int main()\n{\n");
	fprintf(dest, "int _ra = 0;\n");
	fprintf(dest, "int _last_ra = 0;\n");
	fprintf(dest, "int flag_else = 0;\n"); 		//variavel pa saber se ja entrou num ciclo
	fprintf(dest, "char* buffer;\n");
	fprintf(dest, "buffer = (char*) malloc(sizeof(char));\n");
	fprintf(dest, "void* return_value[100];\n"); 	//variavel que guarda o valor a retornar
	fprintf(dest, "frame* fp=NULL;\n");
	fprintf(dest, "frame* sp=NULL;\n");
}

//GLOBAL LIST
void translate_global(FILE* dest, prog_env* pe)
{
	table_element* gtable=pe->global;

	for(; gtable; gtable=gtable->next){
		if(strcmp(gtable->name, "")!=0)
		translate_global_dec_type(dest, gtable->type, gtable->offset);
	}
	

}

//TIPO DAS VARIAVEIS
void translate_global_dec_type(FILE* dest, disc_type type, int offset)
{
	//Declara variaveis *globais* de acordo com o tipo
	switch(type)
	{
		case d_INTEGER:	fprintf(dest, "int g%d=0;\n", offset); break;
		case d_STRING:	fprintf(dest, "char* g%d=\"\";\n", offset); break;
		case d_DOUBLE:	fprintf(dest, "double g%d=0;\n", offset); break;
		case d_FLOAT:	fprintf(dest, "float g%d=0;\n", offset); break;
		case d_BOOL:   	fprintf(dest, "int g%d=0;\n", offset); break;
		default: break;
	}
}


//CLASS
void translate_class(FILE* dest, is_class* iclass, prog_env* pe)
{
	is_class* aux=iclass;
	is_dec_list* idl;
	if(iclass->idecl!=NULL){
		idl = iclass->idecl->dec_list;
	}
	else{
		translate_func_list(dest, aux->ifl,pe);
		return;
	}
	for(; aux->icla; aux=aux->icla){
		idl=aux->idecl->dec_list;
		if(idl!=NULL){
			if(idl->next==NULL){
				
				translate_atr_globals(dest, pe, idl->atr);
			}
			else{
				
				for(; idl; idl = idl->next)
				{
					translate_atr_globals(dest, pe, idl->atr);
				}
			}
		}		
	}

	translate_func_list(dest, aux->ifl,pe);
}

//ATR GLOBALS
void translate_atr_globals(FILE* dest, prog_env* pe, is_atr* idec){
	if(idec==NULL)
		return;

	if(idec->disc_n==d_atribution_atr){
		if(idec->data_atr.u_atribution==NULL)
			return;
		is_atribution* ia = idec->data_atr.u_atribution;
	
		if(ia->atrib_list==NULL)
			return;

		returnState=0;
		translate_atrib_list_globals(dest, pe, ia->atrib_list);
		translate_expression(dest, ia->expression, NULL, pe);
		fprintf(dest,";\n");
	}
}

//ATRIB LIST GLOBALS
void translate_atrib_list_globals(FILE* dest , prog_env *pe, is_atribution_list *ial)
{
	is_atribution_list *aux;
	table_element* t;
	if(ial==NULL)
		return;

	for(aux=ial; aux; aux = aux->next){
		t=lookup(pe->global, aux->id->id);

		switch(ial->disc_d){
			case d_EQUAL:
				fprintf(dest, "g%d = ", t->offset);
				break;
			case d_MINUSEQUAL:
				fprintf(dest, "g%d = g%d - ", t->offset, t->offset);
				break;
			case d_PLUSEQUAL:
				fprintf(dest, "g%d = g%d + ", t->offset, t->offset);
				break;
			default: break;
		}	
	}
}


//ATRIB LIST
void translate_atrib_list(FILE* dest , prog_env *pe, environment_list* el, is_atribution_list *ial)
{
	is_atribution_list *aux;
	table_element* t;
	if(ial==NULL)
		return;

	for(aux=ial; aux; aux = aux->next){
		t=lookup(el->locals, aux->id->id);

		if(t==NULL)
		{
			t=lookup(pe->global, aux->id->id);
			switch(ial->disc_d){

				case d_EQUAL:
					fprintf(dest, "g%d = ", t->offset);
					break;
				case d_MINUSEQUAL:
					fprintf(dest, "g%d = g%d - ", t->offset, t->offset);
					break;
				case d_PLUSEQUAL:
					fprintf(dest, "g%d = g%d + ", t->offset, t->offset);
					break;
				default: break;
			}
		}
		else
		{
			
			switch(ial->disc_d){
				
				case d_EQUAL:
					translate_args(dest, t->type);
					fprintf(dest, "sp->locals[%d]) = ", t->offset);
					break;
				case d_MINUSEQUAL:
					translate_args(dest, t->type);
					fprintf(dest, "sp->locals[%d]) = ", t->offset);
					translate_args(dest, t->type);
					fprintf(dest, "sp->locals[%d]) - ", t->offset);
					break;
				case d_PLUSEQUAL:
					translate_args(dest, t->type);
					fprintf(dest, "sp->locals[%d]) = ", t->offset);
					translate_args(dest, t->type);
					fprintf(dest, "sp->locals[%d]) + ", t->offset);
					break;
				default: break;
			}
		}		
	}
	
}

//FUNC LIST
void translate_func_list(FILE* dest, is_func_list* ifl,prog_env* pe)
{
	is_func_list* aux = ifl;
	environment_list* el = pe->procs; 

	
	for(; aux; aux=aux->next, el=el->next){
		
		if(strcmp(aux->ifdef->id->id, "")==0)//serve para sincronizar o funcdef com o environment_list
			aux=aux->next;

		if(strcmp(el->name, "")==0)
			el=el->next;
		
		if(strcmp(aux->ifdef->id->id, el->name)==0){
		
			translate_func_def(dest, aux->ifdef,el,pe);
	
		}
	}


}

//FUNC DEF
void translate_func_def(FILE* dest, is_func_def* ifdef, environment_list* el, prog_env* pe)
{
	returnState=-1;
	if(strcmp(el->name, "main")==0){
		printf("----MAIN ENCONTRADA----\n");
		translate_main(dest, ifdef, el, pe);
	}
	else{
		translate_function(dest, ifdef, el, pe);
	}
}


//FUNCTION
void translate_function(FILE* dest, is_func_def* ifdef, environment_list* el, prog_env* pe)
{
	
	el->passagem=0;

	//Prologo
	fprintf(dest, "\n/*BLOCO DO PROCEDIMENTO %s*/\n", ifdef->id->id); 
	fprintf(dest, "/*Prologo*/\n");
	fprintf(dest, "goto %sskip;\n", ifdef->id->id);
	fprintf(dest, "%s:\n",ifdef->id->id);			//Label do procedimento	

	fprintf(dest, "fp=sp;\n");				//Guarda do endereco da frame anterior (sp), no frame pointer (fp)
	fprintf(dest, "sp=(frame*)malloc(sizeof(frame));\n");	//Criacao de uma nova frame, identificada com com o Stack Pointer (sp)
	fprintf(dest, "sp->frame_buffer=(char*) malloc (sizeof(char));\n");
	fprintf(dest, "sp->parent=fp;\n");			//Guarda do endereco para a frame anterior, na propria frame
	fprintf(dest, "sp->return_address=_ra;\n");		//Guarda do endereco de retorno (por norma existente no registo _ra), na frame

	fprintf(dest, "\n/*DECLARATIONS*/\n");
	translate_declare_locals(dest, el, pe);  //DECLARA AS LOCAIS
	fprintf(dest, "\n/*ARGUMENTS ATRIBUTION*/\n");
	translate_arg_list(dest, ifdef->ial, el, pe); //IGUALA OS ARGUMENTOS AO OUTGOING
	//Corpo do procedimento
	fprintf(dest, "\n/*Corpo do procedimento*/\n");

	translate_cont_func(dest, ifdef->icf, el, pe);

	if(returnState==-1){
		//Epilogo
		fprintf(dest, "\n/*Epilogo*/\n");
		fprintf(dest, "_last_ra=_ra;\n");
		fprintf(dest, "_ra=sp->return_address;\n");		//Restauro do valor de retorno, a ser utilizando aquando do redireccionamento do fluxo
		fprintf(dest, "sp=sp->parent;\n");			//"pop" da pilha de frames
		fprintf(dest, "fp=sp->parent;\n");			//actualizacao do registo FP de acordo
		fprintf(dest, "goto redirector;\n");			//Instrucao especifica para a nossa implementacao em C "restringido"
	}
	fprintf(dest, "%sskip:\n", ifdef->id->id); 			//label para acesso Ã  instruccao seguinte ao cÃ³digo do procedimento (para evitar ser executado inadvertidamente)
	
}

//CONT FUNC
void translate_cont_func(FILE* dest, is_cont_func* icf, environment_list* el, prog_env* pe)
{
	if(icf==NULL){
		return;
	}
	
	translate_statement_list(dest,  icf->u_stmt_list,  el, pe);
}



//MAIN
void translate_main(FILE* dest, is_func_def* main, environment_list* el, prog_env* pe)
{
	el->passagem=1;
	fprintf(dest, "\n/*BLOCO MAIN */\n");
	fprintf(dest, "sp=(frame*)malloc(sizeof(frame));\n");
	fprintf(dest, "sp->frame_buffer=(char*) malloc (sizeof(char));\n");
	//translate_arg_list(dest, main->ial, local, pe); //NO NOSSO CASO DA MAIN NAO TEM ARGUMENTOS, MAS FICA AQUI PARA CASO QUEIRAMOS FAZER O EXTRA DE RECEBER DA LINHA DE COMANDOS
	fprintf(dest, "\n/*DECLARATIONS */\n");
	translate_declare_locals(dest, el, pe);
	translate_cont_func(dest, main->icf, el, pe);	
}

//ARG LIST
void translate_arg_list(FILE* dest,  is_arg_list* ial, environment_list* el, prog_env* pe)
{
	
	if(ial==NULL){
		return;
	}
		
	translate_args_outgoing(dest, el->arguments, pe);
	
}

//IGUALAR ARGUMENTOS AOS OUTGOINGS
void translate_args_outgoing(FILE* dest, table_element* args, prog_env *pe){
	table_element* aux;
	for(aux=args; aux; aux=aux->next){
		
		translate_args(dest, aux->type);
		fprintf(dest, "sp->locals[%d])= ", aux->offset);
		translate_args(dest, aux->type);
		fprintf(dest, "fp->outgoing[%d]);\n", aux->offset);
	}
}

//TIPO ARGS
void translate_args(FILE* dest, disc_type type)
{
	//Declara variaveis *globais* de acordo com o tipo
	switch(type)
	{
		case d_INTEGER:	fprintf(dest, "*((int*)"); break;
		case d_STRING:	
			if(printState==0)
				fprintf(dest, "("); 
			else
				fprintf(dest, "((char*)"); 
			break;
		case d_DOUBLE:	fprintf(dest, "*((double*)"); break;
		case d_FLOAT:	fprintf(dest, "*((float*)"); break;
		case d_BOOL:	fprintf(dest, "*((int*)"); break;
		default:break;
	}
}

//DECLARE LOCALS
void translate_declare_locals(FILE* dest,  environment_list* el, prog_env* pe)
{
	table_element* locals=el->locals;

	for(;locals; locals=locals->next){
		translate_local_dec_type(dest, locals, locals->type);
	}

}

//ATRIBUTION
void translate_atribution(FILE* dest,  is_atribution* ia , environment_list* el, prog_env* pe)
{
	if(el->passagem==1){
		translate_expression_first(dest, ia->expression, el, pe);
		if(declare==0)
			return;
	}
	declare=0;	
	
	returnState=0;
	translate_atrib_list(dest, pe, el,ia->atrib_list);
	translate_expression(dest, ia->expression, el, pe);
	fprintf(dest,";\n");
}

//LOCALS VAR DECLARE
void translate_local_dec_type(FILE* dest, table_element* t, disc_type dt)
{

	switch(dt)
	{
		case d_INTEGER:	fprintf(dest, "sp->locals[%d]=(int*)malloc(sizeof(int));\n", t->offset); 
				fprintf(dest, "*((int*)sp->locals[%d])=0;\n", t->offset); 
				break;
		case d_STRING:	fprintf(dest, "sp->locals[%d]=(char*)malloc(sizeof(char));\n", t->offset); //LINE_MAX *
				fprintf(dest, "sp->locals[%d]=\"\";\n", t->offset);
				break;
		case d_DOUBLE:	fprintf(dest, "sp->locals[%d]=(double*)malloc(sizeof(double));\n", t->offset); 
				fprintf(dest, "*((double*)sp->locals[%d])=0;\n", t->offset);			
				break;
		case d_FLOAT:   fprintf(dest, "sp->locals[%d]=(float*)malloc(sizeof(float));\n", t->offset); 
				fprintf(dest, "*((float*)sp->locals[%d])=0;\n", t->offset);	
				break;
		case d_BOOL:	fprintf(dest, "sp->locals[%d]=(int*)malloc(sizeof(int));\n", t->offset); 
				fprintf(dest, "*((int*)sp->locals[%d])=0;\n", t->offset);	
				break;
		default: break;
	}
}

//STATEMENT LIST
void translate_statement_list(FILE* dest,  is_statement_list* isl, environment_list* el, prog_env* pe)
{
	fprintf(dest, "\n/*STATEMENTS */\n");
	is_statement_list* aux;
	for(aux=isl; aux; aux=aux->next){
		translate_statement(dest, aux->statement, el, pe);
		fprintf(dest,";\n");	
	}
}


//STATEMENT
void translate_statement(FILE* dest,  is_statement* is , environment_list* el, prog_env* pe)
{
	func_calls=-1;
	
	switch (is->disc_d)
	{
		case d_instruction:
			if(is->data_statement.u_instruction->disc_d==d_atribution){
				el->passagem=1;
				translate_instruction(dest, is->data_statement.u_instruction, el, pe);
				el->passagem=0;	
			}
			translate_instruction(dest, is->data_statement.u_instruction, el, pe);			
			break;
			
		case d_compound_statement:
			translate_compound_statement(dest, is->data_statement.u_compound_statement, el, pe);
			break;
			
		case d_println_statement:
			translate_println_statement(dest, is->data_statement.u_println_statement, el, pe);		
			break;
			
		case d_declaration:
			translate_declaration(dest, el, pe, is->data_statement.u_declaration);
			break;
			
		case d_return_statement:
			translate_return_statement(dest, is->data_statement.u_return_statement, el, pe);		
			break;
			
		case d_func_call:
			translate_is_func_call(dest, el, pe, is->data_statement.u_func_call);
			break;
			
		case d_read_statement:
			translate_read_statement(dest, el, pe, is->data_statement.u_read_statement);
			break;
		case d_concat:
			translate_concat(dest, el, pe, is->data_statement.u_concat);
			break;
		case d_break_cont:
			translate_break_cont(dest, el, pe, is->data_statement.u_break_cont);
			break;
		default: 
			break;
	}
}

//BREAK CONT
void translate_break_cont(FILE* dest,environment_list* el, prog_env *pe, is_break_cont* ibc)
{
	//tira das pilhas os valores respectivos para colocar no print final os nomes certos
	int tmp_w = pop(pilha_w);
	int tmp_f = pop(pilha_f);
	char where=pop2(pilha_ciclos);
	
	switch(ibc->disc_bc)
	{
		case is_BREAK:
			fprintf(dest, "/* BREAK */\n");
			if(flag_bc>0){
				if(where=='w'){
					fprintf(dest, "goto breakw%d;\n",tmp_w);
					}
				else{
					fprintf(dest, "goto breakf%d;\n",tmp_f);
						
					}
			}
				
		break;
		case is_CONTINUE:
			fprintf(dest, "/* CONTINUE */ \n");
			if(flag_bc>0){
				if(where=='w'){
					fprintf(dest, "goto continuew%d;\n",tmp_w);
					}
				else{
					fprintf(dest, "goto continuef%d;\n",tmp_f);
				}
			}
		break;
	
	
	}

}



//CONCAT
void translate_concat(FILE* dest, environment_list* el, prog_env *pe, is_concat* ic){
	translate_concat_args(dest, el, pe, ic->icargs);
}

//CONCAT ARGS
void translate_concat_args(FILE* dest, environment_list* el, prog_env *pe, is_concat_args* icargs){
	
	int offsetC=0; //offset da variavel que vai guardar a concatenacao
	fprintf(dest, "\n/*CONCAT */\n");
	fprintf(dest, "sp->frame_buffer=(char*) malloc (2048 * sizeof(char));\n");
	fprintf(dest, "strcpy(sp->frame_buffer, \"\");\n");
	is_concat_args* aux;
	if(icargs->next==NULL){
		offsetC=translate_type_concat(dest, el, pe, icargs->ity1,1);
		translate_type_first(dest, icargs->ity2, el , pe);
		translate_type_concat(dest, el, pe, icargs->ity2,0);
	}
	else{
		offsetC=translate_type_concat(dest, el, pe, icargs->ity1, 1);

		aux=icargs->next;

		if(aux->next==NULL){
			translate_type_first(dest, aux->ity1, el , pe);
			translate_type_concat(dest, el, pe, aux->ity1, 0);
			translate_type_first(dest, aux->ity2, el , pe);
			translate_type_concat(dest, el, pe, aux->ity2, 0);
		}
		else{
			for(; aux->next; aux=aux->next){
				translate_type_first(dest, aux->ity1, el , pe);
				translate_type_concat(dest, el, pe, aux->ity1, 0);	
			}
			translate_type_first(dest, aux->ity1, el , pe);
			translate_type_concat(dest, el, pe, aux->ity1, 0);
			translate_type_first(dest, aux->ity2, el , pe);
			translate_type_concat(dest, el, pe, aux->ity2, 0);
		}
	}

	if(varAmbConcat==1){
			fprintf(dest, "g%d = (char*) malloc (strlen(sp->frame_buffer)+1*sizeof(char));\n", offsetC);
			fprintf(dest, "strcpy(g%d, sp->frame_buffer;\n", offsetC);
		
	}
	else{	
			fprintf(dest, "sp->locals[%d]=(char*)malloc(strlen(sp->frame_buffer)+1*sizeof(char));\n", offsetC);
			fprintf(dest, "strcpy(sp->locals[%d], sp->frame_buffer);\n", offsetC);
	}
}


//TYPE CONCAT
int translate_type_concat(FILE* dest, environment_list* el , prog_env *pe, is_type* ity, int operacao){
	table_element* t;
	environment_list* procFunc;
	
	switch(ity->disc_n){
		case d_type_ID:
			t=lookup(el->locals, ity->data_type.id->id);
			varAmbConcat=0;//Para saber que e' local
			if(t==NULL){
				t=lookup(pe->global, ity->data_type.id->id);
				varAmbConcat=1;//Para saber que e' global
			}
			if(operacao==1){
				return t->offset;
			}
			else if(1){
				if(varAmbConcat==1)
				{
					if(t->type==d_STRING){
						fprintf(dest, "strcat(sp->frame_buffer, g%d);\n", t->offset);
					}
					else{
						fprintf(dest, "buffer=(char*) malloc (sizeof(char));\n");
						fprintf(dest, "sprintf(buffer, \"");
						translate_var_print(dest, t->type);
						fprintf(dest, "\", g%d);\n",  t->offset);
						fprintf(dest, "strcat(sp->frame_buffer, buffer);\n");
					}
				}
				else{
					if(t->type==d_STRING){
						fprintf(dest, "strcat(sp->frame_buffer, sp->locals[%d]);\n", t->offset);
					}
					else{
						fprintf(dest, "buffer=(char*) malloc (sizeof(char));\n");
						fprintf(dest, "sprintf(buffer, \"");
						translate_var_print(dest, t->type);
						fprintf(dest, "\", ");
						translate_args(dest, t->type);
						fprintf(dest, " sp->locals[%d]));\n",  t->offset);
						fprintf(dest, "strcat(sp->frame_buffer, buffer);\n");
					}
				}
			}

			break;

		case d_type_func_call:
			procFunc=plookup(pe->procs, ity->data_type.fcall->id->id);

			if(procFunc->type==d_STRING){
				fprintf(dest, "strcat(sp->frame_buffer, return_value[_last_ra]);\n");
			}
			else{
				fprintf(dest, "buffer=(char*) malloc (sizeof(char));\n");
				fprintf(dest, "sprintf(buffer, \"");
				translate_var_print(dest, procFunc->type);
				fprintf(dest, "\", ");
				translate_args(dest, procFunc->type);
				fprintf(dest, " return_value[_last_ra]));\n");
				fprintf(dest, "strcat(sp->frame_buffer, buffer);\n");
			}
			break;

		case d_INTEGER:
			fprintf(dest, "buffer=(char*) malloc (sizeof(char));\n");
			fprintf(dest, "sprintf(buffer, \"");
			translate_var_print(dest, d_INTEGER);
			fprintf(dest, "\", %d);\n", ity->data_type.integer);
			fprintf(dest, "strcat(sp->frame_buffer, buffer);\n");
			break;

		case d_DOUBLE:
			fprintf(dest, "buffer=(char*) malloc (sizeof(char));\n");
			fprintf(dest, "sprintf(buffer, \"");
			translate_var_print(dest, d_DOUBLE);
			fprintf(dest, "\", %lf);\n", ity->data_type.db);
			fprintf(dest, "strcat(sp->frame_buffer, buffer);\n");
			break;
			
		case d_FLOAT:
			fprintf(dest, "buffer=(char*) malloc (sizeof(char));\n");
			fprintf(dest, "sprintf(buffer, \"");
			translate_var_print(dest, d_FLOAT);
			fprintf(dest, "\", %f);\n", ity->data_type.fl);
			fprintf(dest, "strcat(sp->frame_buffer, buffer);\n");
			break;

		case d_STRING:
			fprintf(dest, "strcat(sp->frame_buffer,%s);\n", ity->data_type.string);
			break;
			
		case d_BOOL:
			if(ity->data_type.boolean)
				fprintf(dest, "strcat(sp->frame_buffer,\"True\");\n");
			else
				fprintf(dest, "strcat(sp->frame_buffer,\"False\");\n");
			break;
		default: break;
	}


	return 0;

}


//PRINTLN STATEMENT
void translate_println_statement(FILE* dest, is_println_statement* ips, environment_list* el, prog_env* pe)
{
	printState=1;

	if(ips->disc_d==d_PRINTLN){
		printType=1;
	}
	else{
		printType=2;
	}

	translate_println_args(dest, ips->ipargs, el, pe);
	printType=0;
	printState=0;
}

//PRINTLN ARGS
void translate_println_args(FILE* dest, is_println_args* ipa, environment_list* el, prog_env* pe){

	fprintf(dest, "\n/*PRINT */\n");
	fprintf(dest, "sp->frame_buffer=(char*) malloc (2048*sizeof(char));\n");
	fprintf(dest, "strcpy(sp->frame_buffer, \"\");\n");
	is_println_args* aux;
	if(ipa->next==NULL){
		translate_type_first(dest, ipa->ity, el , pe);
		translate_type_print(dest, ipa->ity, el, pe);
	}
	else{
		for(aux=ipa; aux; aux=aux->next){
			translate_type_first(dest, aux->ity, el , pe);
			translate_type_print(dest, aux->ity, el, pe);	
		}
	}
	if(printType==1)
		fprintf(dest, "printf(\"%%s\\n\", sp->frame_buffer);\n");
	else
		fprintf(dest, "printf(\"%%s\", sp->frame_buffer);\n");
}

//TYPE PRINT
void translate_type_print(FILE* dest, is_type* ity, environment_list* el , prog_env *pe){
	table_element* t;
	environment_list* procFunc;
	switch(ity->disc_n){
		case d_type_ID:
			t=lookup(el->locals, ity->data_type.id->id);
			varAmbConcat=0;//Para saber que e' local
			if(t==NULL){
				t=lookup(pe->global, ity->data_type.id->id);
				varAmbConcat=1;//Para saber que e' global
			}
			
			if(varAmbConcat==1)
			{
				if(t->type==d_STRING){
					fprintf(dest, "strcat(sp->frame_buffer, g%d);\n", t->offset);
				}
				else{
					fprintf(dest, "buffer=(char*) malloc (sizeof(char));\n");
					fprintf(dest, "sprintf(buffer, \"");
					translate_var_print(dest, t->type);
					fprintf(dest, "\", g%d);\n",  t->offset);
					fprintf(dest, "strcat(sp->frame_buffer, buffer);\n");
				}
			}
			else{
				if(t->type==d_STRING){
					fprintf(dest, "strcat(sp->frame_buffer,sp->locals[%d]);\n", t->offset);
				}
				else{
					fprintf(dest, "buffer=(char*) malloc (sizeof(char));\n");
					fprintf(dest, "sprintf(buffer, \"");
					translate_var_print(dest, t->type);
					fprintf(dest, "\", ");
					translate_args(dest, t->type);
					fprintf(dest, " sp->locals[%d]));\n",  t->offset);
					fprintf(dest, "strcat(sp->frame_buffer, buffer);\n");
				}
			}

			break;

		case d_type_func_call:
			procFunc=plookup(pe->procs, ity->data_type.fcall->id->id);

			if(procFunc->type==d_STRING){
				fprintf(dest, "strcat(sp->frame_buffer, return_value[_last_ra]);\n");
			}
			else{
				fprintf(dest, "buffer=(char*) malloc (sizeof(char));\n");
				fprintf(dest, "sprintf(buffer, \"");
				translate_var_print(dest, procFunc->type);
				fprintf(dest, "\", ");
				translate_args(dest, procFunc->type);
				fprintf(dest, " return_value[_last_ra]));\n");
				fprintf(dest, "strcat(sp->frame_buffer, buffer);\n");
			}
			break;

		case d_INTEGER:
			fprintf(dest, "buffer=(char*) malloc (sizeof(char));\n");
			fprintf(dest, "sprintf(buffer, \"");
			translate_var_print(dest, d_INTEGER);
			fprintf(dest, "\", %d);\n", ity->data_type.integer);
			fprintf(dest, "strcat(sp->frame_buffer, buffer);\n");
			break;

		case d_DOUBLE:
			fprintf(dest, "buffer=(char*) malloc (sizeof(char));\n");
			fprintf(dest, "sprintf(buffer, \"");
			translate_var_print(dest, d_DOUBLE);
			fprintf(dest, "\", %lf);\n", ity->data_type.db);
			fprintf(dest, "strcat(sp->frame_buffer, buffer);\n");
			break;
			
		case d_FLOAT:
			fprintf(dest, "buffer=(char*) malloc (sizeof(char));\n");
			fprintf(dest, "sprintf(buffer, \"");
			translate_var_print(dest, d_FLOAT);
			fprintf(dest, "\", %f);\n", ity->data_type.fl);
			fprintf(dest, "strcat(sp->frame_buffer, buffer);\n");
			break;

		case d_STRING:
			fprintf(dest, "strcat(sp->frame_buffer,%s);\n", ity->data_type.string);
			break;
			
			
		case d_BOOL:
			if(ity->data_type.boolean)
				fprintf(dest, "strcat(sp->frame_buffer,\"True\");\n");
			else
				fprintf(dest, "strcat(sp->frame_buffer,\"False\");\n");
			break;
		default: break;
	}
}



//READLINE STATEMENT
void translate_readln_statement(FILE* dest, table_element* newel, int flag)
{
	
	if(flag==0){
		fprintf(dest, "fgets(buffer, LINE_MAX, stdin);\n");
		fprintf(dest, "sp->locals[%d]=(char*)malloc(strlen(buffer+1)*sizeof(char));\n", newel->offset);
		fprintf(dest, "strcpy(sp->locals[%d], buffer);\n", newel->offset);
		
	}
	else{
		fprintf(dest,"fgets(g[%d], LINE_MAX, stdin);\n",newel->offset);
		}
	
		

}

//READ STATEMENT
void translate_read_statement(FILE* dest, environment_list* el, prog_env *pe, is_read_statement* irs)
{
	int flag=0;
	table_element* newel = lookup(el->locals,irs->id->id);
	
	
	if(newel==NULL)
	{
		 newel = lookup(pe->global,irs->id->id);
		 flag=1;
	}
	
	if(irs->disc_d==d_READLINE){ translate_readln_statement(dest, newel, flag); return;}
	
	switch(newel->type)
	{
		case d_INTEGER: 
			if(flag==0)
				fprintf(dest,"scanf(\"%%d\", ((int*) sp->locals[%d])",newel->offset);
			else
				fprintf(dest,"scanf(\"%%d\", &g%d",newel->offset);
			break;
		case d_DOUBLE: 	
			if(flag==0)
				fprintf(dest,"scanf(\"%%lf\", ((double*) sp->locals[%d])",newel->offset);
			else
				fprintf(dest,"scanf(\"%%lf\", &g%d",newel->offset);
			break;
		case d_FLOAT: 	
			if(flag==0)
				fprintf(dest,"scanf(\"%%f\", ((float*) sp->locals[%d])",newel->offset);
			else
				fprintf(dest,"scanf(\"%%f\", g%d",newel->offset);
			break;
		case d_STRING: 	
			if(flag==0){
				fprintf(dest,"fgets(buffer, LINE_MAX, stdin);\n");
				fprintf(dest, "sp->locals[%d]=(char*)malloc(strlen(buffer+1)*sizeof(char));\n", newel->offset);
				fprintf(dest, "strcpy(sp->locals[%d], buffer", newel->offset);
			}
			else
				fprintf(dest,"fgets(g[%d], LINE_MAX, stdin",newel->offset);
		
			break;
		default:
			break;	
	}
	fprintf(dest,");\n");
	
	if(newel->type!=d_STRING){
		fprintf(dest,"fgets(buffer,LINE_MAX,stdin);\n");
	}
	


}

//COMPOUND STATEMENT
void translate_compound_statement(FILE* dest, is_compound_statement* ics, environment_list* el, prog_env *pe)
{	
	
	switch(ics->disc_cs)
	{
		case d_if_statement: 
			translate_if_statement(dest, ics->data_compound_statement.u_stmt_if, el, pe);
			break;
		case d_while_statement: 
			push2('w',pilha_ciclos); 
			
			translate_while_statement(dest, ics->data_compound_statement.u_stmt_while, el, pe);
			break;
		case d_for_statement:
			push2('f',pilha_ciclos); 
			
			translate_for_statement(dest, ics->data_compound_statement.u_stmt_for, el, pe);
			break;
	}

}

//FOR STATEMENT
void translate_for_statement(FILE* dest, is_for_statement* ifs, environment_list* el, prog_env *pe)
{

	int tmp_for = num_for;
	
	pass=el->passagem;
	fprintf(dest, "\n/*Estrutura FOR*/\n");
	num_for++;
	
	//mete o numero do for na pilha respectiva
	push(tmp_for,pilha_f);

	
	translate_for_args(dest,ifs->ifarg1, el, pe);
	fprintf(dest, ";\n");
	translate_expression_first(dest, ifs->ire->exp1, el, pe);
	translate_expression_first(dest, ifs->ire->exp2, el, pe);
	fprintf(dest, "if(");
	translate_relac_exp(dest,ifs->ire, el, pe);
	fprintf(dest, ")\tgoto for%d;\n",tmp_for);
	fprintf(dest, "\tgoto endfor%d;\n",tmp_for);
	fprintf(dest, "\nfor%d:\n",tmp_for);
	
	flag_bc ++;	
	translate_cont_statement(dest,ifs->ics, el, pe);
	fprintf(dest, "continuef%d:\n",tmp_for);
	fprintf(dest, "endfor%d:\n",tmp_for);
	translate_for_args(dest,ifs->ifarg2, el, pe);
	fprintf(dest, ";\n");

	translate_expression_first(dest, ifs->ire->exp1, el, pe);
	translate_expression_first(dest, ifs->ire->exp2, el, pe);
	fprintf(dest, "	if(");
	translate_relac_exp(dest,ifs->ire, el, pe);
	fprintf(dest, ")\tgoto for%d;\n",tmp_for);
	fprintf(dest,"breakf%d:\n",tmp_for);

	el->passagem=pass;	
	

}

//FOR ARGS
void translate_for_args(FILE *dest, is_for_args* ifa, environment_list* el, prog_env *pe)
{
	//Caso em que o argumento seja NULL
	if(ifa==NULL){
		return;
	}
		
	switch(ifa->disc_n){
		case d_for_declaration:
			translate_declaration(dest, el, pe, ifa->data_for_args.u_declaration);
			break;
			
		case d_for_dec_list:
			translate_dec_list( dest, el, pe, ifa->data_for_args.u_dec_list);
			break;
		case d_for_plusminus:
			translate_plusminus(dest, ifa->data_for_args.u_plusminus, el, pe);
			break;
	}
	return;
}


//WHILE STATEMENT
void translate_while_statement(FILE* dest, is_while_statement* iws, environment_list* el, prog_env *pe){

	int tmp_while = num_while;
	fprintf(dest, "\n	/*Estrutura WHILE*/\n");
	num_while++;
	
	//mete o numero do while na pilha respectiva
	push(tmp_while,pilha_w);

	pass=el->passagem;
	find_expression(dest, iws->instr, el, pe);
	fprintf(dest, "	if(");
	translate_instruction(dest,iws->instr, el, pe);
	fprintf(dest, ")\tgoto while%d;\n",tmp_while);
	fprintf(dest, "goto endwhile%d\n;",tmp_while);
	
	fprintf(dest, "while%d:\n",tmp_while);
	flag_bc++;

	translate_cont_statement(dest,iws->iconts, el, pe);
	fprintf(dest, ";\ncontinuew%d:\n",tmp_while);
	fprintf(dest, "endwhile%d:\n",tmp_while);
	find_expression(dest, iws->instr, el, pe);

	fprintf(dest, "	if(");
	translate_instruction(dest,iws->instr, el, pe);
	fprintf(dest, ")\tgoto while%d;\n",tmp_while);
	fprintf(dest,"breakw%d:\n", tmp_while);
	el->passagem=pass;

}

//PROCURA E ENVIA EXPRESSION PARA O FIRST
void find_expression(FILE* dest, is_instruction* instr, environment_list* el, prog_env *pe){
	if(instr->disc_d==d_expression)
		translate_expression_first(dest, instr->data_instr.u_expression, el, pe);
	else if(instr->disc_d==d_atribution)
		translate_expression_first(dest, instr->data_instr.u_atribution->expression, el, pe);
	
}

//IF STATEMENT
void translate_if_statement(FILE* dest, is_if_statement* iis, environment_list* el, prog_env *pe){

	int tmp_if = num_if;
	num_if++;
	find_expression(dest, iis->instr, el, pe);
	fprintf(dest, "\n	/*Estrutura IF*/\n");
	pass=el->passagem;
	el->passagem=0;
	if(iis->ielses==NULL && iis->ieisl==NULL){ //caso em que e so 1 if
		fprintf(dest, "	if(");
		translate_instruction(dest,iis->instr, el, pe);
		fprintf(dest, ")\t");
		fprintf(dest,"	goto then%d;\n",tmp_if);
		fprintf(dest,"goto endif%d;\n", tmp_if);
		fprintf(dest,"then%d:\n",tmp_if);
		translate_cont_statement(dest,iis->iconts, el, pe);
		fprintf(dest,"endif%d:\n", tmp_if);
	}
	else if(iis->ielses!=NULL &&  iis->ieisl==NULL){ //caso em que e um if e 1 else
		fprintf(dest, "	if(");
		translate_instruction(dest,iis->instr, el, pe);
		fprintf(dest, ")\t");
		fprintf(dest,"	goto then%d;\n",tmp_if);
		fprintf(dest,"goto else%d;\n",tmp_if);
		translate_else_statement(dest, iis->ielses, el, pe);
		fprintf(dest,"then%d:\n",tmp_if);
		translate_cont_statement(dest,iis->iconts, el, pe);
		fprintf(dest,"endif%d:\n", tmp_if);
	
	}else if(iis->ielses==NULL &&  iis->ieisl!=NULL){ // caso em que e 1 if e varios elsifs
		fprintf(dest, "	if(");
		translate_instruction(dest,iis->instr, el, pe);
		fprintf(dest, ")\t");
		fprintf(dest,"	goto then%d;\n",tmp_if);
		
		translate_elseif_statement_list(dest,iis->ieisl, el, pe);
		fprintf(dest,"	goto endif%d;\n", tmp_if);
		fprintf(dest,"then%d:\n",tmp_if);
		translate_cont_statement(dest,iis->iconts, el, pe);
		fprintf(dest,"endif%d:\n", tmp_if);
	
	
	}
	else{ //caso em que e 1 if, varios elsifs e um else
		fprintf(dest, "	if(");
		translate_instruction(dest,iis->instr, el, pe);
		fprintf(dest, ")\t");
		fprintf(dest,"	goto then%d;\n",tmp_if);
		translate_elseif_statement_list(dest,iis->ieisl, el, pe);
		fprintf(dest,"	goto else%d;\n", tmp_if);
		translate_else_statement(dest, iis->ielses, el, pe);
		
		fprintf(dest,"then%d:\n",tmp_if);
		translate_cont_statement(dest,iis->iconts, el, pe);
		fprintf(dest,"endif%d:\n", tmp_if);
	}
	
	fprintf(dest,"flag_else=0;\n");
	el->passagem=pass;
}

//ELSE
void translate_else_statement(FILE* dest, is_else_statement* ise, environment_list* el, prog_env *pe)
{
	int tmp_if = num_if-1;
	
	if ( ise == NULL ){
		return;
	}
	
	fprintf(dest, "\n	/*Estrutura ELSE*/\n");
	
	fprintf(dest,"else%d:\n", tmp_if);
	fprintf(dest,"if(flag_else==1) goto endif%d;\n",tmp_if);
	// Faz a tradução do conteudo do ELSE
	translate_cont_statement(dest,ise->iconts, el, pe);

	fprintf(dest,";\ngoto endif%d;\n", tmp_if);
}

//CONT_STATEMENT
void translate_cont_statement(FILE* dest, is_cont_statement* ics, environment_list* el, prog_env *pe )
{
		
	switch(ics->disc_cts)
	{
		case d_statement:
			translate_statement(dest,  ics->data_cont_statement.u_stmt,  el, pe);
			break;
		
		case d_statement_list:
			translate_statement_list(dest,  ics->data_cont_statement.u_stmt_list,  el, pe);
			break;	
	}
	
	fprintf(dest,";\n");
	return;
}



//ELSEIF LIST
void translate_elseif_statement_list(FILE* dest , is_elseif_statement_list* ieisl, environment_list* el, prog_env *pe)
{
	is_elseif_statement_list* aux = ieisl;
	int tmp_elseif= num_elseif;
	
	for(;aux;aux=aux->next){

		translate_elseif_statement(dest, aux->ielseifs, el, pe);
		
		tmp_elseif++;
		fprintf(dest,";\n");
	}
	

}

//ELSE IF STATEMENT
void translate_elseif_statement(FILE* dest, is_elseif_statement* ieis, environment_list* el, prog_env *pe)
{

	int tmp_if = num_if ;
	int tmp_elseif = num_elseif;
	
	pass=el->passagem;
	el->passagem=0;
	fprintf(dest, "\n	/*Estrutura ELSE IF*/\n");
	
	fprintf(dest,"goto elseif%d_%d;\n", tmp_if, tmp_elseif);
	fprintf(dest,"elseif%d_%d:\n", tmp_if, tmp_elseif);
	find_expression(dest, ieis->instr, el, pe);
	fprintf(dest, "	if(");
	translate_instruction(dest,ieis->instr, el, pe);
	//fprintf(dest, "%s", buffer);
	fprintf(dest, ")\n");
	fprintf(dest,"	goto then%d_%d;\n",tmp_if, num_elseif);
	fprintf(dest,"goto endelseif%d_%d;\n",tmp_if, tmp_elseif);
	fprintf(dest,"then%d_%d:\n",tmp_if,  num_elseif);
	//meter uma var na locals a 0 e 1 para saber se ja entrou em algum esif num determinado ciclo
	fprintf(dest,"flag_else = 1;");
	translate_cont_statement(dest,ieis->iconts, el, pe);
	fprintf(dest,";\nendelseif%d_%d:\n",tmp_if, tmp_elseif);

	num_elseif++;
	el->passagem=pass;
}


//FUNC CALL
void translate_is_func_call(FILE* dest, environment_list* el, prog_env* pe, is_func_call* ifc){
	
	environment_list* funcDest;
	char* funcDestName=ifc->id->id;

	funcDest=plookup(pe->procs, funcDestName);


	if(funcDest==NULL){
		return;
	}
	
	if(ifc->icl!=NULL){
		translate_call_list(dest, el, funcDest, pe, ifc->icl);
	}	

	fprintf(dest, "_ra=%d;\n",returncounter);		//guarda de endereco de retorno
	fprintf(dest, "goto %s;\n", funcDest->name);		//Salto para codigo do procedimento
	fprintf(dest, "return%d:\n", returncounter);		//label de retorno
	returncounter++;	
}

//CALL LIST
void translate_call_list(FILE* dest, environment_list* el, environment_list* funcDest, prog_env* pe, is_call_list* list){

	table_element* aux=funcDest->arguments;
	is_call_list* call_aux=list;

	if(strcmp(aux->name, "")==0){
		aux=aux->next;
	}

	for(; aux; aux=aux->next, call_aux=call_aux->next){
		translate_ourgoing_dec_type(dest, aux, aux->type);
		translate_args(dest, aux->type);
		fprintf(dest, "sp->outgoing[%d])= ", aux->offset);
		translate_type(dest, call_aux->ty, el , pe);
		fprintf(dest, ";\n");
	}


}

//OUTGOING VAR DECLARE
void translate_ourgoing_dec_type(FILE* dest, table_element* t, disc_type dt)
{

	switch(dt)
	{
		case d_INTEGER:	fprintf(dest, "sp->outgoing[%d]=(int*)malloc(sizeof(int));\n", t->offset); break;
		case d_STRING:	fprintf(dest, "sp->outgoing[%d]=(char*)malloc(sizeof(char));\n", t->offset); break;
		case d_DOUBLE:	fprintf(dest, "sp->outgoing[%d]=(double*)malloc(sizeof(double));\n", t->offset); break;
		case d_FLOAT:   fprintf(dest, "sp->outgoing[%d]=(float*)malloc(sizeof(float));\n", t->offset); break;
		case d_BOOL: 	fprintf(dest, "sp->outgoing[%d]=(int*)malloc(sizeof(int));\n", t->offset); break;
		default: break;
	}
}


//DECLARATION
void translate_declaration(FILE* dest, environment_list* el, prog_env* pe, is_declaration* decl)
{
	declare=1;
	translate_dec_list( dest, el, pe, (is_dec_list*) decl->dec_list);
	declare=0;
}

//DECLARATION LIST
void translate_dec_list(FILE* dest, environment_list* el, prog_env* pe, is_dec_list* idl)
{
	if(idl->next==NULL){
		translate_atr(dest, el, pe, idl->atr); 
		return;
	}

	for(; idl != NULL; idl = idl->next)
	{
		translate_atr(dest, el, pe, idl->atr);
	}
}

//ATR
void translate_atr(FILE* dest, environment_list* el, prog_env* pe, is_atr* ia)
{
	switch(ia->disc_n)
		{
		case d_ID: break;

		case d_atribution:
			translate_atribution(dest, ia->data_atr.u_atribution,  el, pe); 
			break;
		}
}

//RETURN STATEMENT
void translate_return_statement(FILE* dest, is_return_statement* irs, environment_list* el, prog_env* pe)
{
	
	//Caso em que nao retorna nada
	if(irs->instr==NULL){
		//Epilogo
		fprintf(dest, "\n/*Epilogo*/\n");
		fprintf(dest, "_last_ra=_ra;\n");
		fprintf(dest, "_ra=sp->return_address;\n");		//Restauro do valor de retorno, a ser utilizando aquando do redireccionamento do fluxo
		fprintf(dest, "sp=sp->parent;\n");			//"pop" da pilha de frames
		fprintf(dest, "fp=sp->parent;\n");			//actualizacao do registo FP de acordo
		fprintf(dest, "goto redirector;\n");			//Instrucao especifica para a nossa implementacao em C "restringido"
		returnState=0;
		return;
	}
	
	if(strcmp(el->name, "main")==0){
		//translate_instruction(dest, irs->instr, el, pe);
		fprintf(dest, "goto exit;\n");
		returnState=0;
		return;
	}
	
	el->passagem=1;
	translate_instruction(dest, irs->instr, el, pe);
	el->passagem=0;
	//Epilogo
	fprintf(dest, "\n/*Epilogo*/\n");
	fprintf(dest, "_last_ra=_ra;\n");
	fprintf(dest, "_ra=sp->return_address;\n");		//Restauro do valor de retorno, a ser utilizando aquando do redireccionamento do fluxo

	create_return_value(dest, el->type);

	returnState=0;
	translate_instruction(dest, irs->instr, el, pe);
	
	fprintf(dest, ";\n");
	fprintf(dest, "sp=sp->parent;\n");			//"pop" da pilha de frames
	fprintf(dest, "fp=sp->parent;\n");			//actualizacao do registo FP de acordo
	fprintf(dest, "_last_ra=_ra;\n");
	fprintf(dest, "goto redirector;\n");			//Instrucao especifica para a nossa implementacao em C "restringido"
	
}

//INICIALIZA O RETURN VALUE
void create_return_value(FILE* dest, disc_type ty){
	switch(ty)
	{
		case d_INTEGER:	fprintf(dest, "return_value[_ra]=(int*)malloc(sizeof(int));\n"); 
			fprintf(dest, "*((int*)return_value[_ra])=  "); 
			break;
		case d_STRING:	fprintf(dest, "return_value[_ra]=(char*)malloc(sizeof(char));\n");
			fprintf(dest, "return_value[_ra]= ");
 			break;
		case d_DOUBLE:	fprintf(dest, "return_value[_ra]=(double*)malloc(sizeof(double));\n"); 
			fprintf(dest, "*((double*) return_value[_ra]=  ");
			break;
		case d_FLOAT:   fprintf(dest, "return_value[_ra]=(float*)malloc(sizeof(float));\n");
			fprintf(dest, "*((float*) return_value[_ra])=  "); 
			break;
		case d_BOOL:fprintf(dest, "return_value[_ra]=(int*)malloc(sizeof(int));\n"); 
			fprintf(dest, "*((int*)return_value[_ra])=  ");
			break; 	
		default: 
			break;
	}
}


//INSTRUCTION
void translate_instruction(FILE* dest,  is_instruction* iinstr , environment_list* el, prog_env* pe)
{
	switch(iinstr->disc_d)
	{
		case d_atribution: 
			translate_atribution(dest, iinstr->data_instr.u_atribution, el, pe);
			break;
		case d_expression: 
			if(el->passagem==1)	
				translate_expression_first(dest, iinstr->data_instr.u_expression, el, pe);
			else
				translate_expression(dest, iinstr->data_instr.u_expression, el, pe);
			break;
		case d_plusminus:
			translate_plusminus(dest, iinstr->data_instr.u_plusminus, el, pe);
			break;
	}

}

//PLUSMINUS
void translate_plusminus(FILE* dest,  is_plusminus* ipm , environment_list* el, prog_env* pe)
{
	table_element* t;
	t=lookup(el->locals,ipm->id->id);
	if(t==NULL)
	{
		t=lookup(pe->global,ipm->id->id);
		fprintf(dest, "g%d = ", t->offset);
		switch(ipm->disc_d)
		{
			case d_PLUSPLUS: 
				fprintf(dest, "g%d + 1 ", t->offset);
				break;
			case d_MINUSMINUS: 
				fprintf(dest, "g%d - 1 ", t->offset);
				break;
			default:
				break;
		}
	}
	else{
		translate_args(dest, t->type);
		fprintf(dest, "sp->locals[%d]) = ", t->offset);
		switch(ipm->disc_d)
		{
			case d_PLUSPLUS:
				translate_args(dest, t->type); 
				fprintf(dest, " sp->locals[%d]) + 1 ", t->offset);
				break;
			case d_MINUSMINUS: 
				translate_args(dest, t->type);
				fprintf(dest, " sp->locals[%d]) - 1 ", t->offset);
				break;
			default:
				break;
		}

	}
}

//EXPRESSION PRIMEIRA PASSAGEM
void translate_expression_first(FILE* dest,  is_expression* ie , environment_list* el, prog_env* pe)
{
	switch (ie->disc_d)
	{
		case d_expression_exp:
			translate_expression_first(dest, ie->data_expr.u_expression, el, pe);
			break;
			
		case d_logic_exp_or_and:
			translate_expression_first(dest, ie->data_expr.u_logic_exp_or_and->exp1, el, pe);
			translate_expression_first(dest, ie->data_expr.u_logic_exp_or_and->exp2, el, pe);
			break;
		
		case d_logic_exp_not:
			translate_expression_first(dest, ie->data_expr.u_logic_exp_not->exp1, el, pe);
			break;
			
		case d_exp_minus_plus:
			translate_expression_first(dest, ie->data_expr.u_exp_minus_plus->exp, el, pe);
			break;	

		case d_aritmetic_exp:
			translate_expression_first(dest, ie->data_expr.u_aritm_exp->exp1, el, pe);
			translate_expression_first(dest, ie->data_expr.u_aritm_exp->exp2, el, pe);
			break;
	
		case d_relac_exp:
			translate_expression_first(dest, ie->data_expr.u_relac_exp->exp1, el, pe);
			translate_expression_first(dest, ie->data_expr.u_relac_exp->exp2, el, pe);
			break;

		case d_type:
			translate_type_first(dest, ie->data_expr.u_type, el, pe);
			break;
	}	

}

//TYPE PRIMEIRA PASSAGEM
void translate_type_first(FILE* dest, is_type* ity, environment_list* el , prog_env *pe)
{
	switch(ity->disc_n){
		case d_type_func_call:
			func_calls++;
			translate_is_func_call(dest, el, pe, ity->data_type.fcall);
			break;
		default: 
			break;
	}
	return;
}

//EXPRESSION
void translate_expression(FILE* dest,  is_expression* ie , environment_list* el, prog_env* pe)
{
	switch (ie->disc_d)
	{
		case d_expression_exp:
			fprintf(dest,"(");
			translate_expression(dest, ie->data_expr.u_expression, el, pe);
			fprintf(dest,")");
			break;
			
		case d_logic_exp_or_and:
			translate_logic_exp_or_and(dest, ie->data_expr.u_logic_exp_or_and, el, pe);
			break;
		
		case d_logic_exp_not:
			translate_logic_exp_not(dest, ie->data_expr.u_logic_exp_not, el, pe);
			break;
			
		case d_exp_minus_plus:
			translate_exp_minus_plus(dest, ie->data_expr.u_exp_minus_plus, el, pe);			
			break;	

		case d_aritmetic_exp:
			translate_aritmetic_exp(dest, ie->data_expr.u_aritm_exp, el, pe);
			break;
	
		case d_relac_exp:
			translate_relac_exp(dest, ie->data_expr.u_relac_exp, el, pe);
			break;

		case d_type:
			translate_type(dest, ie->data_expr.u_type, el, pe);
			break;
	}	

}

//MINUS PLUS EXP
void translate_exp_minus_plus(FILE* dest, is_exp_minus_plus* iemp, environment_list* el, prog_env* pe)
{
	switch(iemp->oper){
		case is_PLUS:
			break;

		case is_MINUS:
			fprintf(dest," - ");
			break;
		default: break;
	}
	translate_expression(dest, iemp->exp, el, pe);
}

//RELAC EXP
void translate_relac_exp(FILE* dest, is_relac_exp* ire, environment_list* el, prog_env* pe)
{
	translate_expression(dest,  ire->exp1 , el, pe);

	switch(ire->oper){
		case is_GREATER:
			fprintf(dest," > ");
		break;

		case is_GREATEREQUAL:
			fprintf(dest," >= ");
		break;

        	case is_LESS:
			fprintf(dest," < ");
		break;

		case is_LESSEQUAL:
			fprintf(dest," <= ");
		break;

		case is_EQUAL:
			fprintf(dest," == ");	
		break;	

		case is_NOTEQUAL:
			fprintf(dest," != ");	
		break;
		
       		 
	}	
	translate_expression(dest,   ire->exp2 ,  el, pe);	
		
}

//LOGIC EXP NOT
void translate_logic_exp_not(FILE* dest, is_logic_exp_not* ilen, environment_list* el, prog_env* pe)
{
	fprintf(dest," !");
        translate_expression(dest,  ilen->exp1 , el, pe);		
}

//LOGIC EXP OR AND
void translate_logic_exp_or_and(FILE* dest, is_logic_exp_or_and* ileoa, environment_list* el, prog_env* pe)
{

        translate_expression(dest,  ileoa->exp1 , el, pe);
	switch (ileoa->oper)
	{
		case is_AND:
			fprintf(dest," && ");
			break;
		case is_OR:	
			fprintf(dest, " || ");
			break;
	}
        translate_expression(dest,   ileoa->exp2 ,  el, pe);			
}

//TYPE
void translate_type(FILE* dest, is_type* ity, environment_list* el , prog_env *pe)
{
	table_element* t;
	environment_list* ev;
	switch(ity->disc_n){
		case d_type_ID:
			t=lookup(el->locals, ity->data_type.id->id);

			if(t==NULL)
			{

				t=lookup(pe->global, ity->data_type.id->id);
				fprintf(dest, "g%d", t->offset);
			}
			else
			{
				translate_args(dest, t->type);
				fprintf(dest, "sp->locals[%d])", t->offset);
			}

			break;

		case d_type_func_call:
			ev=plookup(pe->procs, ity->data_type.fcall->id->id);
			translate_args(dest, ev->type);
			if(returnState==0){
				if(func_calls>0){
					fprintf(dest, "return_value[_last_ra-%d])", func_calls);
					func_calls--;
				}
				else{
					fprintf(dest, "return_value[_last_ra])");
				}
			}
			else{
				fprintf(dest, "return_value[_ra])");
			}
			break;

		case d_INTEGER:
			fprintf(dest, "%d", ity->data_type.integer);
			break;

		case d_DOUBLE:
			fprintf(dest, "%lf", ity->data_type.db);
			break;
			
		case d_FLOAT:
			fprintf(dest, "%f", ity->data_type.fl);
			break;

		case d_STRING:
			fprintf(dest, "%s", ity->data_type.string);
			break;
		case d_BOOL:
			if(ity->data_type.boolean)
				fprintf(dest, "1");
			else
				fprintf(dest, "0");
			break;
		default: 
			break;
	}
}




//VAR PRINT
void translate_var_print(FILE* dest, disc_type type)
{
	//Declara variaveis *globais* de acordo com o tipo
	switch(type)
	{
		case d_INTEGER:	fprintf(dest, "%%d"); break;
		case d_STRING:	fprintf(dest, "%%s"); break;
		case d_DOUBLE:	fprintf(dest, "%%lf"); break;
		case d_FLOAT:	fprintf(dest, "%%f"); break;
		case d_BOOL:	fprintf(dest, "%%d"); break;
		default:break;
	}
}


//ARITMETIC EXP
void translate_aritmetic_exp(FILE* dest, is_aritmetic_exp* iae, environment_list* el, prog_env* pe)
{
	if(printState==0){
		if(iae->oper==is_POT)
			fprintf(dest,"pow(");		
	}

	translate_expression(dest,  iae->exp1 , el, pe);
	if(printState==0){
		switch(iae->oper){
			case is_PLUS:
				fprintf(dest," + ");
			break;

			case is_MINUS:
				fprintf(dest," - ");
			break;

			case is_MULT:
				fprintf(dest," * ");
			break;

			case is_DIV:
				fprintf(dest," / ");
			break;

			case is_MOD:
				fprintf(dest," %% ");
			break;

			case is_POT:
				fprintf(dest," ,");	
			break;			
	       		 
		}
	}	
	translate_expression(dest,   iae->exp2 ,  el, pe);
	if(printState==0){
		if(iae->oper==is_POT)
			fprintf(dest,")");	
		}		
}

//FOOTER
void translate_footer(FILE* dest)
{
	translate_redirector(dest);
	fprintf(dest, "\n}\n\n");
}

/*funcao para redireccionar o fluxo de codigo de acordo com enderecos de retorno. Necessario para C.*/
void translate_redirector(FILE* dest)
{
	int i;
	fprintf(dest, "/*Redirector*/\n");
	fprintf(dest, "goto exit;\n");
	fprintf(dest, "redirector:\n");

	for(i=0; i<returncounter; i++)	//Para cada endereco de retorno, sua label associada
	{
		fprintf(dest, "if(_ra==%d) goto return%d;\n", i, i);
	}
	fprintf(dest, "exit:\n;\n");
}

