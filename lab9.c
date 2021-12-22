#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

struct _cvor;
typedef struct _cvor* Poz;
typedef struct _cvor
{
	int br;
	Poz L;
	Poz D;
}cvor;

struct _lista;
typedef struct _lista* ListaPoz;
typedef struct _lista
{
	int el;
	ListaPoz next;
}lista;

int inorder(Poz S, ListaPoz head);
Poz StvoriPrazno(Poz S);
Poz insert(Poz S, int el);
Poz replace(Poz S);
int suma(Poz S);
Poz random(Poz S);
int UmetniNaKraj(ListaPoz head, int br);
ListaPoz PronadiZadnji(ListaPoz head);
int umetni(ListaPoz head, int br);
int ispisliste(ListaPoz p1, ListaPoz p2, ListaPoz p3, char* dat);

int main()
{
	Poz root = NULL;
	ListaPoz head1 = NULL, head2 = NULL, head3 = NULL;
	char ime[50] = "vjezba9_stablo.txt";

	root = StvoriPrazno(root);
	head1 = (ListaPoz)malloc(sizeof(lista));
	head1->next = NULL;
	head2 = (ListaPoz)malloc(sizeof(lista));
	head2->next = NULL;
	head3 = (ListaPoz)malloc(sizeof(lista));
	head3->next = NULL;

	root = insert(root, 2);
	root = insert(root, 5);
	root = insert(root, 7);
	root = insert(root, 8);
	root = insert(root, 11);
	root = insert(root, 1);
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 3);
	root = insert(root, 7);
	inorder(root, head1);

	root = replace(root);
	inorder(root, head2);

	root = StvoriPrazno(root);
	root = random(root);
	inorder(root, head3);
	ispisliste(head1->next, head2->next, head3->next, ime);

	return 0;
}

Poz StvoriPrazno(Poz S)
{
	if (S != NULL)
	{
		S->L = StvoriPrazno(S->L);
		S->D = StvoriPrazno(S->D);
		free(S);
	}
	return NULL;
}

int inorder(Poz S, ListaPoz head)
{
	if (S == NULL)
		return 0;

	inorder(S->L, head);
	UmetniNaKraj(head, S->br);
	inorder(S->D, head);

	return 0;
}

Poz insert(Poz S, int el)
{
	if (S == NULL)
	{
		S = (Poz)malloc(sizeof(cvor));
		S->br = el;
		S->L = NULL;
		S->D = NULL;
	}
	else if (el >= S->br)
	{
		S->L = insert(S->L, el);
	}
	else if (el <= S->br)
	{
		S->D = insert(S->D, el);
	}

	return S;
}

int suma(Poz S)
{
	int suma1 = 0;
	if (S == NULL)
		return suma1;
	if (S->L != NULL)
		suma1 += S->L->br + suma(S->L);
	if (S->D != NULL)
		suma1 += S->D->br + suma(S->D);

	return suma1;
}
Poz replace(Poz S)
{
	if (S != NULL)
	{
		S->br = suma(S);
		S->L = replace(S->L);
		S->D = replace(S->D);
	}
	return S;
}

Poz random(Poz S)
{
	int i = 0, br = 0;

	srand(time(NULL));
	for (i = 0;i < 10;i++)
	{
		br = (rand() % (90 - 10 + 1)) + 10;
		S = insert(S, br);
	}

	return S;
}

int UmetniNaKraj(ListaPoz head, int br)
{
	ListaPoz zadnji = NULL;
	zadnji = PronadiZadnji(head);
	umetni(zadnji, br);
	return 0;
}

ListaPoz PronadiZadnji(ListaPoz head)
{
	while (head->next != NULL)
		head = head->next;

	return head;
}

int umetni(ListaPoz head, int br)
{
	ListaPoz prvi = NULL;
	prvi = (ListaPoz)malloc(sizeof(lista));

	if (prvi == NULL)
		return -1;
	prvi->el = br;
	prvi->next = head->next;
	head->next = prvi;

	return 0;
}

int ispisliste(ListaPoz p1, ListaPoz p2, ListaPoz p3, char* dat)
{
	FILE* f = NULL;
	f = fopen(dat, "w");
	if (f == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!");
		return -1;
	}


	while (p1 != NULL)
	{
		fprintf(f,"%d\t", p1->el);
		p1 = p1->next;
	}
	fprintf(f,"\n");
	while (p2 != NULL)
	{
		fprintf(f, "%d\t", p2->el);
		p2 = p2->next;
	}
	fprintf(f, "\n");
	while (p3 != NULL)
	{
		fprintf(f, "%d\t", p3->el);
		p3 = p3->next;
	}


	fclose(f);
	return 0;
}
