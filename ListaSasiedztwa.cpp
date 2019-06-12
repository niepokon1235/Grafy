#include "ListaSasiedztwa.h"

/*
Konstruktor
*/
ListaSasiedztwa::ListaSasiedztwa()
{

}

/*
Konstruktor
Dzia³anie jest podobne jak konstruktora w MacierzyS¹siedztwa. Tworzy MacierzS¹siedztwa, a nastêpnie
Uzupe³nia Listê s¹siedztwa elementami MacierzyS¹siedztwa
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

	/*Uzupe³nia listê zerami*/
	for (int i = 0; i < ilosc_Wierzcholkow; i++)
		macierz_List[i] = NULL;

	/*Inicjuje tablice potrzebn¹ do uzupe³niania listy*/
	pomocnik = new int*[ilosc_Wierzcholkow];
	for (int i = 0; i < ilosc_Wierzcholkow; i++)
		pomocnik[i] = new int[ilosc_Wierzcholkow];

	/*Wype³nia tablice zerami*/
	for (int i = 0; i < iloscWierzcholkow; i++)
		for (int j = 0; j < iloscWierzcholkow; j++)
			pomocnik[i][j] = 0;

	/*Tworzy macierz podstawowych po³¹czeñ, 0 z 1, 1 z 2 itd.*/
	int j = 0;
	for (int i = 0; i < iloscWierzcholkow - 1; i++) {
		waga = rand() % 10 + 1;
		pomocnik[i][i + 1] = waga;
		pomocnik[i + 1][i] = waga;
		pw = new Lista;             // Tworzymy element listy s¹siedztwa
		pw->wezel_Docelowy = i + 1;                    // Wierzcho³ek docelowy krawêdzi
		pw->waga= waga;                    // Waga krawêdzi
		pw->nastepny = macierz_List[i];
		macierz_List[i] = pw;	//Element do³¹czamy do listy

		pw = new Lista;             // Tworzymy element listy s¹siedztwa
		pw->wezel_Docelowy = i;                    // Wierzcho³ek docelowy krawêdzi
		pw->waga = waga;                    // Waga krawêdzi
		pw->nastepny = macierz_List[i + 1];
		macierz_List[i + 1] = pw; //Element do³¹czamy do listy
		j++;
	}
	/*Uzupe³niamy listê je¿eli pocz¹tek i koniec tablicy s¹ ró¿nej wartoœci, oraz elem tablicy s¹ równe 0*/
	while (j < ilosc_Krawedzi)
	{
		poczatek = rand() % iloscWierzcholkow;
		koniec = rand() % iloscWierzcholkow;
		if (poczatek != koniec && pomocnik[poczatek][koniec] == 0)
		{
			waga = rand() % 10 + 1;
			pomocnik[poczatek][koniec] = waga;
			pomocnik[koniec][poczatek] = waga;
			pw = new Lista;             // Tworzymy element listy s¹siedztwa
			pw->wezel_Docelowy = poczatek;                    // Wierzcho³ek docelowy krawêdzi
			pw->waga = waga;                    // Waga krawêdzi
			pw->nastepny = macierz_List[koniec];
			macierz_List[koniec] = pw;	//Element do³¹czamy do listy

			pw = new Lista;             // Tworzymy element listy s¹siedztwa
			pw->wezel_Docelowy = koniec;                    // Wierzcho³ek docelowy krawêdzi
			pw->waga = waga;                    // Waga krawêdzi
			pw->nastepny = macierz_List[poczatek];
			macierz_List[poczatek] = pw; //Element do³¹czamy do listy
			j++;
		}
	}
	/*Tworzy macierz poprzedników*/
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
Zwraca numer wierzcho³ka o najmniejszej wadze
*/
int ListaSasiedztwa::Szukaj_Minimum()
{
	int j;
	int najmniejsza_wartosc; //indeks do wierzcholka o najmniejszej wartosci
	/*Pêtla przeszukuje wszystkie wierzcho³ki i sprawdza warunek*/
	/*Je¿eli element grafu nie by³ odwiedzony i waga jakiegoœ elementu grafu jest mniejsza ni¿ waga*/
	/*Obecnie najmniejszego grafu to zamiania najmniejszy wierzcho³ek*/
	for (j = 0; macierz_Poprzednikow[j].odwiedzony; j++); 
	for (najmniejsza_wartosc = j++; j < ilosc_Wierzcholkow; j++)
		if (macierz_Poprzednikow[j].odwiedzony == false && (macierz_Poprzednikow[j].waga < macierz_Poprzednikow[najmniejsza_wartosc].waga)) najmniejsza_wartosc = j;
	
	macierz_Poprzednikow[najmniejsza_wartosc].odwiedzony = true;
	return najmniejsza_wartosc;
}

/*
Algorytm Dijkstry, szuka najkrótszej œcie¿ki dojœcia od konkretnego elementu grafu, do innego
*/
void ListaSasiedztwa::Dijkstra()
{	
	/*Przeszukuje wszystkie wierzcho³ki*/
	for (int i = 0; i < ilosc_Wierzcholkow; i++)
	{
		/*Pobiera najmnieszy wierzcho³ek*/
		int najmniejszy= this->Szukaj_Minimum();
		
		/*Pod wskaŸnik na liste przypisuje wierzcho³ek o najmniejszej wadze, nastêpnie przechodzi do nastêpnego*/
		/*elementu listy*/
		for (pw = macierz_List[najmniejszy]; pw; pw = pw->nastepny)
		
		{
				/*Je¿eli wierzcho³ek by³ odwiedzony i suma wag wierzcho³ka poprzedniego i obecnego jest mniejsza ni¿*/
				/*od wagi poprzedniego wierzcho³ka w œcie¿ce to podstawia sume ich wag pod poprzednika */
				/*A za poprzedni wierzcho³ek, wierzcho³ek najmniejszy*/
			if (!macierz_Poprzednikow[pw->wezel_Docelowy].odwiedzony && (macierz_Poprzednikow[pw->wezel_Docelowy].waga > macierz_Poprzednikow[najmniejszy].waga + pw->waga))
			{
				macierz_Poprzednikow[pw->wezel_Docelowy].waga = macierz_Poprzednikow[najmniejszy].waga + pw->waga;
				macierz_Poprzednikow[pw->wezel_Docelowy].poprzedni = najmniejszy;
			}
		}
	}
}

/*
Funkcja wczytania z pliku, obecnie nieu¿ywana, jednak wymagana w programie
*/
void ListaSasiedztwa::Wczytaj_Z_Pliku(string nazwa) {
	int poczatek;
	int koniec;
	int waga;
	/*Otwiera plik, dodaje koñcówkê .txt, ¿eby nie trzeba by³o jej uwzglêdniaæ za ka¿dym razem*/
	nazwa += ".txt";
	ifstream plik;
	plik.open(nazwa);

	/*Sprawdza czy plik jest otwarty, wczytuje wartoœci i uzupe³nia listê*/
	if (plik.good() == true) {
		/*Wczytuje odpowiednie wartoœci i inicjuje liste*/
		plik >> ilosc_Krawedzi;
		plik >> ilosc_Wierzcholkow;
		plik >> wierzcholek_Startowy;
		macierz_List = new Lista *[ilosc_Wierzcholkow];

		for (int i = 0; i < ilosc_Wierzcholkow; i++)
			macierz_List[i] = NULL;
		/*Uzupe³nia listê*/
		for (int i = 0; i < ilosc_Krawedzi; i++)
		{
			plik >> poczatek;
			plik >> koniec;
			plik >> waga;
			pw = new Lista;          //Tworzymy element listy s¹siedztwa   
			pw->wezel_Docelowy = koniec;        //Wierzcholek docelowy krawdzei
			pw->waga = waga;                    //Waga krawêdzi
			pw->nastepny = macierz_List[poczatek]; 
			macierz_List[poczatek] = pw;	//Element do³¹czamy do listy
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
	/*Tworzy tablice dynamiczn¹*/
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
ListaSasiedztwa::~ListaSasiedztwa()
{

}