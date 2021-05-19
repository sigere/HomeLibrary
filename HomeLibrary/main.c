#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

void wypisz_ksiazke(struct book* b)
{
	printf("------------------\n");
	printf("Imie autora:    \t%s\n", b->authorName);
	printf("Nazwisko autora:\t%s\n", b->authorSurname);
	printf("Tytul ksiazki:  \t%s\n", b->topic);
	printf("Rok wydania:    \t%d\n", b->year);
	printf("Rodzaj okladki: \t%d\n", b->hardCover);
	printf("Liczba stron:   \t%d\n", b->pages);
	printf("Rodzaj ksiazki: \t%d\n", b->type);
}

void dodaj_ksiazke(struct spis* biblioteka) {
	struct book newbie;
	char name[50], surname[50], title[100];
	printf("podaj imie i nazwisko autora:\n");
	scanf_s("%s\n%s", newbie.authorName, sizeof(newbie.authorName), newbie.authorSurname, sizeof(newbie.authorSurname));
	printf("podaj tytul ksiazki:\n");
	scanf_s("%s", newbie.topic, sizeof(newbie.topic));
	int c;
	int ok = 0;
	printf("Wybierz rodziaj okladki: 1, gdy miekka / 2, gdy twarda\n");
	do {
		if (scanf_s("%d", &c) < 1) {
			while ((getchar()) != '\n');
			c = 3;
		}
		switch (c) {

		case 1:
			printf("miekka\n");
			ok = 1;
			newbie.hardCover = false;
			break;
		case 2:
			printf("twarda\n");
			ok = 1;
			newbie.hardCover = true;
			break;
		default:
			printf("Niepoprawne dane, wprowadz cyfre z zakresu 1-2.\n");
		}
	} while (ok != 1);

	printf("Wybierz rodzaj ksiazki: \n1-fantasy\n2-dramat\n3-komedia\n");
	int d;
	int ok1 = 0;
	do {
		if (scanf_s("%d", &d) < 1) {
			while ((getchar()) != '\n');
			d = 5;
		}
		switch (d) {

		case 1:
			printf("Fantastyka\n");
			ok1 = 1;
			newbie.type = Fantasy;
			break;
		case 2:
			printf("Dramat\n");
			ok1 = 1;
			newbie.type = Drama;
			break;
		case 3:
			printf("Komedia\n");
			ok1 = 1;
			newbie.type = Comedy;
			break;
		default:
			printf("Niepoprawne dane, wprowadz cyfre z zakresu 1-3.\n");
		}
	} while (ok1 != 1);
	int liczba_stron;
	int ok2 = 0;
	printf("podaj liczbe stron:\n");
	do {
		if (scanf_s("%d", &liczba_stron) < 1) {
			while ((getchar()) != '\n');
			printf("Niepoprawne dane, wprowadz liczbe.\n");
		}
		else {
			ok2 = 1;
			newbie.pages = liczba_stron;
		}
	} while (ok2 != 1);
	printf("podaj rok wydania:\n");
	int rok_wydania;
	int ok3 = 0;
	do {
		if (scanf_s("%d", &rok_wydania) < 1) {
			while ((getchar()) != '\n');
			printf("Niepoprawne dane, wprowadz liczbe.\n");
		}
		else {
			ok3 = 1;
			newbie.year = rok_wydania;
		}
	} while (ok3 != 1);

	if (addBook(biblioteka, newbie))
	{
		//wpisz, ze udalo sie
		//write(biblioteka);
	}
	else
	{
		//wpisz ze sie nie uda³o
	}
}


void wyszukaj_ksiazke(struct spis* biblioteka) {
	int b;
	int okay = 0;
	char surname[50], title[100];
	struct book* ksiazka;
	printf("Wybierz numer operacji:\n");
	printf("1 - wyszukaj ksiazke po nazwisku autora\n2 - wyszukaj ksiazke po tytule\n");
	do {
		if (scanf_s("%d", &b) < 1) {
			while ((getchar()) != '\n');
			b = 3;
		}
		switch (b) {

		case 1:
			printf("Podaj nazwisko autora:\n");
			scanf_s("%s", surname, sizeof(surname));
			okay = 1;
			ksiazka = getByAuthorName(biblioteka, surname);
			if (ksiazka)
				wypisz_ksiazke(ksiazka);
			break;
		case 2:
			printf("Podaj tytul ksiazki:\n");
			scanf_s("%s", title, sizeof(title));
			okay = 1;
			ksiazka = getByTitle(biblioteka, title);
			if (ksiazka)
				wypisz_ksiazke(ksiazka);
			break;
		default:
			printf("Niepoprawne dane, wprowadz cyfre z zakresu 1-2.\n");
		}
	} while (okay != 1);
}

void usun_ksiazke(struct spis* biblioteka) {
	char title[100];
	printf("Podaj tytul ksiazki, ktora chcesz usunac:\n");
	scanf_s("%s", title, sizeof(title));
	if (deleteByTopic(biblioteka, title))
	{
		//wpisz, ze sie uda³o
		write(biblioteka);
	}
	else
	{
		//wypisz ze nie znaleziono ksiazki o tym tytule

	}

}



void wypisz_ksiazki(struct spis* biblioteka)
{
	struct elem* tmp = biblioteka->poczatek;
	printf("Zawartosc biblioteczki:\n");

	while (tmp)
	{
		wypisz_ksiazke(&tmp->Dane);
		tmp = tmp->nast;
	}
	printf("\n");
}

void sortuj_ksiazki(struct spis* biblioteka)
{
	//zapytac uzytkownika czy rosnaco czy malejaco
	//jesli rosnaco:
	sortByTopic(biblioteka, true);

	//jesli malajaco:
	//sortByTopic(biblioteka, false);

	write(biblioteka);
}

int main()
{
	struct spis* library = read();
	system("cls");
	printf("Hello library!\n");
	int a;
	do {
		printf("Mozliwe do wykonania operacje:\n");
		printf("0 - wyjscie\n1 - dodaj ksiazke do biblioteki\n2 - wyszukaj ksiazke w bibliotece\n3 - usun ksiazke z biblioteki\n4 - posortuj ksiazki\n5 - wyswietl zawartosc\n");
		printf("Wybierz numer operacji:\n");
		if (scanf_s("%d", &a) < 1) {
			while ((getchar()) != '\n');
			a = 6;
		}
		switch (a) {
		case 0:
			exit(0);
			break;

		case 1:
			dodaj_ksiazke(library);
			break;

		case 2:
			wyszukaj_ksiazke(library);
			break;

		case 3:
			usun_ksiazke(library);
			break;

		case 4:
			sortuj_ksiazki(library);
			break;

		case 5:
			wypisz_ksiazki(library);
			break;

		default:
			printf("Niepoprawne dane, wprowadz cyfre z zakresu 0-5.\n");
		}
	} while (1);
}