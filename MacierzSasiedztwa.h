#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Wierzcholek
{
	int waga; 
	int poprzedni; 
	bool odwiedzony;
};

class MacierzSasiedztwa
{
private:
	int ilosc_Wierzcholkow;
	int wierzcholek_Startowy;
	int ilosc_Krawedzi;

	int** macierz_Sasiedztwa;
	//Wierzcholek* macierz_Poprzednikow;
public:
	Wierzcholek* macierz_Poprzednikow;
	const int MAX_INT = 2147483647;

	MacierzSasiedztwa();
	MacierzSasiedztwa(int iloscWierzcholkow,int wierzcholekStartowy, int gestosc);
	void Wczytaj_Z_Pliku(string plik);
	~MacierzSasiedztwa();

	int SzukajMinimum();
	void Dijkstra();
	void RysowanieSciezki();

	int Ilosc_Wierzcholkow() { return ilosc_Wierzcholkow; }
	//Wierzcholek *Macierz_Poprzednikow[int i] { return macierz_Poprzednikow[i]; }
};