#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "MacierzSasiedztwa.h"
#include "ListaSasiedztwa.h"

using namespace std;

const int MAX_INT = 2147483647;

int main() {
	
	//string nazwa = "Test";
	//ListaSasiedztwa graf;
	//graf.Wczytaj_Z_Pliku(nazwa);
	//ListaSasiedztwa graf(1000, 0, 100);

	//graf.Dijkstra();
	
	//graf.RysowanieSciezki();

	
	srand(time(NULL));
	clock_t start, stop, start1, stop1;
	int Wierzcholki[] = { /*10, 50, 100,*/ /*500,*/ 1000 };
	int Posortowana[] = { 25/*, 50, 75, 100*/ };
	double czas = 0;

	//start = clock();
	
	for (int i = 0; i < sizeof(Posortowana) / sizeof(int); i++)
	{
		for (int j = 0; j < sizeof(Wierzcholki) / sizeof(int); j++)
		{
			for (int k = 0; k <	20; k++)
			{
				MacierzSasiedztwa graf(Wierzcholki[j], 0, Posortowana[i]);
				start1 = clock();

				graf.Dijkstra();

				stop1 = clock();
				//graf.RysowanieSciezki();
				czas += (double)(stop1 - start1) / CLOCKS_PER_SEC;
			}

			czas = czas / 100;
			cout << "Dla wierzcholkow :" << Wierzcholki[j] << "\t" << "Dla gestosci :" << Posortowana[i] << "\t" << "Czas :" << czas << endl;
		}
		cout << endl;
	}
	//stop = clock();

	//czas = (double)(stop - start) / CLOCKS_PER_SEC;
	//cout << "Czas wykonywania calego programu wynosil :" << czas << " s" << endl;
	


	/*
	cout << "Wezel\tPoprzedni\tDystans" << endl;
	for (int i = 0; i < graf.Ilosc_Wierzcholkow(); i++)
	{
		cout << i << "\t" << graf.macierz_Poprzednikow[i].poprzedni << "\t" << graf.macierz_Poprzednikow[i].waga << endl;
	}
	*/
	
	system("pause");
	return 0;
}