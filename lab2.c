
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#define BUFFER_LENGTH 1024
#define ERROR -1
#define SUCCESS 0


typedef struct student* Position;
typedef struct student {
	char name[BUFFER_LENGTH];
	char surname[BUFFER_LENGTH];
	int birht_year;
	Position Next;
}student;



int Print_Menu();
Position CreateListNode(Position);
Position Insert_Student_Data(Position);
int Insert_At_Beggining_Of_List(Position);
int Print_List(Position);
Position Find_Last(Position);
int Insert_At_End_Of_List(Position);
Position Find_By_LastName(Position);
int Delete_By_LastName(Position);
Position Find_Previous_List_Element(Position);
int Garbage_Collector(Position);


int main()
{
	student head;
	Position searched_Student = NULL;
	char* choice;
	head.Next = NULL;
	choice = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (choice == NULL)
	{
		printf("\r\tMemorija nije dobro alocirana");
		return ERROR;
	}
	memset(choice, '\0', BUFFER_LENGTH);

	while (strcmp(choice, "EXIT") != SUCCESS)
	{
		memset(choice, 0, BUFFER_LENGTH);
		Print_Menu();

		scanf(" %s", choice);

		if (strcmp(choice, "1") == SUCCESS)
		{
			Insert_At_Beggining_Of_List(&head);
		}
		else if (strcmp(choice, "2") == SUCCESS)
		{
			Print_List(&head);
		}
		else if (strcmp(choice, "3") == SUCCESS)
		{
			Insert_At_End_Of_List(&head);
		}
		else if (strcmp(choice, "4") == SUCCESS)
		{
			searched_Student = Find_By_LastName(&head);
			if (searched_Student != NULL)
			{
				printf("\r\tTrazili ste studenta:\r\n %s %s %d\r\n", searched_Student->name, searched_Student->surname, searched_Student->birht_year);
			}
			else
			{
				printf("\r\tStudent kojeg ste unijeli trenutno nije u bazi podataka.\r\n");
			}
		}
		else if (strcmp(choice, "5") == SUCCESS)
		{
			Delete_By_LastName(&head);
			Print_List(&head);
		}


		else if (strcmp(choice, "Exit") == SUCCESS)
		{
			break;
		}
		else
		{
			printf("\r\tNepravilan unos <%s>.\rProbajte ponovo.\n", choice);
		}
	}
	free(choice);
	Garbage_Collector(&head);

	return SUCCESS;
}

int Print_Menu()
{

	printf("VJEZBA 2 - Vezane liste\n");

	printf("1. Unesi studenta na pocetak.\n");
	printf("2. Ispisi listu.\n");
	printf("3. Unesi studenta na kraj.\n");
	printf("4. Pronadji preko prezimena.\n");
	printf("5. Izbrisi preko prezimena.\n");
	printf("A. Ispisi listu u FILE.\n");
	printf("Exit. Izadji iz programa.\n");

	printf("\nUnesite izbor : ");

	return SUCCESS;
}

int Insert_At_Beggining_Of_List(Position P)
{

	Position Q = NULL;
	Q = CreateListNode(Q);

	if (Q == NULL)
	{
		printf("\nMemorija nije dobro alocirana za varijablu u CreateListNode.");
		return ERROR;
	}
	Q = Insert_Student_Data(Q);
	if (Q == NULL)
	{
		printf("\nEror u funkciji Insert_Student_Data.");
		return ERROR;
	}

	Q->Next = P->Next;
	P->Next = Q;

	return SUCCESS;
}

Position CreateListNode(Position Q)
{
	Q = (Position)malloc(sizeof(student));
	if (Q == NULL)
	{
		printf("\nMemorija nije dobro alocirana za varijablu u CreateListNode.");
		return NULL;
	}

	Q->Next = NULL;
	return Q;
}
Position Insert_Student_Data(Position Q)
{
	if (Q == NULL) {
		printf("\nDoslo je do pogreske u Insert_Student_Data funkciji.");
		return NULL;
	}
	printf("Unesite ime, prezime i godinu rodjena studenta: \n");
	scanf(" %s %s %d", Q->name, Q->surname, &Q->birht_year);

	return Q;
}

int Print_List(Position P) {
	P = P->Next;
	if (P == NULL) {
		printf("\nBaza podataka je prazna!");
	}
	else {
		printf("\nOvi studenti su u bazi podataka: \r\n");
		while (P != NULL) {
			printf("%s %s %d\r\n", P->name, P->surname, P->birht_year);
			P = P->Next;
		}
	}
	printf("\n");
	return SUCCESS;
}

int Insert_At_End_Of_List(Position P) {
	if (P == NULL) {
		printf("\nDoslo je do pogreske u funkciji Insert_At_End_Of_List.");
		return ERROR;
	}
	P = Find_Last(P);
	return Insert_At_Beggining_Of_List(P);
}
Position Find_Last(Position P) {
	if (P == NULL) {
		printf("\nDoslo je do pogreske u funkciji Find_Last.");
		return NULL;
	}
	while (P->Next != NULL)
		P = P->Next;

	return P;
}

Position Find_By_LastName(Position P) {
	P = P->Next;
	char* lastName = NULL;
	lastName = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (lastName == NULL) {
		printf(" Doslo je do pogreske u funkciji Find_By_LastName.");
		return NULL;
	}
	memset(lastName, '\0', BUFFER_LENGTH);

	printf("\nUnesite prezime studenta kojeg trazite: \n");
	scanf(" %s", lastName);
	while (P != NULL && strcmp(P->surname, lastName) != 0) {
		P = P->Next;
	}
	free(lastName);
	return P;
}

int Delete_By_LastName(Position P) {
	Position temp = NULL;
	P = Find_Previous_List_Element(P);
	if (P == NULL) {
		printf("Student kojeg ste trazili prezimenom ne postoji u bazi podataka.");
		return ERROR;
	}
	temp = P->Next;
	if (temp != NULL) {
		P->Next = temp->Next;
		printf("Student sa sljedecim podacima bit ce uklonjen s liste: %s %s %d", temp->name, temp->surname, temp->birht_year);
		free(temp);
	}
	return SUCCESS;
}
Position Find_Previous_List_Element(Position P) {
	char* lastName = NULL;

	lastName = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (lastName == NULL) {
		printf("Doslo je do pogreske u Find_Previous_List_Element");
		return NULL;
	}
	memset(lastName, '\0', BUFFER_LENGTH);
	printf("Unesite prezime studenta kojeg trazite: ");
	scanf(" %s", lastName);
	while (P->Next != NULL && strcmp(P->Next->surname, lastName) != 0)
		P = P->Next;

	if (P->Next == NULL)
		return NULL;

	free(lastName);

	return P;
}
int Garbage_Collector(Position P) {
	if (P->Next != NULL) {
		Garbage_Collector(P->Next);
	}
	free(P);
	return SUCCESS;
}
