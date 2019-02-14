/*BOMPA Remus-315CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef _STRUCTURI_
#define _STRUCTURI_

typedef struct celula
{
	char caracter;
	struct nod *copil;
	struct celula *urm;
} TCelula, *TLista, **ALista;

typedef struct nod
{
	unsigned int terminat;
	TLista cale;
} TNod, *TArb, **AArb;

TArb AlocNod ();
TLista AlocCelula (char ae);
TArb InitArb ();
TLista InsertOLista (ALista l, char ae);
void ElibLista (TLista l);
void ElibNod (TArb nod);
void ElibArb (TArb * a);
int add (TArb * a, char *word);
int find (TArb * a, char *word);
int Remove (TArb * a, char *word, int i);
void find_longest_prefix (TArb * a, char *word, FILE * fout);
void listare (TArb * a, FILE * fout, char *word);
void find_all_with_prefix (TArb * a, char *word, FILE * fout);
int suma_lungime (TArb * a, int *nr, char *word);
void mean_length (TArb * a, char *word, FILE * fout);
#endif
