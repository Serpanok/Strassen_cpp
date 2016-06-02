#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

typedef float shType;

/* Reading matrix from stream */
void readMatrix(istream& inMatrix, unsigned const int N, shType** matrix);

/* Record matrix to stream */
void writeMatrix(ostream& out, unsigned const int N, shType** matrix, unsigned const int xR = 0, unsigned const int yR = 0);

/* Generation matrix to stream */
void genMatrix(ostream& out, unsigned const int N, const int min = 0, const int max = 1000, time_t* sranGen = nullptr);

/*	Strassen algorithm for matrix multiplication

	int N			- dimension of the matrix;
	int ** A		- matrix A with pre-allocated dynamiñ memory;
	int ** B		- matrix B with pre-allocated dynamiñ memory;
	int ** result	- matrix result with pre-allocated dynamiñ memory;
	bool useSimd	- is need to use SIMD;
*/
void shtrassen(unsigned const int N, shType** A, shType** B, shType** result, bool const useSIMD = true, unsigned const int xA = 0, unsigned const int yA = 0, unsigned const int xB = 0, unsigned const int yB = 0, unsigned const int xR = 0, unsigned const int yR = 0);

void algCounter(unsigned const __int8 addition = 0, unsigned const __int8 subtraction = 0, unsigned const __int8 multiplication = 0);