/*BOMPA Remus-315CB*/
#include"TStructuri.h"

TArb AlocNod ()
{
	TArb n = (TArb) malloc (sizeof (TNod));
	if (!n)
	{
		printf ("Eroare la alocare nod!\n");
		return NULL;
	}
	n->terminat = 0;
	n->cale = NULL;
	return n;
}

TLista AlocCelula (char ae)
{
	TLista l = (TLista) malloc (sizeof (TCelula));
	if (!l)
	{
		printf ("Eroare alocare celula!\n");
		return NULL;
	}
	l->caracter = ae;
	l->copil = NULL;
	l->urm = NULL;
	return l;
}

TArb InitArb ()
{
	TArb a = AlocNod ();
	return a;
}

TLista InsertOLista (ALista l, char ae)
{
	for (; *l && (*l)->caracter < ae; l = &((*l)->urm));
	if (*l && (*l)->caracter == ae)
		return *l;
	TLista new = AlocCelula (ae);
	if (!new)
		return NULL;
	new->urm = *l;
	*l = new;
	return new;
}

void ElibLista (TLista l)
{
	if (!l)
		return;
	TLista p = l;
	l = l->urm;
	ElibNod (p->copil);
	free (p);
	ElibLista (l);
}

void ElibNod (TArb nod)
{
	TLista l = nod->cale;
	free (nod);
	ElibLista (l);
}

void ElibArb (TArb * a)
{
	if (!(*a))
		return;
	ElibNod (*a);
	*a = NULL;
}

int add (TArb * a, char *word)
{
	int i;
	for (i = 0; i < strlen (word); i++)
	{
		TLista l = InsertOLista (&(*a)->cale, word[i]);
		if (!l)
			return 0;
		if (!l->copil)
			l->copil = AlocNod ();
		if (!l->copil)
			return 0;
		TArb *nod = &l->copil;
		if (i == strlen (word) - 1)
			(*nod)->terminat = 1;
		a = nod;
	}
	return 1;
}

int find (TArb * a, char *word)
{
	int i;
	for (i = 0; i < strlen (word); i++)
	{
		ALista l = &(*a)->cale;
		for (; *l && (*l)->caracter != word[i]; l = &((*l)->urm));
		if (!*l)
			return 0;
		TArb *nod = &(*l)->copil;
		a = nod;
	}
	if ((*a)->terminat == 1)
		return 1;
	return 0;
}

int Remove (TArb * a, char *word, int i)
{
	if (i == strlen (word))
	{
		(*a)->terminat = 0;
		return 1;
	}
	int rez = 0;
	ALista l = &(*a)->cale;
	for (; *l && (*l)->caracter != word[i]; l = &((*l)->urm));
	if (!*l)
		return 0;
	TArb *nod = &(*l)->copil;
	rez = Remove (nod, word, i + 1);
	if (!rez)
		return 0;
	if (!(*nod)->cale && (*nod)->terminat == 0)
	{
		free (*nod);
		*nod = NULL;
		TLista p = *l;
		*l = (*l)->urm;
		free (p);
	}
	else
		return 0;			/*daca gaseste un nod plin (cu terminat=1) 
						sau care are copii, nu mai sterge nimic dupa */
	return 1;
}

void find_longest_prefix (TArb * a, char *word, FILE * fout)
{
	int i;
	for (i = 0; i < strlen (word); i++)
	{
		ALista l = &(*a)->cale;
		for (; *l && (*l)->caracter != word[i]; l = &((*l)->urm));
		if (!*l)
		{
			if (i == 0)
			{
				fprintf (fout, "None\n");
				return;
			}
			break;
		}
		TArb *nod = &(*l)->copil;
		fprintf (fout, "%c", (*l)->caracter);
		a = nod;
	}
	fprintf (fout, "\n");
}

void listare (TArb * a, FILE * fout, char *word)
{
	if ((*a)->terminat == 1)
		fprintf (fout, "%s ", word);
	if (!(*a)->cale)
		return;
	ALista l = &(*a)->cale;
	for (; *l; l = &(*l)->urm)
	{
		TArb *nod = &(*l)->copil;
		char *cuvant = (char *) malloc (strlen (word) + 2);
		strcpy (cuvant, word);
		cuvant[strlen (word)] = (*l)->caracter;
		cuvant[strlen (word) + 1] = 0;
		listare (nod, fout, cuvant);
		free (cuvant);
	}
}

void find_all_with_prefix (TArb * a, char *word, FILE * fout)
{
	int i;
	for (i = 0; i < strlen (word); i++)
	{
		ALista l = &(*a)->cale;
		for (; *l && (*l)->caracter != word[i]; l = &((*l)->urm));
		if (!*l)
		{
			fprintf (fout, "None\n");
			return;
		}
		TArb *nod = &(*l)->copil;
		a = nod;
	}
	listare (a, fout, word);
	fprintf (fout, "\n");
}

int suma_lungime (TArb * a, int *nr, char *word)
{
	int suma = 0;
	if ((*a)->terminat == 1)
	{
		suma += strlen (word);
		(*nr)++;
	}
	if (!(*a)->cale)
		return suma;
	ALista l = &(*a)->cale;
	for (; *l; l = &(*l)->urm)
	{
		TArb *nod = &(*l)->copil;
		char *cuvant = (char *) malloc (strlen (word) + 2);
		strcpy (cuvant, word);
		cuvant[strlen (word)] = (*l)->caracter;
		cuvant[strlen (word) + 1] = 0;
		suma += suma_lungime (nod, nr, cuvant);
		free (cuvant);
	}
	return suma;
}

void mean_length (TArb * a, char *word, FILE * fout)
{
	int i, suma, nr = 0;
	for (i = 0; i < strlen (word); i++)
	{
		ALista l = &(*a)->cale;
		for (; *l && (*l)->caracter != word[i]; l = &((*l)->urm));
		if (!*l)
		{
			fprintf (fout, "0\n");
			return;
		}
		TArb *nod = &(*l)->copil;
		a = nod;
	}
	suma = suma_lungime (a, &nr, word);
	fprintf (fout, "%.3f\n", (float) suma / nr);
}
