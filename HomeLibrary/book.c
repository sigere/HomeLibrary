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
    printf("numer bledu fopen_s: %d\n", fopen_s(&file,"library.dat", "w")); //"wb", zamiast "ab" - celowo wymazujemy dotychczasowe dane w library.dat
    if (!file) return false; //nie udalo sie otworzyc pliku

    struct elem* tmp = library->poczatek;
    struct elem* del;
    while(tmp){
        struct book b = tmp->Dane;
        fwrite(&b, sizeof(struct book), 1, file);
        del = tmp;
        tmp = tmp->nast;
        free(del);
    }
    free(library);
    fclose(file);
    return true;
}

struct spis* read()
{
    FILE* file = NULL;
    fopen_s(&file,"library.dat", "r");

    struct spis* library = (struct spis*)malloc(sizeof(struct spis));
    library->koniec = NULL;
    library->poczatek = NULL;

    if (!file)//nie udalo sie otworzyc pliku
        return library;

    struct book input;
    
    while (fread(&input, sizeof(struct book), 1, file))
    {
        /*printf("sizeof: %d", sizeof(struct book));
        printf("debug %s\n", input.topic);*/
        if (!addBook(library, input)) {
            printf("err addBook!\n");
            fclose(file);
            return false;
        }
    }
    fclose(file);
    return library;
}

struct book* getByAuthorName(struct spis* library, char* authorName)
{
    //wyszukiwanie w library ksiazki o book->authorName identycznym do authorName(parametr)

}

void deletebytopic(spis* SP, const char nazwa[])
{
    elem* prev = 0, * tmp = SP->poczatek;
    while (tmp)
    {
        if (!strcmp(nazwa, tmp->Dane.topic))
        {
            if (prev) prev->nast = tmp->nast;
            else SP->poczatek = tmp->nast;
            free(tmp);
            break;
        }
        prev = tmp;
        tmp = tmp->nast;
    }
}


void sortByTopic(struct spis* library, bool asc)
{
    if(!library->poczatek)
        return;
    
    struct spis* newLibrary = (struct spis*)malloc(sizeof(struct spis));
    newLibrary->poczatek = NULL;
    newLibrary->koniec = NULL;

    struct elem* preTemp = NULL;
    struct elem* preSuspect = NULL;
    struct elem* suspect = library->poczatek;
    struct elem* temp = library->poczatek;
    while(library->poczatek){
        temp = library->poczatek;
        preTemp = NULL;
        preSuspect = NULL;
        suspect = library->poczatek;

        while (temp) {
            if      ((asc && strcmp(temp->Dane.topic, suspect->Dane.topic) < 0)
                ||  (!asc && strcmp(temp->Dane.topic, suspect->Dane.topic) > 0))
            {
                preSuspect = preTemp;
                suspect = temp;
            }
            preTemp = temp;
            temp = temp->nast;
        }

        if (preSuspect) {
            preSuspect->nast = suspect->nast;
            //printf("jest presuspect\n");
        }
            
        if (library->poczatek == suspect)
        {
            //printf("poczatek == suspect\n");
            //if(!suspect->nast) printf("nie ma susp->nast!\n");
            //printf("a\n");
            library->poczatek = suspect->nast;
            //printf("b\n");
        }
            
        addBook(newLibrary,suspect->Dane);
    }
    library->koniec = newLibrary->koniec;
    library->poczatek = newLibrary->poczatek;
    free(newLibrary);
}