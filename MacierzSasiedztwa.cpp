#include "MacierzSasiedztwa.h"

/*
Konstruktor
*/
MacierzSasiedztwa::MacierzSasiedztwa()
{

}

/*
Konstruktor tworzacy graf i nastêpnie go wype³nia
na dwa sposoby zale¿ne od gêstoœci grafu 
*/
MacierzSasiedztwa::MacierzSasiedztwa(int iloscWierzcholkow, int wierzcholekStartowy, int gestosc)
{	
	ilosc_Wierzcholkow = iloscWierzcholkow;
	wierzcholek_Startowy = wierzcholekStartowy;
	ilosc_Krawedzi = (iloscWierzcholkow - 1) * iloscWierzcholkow / 2 * gestosc / 100;
	int waga;
	macierz_Sasiedztwa = new int *[ilosc_Wierzcholkow];
	for (int i = 0; i < ilosc_Wierzcholkow; i++) macierz_Sasiedztwa[i] = new int[ilosc_Wierzcholkow];
	
	/*Dla gêstoœci mniejszej ni¿ 50% */
	/*Uzupe³nia macierz zerami*/
	if (gestosc < 51) {
		for (int i = 0; i < ilosc_Wierzcholkow; i++)
			for (int j = 0; j < ilosc_Wierzcholkow; j++)
				macierz_Sasiedztwa[i][j] = 0;
		
		/*Tworzy podstawow¹ œcie¿kê, która gwarantuje ¿e do ka¿dego elementu grafu bêdzie dostêp*/
		/* Przy uzupe³nianiu macierzy zwiêkszamy zmienn¹ j, aby póŸniej wype³niæ tablicê o odpowiedni¹*/
		/*gêstoœæ j < iloœæ krawêdzi*/
		int j = 0;
		
		for (int i = 0; i < ilosc_Wierzcholkow - 1; i++)
		{

			waga = rand() % 10 + 1;

			macierz_Sasiedztwa[i][i + 1] = waga;
			macierz_Sasiedztwa[i + 1][i] = waga;

			j++;

		}
		
		int poczatek;
		int koniec;
		/*Uzupe³nia resztê macierzy o wyznaczon¹ gêstoœæ. Uwzglêdnia zmienjszenie uzupe³niania o iloœæ j*/
		/*¯eby macierz nie powtarza³a wczeœniej uzupe³nionych elementów musz¹ zostaæ spe³nione warunki */
		/*pocz¹tek jest ró¿ny od koñca ¿eby przek¹tna by³a uzupe³niona zerami, element musi mieæ wagê 0*/
		/*Co odrzuca uzupe³nianie podstawowej œcie¿ki*/
		while (j < ilosc_Krawedzi)
		{
			poczatek = rand() % ilosc_Wierzcholkow;
			koniec = rand() % ilosc_Wierzcholkow;

			if (poczatek != koniec && macierz_Sasiedztwa[poczatek][koniec] == 0)
			{
				waga = rand() % 10 + 1;
				macierz_Sasiedztwa[poczatek][koniec] = waga;
				macierz_Sasiedztwa[koniec][poczatek] = waga;
				j++;
			}
		}
	}
	/*Je¿eli gêstoœæ przekracza wartoœæ 51 %*/
	else
	{
		/*Uzupe³nia ca³¹ macierz losowymi wagami*/
		for (int i = 0; i < ilosc_Wierzcholkow; i++)
			for (int j = 0; j < ilosc_Wierzcholkow; j++)
			{
					waga = rand() % 10 + 1;
					macierz_Sasiedztwa[i][j] = waga;
					macierz_Sasiedztwa[j][i] = waga;
			}
		/*Uzupe³nia przek¹tn¹ 0, ¿eby nie tworzyæ œcie¿ki do tego samego elementu grafu*/
		for (int i = 0; i < iloscWierzcholkow; i++)
			macierz_Sasiedztwa[i][i] = 0;

		int j = 0;

		int poczatek;
		int koniec;
		/*wzór na gêstoœæ*/
		int licznik= (iloscWierzcholkow - 1) * iloscWierzcholkow / 2 * (100-gestosc) / 100;
		/*Uzupe³nienie reszty macierzy wedle gêstoœci zerami*/
		while (j < licznik)
		{
			poczatek = rand() % ilosc_Wierzcholkow;
			koniec = rand() % ilosc_Wierzcholkow;
			/*Uwzglêdnia 3 warunki, pocz¹tek i koniec musz¹ byæ ró¿ne, uwzglêdnione wczeœniej, element uzupe³niany ró¿ny od 0*/
			/*Odrzuca podstawow¹ œcie¿kê */
			if (poczatek != koniec && macierz_Sasiedztwa[poczatek][koniec] != 0 && poczatek != koniec-1 && poczatek != koniec+1)
			{
				macierz_Sasiedztwa[poczatek][koniec] = 0;
				macierz_Sasiedztwa[koniec][poczatek] = 0;
				j++;
			}
		}
	}
}

/*
Opcjonalnie wczytuje dane z pliku
Funkcja napisana przez wymagania programu, jednak nie jest u¿ywana w programie
*/
void MacierzSasiedztwa::Wczytaj_Z_Pliku(string nazwa)
{
	/*Otwiera plik, dodaje koñcówkê .txt, ¿eby nie trzeba by³o jej uwzglêdniaæ za ka¿dym razem*/
	nazwa += ".txt";
	ifstream plik;
	plik.open(nazwa);

	/*Sprawdza czy plik jest otwarty, wczytuje wartoœci i uzupe³nia macierz*/
	if (plik.good() == true)
	{
		/*Wczytuje odpowiednie wartoœci*/
		plik >> ilosc_Krawedzi;
		plik >> ilosc_Wierzcholkow;
		plik >> wierzcholek_Startowy;

		/*Tworzy maciesz s¹siedztwa*/
		macierz_Sasiedztwa = new int *[ilosc_Wierzcholkow];
		for (int i = 0; i < ilosc_Wierzcholkow; i++) macierz_Sasiedztwa[i] = new int[ilosc_Wierzcholkow];

		int poczatek;
		int koniec;
		int waga;

		/*Uzupe³nia macierz s¹siedztwa*/
		for (int i = 0; i < ilosc_Krawedzi; i++)
		{
			plik >> poczatek;
			plik >> koniec;
			plik >> waga;

			macierz_Sasiedztwa[poczatek][koniec] = waga;
			macierz_Sasiedztwa[koniec][poczatek] = waga;
 		}

		plik.close();
	}

	else cout << "Plik nie zosta³ otwarty";
}

/*
Szuka Wierzcholka o najmniejszej wartoœci.
Jej wynikiem diza³ania jest numer wierzcholka, który nale¿y wybraæ.
*/
int MacierzSasiedztwa::SzukajMinimum()
{
	int najmniejszy = -1; //numer wierzcholka o najmniejszej wartosci poczatkowej
	int najmniejsza_wartosc = INT_MAX; //int max jako nieskoñczonoœæ  

	/*Pêtla przeszukuje wszystkie wierzcho³ki i sprawdza warunek*/
	/*Je¿eli element grafu nie by³ odwiedzony i waga jakiegoœ elementu grafu jest mniejsza ni¿ waga*/
	/*Obecnie najmniejszego grafu to zamiania najmniejszy wierzcho³ek*/
	for (int i = 0; i < ilosc_Wierzcholkow; i++)
	{
		if (macierz_Poprzednikow[i].odwiedzony == false && macierz_Poprzednikow[i].waga < najmniejsza_wartosc)
		{
			najmniejszy = i;
			najmniejsza_wartosc = macierz_Poprzednikow[i].waga;
		}
	}
	return najmniejszy;
}

/*
Algorytm Dijkstry
*/
void MacierzSasiedztwa::Dijkstra()
{	
	/*Tworzy macierz poprzedników. Jest to macierz poprzednich elementów w œcie¿ce dojœcia do konkretnego wierzcho³ka*/
	macierz_Poprzednikow = new Wierzcholek[ilosc_Wierzcholkow];
	
	/*Ustawia wagê startowego elementu na 0, wagê reszty wierzcho³ków na nieskoñczonoœæ, poprzednie wierzcho³ki*/
	/*na -1 oraz czy odwiedzony na fa³sz*/
	for (int i = 0; i < ilosc_Wierzcholkow; i++)
	{
		if (i == wierzcholek_Startowy)	macierz_Poprzednikow[i].waga = 0;
		else macierz_Poprzednikow[i].waga = INT_MAX;

		macierz_Poprzednikow[i].odwiedzony = false;
		macierz_Poprzednikow[i].poprzedni = -1;
	}
	
	/*Szuka najmniejszego wierzcho³ka, jeœli wartoœæ najmniejszego jest ró¿na od -1 wynosi -1 je¿eli nie ma*/
	/*Ju¿ mniejszego wierzcho³ka*/
	int u = this->SzukajMinimum();
	while (u != -1)
	{

		macierz_Poprzednikow[u].odwiedzony = true;
		/*Sprawdza po kolei wszystkie wierzcho³ki, je¿eli waga najmniejszego obecnie i waga któregoœ wierzcho³ka*/
		/*Jest mniejsza od wagi poprzedniego wierzcho³ka w œcie¿ce, to podstawia sumê ich wag pod poprzednika*/
		/*A za poprzedni wierzcho³ek, wierzcho³ek najmniejszy*/
		for (int i = 0; i < ilosc_Wierzcholkow; i++)
		{
			if (macierz_Sasiedztwa[u][i] > 0 && macierz_Poprzednikow[u].waga + macierz_Sasiedztwa[u][i] < macierz_Poprzednikow[i].waga)
			{
				macierz_Poprzednikow[i].waga = macierz_Poprzednikow[u].waga + macierz_Sasiedztwa[u][i];
				macierz_Poprzednikow[i].poprzedni = u;
			}
		}
		u = this->SzukajMinimum();
	}
}

/*
Zapisywanie do pliku, rysowanie œcie¿ki ...
*/

void MacierzSasiedztwa::RysowanieSciezki()
{	
	/*Otwiera plik do zapisum, pomocnik potrzebny do rysowania œcie¿ki*/
	fstream plik;
	int i;
	plik.open("Wynik.txt", ios::out);
	int * pomocnik = new int[ilosc_Wierzcholkow];
	/*Sprawdza wszystkie wierzcho³ki*/
	for (int j = 0; j < ilosc_Wierzcholkow; j++)
	{
		pomocnik[0] = j;
		i = 1;
		/*Uzupe³nia macierz poprzedników kolejnymi elementami œcie¿ki koñcowego do pocz¹tkowego*/
		while (pomocnik[i - 1] != wierzcholek_Startowy)
		{
			pomocnik[i] = macierz_Poprzednikow[pomocnik[i - 1]].poprzedni;
			i++;
		}
		if (plik.good() == true)
		{
			/*Wypisywanie od pocz¹tkowego do koñcowego*/
			plik << "Wierzcholek poczatkowy :" << wierzcholek_Startowy << "\t" << "Wierzcholek koncowy :   " << j << "\t" << "Waga sciezki :" << macierz_Poprzednikow[j].waga << "\t" << "Sciezka :   ";
			while (i > 0)
			{
				plik << pomocnik[i - 1] << " ";
				i--;
			}
		}
		plik << endl;
	}
	
}

/*
Destruktor
*/
MacierzSasiedztwa::~MacierzSasiedztwa()
{
	
}