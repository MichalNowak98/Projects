#pragma once
#include<SFML\Graphics.h>
#include<SFML\Window.h>
#include<SFML\System.h>
//Implementacja filtrów: uœredniaj¹cego, dolnoprzepustowego, górnoprzepustowego, Gaussa i Laplace'a
//Przyjmuje tylko wartoœci sta³e, których nie modyfikuje.
//Parametry: 
//œcie¿ka do pliku zapisu, 
//przetwarzany obraz zapisany w zmiennej typu sfImage, 
//wymiary obrazu w zmiennej typu sfVector2u,
//maska odpowiedniego filtru,
//szerokosc maski.
//Funkcja nic nie zwraca .
void simpleFilter(const char pathSave[], const sfImage *pic, const sfVector2u *size, const double mask[], const int N);
//Implementacja filtrów: medianowego, maksymalnego i minimalnego
//Przyjmuje tylko wartoœci sta³e, których nie modyfikuje.
//Parametry: 
//œcie¿ka do pliku zapisu, 
//przetwarzany obraz zapisany w zmiennej typu sfImage, 
//wymiary obrazu w zmiennej typu sfVector2u,
//maska odpowiedniego filtru,
//szerokosc maski.
//Funkcja nic nie zwraca.
void staticFilter(const char pathSave[], const sfImage *pic, const sfVector2u *size, const int filter, const int N);