#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//stały rozmiar biblioteki, nie powinien się zmieniac,
//zakladamy ze struct book** library to tablica 50 ksiazek,
//a wartosci NULL w tej tablicy oznaczaja wolne miejsca na ksiazki
#define LIB_SIZE 50

enum book_type
{
	Fantasy,
	Drama,
	Comedy
};

struct book {
	char authorName[50];
	char authorSurname[50];
	char topic[50];
	unsigned int year;
	bool hardCover;
	unsigned pages;
	enum book_type type; 
};

bool addBook(struct book** library)
{
	struct book newbie;
	int indexForNewbie = -1;
	for(int i=0; i < LIB_SIZE; i++) //znajdz wolne miejsce na ksiazke w bibliotece
		if(library[i] == NULL){// znalazlem wolne miejsce pod indexem i
			//TODO scanf z klawiatury dane nowej ksiazki
			// np za pomoca osobnej funkcji readFromKeyboard(&newbie);

			newbie.authorName = "Adam";
			newbie.authorSurname = "Mickiewicz";
			newbie.hardCover = true;
			newbie.topic = "Wacki i Slowacki";
			newbie.year = 2021;
			newbie.pages = 100;
			newbie.type = Fantasy;

			library[i] = &newbie;
			return true;
		}
	//brak wolnego miejsca, zwracam false
	return false;
}

bool write(struct book** library) {
	//prosty zapis tablicy ksiazek do pliku
	//library to tablica wska�nik�w
	//return true jesli si� uda�o, inaczej false

	FILE *file = fopen("library.dat", "wb"); //"wb", zamiast "ab" - celowo wymazujemy dotychczasowe dane w library.dat
	if(!file) return false; //nie udalo sie otworzyc pliku

	for(int i=0; i < LIB_SIZE; i++) //zapisz wszystkie nie-nullowe pozyje z library
		if(library[i])
			fwrite(library[i], sizeof(struct book), 1, file);

	return true;
}

struct book** read()
{
	//"proste" wczytanie z pliku tablicy wska�nik�w ksiazek
	FILE* file = fopen("library.dat", "rb");
	if(!file) return NULL;//nie udalo sie otworzyc pliku

	struct book** library = (struct book**)malloc(sizeof(struct book*) * LIB_SIZE);
	
	struct book *input = (struct book*)malloc(sizeof(struct book));

	int i = 0;
	while(i < LIB_SIZE && fread(input, sizeof(struct book), 1, file))
	{
		library[i++] = input;
		input = (struct book*)malloc(sizeof(struct book));
	}
	return library;
}

struct book* getByAuthorName(struct book** library, char* authorName)
{
	//wyszukiwanie w library ksiazki o book->authorName identycznym do authorName(parametr)

}

bool deleteByTopic(struct book** library, char* topic)
{
	//znajdz w library i usun
}

void sortByTopic(struct book** library, bool asc)
{
	//posortuj library, w zaleznosci od asc (true -> rosnaco, false -> malejaco)
}