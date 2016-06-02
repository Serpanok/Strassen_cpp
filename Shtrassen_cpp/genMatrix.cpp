#include "header.h"
#include <cstdlib>

void genMatrix(ostream& out, unsigned int N, int min, int max, time_t* sranGen)
{
	srand(time(sranGen));

	out << N;

	for (int i = 0; i < N * 2; i++)
	{
		out << std::endl;
		for (int j = 0; j < N; j++)
		{
			if (j != 0)
			{
				out << " ";
			}
			out << (min + rand() % max);
		}
	}
}