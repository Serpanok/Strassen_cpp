#include "header.h"

void readMatrix(istream& inMatrix, unsigned int N, shType** matrix)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			inMatrix >> matrix[i][j];
		}
	}
}