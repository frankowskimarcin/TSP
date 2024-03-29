#include "generator.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std;

int main()
{
	int punkt1, nr_punktu, now, next; //punkt startowy, numer odczytywanego punktu, punkt obecny, punkt nastepny
	int ilosc; //ilosc punktow
	double droga=0; //calkowita pokonana droga

	generuj();
	
	fstream plik;
	plik.open("dane1.txt"); //odczyt pliku
	if (!plik.good()){
		cout << "Blad pliku" <<endl;
		return 0;
	}
	plik >> ilosc; //pobranie ilosci punktow z pliku

	int **tab2 = new int *[ilosc]; //stworzenie tablicy
	for (int i = 0; i < ilosc; i++) {
		tab2[i] = new int[2];
	}

	for (int i = 0;i < ilosc;i++) {	//wypelnienie tablicy
		plik >> nr_punktu;
		plik >> tab2[i][0];
		plik >> tab2[i][1];
	}
	/*for (int i = 0; i < ilosc; i++) {	//wypisanie danych z tablicy(sprawdzenie)
		cout <<i+1<<" "<< tab2[i][0] << " " << tab2[i][1] << endl;
	}*/

	cout << "Wybierz numer punktu startowego: "; //punkt startowy
	cin >> punkt1;
	if (punkt1 <= 0 || punkt1 > ilosc) {
		cout << "Blad punktu startowego." << endl;
		exit(0);
	}
	punkt1--;

	bool *visited= new bool[ilosc]; //tablica odwiedzonych punktow

	for (int i = 0; i < ilosc; i++) {
		visited[i] = false;
	}
	visited[punkt1] = true;
	/*for (int i = 0; i < ilosc; i++) { //sprawdzenie
		cout<<visited[i]<<endl;
	}*/

	cout << "Twoja podroz: " << endl;
	auto start = chrono::system_clock::now();
	// ALGORYTM
	now = punkt1;
	cout << now+1 << endl; //hide
	for (int i = 0; i < ilosc - 1; i++) { //dla kazdego punktu przelatujemy cala tablice

		double odleglosc; //odleglosc liczona do potencjalnego nastepnego punktu
		double odleglosc_min = 99999; //odleglosc minimalna

		for (int i = 0; i < ilosc; i++) {
			if (visited[i] == true) continue;

			odleglosc = sqrt( pow((tab2[now][0] - tab2[i][0]), 2) + pow((tab2[now][1] - tab2[i][1]), 2)); //odleglosc do wybranego punktu

			if (odleglosc <= odleglosc_min) { //jezeli najmniejsza
				next = i;
				odleglosc_min = odleglosc;
			}
		}
		now = next; //przejscie na kolejny punkt
		cout << now + 1 << endl; //hide
		visited[next] = true;
		droga += odleglosc_min;
	}
	cout << punkt1+1 << endl; //powrot do punktu startowego //hide
	droga+= sqrt(pow((tab2[punkt1][0] - tab2[now][0]), 2) + pow((tab2[punkt1][1] - tab2[now][1]), 2));

	auto end = chrono::system_clock::now();
	chrono::duration<double> time = end - start;
	cout << "Dlugosc: " << droga << endl;
	cout << "Czas: " << time.count() << endl;

	//sprzatanie
	delete[] visited;

	for (int i = 0; i<ilosc; i++)
		delete[] tab2[i];

	delete[] tab2;

	plik.close();

    return 0;
}