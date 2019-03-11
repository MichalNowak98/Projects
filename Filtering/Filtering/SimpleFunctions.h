#pragma once
#include<SFML\Graphics.h>
#include<SFML\Window.h>
#include<SFML\System.h>
//Funkcja por�wnuj�ca wykorzystywana przez quicksort. 
//Parametry:
//a i b (konwertowane na typ double w ciele funkcji).
//Funkcja zwraca 0 dla a == b, -1 dla b > a, 1 dla a > b.
int compare(const double* a, const double* b);
//Alokuje tablic� o podanym rozmiarze.
//Parametry:
//Przyjmuje adres zmiennej size typu sfVector2u zawieraj�cej wymiary tablicy. 
//Funkcja zwraca adres pierwszego elementu tablicy typu sfVector2u.
sfColor* newArray(const sfVector2u *size);
//Alokuje tablic� o podanym rozmiarze i wype�nia j� warto�ciami w zale�no�ci od rodzaju maski.
//Parametry:
//przyjmuje szeroko�� maski jako warto�� ca�kowit� N oraz typ maski jako warto�� ca�kowit� maskType.
//Funkcja zwraca adres pierwszego elementu tablicy typu double.
double* newMask(const int N, const int maskType);