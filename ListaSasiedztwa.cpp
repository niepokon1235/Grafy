#include "ListaSasiedztwa.h"

/*
Konstruktor
*/
ListaSasiedztwa::ListaSasiedztwa()
{

}

/*
Konstruktor
Dzia�anie jest podobne jak konstruktora w MacierzyS�siedztwa. Tworzy MacierzS�siedztwa, a nast�pnie
Uzupe�nia List� s�siedztwa elementami MacierzyS�siedztwa
*/
ListaSasiedztwa::ListaSasiedztwa(int iloscWierzcholkow, int wierzcholek_startowy, int gestosc) {
	int poczatek;
	int koniec;
	int ** pomocnik;
	ilosc_Wierzcholkow = iloscWierzcholkow;
	wierzcholek_Startowy = wierzcholek_startowy;
	ilosc_Krawedzi = (iloscWierzcholkow - 1)*iloscWierzcholkow / 2 * gestosc / 100;
	int waga;
	
	macierz_List = new Lista *[ilosc_Wierzcholkow];

	/*Uzupe�nia list� zerami*/
	for (int i = 0; i < ilosc_Wierzcholkow; i++)
		macierz_List[i] = NULL;

	/*Inicjuje tablice potrzebn� do uzupe�niania listy*/
	pomocnik = new int*[ilosc_Wierzcholkow];
	for (int i = 0; i < ilosc_Wierzcholkow; i++)
		pomocnik[i] = new int[ilosc_Wierzcholkow];

	/*Wype�nia tablice zerami*/
	for (int i = 0; i < iloscWierzcholkow; i++)
		for (int j = 0; j < iloscWierzcholkow; j++)
			pomocnik[i][j] = 0;

	/*Tworzy macierz podstawowych po��cze�, 0 z 1, 1 z 2 itd.*/
	int j = 0;
	for (int i = 0; i < iloscWierzcholkow - 1; i++) {
		waga = rand() % 10 + 1;
		pomocnik[i][i + 1] = waga;
		pomocnik[i + 1][i] = waga;
		pw = new Lista;             // Tworzymy element listy s�siedztwa
		pw->wezel_Docelowy = i + 1;                    // Wierzcho�ek docelowy kraw�dzi
		pw->waga= waga;                    // Waga kraw�dzi
		pw->nastepny = macierz_List[i];
		macierz_List[i] = pw;	//Element do��czamy do listy

		pw = new Lista;             // Tworzymy element listy s�siedztwa
		pw->wezel_Docelowy = i;                    // Wierzcho�ek docelowy kraw�dzi
		pw->waga = waga;                    // Waga kraw�dzi
		pw->nastepny = macierz_List[i + 1];
		macierz_List[i + 1] = pw; //Element do��czamy do listy
		j++;
	}
	/*Uzupe�niamy list� je�eli pocz�tek i koniec tablicy s� r�nej warto�ci, oraz elem tablicy s� r�wne 0*/
	while (j < ilosc_Krawedzi)
	{
		poczatek = rand() % iloscWierzcholkow;
		koniec = rand() % iloscWierzcholkow;
		if (poczatek != koniec && pomocnik[poczatek][koniec] == 0)
		{
			waga = rand() % 10 + 1;
			pomocnik[poczatek][koniec] = waga;
			pomocnik[koniec][poczatek] = waga;
			pw = new Lista;             // Tworzymy element listy s�siedztwa
			pw->wezel_Docelowy = poczatek;                    // Wierzcho�ek docelowy kraw�dzi
			pw->waga = waga;                    // Waga kraw�dzi
			pw->nastepny = macierz_List[koniec];
			macierz_List[koniec] = pw;	//Element do��czamy do listy

			pw = new Lista;             // Tworzymy element listy s�siedztwa
			pw->wezel_Docelowy = koniec;                    // Wierzcho�ek docelowy kraw�dzi
			pw->waga = waga;                    // Waga kraw�dzi
			pw->nastepny = macierz_List[poczatek];
			macierz_List[poczatek] = pw; //Element do��czamy do listy
			j++;
		}
	}
	/*Tworzy macierz poprzednik�w*/
	macierz_Poprzednikow = new WierzcholekL[ilosc_Wierzcholkow];
	for (int i = 0; i < ilosc_Wierzcholkow; i++)
	{
		macierz_Poprzednikow[i].waga = MAX_INT;
		macierz_Poprzednikow[i].poprzedni = -1;
		macierz_Poprzednikow[i].odwiedzony = false;
	}
	macierz_Poprzednikow[wierzcholek_Startowy].waga = 0;

	for (int o = 0; o < ilosc_Wierzcholkow; o++) delete[] pomocnik[o];
	delete[] pomocnik;
}

/*
Zwraca numer wierzcho�ka o najmniejszej wadze
*/
int ListaSasiedztwa::Szukaj_Minimum()
{
	int j;
	int najmniejsza_wartosc; //indeks do wierzcholka o najmniejszej wartosci
	/*P�tla przeszukuje wszystkie wierzcho�ki i sprawdza warunek*/
	/*Je�eli element grafu nie by� odwiedzony i waga jakiego� elementu grafu jest mniejsza ni� waga*/
	/*Obecnie najmniejszego grafu to zamiania najmniejszy wierzcho�ek*/
	for (j = 0; macierz_Poprzednikow[j].odwiedzony; j++); 
	for (najmniejsza_wartosc = j++; j < ilosc_Wierzcholkow; j++)
		if (macierz_Poprzednikow[j].odwiedzony == false && (macierz_Poprzednikow[j].waga < macierz_Poprzednikow[najmniejsza_wartosc].waga)) najmniejsza_wartosc = j;
	
	macierz_Poprzednikow[najmniejsza_wartosc].odwiedzony = true;
	return najmniejsza_wartosc;
}

/*
Algorytm Dijkstry, szuka najkr�tszej �cie�ki doj�cia od konkretnego elementu grafu, do innego
*/
void ListaSasiedztwa::Dijkstra()
{	
	/*Przeszukuje wszystkie wierzcho�ki*/
	for (int i = 0; i < ilosc_Wierzcholkow; i++)
	{
		/*Pobiera najmnieszy wierzcho�ek*/
		int najmniejszy= this->Szukaj_Minimum();
		
		/*Pod wska�nik na liste przypisuje wierzcho�ek o najmniejszej wadze, nast�pnie przechodzi do nast�pnego*/
		/*elementu listy*/
		for (pw = macierz_List[najmniejszy]; pw; pw = pw->nastepny)
		
		{
				/*Je�eli wierzcho�ek by� odwiedzony i suma wag wierzcho�ka poprzedniego i obecnego jest mniejsza ni�*/
				/*od wagi poprzedniego wierzcho�ka w �cie�ce to podstawia sume ich wag pod poprzednika */
				/*A za poprzedni wierzcho�ek, wierzcho�ek najmniejszy*/
			if (!macierz_Poprzednikow[pw->wezel_Docelowy].odwiedzony && (macierz_Poprzednikow[pw->wezel_Docelowy].waga > macierz_Poprzednikow[najmniejszy].waga + pw->waga))
			{
				macierz_Poprzednikow[pw->wezel_Docelowy].waga = macierz_Poprzednikow[najmniejszy].waga + pw->waga;
				macierz_Poprzednikow[pw->wezel_Docelowy].poprzedni = najmniejszy;
			}
		}
	}
}

/*
Funkcja wczytania z pliku, obecnie nieu�ywana, jednak wymagana w programie
*/
void ListaSasiedztwa::Wczytaj_Z_Pliku(string nazwa) {
	int poczatek;
	int koniec;
	int waga;
	/*Otwiera plik, dodaje ko�c�wk� .txt, �eby nie trzeba by�o jej uwzgl�dnia� za ka�dym razem*/
	nazwa += ".txt";
	ifstream plik;
	plik.open(nazwa);

	/*Sprawdza czy plik jest otwarty, wczytuje warto�ci i uzupe�nia list�*/
	if (plik.good() == true) {
		/*Wczytuje odpowiednie warto�ci i inicjuje liste*/
		plik >> ilosc_Krawedzi;
		plik >> ilosc_Wierzcholkow;
		plik >> wierzcholek_Startowy;
		macierz_List = new Lista *[ilosc_Wierzcholkow];

		for (int i = 0; i < ilosc_Wierzcholkow; i++)
			macierz_List[i] = NULL;
		/*Uzupe�nia list�*/
		for (int i = 0; i < ilosc_Krawedzi; i++)
		{
			plik >> poczatek;
			plik >> koniec;
			plik >> waga;
			pw = new Lista;          //Tworzymy element listy s�siedztwa   
			pw->wezel_Docelowy = koniec;        //Wierzcholek docelowy krawdzei
			pw->waga = waga;                    //Waga kraw�dzi
			pw->nastepny = macierz_List[poczatek]; 
			macierz_List[poczatek] = pw;	//Element do��czamy do listy
		}


		plik.close();
	}
}

/*
Rysowanie z macierzy poprzednikow
*/

void ListaSasiedztwa::RysowanieSciezki()
{
	/*Otwiera plik o konkretnej nazwie, Wynik.txt*/
	fstream plik;
	int i;
	plik.open("Wynik.txt", ios::out);
	/*Tworzy tablice dynamiczn�*/
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
ListaSasiedztwa::~ListaSasiedztwa()
{

}