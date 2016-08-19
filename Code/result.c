#include "frame.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#define LINE_MAX 1024


int main()
{
int _ra = 0;
int _last_ra = 0;
int flag_else = 0;
char* buffer;
buffer = (char*) malloc(sizeof(char));
void* return_value[100];
frame* fp=NULL;
frame* sp=NULL;
int g0=0;
char* g1="";
int g2=0;
char* g3="";
double g4=0;
double g5=0;
char* g6="";
g0 = 169;
g1 = "Programa Correcto!";
g2 = 69;
g4 = 10;
g5 = 10;
g6 = "ola burro!";

/*BLOCO DO PROCEDIMENTO ifb*/
/*Prologo*/
goto ifbskip;
ifb:
fp=sp;
sp=(frame*)malloc(sizeof(frame));
sp->frame_buffer=(char*) malloc (sizeof(char));
sp->parent=fp;
sp->return_address=_ra;

/*DECLARATIONS*/
sp->locals[0]=(int*)malloc(sizeof(int));
*((int*)sp->locals[0])=0;

/*ARGUMENTS ATRIBUTION*/
*((int*)sp->locals[0])= *((int*)fp->outgoing[0]);

/*Corpo do procedimento*/

/*STATEMENTS */

/*Epilogo*/
_last_ra=_ra;
_ra=sp->return_address;
return_value[_ra]=(int*)malloc(sizeof(int));
*((int*)return_value[_ra])=  *((int*)sp->locals[0]) - 10;
sp=sp->parent;
fp=sp->parent;
_last_ra=_ra;
goto redirector;
;
ifbskip:

/*BLOCO MAIN */
sp=(frame*)malloc(sizeof(frame));
sp->frame_buffer=(char*) malloc (sizeof(char));

/*DECLARATIONS */
sp->locals[0]=(int*)malloc(sizeof(int));
*((int*)sp->locals[0])=0;
sp->locals[1]=(int*)malloc(sizeof(int));
*((int*)sp->locals[1])=0;
sp->locals[2]=(int*)malloc(sizeof(int));
*((int*)sp->locals[2])=0;
sp->locals[3]=(int*)malloc(sizeof(int));
*((int*)sp->locals[3])=0;
sp->locals[4]=(int*)malloc(sizeof(int));
*((int*)sp->locals[4])=0;
sp->locals[5]=(int*)malloc(sizeof(int));
*((int*)sp->locals[5])=0;
sp->locals[6]=(double*)malloc(sizeof(double));
*((double*)sp->locals[6])=0;
sp->locals[7]=(int*)malloc(sizeof(int));
*((int*)sp->locals[7])=0;

/*STATEMENTS */
;
*((int*)sp->locals[5]) = 100;
;
;
*((int*)sp->locals[0]) = 3;
;

/*Estrutura FOR*/
*((int*)sp->locals[7]) = 0;
;
if(*((int*)sp->locals[7]) < 5)	goto for0;
	goto endfor0;

for0:

/*STATEMENTS */

/*PRINT */
sp->frame_buffer=(char*) malloc (2048*sizeof(char));
strcpy(sp->frame_buffer, "");
strcat(sp->frame_buffer,"A ");
buffer=(char*) malloc (sizeof(char));
sprintf(buffer, "%d", *((int*) sp->locals[7]));
strcat(sp->frame_buffer, buffer);
printf("%s\n", sp->frame_buffer);
;

	/*Estrutura IF*/
	if(*((int*)sp->locals[7]) == 3)		goto then0;
goto endif0;
then0:

/*STATEMENTS */

/*PRINT */
sp->frame_buffer=(char*) malloc (2048*sizeof(char));
strcpy(sp->frame_buffer, "");
strcat(sp->frame_buffer,"AAAAAAAAAA ");
buffer=(char*) malloc (sizeof(char));
sprintf(buffer, "%d", *((int*) sp->locals[7]));
strcat(sp->frame_buffer, buffer);
printf("%s\n", sp->frame_buffer);
;
/* BREAK */
goto breakf0;
;
;
endif0:
flag_else=0;
;

/*Estrutura FOR*/
*((int*)sp->locals[0]) = 0;
;
if(*((int*)sp->locals[0]) < 5)	goto for1;
	goto endfor1;

for1:

/*STATEMENTS */

/*PRINT */
sp->frame_buffer=(char*) malloc (2048*sizeof(char));
strcpy(sp->frame_buffer, "");
strcat(sp->frame_buffer,"b ");
buffer=(char*) malloc (sizeof(char));
sprintf(buffer, "%d", *((int*) sp->locals[0]));
strcat(sp->frame_buffer, buffer);
printf("%s\n", sp->frame_buffer);
;

	/*Estrutura IF*/
	if(*((int*)sp->locals[0]) == 3)		goto then1;
goto endif1;
then1:

/*STATEMENTS */

	/*Estrutura WHILE*/
	if(1)	goto while0;
goto endwhile0
;while0:

/*STATEMENTS */

/*PRINT */
sp->frame_buffer=(char*) malloc (2048*sizeof(char));
strcpy(sp->frame_buffer, "");
strcat(sp->frame_buffer,"TOU CA DENTRO ");
buffer=(char*) malloc (sizeof(char));
sprintf(buffer, "%d", *((int*) sp->locals[7]));
strcat(sp->frame_buffer, buffer);
printf("%s\n", sp->frame_buffer);
;

/*Estrutura FOR*/
*((int*)sp->locals[0]) = 0;
;
if(*((int*)sp->locals[0]) < 5)	goto for2;
	goto endfor2;

for2:

/*STATEMENTS */

/*PRINT */
sp->frame_buffer=(char*) malloc (2048*sizeof(char));
strcpy(sp->frame_buffer, "");
strcat(sp->frame_buffer,"BBBBBBBBBBBBBB ");
buffer=(char*) malloc (sizeof(char));
sprintf(buffer, "%d", *((int*) sp->locals[0]));
strcat(sp->frame_buffer, buffer);
printf("%s\n", sp->frame_buffer);
;
/* BREAK */
goto breakf2;
;
;
continuef2:
endfor2:
*((int*)sp->locals[0]) = *((int*) sp->locals[0]) + 1 ;
	if(*((int*)sp->locals[0]) < 5)	goto for2;
breakf2:
;
/* BREAK */
goto breakw0;
;
;
;
continuew0:
endwhile0:
	if(1)	goto while0;
breakw0:
;

/*PRINT */
sp->frame_buffer=(char*) malloc (2048*sizeof(char));
strcpy(sp->frame_buffer, "");
strcat(sp->frame_buffer,"SAIU ");
buffer=(char*) malloc (sizeof(char));
sprintf(buffer, "%d", *((int*) sp->locals[0]));
strcat(sp->frame_buffer, buffer);
printf("%s\n", sp->frame_buffer);
;
/* BREAK */
goto breakf1;
;
;
endif1:
flag_else=0;
;
;
continuef1:
endfor1:
*((int*)sp->locals[0]) = *((int*) sp->locals[0]) + 1 ;
	if(*((int*)sp->locals[0]) < 5)	goto for1;
breakf1:
;
;
continuef0:
endfor0:
*((int*)sp->locals[7]) = *((int*) sp->locals[7]) + 1 ;
	if(*((int*)sp->locals[7]) < 5)	goto for0;
breakf0:
;

	/*Estrutura WHILE*/
	if(1)	goto while1;
goto endwhile1
;while1:

/*STATEMENTS */

/*PRINT */
sp->frame_buffer=(char*) malloc (2048*sizeof(char));
strcpy(sp->frame_buffer, "");
strcat(sp->frame_buffer,"FIM ");
buffer=(char*) malloc (sizeof(char));
sprintf(buffer, "%d", *((int*) sp->locals[0]));
strcat(sp->frame_buffer, buffer);
printf("%s\n", sp->frame_buffer);
;
/* BREAK */
goto breakw1;
;
;
;
continuew1:
endwhile1:
	if(1)	goto while1;
breakw1:
;
goto exit;
;
/*Redirector*/
goto exit;
redirector:
exit:
;

}

