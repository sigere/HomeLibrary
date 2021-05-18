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
    char authorName[50];
    char authorSurname[50];
    char topic[50];
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

bool addBook(struct spis* library, struct book newbie);
bool write(struct spis* library);
struct spis* read();
struct book* getByAuthorName(struct spis* library, char* authorName);
void deletebytopic(spis* SP, const char nazwa[]);
void sortByTopic(struct spis* library, bool asc);
