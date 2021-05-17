#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

enum book_type
{
    Fantasy,
    Drama,
    Comedy
};

typedef struct book {
    char *authorName;
    char *authorSurname;
    char *topic;
    unsigned int year;
    bool hardCover;
    unsigned pages;
    enum book_type type;
}book;

typedef struct elem
{
    book Dane;
    struct elem* nast;
} elem;

typedef struct spis
{
    elem* poczatek;
    elem* koniec;
} spis;

bool addBook(struct spis* library, struct book newbie)
{
    struct elem* newNode = malloc(sizeof(struct elem));
    newNode->Dane = newbie;
    newNode->nast = NULL;
    library->koniec->nast = newNode;
    library->koniec = newNode;
    return true;
}

bool write(struct spis* library) {
    FILE* file = fopen("library.dat", "wb"); //"wb", zamiast "ab" - celowo wymazujemy dotychczasowe dane w library.dat
    if (!file) return false; //nie udalo sie otworzyc pliku

    struct elem* tmp = library->poczatek;
    struct elem* del;
    while(tmp){
        fwrite(tmp->Dane, sizeof(struct book), 1, file);
        del = tmp;
        tmp = tmp->nast;
        free(del);
    }
    free(library);
    return true;
}

struct spis* read()
{
    FILE* file = fopen("library.dat", "rb");
    if (!file) return NULL;//nie udalo sie otworzyc pliku

    struct spis* library = (struct spis*)malloc(sizeof(struct spis));

    struct book* input = (struct book*)malloc(sizeof(struct book));

    while (fread(*input, sizeof(struct book), 1, file))
    {
        if(!addBook(library, input))
            return false;
        input = (struct book*)malloc(sizeof(struct book));
    }
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
    
    struct spis* newLibrary = malloc(sizeof(struct spis));
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

        if(preSuspect)
            preSuspect->nast = suspect->nast;
        if(library->poczatek == suspect)
            library->poczatek = suspect->nast;
        addBook(newLibrary,*suspect);
    }
    free(library);
    library = newLibrary;

}