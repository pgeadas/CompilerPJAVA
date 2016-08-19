#include "symbol_table.h"
#include "structures.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>



int listaVARIAVEIS=0;//1- PARA IMPRIMIR || 0- PARA NAO IMPRIMIR

extern table_element* symtab;

void show_table()
{

	table_element *aux;
	table_element *tmp;
	environment_list * env_aux;
	environment_list *env_tmp;

	if(strcmp(pe->global->name, "")==0){
		tmp=pe->global->next;
		free(pe->global);
		pe->global=tmp;
	}
	
	if(strcmp(pe->procs->name, "")==0){
		env_tmp=pe->procs->next;
		free(pe->procs);
		pe->procs=env_tmp;

	}


	printf("\n");
	printf("VARIAVEIS GLOBAIS:\n");
	if(pe->global==NULL){
		printf("->NAO TEM ARGUMENTOS<-\n");
	}
	else{
		for(aux=pe->global; aux; aux=aux->next){
			printf("symbol %s, type %d, offset %d\n", aux->name, aux->type, aux->offset);
		}
	}
	printf("---------------------\n");
	
	printf("FUNCOES:\n");
	for(env_aux=pe->procs; env_aux; env_aux=env_aux->next){
		if(strcmp(env_aux->arguments->name, "")==0){
			tmp=env_aux->arguments->next;
			free(env_aux->arguments);
			env_aux->arguments=tmp;

		}
		printf("----FUNCAO %s----\nARGUMENTOS:\n", env_aux->name);
		if(env_aux->arguments==NULL){
			printf("->NAO TEM ARGUMENTOS<-\n");
		}
		else{
			for(aux=env_aux->arguments; aux; aux=aux->next){
				printf("symbol %s, type %d, offset %d\n", aux->name, aux->type, aux->offset);
			}
		}
	
		printf("---------------------\nVARIAVEIS LOCAIS:\n");

		if(strcmp(env_aux->locals->name, "")==0){
			tmp=env_aux->locals->next;
			free(env_aux->locals);
			env_aux->locals=tmp;

		}
	
		if(env_aux->locals==NULL){
			printf("->NAO TEM VARIAVEIS LOCAIS<-\n");
		}
		else{
			for(aux=env_aux->locals; aux; aux=aux->next){
				printf("symbol %s, type %d, offset %d\n", aux->name, aux->type, aux->offset);
			}
		}

		printf("---------------------\n");
	}
	printf("---------------------\n");
}

void push(int num, Pilha* p)
{
	No_pilha* element;
	
	element= (No_pilha*)malloc(sizeof(No_pilha));
	if(element==NULL) return;
		
	element->num=num;
	element->next=NULL;
	
	if(p->size==0)
	{
		p->size=1;
		p->header=element;
		p->tail=p->header;
	
	}else
	{
		(p->tail)->next=element;
		p->tail=element;
		p->size++;
	
	}	

}


int pop(Pilha* p)
{
	No_pilha* element= p->header;
	int retorno;

	if(element==NULL) return 0;

	
	if(p->header==p->tail)
	{
		retorno=p->header->num;
		p->size=0;
		//p->header=NULL;
		p->tail=p->header;
		
		return retorno;
	
	}else
	{
		while(element->next!=p->tail) element=element->next;
		
		
		element->next=NULL;
		p->size--;
		retorno=p->tail->num;
		
		p->tail=element;
	
	}
return retorno;

}

void push2(char c, Pilha2* p)
{
	No_pilha2* element;
	
	element= (No_pilha2*)malloc(sizeof(No_pilha2));
	if(element==NULL) return ;
		
	element->c=c;
	element->next=NULL;
	
	if(p->size==0)
	{
		p->size=1;
		p->header=element;
		p->tail=p->header;
	
	}else
	{
		((p->tail)->next)=element;
		p->tail=element;
		p->size++;
	
	}	
	return;
}


char pop2(Pilha2* p)
{
	No_pilha2* element= p->header;
	char retorno;

	if(element==NULL) return 0;

	
	if(p->header==p->tail)
	{
		retorno=p->header->c;
		p->size=0;
		//p->header=NULL;
		p->tail=p->header;
		
		return ((char)retorno);
	
	}else
	{
		while(element->next!=p->tail) element=element->next;
		
		
		element->next=NULL;
		p->size--;
		retorno=p->tail->c;
		
		p->tail=element;
	
	}
return ((char)retorno);

}

