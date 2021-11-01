#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _osoba;
typedef struct _osoba* pozicija;
typedef struct _osoba
{
	char ime[100];
	char prezime[100];
	int god;
	pozicija next;
}Osoba;

int UnosP(pozicija);
pozicija UnosEl(pozicija);
int Ispis(pozicija);
int UnosK(pozicija);
pozicija TraziZadnji(pozicija);
int Brisanje(pozicija, char*);
pozicija TraziElement(pozicija);
int UnosNakon(pozicija);
int UnosPrije(pozicija);
pozicija Pronadi(pozicija, char*);
pozicija PronadiPrethodni(pozicija, char*);
int Sortiranje(pozicija);
int UpisDat(pozicija);
int CitanjeDat(pozicija);

int main()
{
	pozicija head = NULL;
	head = (pozicija)malloc(sizeof(Osoba));
	head->next = NULL;

	int i, n;
	char prezime[20];

	printf("Unesite broj zeljenih elemenata u listi:\n\n");
	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		UnosP(head);
	}
	printf("Ispis liste koju ste unijeli:\n\n");
	Ispis(head->next);
	printf("Unesite jedan element na kraj liste:\n\n");
	UnosK(head);
	printf("Ispis nove liste:\n");
	Ispis(head->next);
	printf("Unesite prezime koje zelite izbrisati s liste:\n\n");
	scanf("%s", &prezime);
	Brisanje(head->next, &prezime);
	printf("Konacan ispis liste:\n\n");
	Ispis(head->next);
	printf("Dodajte novi element nakon izabranog:\n\n");
	UnosNakon(head->next);
	printf("Dodajte novi element prije izabranog:\n\n");
	UnosPrije(head);
	printf("Ispis liste nakon dodavanja novih elemenata:\n\n");
	Ispis(head->next);
	printf("Ispis sortirane liste:\n\n");
	Sortiranje(head);
	Ispis(head->next);
	UpisDat(head->next);
	CitanjeDat(head);

	return 0;
}

int UnosP(pozicija p)
{
	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(Osoba));
	if (q == NULL)
	{
		printf("Nema slobodnog mjesta u memoriji!\n");
		return -1;
	}

	UnosEl(q);

	q->next = p->next;
	p->next = q;

	return 0;
}

pozicija UnosEl(pozicija q)
{
	printf("Unesite ime, prezime i godinu rodenja:\n");
	scanf("%s %s %d. \n", q->ime, q->prezime, &q->god);

	return 0;
}
int Ispis(pozicija p)
{
	if (p == NULL)
	{
		printf("Lista je prazna!!!\n");
		return -1;
	}
	else
	{
		while (p != NULL)
		{
			printf("%s %s %d.\n", p->ime, p->prezime, p->god);
			p = p->next;
		}
	}

	return 0;
}

int UnosK(pozicija p)
{
	pozicija zadnji = NULL;

	zadnji = (pozicija)malloc(sizeof(Osoba));

	zadnji = TraziZadnji(p);

	UnosP(zadnji);

	return 0;
}
pozicija TraziZadnji(pozicija p)
{
	while (p->next != NULL)
		p = p->next;

	return p;
}
int Brisanje(pozicija p, char* prezime)
{
	pozicija prev = NULL;
	pozicija curr = NULL;

	prev = TraziElement(p, prezime); //trazimo prethodni element

	if (prev == NULL)
	{
		printf("Ta osoba ne postoji u listi!\n\n");
		return -1;
	}

	curr = prev->next;
	prev->next = curr->next;
	free(curr);

	return 0;
}
pozicija TraziElement(pozicija p, char* prezime)
{
	pozicija prev = NULL;
	pozicija curr = NULL;

	prev = p;
	curr = p->next;

	while (curr != NULL && strcmp(curr->prezime, prezime) != NULL)
	{
		prev = curr;
		curr = prev->next;
	}
	if (curr == NULL)
		return NULL;
	else
		return prev;

}
int UnosNakon(pozicija p)
{
	pozicija prev = NULL;
	char prezime[20];
	printf("Unesite prezime nakon kojeg zelite dodati novi element:\n\n");
	scanf("%s", &prezime);

	prev = Pronadi(p, &prezime);

	UnosP(prev);

	return 0;
}
pozicija Pronadi(pozicija p, char* prezime)
{
	while (p != NULL && strcmp(p->prezime, prezime) != NULL)
		p = p->next;

	if (p == NULL)
	{
			printf("Takav element ne postoji!\n");
			return -1;
	}

	return p;
}
int UnosPrije(pozicija p)
{
	pozicija prev = NULL;
	char prezime[20];

	printf("Unesite prezime prije kojeg zelite unijeti element:\n\n");
	scanf("%s", &prezime);

	prev = PronadiPrethodni(p, &prezime);

	UnosP(prev);

	return 0;
}
pozicija PronadiPrethodni(pozicija p, char* prezime)
{
	pozicija prev = NULL;
	pozicija curr = NULL;

	prev = p;
	curr = prev->next;

	while (curr != NULL && strcmp(p->prezime, prezime) != NULL)
	{
		prev = curr;
		curr = prev->next;
	}

	if (prev == NULL)
	{
		printf("Ta osoba ne postoji u listi!\n\n");
		return -1;
	}

	return prev;
}
int Sortiranje(pozicija p)
{
	pozicija j, prev_j, temp, end;

	end = NULL;

	while (p->next != end)
	{
		prev_j = p;
		j = p->next;
		while (j->next != end)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;
				j = temp;
			}

			prev_j = j;
			j = j->next;
		}
		end = j;
	}
	return 0;
}
int UpisDat(pozicija p)
{
	FILE* fp;
	char imeDat[20];

	printf("Unesite ime datoteke:\n\n");
	scanf("%s", &imeDat);

	fp = fopen(imeDat, "w");

	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (p != NULL)
	{
		printf(fp, "%s %s %d", p->ime, p->prezime, p->god);
		p = p->next;
	}

	fclose(fp);

	return 0;
}
int CitanjeDat(pozicija p)
{
	pozicija temp = NULL;

	FILE* fp;
	char imeDat[20];

	printf("Unesite ime datoteke:\n\n");
	scanf("%s", &imeDat);

	fp = fopen(imeDat, "r");

	if(fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(fp))
	{
		temp = (pozicija)malloc(sizeof(Osoba));

		fscanf(fp, "%s %s %d", temp->ime, temp->prezime, &temp->god);

		temp->next = p->next;
		p->next = temp;
		p = temp;
	}
	fclose(fp);

	return 0;
}
