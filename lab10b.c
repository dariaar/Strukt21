#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 60

struct _list;
typedef struct _list* poz;
typedef struct _list
{
    char grad[MAX];
    int stanovnistvo;
    poz next;
}list;

struct _stablo;
typedef struct _stablo* pozicija;
typedef struct _stablo
{
    char drzava[MAX];
    poz list;
    pozicija L;
    pozicija D;
}stablo;

pozicija stvoriElement(pozicija s);
pozicija citajDatoteku(pozicija p, char*dat);
pozicija unosStabla(pozicija s, char*drzava, char*drzava_ime);
pozicija nadiDrzavu(pozicija s, char*drzava);
int inoreder(pozicija s);
int napraviListu(poz p, char*grad, int stanovnistvo);
poz procitajGradove(poz p, char*dat);
int print(poz p);
poz stvoriClan(poz p);
int ispis(poz p, int br);

int main()
{
    pozicija root = NULL, tren=NULL;
	char dat[MAX] = "drzave.txt", drzava[MAX] = { 0 }, c = { 0 };
	int br=0;

	root = stvoriElement(root);

	root = citajDatoteku(root, dat);
	inorder(root);

    printf("\n1.Biraj drzavu\n2.Izlaz iz petlje\n");
		printf("\nOdabir:");
		scanf(" %c", &c);
		switch (c)
		{
		case '1':
			printf("Odaberi drzavu:");
			scanf(" %s", drzava);
			tren = nadiDrzavu(root, drzava);
			if (tren == NULL)
			{
				printf("Odabrana drzava nije unesena u file.");
				return 0;
			}
			printf("\nPrikazat ce se gradovi s brojem stanovnika vecim nego uneseni.Unesi broj:");
			scanf("%d", &br);
			ispis(tren->list, br);
			break;
		case '2':
			printf("Izlazak iz petlje.\n");
			break;
		}

		return 0;
}

poz stvoriClan(poz p)
{
    p = (poz)malloc(sizeof(list));
	if (p == NULL) {
		printf("Greska pri alokaciji memorije");
		return NULL;
	}

	strcpy(p->grad, "");
	p->stanovnistvo = 0;
	p->next = NULL;

	return p;
}

pozicija stvoriElement(pozicija s)
{
   s = (pozicija)malloc(sizeof(stablo));

	if (s == NULL)
	{
		printf("Greska pri alokaciji memorije.");
		return -1;
	}

	s->L = NULL;
	s->D = NULL;
	s->list = NULL;
	strcpy(s->drzava, "");

	return s;
}

pozicija citajDatoteku(pozicija p, char*dat)
{
    FILE* file = NULL;
	char drzava[MAX] = { 0 }, drzava_dat[MAX] = { 0 };

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s\n", drzava, drzava_dat);
		p=unosStabla(p, drzava, drzava_dat);
	}

	fclose(file);
	return p;
}

pozicija unosStabla(pozicija s, char*drzava, char*drzava_dat)
{
    if (s == NULL)
	{
		s = stvoriElement(s);
		strcpy(s->drzava, drzava);
		s->list = NULL;
		s->list = citajDatoteku(s->list, drzava_dat);
	}
	else if (strcmp(s->drzava, drzava) > 0)
		s->L=unosStabla(s->L, drzava, drzava_dat);
	else if (strcmp(s->drzava, drzava) < 0)
		s->D = unosStabla(s->D, drzava, drzava_dat);

	return s;
}

poz procitajGradove(poz p, char *dat)
{
    FILE* file = NULL;
	char grad[MAX] = { 0 };
	int stanovnistvo = 0;

	p = stvoriClan(p);

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %d", grad, &stanovnistvo);
		napraviListu(p, grad, stanovnistvo);
	}

	fclose(file);
	return p;
}

int napraviListu(poz p, char*grad, int stanovnistvo)
{
    poz q = NULL;
	q = stvoriClan(q);

	strcpy(q->grad, grad);
	q->stanovnistvo = stanovnistvo;

	while (p->next != NULL)
	{
		if (q->stanovnistvo < p->next->stanovnistvo)
			break;
		else if(q->stanovnistvo == p->next->stanovnistvo)
		{
			if (strcmp(q->grad, p->next->grad) < 0)
				break;
			else if (strcmp(q->grad, p->next->grad) > 0)
			{
				p = p->next;
				continue;
			}
		}
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;

}

int print(poz p)
{
	if (p == NULL)
		return 0;
	else
	{
		p=p->next;
		while (p != NULL)
		{
			printf(" %s-%d ", p->grad, p->stanovnistvo);
			p = p->next;
		}
		return 0;
	}
}


int inorder(pozicija s)
{
	if (s == NULL)
		return 0;
	else
	{
		inorder(s->L);
		printf("\n%s:\n", s->drzava);
		print(s->list);
		inorder(s->D);
	}
	return 0;
}

pozicija nadiDrzavu(pozicija s, char*drzava)
{
   if (s == NULL)
		return NULL;
	else if (strcmp(drzava, s->drzava) == 0)
		return s;
	else if (strcmp(drzava, s->drzava) > 0)
		return nadiDrzavu(s->D, drzava);

	return nadiDrzavu(s->L, drzava);
}

int ispis(poz p, int br)
{
	while (p != NULL)
	{
		if (br< p->stanovnistvo)
			printf(" %s-%d", p->grad, p->stanovnistvo);
		p = p->next;
	}
	return 0;
}

