#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct WierzcholekL
{
	int waga;
	int poprzedni;
	bool odwiedzony;
};

struct Lista
{
	Lista * nastepny; //wskaznik na nastepny element list
	int wezel_Docelowy;
	int waga; //waga krawedzi
};

class ListaSasiedztwa
{
	int ilosc_Wierzcholkow;
	int ilosc_Krawedzi;
	int wierzcholek_Startowy;
	
	Lista *pw;  //Wskaünik na liste
	Lista **macierz_List;
public:
	const int MAX_INT = 2147483647;
	WierzcholekL *macierz_Poprzednikow;
	ListaSasiedztwa();
	ListaSasiedztwa(int iloscWierzcholkow, int wierzcholekStartowy, int gestosc);
	void Wczytaj_Z_Pliku(string nazwa);
	int Szukaj_Minimum();
	void Dijkstra();
	void RysowanieSciezki();

	int Ilosc_Wierzcholkow() { return ilosc_Wierzcholkow; }
	int Wierzcholek_Startowy() { return wierzcholek_Startowy; }
	~ListaSasiedztwa();
};