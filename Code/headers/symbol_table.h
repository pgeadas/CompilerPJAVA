#ifndef PJAVA_SYMBOL_TABLE_H
#define PJAVA_SYMBOL_TABLE_H

#include "boolean.h"

// is_type --> is_INTEGER V is_FLOAT V is_DOUBLE
typedef enum {
    d_INTEGER, d_FLOAT, d_DOUBLE, d_STRING, d_type_ID, d_type_func_call, d_VOID, d_BOOL
} disc_type;

/**estrutura das pilhas que vao reter a informaçao se estamos
num if ou num while para o tratamento dos breaks e continues**/
typedef struct _nop {
    int num;
    struct _nop *next;
} Int_node;

typedef struct _cabecap {
    Int_node *header;
    Int_node *tail;
    int size;
} Pilha;

typedef struct _nop2 {
    char c;
    struct _nop2 *next;
} Char_node;

typedef struct _cabecap2 {
    Char_node *header;
    Char_node *tail;
    int size;
} Pilha2;

typedef struct _table_element {
    char name[32];
    disc_type type;
    int offset;
    struct _table_element *next;
} table_element;

//lista de procedimentos definidos no programa
typedef struct _env_list {
    char *name;
    int offset;
    int passagem;
    int total_args;
    disc_type type;
    struct _env_list *next;
    table_element *locals;
    table_element *arguments;
} environment_list;

//Estrutura que guarda TODOS os simbolos de um programa: o ambiente "global" e a lista de ambientes
typedef struct _prog_env {
    table_element *global;
    environment_list *procs;
} prog_env;


void show_table();

void push(int num, Pilha *p);

int pop(Pilha *p);

void push2(char c, Pilha2 *p);

char pop2(Pilha2 *p);


#endif
