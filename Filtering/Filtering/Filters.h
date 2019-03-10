#pragma once
#include<SFML\Graphics.h>
#include<SFML\Window.h>
#include<SFML\System.h>
//Implementacja filtr�w: u�redniaj�cego, dolnoprzepustowego, g�rnoprzepustowego, Gaussa i Laplace'a
//Przyjmuje tylko warto�ci sta�e, kt�rych nie modyfikuje.
//Parametry: 
//�cie�ka do pliku zapisu, 
//przetwarzany obraz zapisany w zmiennej typu sfImage, 
//wymiary obrazu w zmiennej typu sfVector2u,
//maska odpowiedniego filtru,
//szerokosc maski.
//Funkcja nic nie zwraca .
void simpleFilter(const char pathSave[], const sfImage *pic, const sfVector2u *size, const double mask[], const int N);
//Implementacja filtr�w: medianowego, maksymalnego i minimalnego
//Przyjmuje tylko warto�ci sta�e, kt�rych nie modyfikuje.
//Parametry: 
//�cie�ka do pliku zapisu, 
//przetwarzany obraz zapisany w zmiennej typu sfImage, 
//wymiary obrazu w zmiennej typu sfVector2u,
//maska odpowiedniego filtru,
//szerokosc maski.
//Funkcja nic nie zwraca.
void staticFilter(const char pathSave[], const sfImage *pic, const sfVector2u *size, const int filter, const int N);