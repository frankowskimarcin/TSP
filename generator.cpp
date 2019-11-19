#include "generator.h"
#include <iostream>
#include <fstream>
#include <chrono>
#define MAX 100

void generuj() {
	std::fstream plik;
	srand(time(NULL));
	plik.open("dane1.txt", std::ios::out | std::ios::trunc);
	if (!plik.good()) {
		std::cout << "Blad pliku" << std::endl;
		exit(0);
	}
	plik << MAX << std::endl;
	for (int i = 1; i <= MAX; i++) {
		plik << i << " ";
		plik << rand() % (MAX * 100 + 1) << " ";
		plik << rand() % (MAX * 100 + 1) << std::endl;
	}
	plik.close();
}