#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

bool addBook(struct spis* library, struct book newbie)
{
	struct elem* newNode = malloc(sizeof(struct elem));
	newNode->Dane = newbie;
	newNode->nast = NULL;
	if (!library->poczatek) {
		library->poczatek = newNode;
		library->koniec = newNode;
		return true;
	}
	library->koniec->nast = newNode;
	library->koniec = newNode;
	return true;
}

bool write(struct spis* library) {
	FILE* file;
	fopen_s(&file, "library.dat", "w");
	if (!file) return false;

	struct elem* tmp = library->poczatek;
	struct elem* del;
	while (tmp) {
		struct book b = tmp->Dane;
		fwrite(&b, sizeof(struct book), 1, file);
		tmp = tmp->nast;
	}
	fclose(file);
	return true;
}

struct spis* read()
{
	FILE* file = NULL;
	fopen_s(&file, "library.dat", "r");

	struct spis* library = (struct spis*)malloc(sizeof(struct spis));
	library->koniec = NULL;
	library->poczatek = NULL;

	if (!file)
		return library;

	struct book input;

	while (fread(&input, sizeof(struct book), 1, file))
		if (!addBook(library, input)) {
			printf("err addBook!\n");
			fclose(file);
			return false;
		}
	fclose(file);
	return library;
}

struct book* getByAuthorName(spis* SP, const char authorName[], const char authorSurname[])
{
	elem* prev = 0, * tmp = SP->poczatek;
	while (tmp)
	{
		if (!strcmp(authorSurname, tmp->Dane.authorSurname) && !strcmp(authorName, tmp->Dane.authorName))
		{
			return &tmp->Dane;
		}
		prev = tmp;
		tmp = tmp->nast;
	}
	return NULL;
}

struct book* getByTitle(spis* SP, const char title[])
{
	elem* prev = 0, * tmp = SP->poczatek;
	while (tmp)
	{
		if (!strcmp(title, tmp->Dane.topic))
		{
			return &tmp->Dane;
		}
		prev = tmp;
		tmp = tmp->nast;
	}
	return NULL;
}

bool deleteByTopic(spis* SP, const char nazwa[])
{
	elem* prev = 0, * tmp = SP->poczatek;
	while (tmp)
	{
		if (!strcmp(nazwa, tmp->Dane.topic))
		{
			if (prev) prev->nast = tmp->nast;
			else SP->poczatek = tmp->nast;
			free(tmp);
			return true;
		}
		prev = tmp;
		tmp = tmp->nast;
	}
	return false;
}

void sortByTopic(struct spis* library, bool asc)
{
	if (!library->poczatek)
		return;

	struct spis* newLibrary = (struct spis*)malloc(sizeof(struct spis));
	newLibrary->poczatek = NULL;
	newLibrary->koniec = NULL;

	struct elem* preTemp = NULL;
	struct elem* preSuspect = NULL;
	struct elem* suspect = library->poczatek;
	struct elem* temp = library->poczatek;
	while (library->poczatek) {
		temp = library->poczatek;
		preTemp = NULL;
		preSuspect = NULL;
		suspect = library->poczatek;

		while (temp) {
			if ((asc && strcmp(temp->Dane.topic, suspect->Dane.topic) < 0)
				|| (!asc && strcmp(temp->Dane.topic, suspect->Dane.topic) > 0))
			{
				preSuspect = preTemp;
				suspect = temp;
			}
			preTemp = temp;
			temp = temp->nast;
		}

		if (preSuspect)
			preSuspect->nast = suspect->nast;

		if (library->poczatek == suspect)
			library->poczatek = suspect->nast;


		addBook(newLibrary, suspect->Dane);
	}
	library->koniec = newLibrary->koniec;
	library->poczatek = newLibrary->poczatek;
	free(newLibrary);
}