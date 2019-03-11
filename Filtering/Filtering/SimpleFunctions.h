#pragma once
#include<SFML\Graphics.h>
#include<SFML\Window.h>
#include<SFML\System.h>
//Funkcja porównuj¹ca wykorzystywana przez quicksort. 
//Parametry:
//a i b (konwertowane na typ double w ciele funkcji).
//Funkcja zwraca 0 dla a == b, -1 dla b > a, 1 dla a > b.
int compare(const double* a, const double* b);
//Alokuje tablicê o podanym rozmiarze.
//Parametry:
//Przyjmuje adres zmiennej size typu sfVector2u zawieraj¹cej wymiary tablicy. 
//Funkcja zwraca adres pierwszego elementu tablicy typu sfVector2u.
sfColor* newArray(const sfVector2u *size);
//Alokuje tablicê o podanym rozmiarze i wype³nia j¹ wartoœciami w zale¿noœci od rodzaju maski.
//Parametry:
//przyjmuje szerokoœæ maski jako wartoœæ ca³kowit¹ N oraz typ maski jako wartoœæ ca³kowit¹ maskType.
//Funkcja zwraca adres pierwszego elementu tablicy typu double.
double* newMask(const int N, const int maskType);