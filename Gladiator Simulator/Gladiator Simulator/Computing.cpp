#include "Computing.h"

int random_int(int lower_limit, int upper_limit)
{
	return rand() % (upper_limit - lower_limit) + lower_limit + 1;
}
