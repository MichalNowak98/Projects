#pragma once
#include "Filters.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
enum filterIndex { median, minimal, maximal, averaging, low, high, gauss , laplace};
int compare(const double *double_a, const double *double_b)
{
	if (*double_a == *double_b) return 0;
	else if (*double_a < *double_b) return -1;
	else return 1;
}
sfColor* newArray(const sfVector2u *size)
{
	sfColor *pixelArray = (sfColor*)malloc(size->x * size->y * sizeof(sfColor));
	return pixelArray;
}
double* newMask(const int N, const int maskType)
{
	double *mask = (double*)malloc(N * N * sizeof(double));
	switch (maskType)
	{
	case averaging:
	{
		for (int i = 0; i < N * N; i++)
		{
			mask[i] = 1 / (double)(N * N);
		}
		break;
	}
	case low:
	{
		for (int i = 0; i < N * N; i++)
		{
			mask[i] = 1 / (double)(N * N + 3); // -1: N*N-1 elementow, +4: srodkowy element jest 4
		}
		mask[N * N / 2] = 4 / (double)(N * N + 3);
		break;
	}
	case high:
	{
		for (int i = 0; i < N * N; i++)
		{
			mask[i] = -1; // -1: N*N-1 elementow, -1: œrdokowy element nie jest jedynka;
		}
		mask[N * N / 2] = N * N;
		break;
	}
	case gauss:
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					mask[i * N + j] = (1.0 / (double)(2.0 * 3.14 * pow(1, 2))) * exp(-(pow(j - (N / 2), 2) + pow(i - (N / 2), 2)) / (2.0 * pow(1, 2)));
				}
			}
			break;
		}
	}
	return mask;
}