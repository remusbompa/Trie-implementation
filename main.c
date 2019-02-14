/*BOMPA Remus-315CB*/
#include"TStructuri.h"

int main (int argc, char *argv[])
{
	char *nume_in = argv[1], *nume_out = argv[2], operatie[20];
	FILE *fin = fopen (nume_in, "rt"), *fout = fopen (nume_out, "wt");
	if (!fin || !fout)
	{
		printf ("Eroare la deschiderea fisierelor!\n");
		return 0;
	}
	int N;
	TArb a = InitArb ();
	fscanf (fin, "%d", &N);
	while (N > 0)
	{
		N--;
		if (fscanf (fin, "%s", operatie) != 1)
		{
			printf ("eroare citire operatie!\n");
			return 0;
		}
		if (!strcmp (operatie, "add"))
		{
			char *word = (char *) malloc (3000 * sizeof (char));
			if (!word)
			{
				printf ("Eroare alocare cuvant!\n");
				return 0;
			}
			fscanf (fin, "%s", word);
			add (&a, word);
			free (word);
		}
		if (!strcmp (operatie, "remove"))
		{
			char *word = (char *) malloc (3000 * sizeof (char));
			if (!word)
			{
				printf ("Eroare alocare cuvant!\n");
				return 0;
			}
			fscanf (fin, "%s", word);
			Remove (&a, word, 0);
			free (word);
		}
		if (!strcmp (operatie, "find"))
		{
			char *word = (char *) malloc (3000 * sizeof (char));
			if (!word)
			{
				printf ("Eroare alocare cuvant!\n");
				return 0;
			}
			fscanf (fin, "%s", word);
			if (find (&a, word))
				fprintf (fout, "True\n");
			else
				fprintf (fout, "False\n");
			free (word);
		}
		if (!strcmp (operatie, "find_longest_prefix"))
		{
			char *word = (char *) malloc (3000 * sizeof (char));
			if (!word)
			{
				printf ("Eroare alocare cuvant!\n");
				return 0;
			}
			fscanf (fin, "%s", word);
			find_longest_prefix (&a, word, fout);
			free (word);
		}
		if (!strcmp (operatie, "find_all_with_prefix"))
		{
			char *word, *linie;
			linie = (char *) malloc (3000 * sizeof (char));
			if (!linie)
			{
				printf ("Eroare alocare cuvant!\n");
				return 0;
			}
			fgets (linie, 3000, fin);
			word = strtok (linie, " \t\n");
			if (!word)
			{
				word = (char *) malloc (sizeof (char));
				if (!word)
				{
					printf ("Eroare alocare cuvant!\n");
					return 0;
				}
				*word = 0;
				free (linie);
				linie = word;
			}
			find_all_with_prefix (&a, word, fout);
			free (linie);
		}
		if (!strcmp (operatie, "mean_length"))
		{
			char *word, *linie;
			linie = (char *) malloc (3000 * sizeof (char));
			if (!linie)
			{
				printf ("Eroare alocare cuvant!\n");
				return 0;
			}
			fgets (linie, 3000, fin);
			word = strtok (linie, " \t\n");
			if (!word)
			{
				word = (char *) malloc (sizeof (char));
				if (!word)
				{
					printf ("Eroare alocare cuvant!\n");
					return 0;
				}
				*word = 0;
				free (linie);
				linie = word;
			}
			mean_length (&a, word, fout);
			free (linie);
		}
	}
	fclose (fin);
	fclose (fout);
	ElibArb (&a);
	return 0;
}
