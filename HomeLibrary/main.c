#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

int main()
{
	/*struct spis* lib = (struct spis*)malloc(sizeof(struct spis));
	lib->koniec = NULL;
	lib->poczatek = NULL;
	struct book newbie = { "Abc", "DeF", "ATemat", 1992, true, 10, Drama };
	addBook(lib, newbie);
	struct book newbie2 = { "Bbb", "dde", "Btemacik", 1988, false, 12, Comedy };
	addBook(lib, newbie2);*/
	//printf("sizeof: %d", sizeof(struct book));
	struct spis* lib = read();
	//printf("adres lib: %d\n", lib);
	sortByTopic(lib, true);
	//printf("adres lib: %d\n", lib);
	struct elem* t = lib->poczatek;
	while (t) {
		printf("temat kolejnego elementu: %s\n", t->Dane.topic);
		t = t->nast;
	}
	//write(lib);
	/*
	if (lib->poczatek) {
		printf("yes\n");
		printf("%s\n", lib->poczatek->Dane.topic);
		if (lib->poczatek->nast)
			printf("ok\n");
	}*/
	
	return 0;
}