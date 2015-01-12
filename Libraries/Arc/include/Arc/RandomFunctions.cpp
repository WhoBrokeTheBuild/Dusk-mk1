#include "RandomFunctions.h"

void Arc::Arc_InitRandom( void )
{
	srand( unsigned(time(nullptr)) );
}

int Arc::Arc_RandInt( int min, int max )
{
	return min + (rand() % (max - min + 1));
}

float Arc::Arc_RandFloat( float min, float max )
{
	return min + (float)rand() / (float)(RAND_MAX / (max - min));
}

double Arc::Arc_RandDouble( double min, double max )
{
	return min + (double)rand() / (double)(RAND_MAX / (max - min));
}

