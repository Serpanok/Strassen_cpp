#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

typedef float shType;

/* Чтение матрицы из потока */
void readMatrix(istream& inMatrix, unsigned int N, shType** matrix);

/* Запись матрицы в поток */
void writeMatrix(ostream& out, unsigned int N, shType** matrix, unsigned int xR = 0, unsigned int yR = 0);

/* Генерация матрицы в поток */
void genMatrix(ostream& out, unsigned int N, int min = 0, int max = 1000, time_t* sranGen = nullptr);

/*	Алгоритм Штрассена для умножения матриц

int N			- Размерность матрицы;
int** A			- Марица A с уже выделенной динамической памятью new int[N][N];
int** B			- Марица B с уже выделенной динамической памятью new int[N][N];
int** result	- Марица result с уже выделенной динамической памятью new int[N][N];
int x			- Начальное положение по стобцам(верхнее);
int y			- Начальное положение по строкам(верхнее);
*/
void shtrassen(unsigned int N, shType** A, shType** B, shType** result, unsigned int xA = 0, unsigned int yA = 0, unsigned int xB = 0, unsigned int yB = 0, unsigned int xR = 0, unsigned int yR = 0);

void algCounter(unsigned __int8 addition = 0, unsigned __int8 subtraction = 0, unsigned __int8 multiplication = 0);