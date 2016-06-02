#include "header.h"

void writeMatrix(ostream& out, unsigned int N, shType** matrix, unsigned int xR, unsigned int yR)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			//cout << "\n(((((( " << (i + yR) << "/" << (j + xR) << " ))))))";
			out << matrix[i + yR][j + xR] << " ";
		}
		out << endl;
	}
}