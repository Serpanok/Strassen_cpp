#include "header.h"

void writeMatrix(ostream& out, unsigned const int N, shType** matrix, unsigned const int xR, unsigned const int yR)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			out << matrix[i + yR][j + xR] << " ";
		}
		out << endl;
	}
}