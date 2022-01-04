#define _CRT_SECURE_NO_WARNINGS_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 60

struct _stablo;
typedef struct _stablo *pozicija;
typedef struct _stablo
{
    char grad[MAX];
    int stanovnistvo;
    pozicija L;
    pozicija D;
}stablo;

struct _list;
typedef struct _list* poz;
typedef struct _list
{
    char drzava[MAX];
    pozicija stablo;
    poz next;
}list;

int citajDatoteku(poz p, char *dat);
int unosListe(poz p, char* drzava_ime, char *drzava_dat);
pozicija napraviStablo(pozicija root, char* grad, int stanovnistvo);
int print(poz p);
int inorder(pozicija s);
int ispisVeceOd(pozicija p, int br);
poz stvoriElement(poz p);
poz pronadiDrzavu(poz p, char* drzava);
pozicija procitajGradove(pozicija root, char *drzava_dat);
int odabir(poz);

int main()
{
    poz head = NULL, p = NULL;
    char dat[MAX] = "drzave.txt";


    head = stvoriElement(head);
    p = stvoriElement(p);

    citajDatoteku(head, dat);
    print(head->next);

  odabir(head);

  return 0;

}

int odabir(poz head)
{
    poz p = NULL;
    char c = {0}, drzava[MAX]= {0};
    int br=0;

     printf("\n1.Odaberi drzavu\n2.Izadi iz oetlje\n");
    scanf("%c", &c);
    switch(c)
    {
        case '1':
            prnitf("odaberi drzavu");
            scanf("%s", drzava);
            p = pronadiDrzavu(head, drzava);
            if(p==NULL)
            {
                printf("drzava nije u file-u");
                return -5;
            }
            printf("unesite minimalan broj stanovnika");
            scanf("%d", &br);
            printf("gradovi sa stanovnistvom vecim od trazenog:");
            ispisVeceOd(p->stablo, br);
            break;
        case '2':
            printf("izlaz iz petlje\n");
            break;

    }
    return 0;
}

poz stvoriElement(poz p)
{
    p = (poz)malloc(sizeof(list));
    if(p==NULL)
    {
        printf("greska pri alokaciji memorije");
        return -3;
    }
    strcpy(p->drzava, "");
    p->next = NULL;
    p->stablo = NULL;
}

int citajDatoteku(poz p, char* dat)
{
    FILE * file = NULL;
    char drzava_ime[MAX] = { 0 }, drzava_dat[MAX] = { 0 };

	file = fopen(dat, "r");
	if (file ==NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return - 1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s\n", drzava_ime, drzava_dat);
		unosListe(p, drzava_ime, drzava_dat);
	}

	fclose(file);
	return 0;
}

int unosListe(poz p, char* drzava_ime, char*drzava_dat)
{
    poz q = NULL;
	char pom[MAX] = { 0 };

	q = (poz)malloc(sizeof(list));
	if (q == NULL)
	{
		printf("Greska pri alokaciji memorije.");
		return -2;
	}


	strcpy(q->drzava, drzava_ime);
	q->stablo = NULL;
	q->stablo = procitajGradove(q->stablo, drzava_dat);
	strcpy(pom, drzava_ime);

	while (p!= NULL)
	{
		if (p->next == NULL)
		{
			p->next = q;
			q->next = NULL;
			break;
		}
		else if (strcmp(pom, p->next->drzava) <0)
		{
			q->next = p->next;
			p->next = q;
			break;
		}
		p = p->next;
	}
	return 0;
}
pozicija procitajGradove(pozicija root, char*drzava_dat)
{
   FILE* file = NULL;
	char grad[MAX] = { 0 };
	int stanovnistvo = 0;

	file = fopen(drzava_dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %d\n", grad, &stanovnistvo);
		root=napraviStablo(root, grad, stanovnistvo);
	}
	fclose(file);
	return root;
}
pozicija napraviStablo(pozicija s, char*grad, int stanovnistvo)
{
   if (s == NULL)
	{
		s = (pozicija)malloc(sizeof(stablo));
		if (s == NULL)
		{
			printf("Greska pri alokaciji memorije");
			return NULL;
		}
		strcpy(s>grad, grad);
		s->stanovnistvo = stanovnistvo;
		s->L = NULL;
		s->D = NULL;
	}
	else if(stanovnistvo == s->stanovnistvo)
	{
		if (strcmp(grad, s->grad) < 0)
			s->L = napraviStablo(s->L, grad, stanovnistvo);
		else if (strcmp(grad, s->grad) > 0)
			s->D = napraviStablo(s->D, grad, stanovnistvo);
	}
	else
	{
		if (stanovnistvo < s->stanovnistvo)
			s->L = napraviStablo(s->L, grad, stanovnistvo);
		else if (stanovnistvo > s->stanovnistvo)
			s->D = napraviStablo(s->D, grad, stanovnistvo);
	}
	return s;
}

int print(poz p)
{
	while (p != NULL)
	{
		printf("\n%s:\n", p->drzava);
		inorder(p->stablo);
		p = p->next;
	}
}

int inorder(pozicija s)
{
	if (s == NULL)
		return 0;

	inorder(s->L);
	printf("%s-%d", s->grad, s->stanovnistvo);
	inorder(s->D);

	return 0;
}

poz pronadiDrzavu(poz p, char* drzava)
{
	while (p->next != NULL && strcmp(drzava, p->drzava) != 0)
		p = p->next;

	return p;
}

int ispisVeceOd(pozicija p, int br)
{
	if (p == NULL)
		return 0;

	ispisVeceOd(p->L, br);

	if (br < p->stanovnistvo)
		printf("%s %d\n", p->grad, p->stanovnistvo);

	ispisVeceOd(p->D, br);

	return 0;
}


