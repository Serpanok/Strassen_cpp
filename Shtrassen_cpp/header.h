#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

typedef float shType;

/* ������ ������� �� ������ */
void readMatrix(istream& inMatrix, unsigned int N, shType** matrix);

/* ������ ������� � ����� */
void writeMatrix(ostream& out, unsigned int N, shType** matrix, unsigned int xR = 0, unsigned int yR = 0);

/* ��������� ������� � ����� */
void genMatrix(ostream& out, unsigned int N, int min = 0, int max = 1000, time_t* sranGen = nullptr);

/*	�������� ��������� ��� ��������� ������

int N			- ����������� �������;
int** A			- ������ A � ��� ���������� ������������ ������� new int[N][N];
int** B			- ������ B � ��� ���������� ������������ ������� new int[N][N];
int** result	- ������ result � ��� ���������� ������������ ������� new int[N][N];
int x			- ��������� ��������� �� �������(�������);
int y			- ��������� ��������� �� �������(�������);
*/
void shtrassen(unsigned int N, shType** A, shType** B, shType** result, unsigned int xA = 0, unsigned int yA = 0, unsigned int xB = 0, unsigned int yB = 0, unsigned int xR = 0, unsigned int yR = 0);

void algCounter(unsigned __int8 addition = 0, unsigned __int8 subtraction = 0, unsigned __int8 multiplication = 0);