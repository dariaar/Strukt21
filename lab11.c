#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 30
#define MAX_HASH_TABLE_SIZE 11

struct _stablo;
typedef struct _stablo* PozicijaStablo;
typedef struct _stablo {
	char grad[MAX];
	int populacija;
	PozicijaStablo L;
	PozicijaStablo D;
} stablo;

struct _lista;
typedef struct _lista* PozicijaLista;
typedef struct lista {
	char drzava[MAX];
	PozicijaStablo gradovi;
	PozicijaLista next;
} lista;

struct _HashT;
typedef struct _HashT* HashTab;
typedef struct _HashT{
	PozicijaLista* headLista;
} HashT;

PozicijaLista StvoriClanListe();
PozicijaLista NadiDrzavu(HashTab, char*);
PozicijaStablo StvoriClanStabla();
int DodajDrzavaUHashTablicu(HashTab, char*, char*);
int ProcitajDatotekuDrzava(HashTab, char*);
int DodajDrzavaUListu(PozicijaLista , char* , char*);
PozicijaStablo DodajGradUStablo(PozicijaStablo, char*, int);
PozicijaStablo ProcitajDatotekuGradovi(PozicijaStablo, char*);
int PrintDrzavaGradovi(PozicijaLista);
int InOrderPrintStablo(PozicijaStablo);
int Odaberi(HashTab);
int NadiPopulacijeGradovaVeceOdX(PozicijaStablo, int);
HashTab StvoriHashTab();

int main() {

	HashTab hashTab = NULL;

	hashTab = StvoriHashTab();

	ProcitajDatotekuDrzava(hashTab, "drzave.txt");

	Odaberi(hashTab);

	printf("\nPritisnite enter za izlaz iz programa ");
	fseek(stdin, 0, SEEK_END);
	getchar();
	return EXIT_SUCCESS;
}


int Odaberi(HashTab hashTab){
	PozicijaLista q = NULL;
	char tmp1[MAX];
	int tmp2;
	printf("Odaberi ime drzave koju zelis pretrazivati: ");
	scanf(" %s", tmp1);
	printf("Nadi sve gradove vece od x stanovnika: ");
	scanf("%d", &tmp2);
	q = NadiDrzavu(hashTab, tmp1);
	if(!q){
		printf("Zadana drzava ne postoji!");
		return EXIT_FAILURE;
	}
	NadiPopulacijeGradovaVeceOdX(q->gradovi, tmp2);
	return EXIT_SUCCESS;
}

int NadiPopulacijeGradovaVeceOdX(PozicijaStablo p, int populacijaX){
	if(p == NULL){
		return EXIT_SUCCESS;
	}

	NadiPopulacijeGradovaVeceOdX(p->L, populacijaX);

	if(p->populacija > populacijaX){
		printf("%s %d, ", p->grad, p->populacija);
	}
	NadiPopulacijeGradovaVeceOdX(p->D, populacijaX);

	return EXIT_SUCCESS;
}

PozicijaLista StvoriClanListe() {
	PozicijaLista q = malloc(sizeof(lista));
	if (q == NULL) {
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	strcpy(q->drzava, "");
	q->gradovi = NULL;
	q->next = NULL;
	return q;
}

PozicijaStablo StvoriClanStabla(char* grad, int populacija) {
	PozicijaStablo q = malloc(sizeof(stablo));
	if (q == NULL) {
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	strcpy(q->grad, grad);
	q->populacija = populacija;
	q->L = NULL;
	q->D = NULL;
	return q;
}

int InOrderPrintStablo(PozicijaStablo p){
	if(p == NULL){
		return EXIT_SUCCESS;
	}
	else{
		InOrderPrintStablo(p->L);
		printf("%s %d, ", p->grad, p->populacija);
		InOrderPrintStablo(p->D);
	}
	return EXIT_SUCCESS;
}

int ProcitajDatotekuDrzava(HashTab hashTab, char* imeDat){
	char imeDrzava[MAX] = "", imeGradoviDat[MAX] = "";

	FILE* dat = NULL;
	dat = fopen(imeDat, "r");
	if(!dat){
		printf("Greska pri otvaranju datoteke");
		return EXIT_FAILURE;
	}

	while(!feof(dat)){
		fscanf(dat, "%s %s", imeDrzava, imeGradoviDat);
		DodajDrzavaUHashTablicu(hashTab, imeDrzava, imeGradoviDat);
	}
	fclose(dat);
	return EXIT_SUCCESS;
}

int DodajDrzavaUListu(PozicijaLista headLista, char* drzava, char* imeGradoviDat) {
	PozicijaLista tmp = NULL;
	char tmp1[MAX], tmp2[MAX];

	tmp = StvoriClanListe();
	strcpy(tmp->drzava, drzava);

	tmp->gradovi = ProcitajDatotekuGradovi(tmp->gradovi, imeGradoviDat);

	strcpy(tmp1, drzava);

	while(headLista->next != NULL){
		strcpy(tmp2, headLista->next->drzava);
		if(strcmp(strupr(tmp1), strupr(tmp2)) > 0){
			headLista = headLista->next;
			continue;
		}
		break;
	}

	tmp->next = headLista->next;
	headLista->next = tmp;
}

PozicijaStablo ProcitajDatotekuGradovi(PozicijaStablo headStablo, char* imeDat){
	char gradIme[MAX] = "";
	int gradPopulacija = 0;
	FILE* dat = NULL;

	dat = fopen(imeDat, "r");
	if(!dat){
		printf("Greska pri otvaranju datoteke");
		return NULL;
	}

	while(!feof(dat)){
		fscanf(dat, "%s %d", gradIme, &gradPopulacija);
		headStablo = DodajGradUStablo(headStablo, gradIme, gradPopulacija);
	}
	fclose(dat);
	return headStablo;
}

PozicijaStablo DodajGradUStablo(PozicijaStablo p, char* grad, int populacija){
	if(p == NULL){
		p = StvoriClanStabla(grad, populacija);
	}
	else if(populacija == p->populacija){
		if(strcmp(grad, p->grad) < 0){
			p->L = DodajGradUStablo(p->L, grad, populacija);
		}
		if(strcmp(grad, p->grad) > 0){
			p->D = DodajGradUStablo(p->D, grad, populacija);
		}
	}
	else{
		if(populacija < p->populacija){
			p->L = DodajGradUStablo(p->L, grad, populacija);
		}
		if(populacija > p->populacija){
			p->D = DodajGradUStablo(p->D, grad, populacija);
		}
	}
	return p;
}

PozicijaLista NadiDrzavu(HashTab hashTab, char* drzava){
	int index = hashFunkcija(drzava);
	PozicijaLista headLista = hashTab->headLista[index];

	while(headLista->next != NULL){
		if(strcmp(drzava, headLista->next->drzava) == 0){
			return headLista->next;
		}
		else{
			headLista = headLista->next;
		}
	}
	return NULL;
}

int hashFunkcija(char* imeDrzave){
	int rez = 0;
	for(int i = 0; i < strlen(imeDrzave) || i < 5; i++){
		rez += imeDrzave[i];
	}
	return rez % MAX_HASH_TABLE_SIZE;
}

HashTab StvoriHashTab(){
	HashTab hash = NULL;
	int i = 0;

	hash = (HashTab) malloc(sizeof(HashT));
	if(hash == NULL){
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	hash->headLista = (PozicijaLista*) malloc(sizeof(PozicijaLista) * MAX_HASH_TABLE_SIZE);
	if(hash->headLista == NULL){
		printf("Greska pri alociranju memorije");
		return NULL;
	}

	for(i = 0; i < MAX_HASH_TABLE_SIZE; i++){
		hash->headLista[i] = StvoriClanListe();
	}
	return hash;
}

int DodajDrzavaUHashTablicu(HashTab hashTab, char* imeDrzava, char* imeGradoviDat){
	int  index = 0;
	index = hashFunkcija(imeDrzava);

	DodajDrzavaUListu(hashTab->headLista[index], imeDrzava, imeGradoviDat);
}
