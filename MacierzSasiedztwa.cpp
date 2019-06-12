#include "MacierzSasiedztwa.h"

/*
Konstruktor
*/
MacierzSasiedztwa::MacierzSasiedztwa()
{

}

/*
Konstruktor tworzacy graf i nast�pnie go wype�nia
na dwa sposoby zale�ne od g�sto�ci grafu 
*/
MacierzSasiedztwa::MacierzSasiedztwa(int iloscWierzcholkow, int wierzcholekStartowy, int gestosc)
{	
	ilosc_Wierzcholkow = iloscWierzcholkow;
	wierzcholek_Startowy = wierzcholekStartowy;
	ilosc_Krawedzi = (iloscWierzcholkow - 1) * iloscWierzcholkow / 2 * gestosc / 100;
	int waga;
	macierz_Sasiedztwa = new int *[ilosc_Wierzcholkow];
	for (int i = 0; i < ilosc_Wierzcholkow; i++) macierz_Sasiedztwa[i] = new int[ilosc_Wierzcholkow];
	
	/*Dla g�sto�ci mniejszej ni� 50% */
	/*Uzupe�nia macierz zerami*/
	if (gestosc < 51) {
		for (int i = 0; i < ilosc_Wierzcholkow; i++)
			for (int j = 0; j < ilosc_Wierzcholkow; j++)
				macierz_Sasiedztwa[i][j] = 0;
		
		/*Tworzy podstawow� �cie�k�, kt�ra gwarantuje �e do ka�dego elementu grafu b�dzie dost�p*/
		/* Przy uzupe�nianiu macierzy zwi�kszamy zmienn� j, aby p�niej wype�ni� tablic� o odpowiedni�*/
		/*g�sto�� j < ilo�� kraw�dzi*/
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
		/*Uzupe�nia reszt� macierzy o wyznaczon� g�sto��. Uwzgl�dnia zmienjszenie uzupe�niania o ilo�� j*/
		/*�eby macierz nie powtarza�a wcze�niej uzupe�nionych element�w musz� zosta� spe�nione warunki */
		/*pocz�tek jest r�ny od ko�ca �eby przek�tna by�a uzupe�niona zerami, element musi mie� wag� 0*/
		/*Co odrzuca uzupe�nianie podstawowej �cie�ki*/
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
	/*Je�eli g�sto�� przekracza warto�� 51 %*/
	else
	{
		/*Uzupe�nia ca�� macierz losowymi wagami*/
		for (int i = 0; i < ilosc_Wierzcholkow; i++)
			for (int j = 0; j < ilosc_Wierzcholkow; j++)
			{
					waga = rand() % 10 + 1;
					macierz_Sasiedztwa[i][j] = waga;
					macierz_Sasiedztwa[j][i] = waga;
			}
		/*Uzupe�nia przek�tn� 0, �eby nie tworzy� �cie�ki do tego samego elementu grafu*/
		for (int i = 0; i < iloscWierzcholkow; i++)
			macierz_Sasiedztwa[i][i] = 0;

		int j = 0;

		int poczatek;
		int koniec;
		/*wz�r na g�sto��*/
		int licznik= (iloscWierzcholkow - 1) * iloscWierzcholkow / 2 * (100-gestosc) / 100;
		/*Uzupe�nienie reszty macierzy wedle g�sto�ci zerami*/
		while (j < licznik)
		{
			poczatek = rand() % ilosc_Wierzcholkow;
			koniec = rand() % ilosc_Wierzcholkow;
			/*Uwzgl�dnia 3 warunki, pocz�tek i koniec musz� by� r�ne, uwzgl�dnione wcze�niej, element uzupe�niany r�ny od 0*/
			/*Odrzuca podstawow� �cie�k� */
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
Funkcja napisana przez wymagania programu, jednak nie jest u�ywana w programie
*/
void MacierzSasiedztwa::Wczytaj_Z_Pliku(string nazwa)
{
	/*Otwiera plik, dodaje ko�c�wk� .txt, �eby nie trzeba by�o jej uwzgl�dnia� za ka�dym razem*/
	nazwa += ".txt";
	ifstream plik;
	plik.open(nazwa);

	/*Sprawdza czy plik jest otwarty, wczytuje warto�ci i uzupe�nia macierz*/
	if (plik.good() == true)
	{
		/*Wczytuje odpowiednie warto�ci*/
		plik >> ilosc_Krawedzi;
		plik >> ilosc_Wierzcholkow;
		plik >> wierzcholek_Startowy;

		/*Tworzy maciesz s�siedztwa*/
		macierz_Sasiedztwa = new int *[ilosc_Wierzcholkow];
		for (int i = 0; i < ilosc_Wierzcholkow; i++) macierz_Sasiedztwa[i] = new int[ilosc_Wierzcholkow];

		int poczatek;
		int koniec;
		int waga;

		/*Uzupe�nia macierz s�siedztwa*/
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

	else cout << "Plik nie zosta� otwarty";
}

/*
Szuka Wierzcholka o najmniejszej warto�ci.
Jej wynikiem diza�ania jest numer wierzcholka, kt�ry nale�y wybra�.
*/
int MacierzSasiedztwa::SzukajMinimum()
{
	int najmniejszy = -1; //numer wierzcholka o najmniejszej wartosci poczatkowej
	int najmniejsza_wartosc = INT_MAX; //int max jako niesko�czono��  

	/*P�tla przeszukuje wszystkie wierzcho�ki i sprawdza warunek*/
	/*Je�eli element grafu nie by� odwiedzony i waga jakiego� elementu grafu jest mniejsza ni� waga*/
	/*Obecnie najmniejszego grafu to zamiania najmniejszy wierzcho�ek*/
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
	/*Tworzy macierz poprzednik�w. Jest to macierz poprzednich element�w w �cie�ce doj�cia do konkretnego wierzcho�ka*/
	macierz_Poprzednikow = new Wierzcholek[ilosc_Wierzcholkow];
	
	/*Ustawia wag� startowego elementu na 0, wag� reszty wierzcho�k�w na niesko�czono��, poprzednie wierzcho�ki*/
	/*na -1 oraz czy odwiedzony na fa�sz*/
	for (int i = 0; i < ilosc_Wierzcholkow; i++)
	{
		if (i == wierzcholek_Startowy)	macierz_Poprzednikow[i].waga = 0;
		else macierz_Poprzednikow[i].waga = INT_MAX;

		macierz_Poprzednikow[i].odwiedzony = false;
		macierz_Poprzednikow[i].poprzedni = -1;
	}
	
	/*Szuka najmniejszego wierzcho�ka, je�li warto�� najmniejszego jest r�na od -1 wynosi -1 je�eli nie ma*/
	/*Ju� mniejszego wierzcho�ka*/
	int u = this->SzukajMinimum();
	while (u != -1)
	{

		macierz_Poprzednikow[u].odwiedzony = true;
		/*Sprawdza po kolei wszystkie wierzcho�ki, je�eli waga najmniejszego obecnie i waga kt�rego� wierzcho�ka*/
		/*Jest mniejsza od wagi poprzedniego wierzcho�ka w �cie�ce, to podstawia sum� ich wag pod poprzednika*/
		/*A za poprzedni wierzcho�ek, wierzcho�ek najmniejszy*/
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
Zapisywanie do pliku, rysowanie �cie�ki ...
*/

void MacierzSasiedztwa::RysowanieSciezki()
{	
	/*Otwiera plik do zapisum, pomocnik potrzebny do rysowania �cie�ki*/
	fstream plik;
	int i;
	plik.open("Wynik.txt", ios::out);
	int * pomocnik = new int[ilosc_Wierzcholkow];
	/*Sprawdza wszystkie wierzcho�ki*/
	for (int j = 0; j < ilosc_Wierzcholkow; j++)
	{
		pomocnik[0] = j;
		i = 1;
		/*Uzupe�nia macierz poprzednik�w kolejnymi elementami �cie�ki ko�cowego do pocz�tkowego*/
		while (pomocnik[i - 1] != wierzcholek_Startowy)
		{
			pomocnik[i] = macierz_Poprzednikow[pomocnik[i - 1]].poprzedni;
			i++;
		}
		if (plik.good() == true)
		{
			/*Wypisywanie od pocz�tkowego do ko�cowego*/
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