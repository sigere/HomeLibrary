#include <stdio.h>
#include <stdbool.h>


struct book {
	char* authorName;
	char* authorSurname;
	char* topic;
	unsigned int year;
	bool hardCover;
	unsigned pages;
	enum type
	{
		Fantasy,
		Drama,
		Comedy
	};
};

bool write(struct book** library) {
	//prosty zapis tablicy ksiazek do pliku
	//library to tablica wska�nik�w
	//return true jesli si� uda�o, inaczej false
}

struct book** read()
{
	//proste wczytanie z pliku tablicy wska�nik�w ksiazek
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