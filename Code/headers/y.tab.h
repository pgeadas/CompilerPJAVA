/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef PJAVA_Y_TAB_H
#define PJAVA_Y_TAB_H

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
/* Put the tokens into the symbol table, so that GDB and other debuggers
   know about them.  */
enum yytokentype {
    MINUSEQUAL = 258,
    PLUSEQUAL = 259,
    EQUAL = 260,
    OR = 261,
    AND = 262,
    EQUALEQUAL = 263,
    NOTEQUAL = 264,
    LESSEQUAL = 265,
    GREATEREQUAL = 266,
    LESS = 267,
    GREATER = 268,
    MINUSMINUS = 269,
    PLUSPLUS = 270,
    MINUS = 271,
    PLUS = 272,
    DIV = 273,
    MULT = 274,
    MOD = 275,
    POT = 276,
    RETURNSYMB = 277,
    FUNCSYMB = 278,
    ELSEIF = 279,
    ELSE = 280,
    WHILE = 281,
    IF = 282,
    NOT = 283,
    CLASSSYMB = 284,
    INTSYMB = 285,
    FLOATSYMB = 286,
    STRINGSYMB = 287,
    DOUBLESYMB = 288,
    VOIDSYMB = 289,
    BOOLSYMB = 290,
    CONCATSYMB = 291,
    INT = 292,
    FLOAT = 293,
    STRING = 294,
    BOOL = 295,
    ID = 296,
    FOR = 297,
    BREAK = 298,
    CONTINUE = 299,
    PRINTLN = 300,
    PRINT = 301,
    READ = 302,
    READLINE = 303
};
#endif
/* Tokens.  */
#define MINUSEQUAL 258
#define PLUSEQUAL 259
#define EQUAL 260
#define OR 261
#define AND 262
#define EQUALEQUAL 263
#define NOTEQUAL 264
#define LESSEQUAL 265
#define GREATEREQUAL 266
#define LESS 267
#define GREATER 268
#define MINUSMINUS 269
#define PLUSPLUS 270
#define MINUS 271
#define PLUS 272
#define DIV 273
#define MULT 274
#define MOD 275
#define POT 276
#define RETURNSYMB 277
#define FUNCSYMB 278
#define ELSEIF 279
#define ELSE 280
#define WHILE 281
#define IF 282
#define NOT 283
#define CLASSSYMB 284
#define INTSYMB 285
#define FLOATSYMB 286
#define STRINGSYMB 287
#define DOUBLESYMB 288
#define VOIDSYMB 289
#define BOOLSYMB 290
#define CONCATSYMB 291
#define INT 292
#define FLOAT 293
#define STRING 294
#define BOOL 295
#define ID 296
#define FOR 297
#define BREAK 298
#define CONTINUE 299
#define PRINTLN 300
#define PRINT 301
#define READ 302
#define READLINE 303




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 22 "mycalc.y"

    int intValue;
    float floatValue;
    double doubleValue;
    char* string;
    bool boolValue;

    is_statement_list* isl;
    is_instruction* ii;
    is_expression* ie;
    is_relac_exp* ire;
    is_logic_exp_or_and* ileoa;
    is_logic_exp_not* ilen;
    is_aritmetic_exp* iae;
    is_atribution_list* ial;
    is_atribution* ia;
    is_id* id;
    is_statement* is;
    is_type* ity;
    is_program* iprogram;
    is_compound_statement* ics;
    is_if_statement* iifs;
    is_while_statement* iws;
    is_else_statement* ielses;
    is_elseif_statement* ielseifs;
    is_elseif_statement_list* ieisl;
    is_cont_statement* iconts;
    is_println_statement* iprints;
    is_declaration* idecl;
    is_atr* iatr;
    is_dec_list* ideclist;
    is_func_def* ifd;
    is_arg_list* iargl;
    is_cont_func* icf;
    is_symbols* isymb;
    is_func_call* ifcall;
    is_call_list* icall;
    is_for_statement* ifors;
    is_for_args* ifa;
    is_exp_minus_plus* impe;
    is_return_statement* ireturn;
    is_class* iclass;
    is_func_list* iflist;
    is_plusminus* ipm;
    is_read_statement* irs;
    is_concat* iconcat;
    is_concat_args* icargs;
    is_println_args* ipargs;
    is_break_cont* ibc;



/* Line 1676 of yacc.c  */
#line 201 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


#endif
