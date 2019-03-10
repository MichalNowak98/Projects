#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Filters.h"
#include"SimpleFunctions.h"
enum filterIndex { median, minimal, maximal, averaging, low, high, gauss , laplace};
int main(int argc, char* argv[])
{
	if (argc != 6)
	{
		printf("%s", "Wrong number of parameters. \n1.Mode \n2.Size of mask \n3.path to custom mask/build-in mask name \n4.path of image \n5.desired location and name for new image \nExample: d:\\folder\\...\\image.txt");
		return 0;
	}
	int N;
	char *pathToMask, *mode, *pathLoad, *pathSave;
	mode = argv[1];
	pathLoad = argv[4];
	pathSave = argv[5];
	N = atoi(argv[2]);
	if (!(N%2))
	{
		printf("%s", "Size of the mask should be an odd number.");
		return 0;
	}
	sfImage *Picture;
	sfVector2u size;
	double *mask;
	Picture = sfImage_createFromFile(pathLoad);
	if (Picture == NULL)
	{
		printf("%s", "Incorrect path to file (4)\nExample: d:\\folder\\...\\picture.jpg");
		sfImage_destroy(Picture);
		return 0;
	}
	double laplaceFilter[9] = { 0.0 ,1.0 ,0.0 ,1.0 ,-4.0 ,1.0 ,0.0 ,1.0 ,0.0 };
	size = sfImage_getSize(Picture);	//wpó³rzêdna y - wiersz, wspó³rzêdna x - kolumna d:\\lena.jpg
	if (!strcmp(mode, "-c"))
	{
		pathToMask = argv[3];
		FILE *customMask = fopen(pathToMask, "r");
		if (customMask == NULL)
		{
			printf("%s", "Incorrect path to file with custom mask (3)\nExample: d:\\folder\\...\\filter.txt");
			sfImage_destroy(Picture);
			return 0;
		}
		mask = (double*) malloc(N * N * sizeof(double));
		for (int i = 0; i < N * N; i++)
		{
			fscanf(customMask, "%lf", &mask[i]); //zapisuje po kolei argumenty do tablicy
		}
		simpleFilter(pathSave, Picture, &size, mask, N);
	}
	else if (!strcmp(mode, "-b"))
	{
		if (!strcmp(argv[3], "median"))
		{
			staticFilter(pathSave, Picture, &size, median, N);
		}
		else if (!strcmp(argv[3], "minimal"))
		{
			staticFilter(pathSave, Picture, &size, minimal, N);
		}
		else if (!strcmp(argv[3], "maximal"))
		{
			staticFilter(pathSave, Picture, &size, maximal, N);
		}
		else if (!strcmp(argv[3], "averaging"))
		{
			mask = newMask(N, averaging);
			simpleFilter(pathSave, Picture, &size, mask, N);
		}
		else if (!strcmp(argv[3], "low"))
		{
			mask = newMask(N, low);
			simpleFilter(pathSave, Picture, &size, mask, N);
		}
		else if (!strcmp(argv[3], "high"))
		{
			mask = newMask(N, high);
			simpleFilter(pathSave, Picture, &size, mask, N);
		}
		else if (!strcmp(argv[3], "gauss"))
		{
			mask = newMask(N, gauss);
			simpleFilter(pathSave, Picture, &size, mask, N);
		}
		else if (!strcmp(argv[3], "laplace"))
		{
			if (N != 3)
			{
				printf("%s", "Incorrect size of mask (2)\nlaplace filter can be only 3x3: N = 3");
				sfImage_destroy(Picture);
				return 0;
			}
			simpleFilter(pathSave, Picture, &size, laplaceFilter, N);
		}
		else
		{
			printf("%s", "Incorrect filter type parameter (3)\nCorrect parameters are: median/minimal/maximal/averaging/low/high/laplace/gauss");
			sfImage_destroy(Picture);
			return 0;
		}
	}
	else
	{
		printf("%s", "Incorrect mode parameter (1)\nCorrect parameters are: -c (custom filter) / -b (built-in filter)");
		sfImage_destroy(Picture);
		return 0;
	}
	sfImage_destroy(Picture);
	if (!strcmp(argv[3], "low") || !strcmp(argv[3], "high") || !strcmp(argv[3], "gauss") || !strcmp(argv[3], "averaging"))
	{
		free(mask);
	}
	return 0;
}