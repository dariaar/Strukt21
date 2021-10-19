#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 128
#define MAX_LINE 1024

typedef struct _student
{
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
}student;

int ProcitajBrojRedakaIzDatoteke(char* NazivDatoteke)
{
	int brojac = 0;
	FILE* datoteka = NULL;
	char buffer[MAX_LINE] = {0};

	datoteka = fopen(NazivDatoteke, "r");
	if (!datoteka)
	{
		printf("Greska");
		return -1;
	}
	while (!feof(datoteka))
	{
		fgets(buffer, MAX_LINE, datoteka);

		brojac++;
	}

	fclose(datoteka);

	return brojac;
}

student* ProcitajMemorijuIAlocirajStudente(int BrojStudenata, char* NazivDatoteke)
{
	int brojac = 0;
	FILE* datoteka = NULL;
	student* studenti = NULL;

	studenti = (student*)malloc(BrojStudenata * sizeof(student));
	datoteka = fopen(NazivDatoteke, "r");

	if (!datoteka)
	{
		printf("Greska alociranja");
		free(studenti);
		return -1;
	}
	while (!feof(datoteka))
	{
		fscanf(datoteka, "%s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);

		brojac++;
	}

	fclose(datoteka);

	return studenti;
}

int main()
{
	int BrojStudenata = ProcitajBrojRedakaIzDatoteke("RezultatiIspita.txt");
	student* studenti = ProcitajMemorijuIAlocirajStudente(BrojStudenata, "RezultatiIspita.txt");

	for (int i = 0; i < BrojStudenata; i++)
	{
		printf("%s %s %lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi);
	}

	return 0;
}
