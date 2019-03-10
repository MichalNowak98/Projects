#pragma once
#include "Filters.h"
#include "SimpleFunctions.h"
#include<SFML\Graphics.h>
#include<SFML\Window.h>
#include<SFML\System.h>
#include<stdio.h>
#include<stdlib.h>
enum filterIndex { median, minimal, maximal, averaging, low, high, gauss, laplace};
void simpleFilter(const char pathSave[], const sfImage *pic, const sfVector2u *size, const double mask[], const int N)
{
	int element = 0, elementPomocniczy = 0;
	sfColor *pixelArray = newArray(size);	//przechowuje informacje o kolorach orygina³u(zakres od 0 do 255)
	sfColor *newPixelArray = newArray(size); //bêdzie przechowywaæ piksele przefiltrowanego zdjêcia
	for (int i = 0; i < size->y; i++)
		for (int j = 0; j < size->x; j++)
		{
			pixelArray[element] = newPixelArray[element] = sfImage_getPixel(pic, j, i);
			element++;
		}
	double red = 0, green = 0, blue = 0, alpha = 0;
	element = (N / 2)*(size->x + 1); //ustawienie zmiennej na 1 piksel, ktory bedzie modyfikowany. Np dla filtra 3x3 bêdzie to skok o jeden wiersz i jedn¹ kolumnê,
									 //dla 5x5: skok o 2 wiersze i 2 kolumny - (5/2)*(size->x + 1) = 2*size->x + 2
	for (int j = 0; j < size->y - 2 * (N / 2); j++)
	{
		for (int i = 0; i < size->x - 2 * (N / 2); i++, element++)
		{
			elementPomocniczy = element - (N / 2)*(1 + size->x);	//pierwszy piksel z otoczenia
			for (int g = 0; g < N; g++, elementPomocniczy += size->x - N)	//skok do nastpnego wiersza
			{
				for (int h = 0; h < N; h++, elementPomocniczy++)
				{
					red += (double)pixelArray[elementPomocniczy].r * mask[N * g + h];	//kolor czerwony
					green += (double)pixelArray[elementPomocniczy].g * mask[N * g + h];	//kolor zielony
					blue += (double)pixelArray[elementPomocniczy].b * mask[N * g + h];	//kolor niebieski
					alpha += (double)pixelArray[elementPomocniczy].a * mask[N * g + h];
				}
			}
			newPixelArray[element].r = (sfUint8)red;
			newPixelArray[element].g = (sfUint8)green;
			newPixelArray[element].b = (sfUint8)blue;
			newPixelArray[element].a = (sfUint8)alpha;
			red = green = blue = alpha = 0;
		}
		element += 2 * (N / 2);
	}
	sfUint8 *newArray = (sfUint8*)malloc((int)size->x * (int)size->y * 4);
	int nAiterator = 0;
	for (int i = 0; i < (int)size->x * (int)size->y; i++)
	{
		newArray[nAiterator] = abs(newPixelArray[i].r);
		nAiterator++;
		newArray[nAiterator] = abs(newPixelArray[i].g);
		nAiterator++;
		newArray[nAiterator] = abs(newPixelArray[i].b);
		nAiterator++;
		newArray[nAiterator] = abs(newPixelArray[i].a);
		nAiterator++;
	}
	sfImage *newPicture = sfImage_createFromPixels(size->x, size->y, newArray);
	sfImage_saveToFile(newPicture, pathSave);
	free(newPixelArray);
	free(newArray);
	free(pixelArray);
}
void staticFilter(const char pathSave[], const sfImage *pic, const sfVector2u *size, const int filter, const int N)
{
	int element = 0, elementPomocniczy;
	double *surroundsR, *surroundsG, *surroundsB, *surroundsA;
	surroundsR = (double*)malloc(N * N * sizeof(double));
	surroundsG = (double*)malloc(N * N * sizeof(double));
	surroundsB = (double*)malloc(N * N * sizeof(double));
	surroundsA = (double*)malloc(N * N * sizeof(double));
	sfColor *pixelArray = newArray(size);	//przechowuje informacje o kolorach (zakres od 0 do 255)
	for (int i = 0; i < size->y; i++)
		for (int j = 0; j < size->x; j++)
		{
			pixelArray[element] = sfImage_getPixel(pic, j, i);
			element++;
		}
	sfColor *newPixelArray = newArray(size);
	element = (N / 2)*(1 + size->x);
	for (int j = 0; j < size->y - 2 * (N / 2); j++)
	{
		for (int i = 0; i < size->x - 2 * (N / 2); i++, element++)
		{
			elementPomocniczy = element - (N / 2)*(1 + size->x);	//pierwszy piksel z otoczenia
			for (int g = 0; g < N; g++, elementPomocniczy += size->x - N)	//skok do nastpnego wiersza
			{
				for (int h = 0; h < N; h++, elementPomocniczy++)
				{
					surroundsR[g * N + h] = (double)pixelArray[elementPomocniczy].r; //h odlicza kolumny, a g odlicza wiersze
					surroundsG[g * N + h] = (double)pixelArray[elementPomocniczy].g;
					surroundsB[g * N + h] = (double)pixelArray[elementPomocniczy].b;
					surroundsA[g * N + h] = (double)pixelArray[elementPomocniczy].a;
				}
			}
			qsort(surroundsR, N * N, sizeof(double), compare);
			qsort(surroundsG, N * N, sizeof(double), compare);
			qsort(surroundsB, N * N, sizeof(double), compare);
			qsort(surroundsA, N * N, sizeof(double), compare);
			switch (filter)
			{
			case median:
			{
				newPixelArray[element].r = (sfUint8)surroundsR[N * N / 2];
				newPixelArray[element].g = (sfUint8)surroundsG[N * N / 2];
				newPixelArray[element].b = (sfUint8)surroundsB[N * N / 2];
				newPixelArray[element].a = (sfUint8)surroundsA[N * N / 2];
				break;
			}
			case minimal:
			{
				newPixelArray[element].r = (sfUint8)surroundsR[0];
				newPixelArray[element].g = (sfUint8)surroundsG[0];
				newPixelArray[element].b = (sfUint8)surroundsB[0];
				newPixelArray[element].a = (sfUint8)surroundsA[0];
				break;
			}
			case maximal:
			{
				newPixelArray[element].r = (sfUint8)surroundsR[N * N - 1];
				newPixelArray[element].g = (sfUint8)surroundsG[N * N - 1];
				newPixelArray[element].b = (sfUint8)surroundsB[N * N - 1];
				newPixelArray[element].a = (sfUint8)surroundsA[N * N - 1];
				break;
			}
			}
		}
		element += 2 * (N / 2);
	}
	sfUint8 *newArray = (sfUint8*)malloc((int)size->x * (int)size->y * 4);
	int nAiterator = 0;
	for (int i = 0; i < (int)size->x * (int)size->y; i++)
	{
		newArray[nAiterator] = abs(newPixelArray[i].r);
		nAiterator++;
		newArray[nAiterator] = abs(newPixelArray[i].g);
		nAiterator++;
		newArray[nAiterator] = abs(newPixelArray[i].b);
		nAiterator++;
		newArray[nAiterator] = abs(newPixelArray[i].a);
		nAiterator++;
	}
	sfImage *newPicture = sfImage_createFromPixels(size->x, size->y, newArray);
	sfImage_saveToFile(newPicture, pathSave);
	free(surroundsR);
	free(surroundsG);
	free(surroundsB);
	free(surroundsA);
	free(newPixelArray);
	free(newArray);
	free(pixelArray);
}