#include "header.h"
#include <stack>

namespace shNS {
	//натуральные степени двойки
	unsigned int naturalDegreeOfTwo[16] = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 };

	//оптимальная размерность матрицы для перехода к обычному умножению
	const unsigned int optimalN = 32; //32

									  /*	Сумма двух матриц

									  int N			- Размерность матрицы;
									  int** A			- Марица A с уже выделенной динамической памятью(размер не меньше [x+N][y+N]);
									  int** B			- Марица B с уже выделенной динамической памятью(размер не меньше [x+N][y+N]);
									  int** result	- Марица result с уже выделенной динамической памятью(размер не меньше [x+N][y+N]);
									  int xA			- Начальное положение по строкам у матрицы A(верхнее);
									  int yA			- Начальное положение по стобцам у матрицы A(верхнее);
									  int xB			- Начальное положение по строкам у матрицы B(верхнее);
									  int yB			- Начальное положение по стобцам у матрицы B(верхнее);
									  int xR			- Начальное положение по строкам у матрицы result(верхнее);
									  int yR			- Начальное положение по стобцам у матрицы result(верхнее);

									  */
	void additionMatrix(unsigned int N, shType** A, shType** B, shType** result, unsigned int xA = 0, unsigned int yA = 0, unsigned int xB = 0, unsigned int yB = 0, unsigned int xR = 0, unsigned int yR = 0)
	{
		unsigned int iR = yR;
		unsigned int iA = yA;
		unsigned int iB = yB;
		__m128 dA, dB, PackedData;
		shType *pA, *pB, *pR;
		float *pVR = new float[4];
		for (unsigned int i = 0; i < N; i++)
		{
			pA = A[iA] + xA;
			pB = B[iB] + xB;
			pR = result[iR] + xR;
			for (unsigned int j = 0; j < N; j += 4)
			{
				//обнуление
				PackedData = _mm_setzero_ps();
				//загрузка данных
				dA = _mm_set_ps(static_cast<float>(pA[0]), static_cast<float>(pA[1]), static_cast<float>(pA[2]), static_cast<float>(pA[3]));
				dB = _mm_set_ps(static_cast<float>(pB[0]), static_cast<float>(pB[1]), static_cast<float>(pB[2]), static_cast<float>(pB[3]));
				//сложение 4 пар целых чисел
				PackedData = _mm_add_ps(dA, dB);
				//записываем результат
				_mm_storeu_ps(pVR, PackedData);
				//увеличиваем счётчик сложений
				algCounter(4);

				pR[0] = pVR[0];
				pR[1] = pVR[1];
				pR[2] = pVR[2];
				pR[3] = pVR[3];

				pA += 4;
				pB += 4;
				pR += 4;
			}
			iR++;
			iA++;
			iB++;
		}
	}
	void _additionMatrix(unsigned int N, shType** A, shType** B, shType** result, unsigned int xA = 0, unsigned int yA = 0, unsigned int xB = 0, unsigned int yB = 0, unsigned int xR = 0, unsigned int yR = 0)
	{
		unsigned int iR = yR;
		unsigned int iA = yA;
		unsigned int iB = yB;
		for (unsigned int i = 0; i < N; i++)
		{
			//cout << "\n\n==== " << i;
			for (unsigned int j = 0; j < N; j++)
			{
				result[iR][xR + j] = A[iA][xA + j] + B[iB][xB + j];

				//cout << "\n[" << (xA + j) << "]" << A[iA][xA + j] << " + " << B[iB][xB + j] << " = " << result[iR][xR + j];

				algCounter(1);
			}
			iR++;
			iA++;
			iB++;
		}
	}
	/*void __additionMatrix(unsigned int N, shType** A, shType** B, shType** result, unsigned int xA = 0, unsigned int yA = 0, unsigned int xB = 0, unsigned int yB = 0, unsigned int xR = 0, unsigned int yR = 0)
	{
	unsigned int iR = yR;
	unsigned int iA = yA;
	unsigned int iB = yB;
	__m128 dA, dB, PackedData;
	shType *pA, *pB, *pR;
	for (unsigned int i = 0; i < N; i++)
	{
	pA = A[iA] + xA;
	pB = B[iB] + xB;
	pR = result[iR] + xR;
	for (unsigned int j = 0; j < N; j+=4)
	{
	//обнуление
	PackedData = _mm_setzero_ps();
	//загрузка данных
	dA = _mm_loadu_ps(pA + j);
	dB = _mm_loadu_ps(pB + j);
	//сложение 4 пар целых чисел
	PackedData = _mm_add_ps(dA, dB);
	//записываем результат
	_mm_storeu_ps(pR + j, PackedData);
	//увеличиваем счётчик сложений
	algCounter(4);
	}
	iR++;
	iA++;
	iB++;
	}
	}*/

	/*	Разность двух матриц

	int N			- Размерность матрицы;
	int** A			- Марица A с уже выделенной динамической памятью(размер не меньше [x+N][y+N]);
	int** B			- Марица B с уже выделенной динамической памятью(размер не меньше [x+N][y+N]);
	int** result	- Марица result с уже выделенной динамической памятью(размер не меньше [x+N][y+N]);
	int xA			- Начальное положение по строкам у матрицы A(верхнее);
	int yA			- Начальное положение по стобцам у матрицы A(верхнее);
	int xB			- Начальное положение по строкам у матрицы B(верхнее);
	int yB			- Начальное положение по стобцам у матрицы B(верхнее);
	int xR			- Начальное положение по строкам у матрицы result(верхнее);
	int yR			- Начальное положение по стобцам у матрицы result(верхнее);
	*/
	void subtractionMatrix(unsigned int N, shType** A, shType** B, shType** result, unsigned int xA = 0, unsigned int yA = 0, unsigned int xB = 0, unsigned int yB = 0, unsigned int xR = 0, unsigned int yR = 0)
	{
		unsigned int iR = yR;
		unsigned int iA = yA;
		unsigned int iB = yB;
		__m128 dA, dB, PackedData;
		shType *pA, *pB, *pR;
		float *pVR = new float[4];
		for (unsigned int i = 0; i < N; i++)
		{
			pA = A[iA] + xA;
			pB = B[iB] + xB;
			pR = result[iR] + xR;
			for (unsigned int j = 0; j < N; j += 4)
			{
				//обнуление
				PackedData = _mm_setzero_ps();
				//загрузка данных
				dA = _mm_set_ps(static_cast<float>(pA[0]), static_cast<float>(pA[1]), static_cast<float>(pA[2]), static_cast<float>(pA[3]));
				dB = _mm_set_ps(static_cast<float>(pB[0]), static_cast<float>(pB[1]), static_cast<float>(pB[2]), static_cast<float>(pB[3]));
				//вычитание 4 пар целых чисел
				PackedData = _mm_sub_ps(dA, dB);
				//записываем результат
				_mm_storeu_ps(pVR, PackedData);
				//увеличиваем счётчик вычетаний
				algCounter(4);

				//result[iR][yR + j] = A[iA][xA + j] - B[iB][xB + j];

				pR[0] = pVR[0];
				pR[1] = pVR[1];
				pR[2] = pVR[2];
				pR[3] = pVR[3];

				pA += 4;
				pB += 4;
				pR += 4;
			}
			iR++;
			iA++;
			iB++;
		}
	}
	void _subtractionMatrix(unsigned int N, shType** A, shType** B, shType** result, unsigned int xA = 0, unsigned int yA = 0, unsigned int xB = 0, unsigned int yB = 0, unsigned int xR = 0, unsigned int yR = 0)
	{
		unsigned int iR = yR;
		unsigned int iA = yA;
		unsigned int iB = yB;
		for (unsigned int i = 0; i < N; i++)
		{

			for (unsigned int j = 0; j < N; j++)
			{
				result[iR][yR + j] = A[iA][xA + j] - B[iB][xB + j];
				algCounter(0, 1);
			}
			iR++;
			iA++;
			iB++;
		}
	}
	/*void __subtractionMatrix(unsigned int N, shType** A, shType** B, shType** result, unsigned int xA = 0, unsigned int yA = 0, unsigned int xB = 0, unsigned int yB = 0, unsigned int xR = 0, unsigned int yR = 0)
	{
	unsigned int iR = yR;
	unsigned int iA = yA;
	unsigned int iB = yB;
	__m128 dA, dB, PackedData;
	shType *pA, *pB, *pR;
	for (unsigned int i = 0; i < N; i++)
	{
	pA = A[iA] + xA;
	pB = B[iB] + xB;
	pR = result[iR] + xR;
	for (unsigned int j = 0; j < N; j += 4)
	{
	//обнуление
	PackedData = _mm_setzero_ps();
	//загрузка данных
	dA = _mm_loadu_ps(pA + j);
	dB = _mm_loadu_ps(pB + j);
	//вычитание 4 пар целых чисел
	PackedData = _mm_sub_ps(dA, dB);
	//записываем результат
	_mm_storeu_ps(pR + j, PackedData);
	//увеличиваем счётчик вычетаний
	algCounter(4);

	//result[iR][yR + j] = A[iA][xA + j] - B[iB][xB + j];
	}
	iR++;
	iA++;
	iB++;
	}
	}*/

	/*	Произведение двух матриц

	int N			- Размерность обрабатываемых значений
	int** A			- Марица A с уже выделенной динамической памятью(размер не меньше [x+N][y+N]);
	int** B			- Марица B с уже выделенной динамической памятью(размер не меньше [x+N][y+N]);
	int** result	- Марица result с уже выделенной динамической памятью(размер не меньше [x+N][y+N]);
	int xA			- Начальное положение по строкам у матрицы A(верхнее);
	int yA			- Начальное положение по стобцам у матрицы A(верхнее);
	int xB			- Начальное положение по строкам у матрицы B(верхнее);
	int yB			- Начальное положение по стобцам у матрицы B(верхнее);
	int xR			- Начальное положение по строкам у матрицы result(верхнее);
	int yR			- Начальное положение по стобцам у матрицы result(верхнее);
	*/
	void calculateMatrix(unsigned int N, shType** A, shType** B, shType** result, unsigned int xA = 0, unsigned int yA = 0, unsigned int xB = 0, unsigned int yB = 0, unsigned int xR = 0, unsigned int yR = 0)
	{
		unsigned int iR = yR;
		unsigned int iA = yA;
		__m128 dA, dB, PackedData;
		shType *pA;
		float *pVR;
		float sum;
		unsigned int lyB;
		pVR = new float[4];
		for (unsigned int i = 0; i < N; i++)
		{
			for (unsigned int l = 0; l< N; l++)
			{
				sum = 0;
				lyB = l + yB;
				pA = A[iA] + xA;
				for (unsigned int j = 0; j< N; j += 4)
				{
					//обнуление
					PackedData = _mm_setzero_ps();
					//загрузка данных
					dA = _mm_set_ps(static_cast<float>(pA[0]), static_cast<float>(pA[1]), static_cast<float>(pA[2]), static_cast<float>(pA[3]));
					dB = _mm_set_ps(static_cast<float>(B[j + xB][lyB]), static_cast<float>(B[j + 1 + xB][lyB]), static_cast<float>(B[j + 2 + xB][lyB]), static_cast<float>(B[j + 3 + xB][lyB]));
					//умножение 4 пар целых чисел
					PackedData = _mm_mul_ps(dA, dB);
					//записываем результат
					_mm_storeu_ps(pVR, PackedData);
					//добавляем сумму умножений
					sum += pVR[0] + pVR[1] + pVR[2] + pVR[3];
					//увеличиваем счётчик умножений и сложений
					algCounter(4, 0, 4);

					pA += 4;

					//temp += A[iA][j + xA] * B[j + xB][l + yB];
				}

				result[iR][l + xR] = static_cast<shType>(sum);
			}
			iR++;
			iA++;
		}
	}
	void _calculateMatrix(unsigned int N, shType** A, shType** B, shType** result, unsigned int xA = 0, unsigned int yA = 0, unsigned int xB = 0, unsigned int yB = 0, unsigned int xR = 0, unsigned int yR = 0)
	{
		unsigned int iR = yR;
		unsigned int iA = yA;
		for (unsigned int i = 0; i < N; i++)
		{
			for (unsigned int l = 0; l< N; l++)
			{
				int temp = 0;
				for (unsigned int j = 0; j< N; j++)
				{
					temp += A[iA][j + xA] * B[j + xB][l + yB];
					algCounter(1, 0, 1);
				}

				result[iR][l + xR] = temp;
			}
			iR++;
			iA++;
		}
	}
	void __calculateMatrix(unsigned int N, shType** A, shType** B, shType** result, unsigned int xA = 0, unsigned int yA = 0, unsigned int xB = 0, unsigned int yB = 0, unsigned int xR = 0, unsigned int yR = 0)
	{
		unsigned int iR = yR;
		unsigned int iA = yA;
		__m128i dA, dB, PackedData;
		shType *pA, *pB, *pVR;
		shType sum;
		unsigned int lyB;
		pB = new shType[2];
		pVR = new shType[2];
		for (unsigned int i = 0; i < N; i++)
		{
			for (unsigned int l = 0; l< N; l++)
			{
				sum = 0;
				lyB = l + yB;
				pA = A[iA] + xA;
				for (unsigned int j = 0; j< N; j += 2)
				{
					//обнуление
					PackedData = _mm_setzero_si128();
					//загрузка данных
					dA = _mm_load_si128((__m128i*)(pA + j));
					//dB = _mm_loadu_ps(pB);
					pB[0] = B[j + xB][lyB];
					pB[1] = B[j + 1 + xB][lyB];
					dB = _mm_load_si128((__m128i*)(pB));
					//умножение 4 пар целых чисел
					PackedData = _mm_add_epi64(dA, dB);
					//записываем результат
					_mm_store_si128((__m128i*)(pVR), PackedData);
					//добавляем сумму умножений
					sum += pVR[0] + pVR[1];
					//увеличиваем счётчик умножений и сложений
					algCounter(2, 0, 2);

					//temp += A[iA][j + xA] * B[j + xB][l + yB];
				}

				result[iR][l + xR] = sum;
			}
			iR++;
			iA++;
		}
	}
	/*void __calculateMatrix(unsigned int N, shType** A, shType** B, shType** result, unsigned int xA = 0, unsigned int yA = 0, unsigned int xB = 0, unsigned int yB = 0, unsigned int xR = 0, unsigned int yR = 0)
	{
	unsigned int iR = yR;
	unsigned int iA = yA;
	__m128 dA, dB, PackedData;
	shType *pA, *pB, *pVR;
	shType sum;
	unsigned int lyB;
	pVR	= new shType[4];
	for (unsigned int i = 0; i < N; i++)
	{
	for (unsigned int l = 0; l< N; l++)
	{
	sum = 0;
	lyB = l + yB;
	pA = A[iA] + xA;
	for (unsigned int j = 0; j< N; j+=4)
	{
	//обнуление
	PackedData = _mm_setzero_ps();
	//загрузка данных
	dA = _mm_loadu_ps(pA + j);
	//dB = _mm_loadu_ps(pB);
	dB = _mm_set_ps(B[j + xB][lyB], B[j + 1 + xB][lyB], B[j + 2 + xB][lyB], B[j + 3 + xB][lyB]);
	//умножение 4 пар целых чисел
	PackedData = _mm_mul_ps(dA, dB);
	//записываем результат
	_mm_storeu_ps(pVR, PackedData);
	//добавляем сумму умножений
	sum += pVR[0] + pVR[1] + pVR[2] + pVR[3];
	//увеличиваем счётчик умножений и сложений
	algCounter(4, 0, 4);

	//temp += A[iA][j + xA] * B[j + xB][l + yB];
	}

	result[iR][l + xR] = sum;
	}
	iR++;
	iA++;
	}
	}*/
}

void shtrassen(unsigned int N, shType** A, shType** B, shType** result, unsigned int xA, unsigned int yA, unsigned int xB, unsigned int yB, unsigned int xR, unsigned int yR)
{
	unsigned int n = N;

	shType** A_;
	shType** B_;

	//проверка на соответствие размерности натуральной степени 2
	bool isChangeN = false;
	for (unsigned int i = 0; i < 16; i++)
	{
		if (n > shNS::naturalDegreeOfTwo[i] && n < shNS::naturalDegreeOfTwo[i + 1])
		{
			n = shNS::naturalDegreeOfTwo[i + 1];
			isChangeN = true;
		}
		else if (shNS::naturalDegreeOfTwo[i] == n)
		{
			break;
		}
	}

	//если нужно расширить матрицу
	if (isChangeN)
	{
		A_ = new shType*[n];
		B_ = new shType*[n];
		for (unsigned int i = 0; i < n; i++)
		{
			A_[i] = new shType[n];
			B_[i] = new shType[n];

			for (unsigned int j = 0; j < n; j++)
			{
				A_[i][j] = j < N && i < N ? A[i][j] : 0;
				B_[i][j] = j < N && i < N ? B[i][j] : 0;
			}
		}
	}
	else
	{
		A_ = A;
		B_ = B;
	}

	//shNS::additionMatrix(N,A,B,result);
	//return;

	//if not optimal size of matrix
	if (N > shNS::optimalN)
	{
		//size of half part matrix
		unsigned int halfN = N / 2;

		//shNS::shtrassenStackItem *items = new shNS::shtrassenStackItem(halfN);
		shType **p1, **p2, **p3, **p4, **p5, **p6, **p7, **temp1, **temp2;
		p1 = new shType*[N];
		p2 = new shType*[N];
		p3 = new shType*[N];
		p4 = new shType*[N];
		p5 = new shType*[N];
		p6 = new shType*[N];
		p7 = new shType*[N];
		temp1 = new shType*[N];
		temp2 = new shType*[N];
		for (unsigned int i = 0; i < N; i++)
		{
			p1[i] = new shType[N];
			p2[i] = new shType[N];
			p3[i] = new shType[N];
			p4[i] = new shType[N];
			p5[i] = new shType[N];
			p6[i] = new shType[N];
			p7[i] = new shType[N];
			temp1[i] = new shType[N];
			temp2[i] = new shType[N];
		}

		//p1 = (A_11 + A_22) * (B_11 + B_22)
		shNS::additionMatrix(halfN, A, A, temp1, xA, yA, xA + halfN, yA + halfN);
		shNS::additionMatrix(halfN, B, B, temp2, xB, yB, xB + halfN, yB + halfN);
		shtrassen(halfN, temp1, temp2, p1);
		//p2 = (A_21 + A_22) * B_11
		shNS::additionMatrix(halfN, A, A, temp1, xA, yA + halfN, xA + halfN, yA + halfN);
		shtrassen(halfN, temp1, B, p2, 0, 0, xB, yB);
		//p3 = A_11 * (B_12 - B_22)
		shNS::subtractionMatrix(halfN, B, B, temp1, xB + halfN, yB, xB + halfN, yB + halfN);
		shtrassen(halfN, A, temp1, p3, xA, yA);
		//p4 = A_22 * (B_21 - B_11)
		shNS::subtractionMatrix(halfN, B, B, temp1, xB, yB + halfN, xB, yB);
		shtrassen(halfN, A, temp1, p4, xA + halfN, yA + halfN);
		//p5 = (A_11 + A_12) * B_22
		shNS::additionMatrix(halfN, A, A, temp1, xA, yA, xA + halfN, yA);
		shtrassen(halfN, temp1, B, p5, 0, 0, xB + halfN, yB + halfN);
		//p6 = (A_21 - A_11) * (B_11 + B_12)
		shNS::subtractionMatrix(halfN, A, A, temp1, xA, yA + halfN, xA, yA);
		shNS::additionMatrix(halfN, B, B, temp2, xB, yB, xB + halfN, yB);
		shtrassen(halfN, temp1, temp2, p6);
		//p7 = (A_12 - A_22) * (B_21 + B_22)
		shNS::subtractionMatrix(halfN, A, A, temp1, xA + halfN, yA, xA + halfN, yA + halfN);
		shNS::additionMatrix(halfN, B, B, temp2, xB, yB + halfN, xB + halfN, yB + halfN);
		shtrassen(halfN, temp1, temp2, p7);

		//c11 = p1 + p4 - p5 + p7
		shNS::additionMatrix(halfN, p1, p4, temp1);
		shNS::subtractionMatrix(halfN, temp1, p5, temp2);
		shNS::additionMatrix(halfN, temp2, p7, result, 0, 0, 0, 0, xR, yR);
		//c12 = p3 + p5
		shNS::additionMatrix(halfN, p3, p5, result, 0, 0, 0, 0, xR + halfN, yR);
		//c21 = p2 + p4
		shNS::additionMatrix(halfN, p2, p4, result, 0, 0, 0, 0, xR, yR + halfN);
		//c22 = p1 - p2
		shNS::subtractionMatrix(halfN, p1, p2, temp1);
		shNS::additionMatrix(halfN, temp1, p3, temp2);
		shNS::additionMatrix(halfN, temp2, p6, result, 0, 0, 0, 0, xR + halfN, yR + halfN);

		/*delete[] p1;
		delete[] p2;
		delete[] p3;
		delete[] p4;
		delete[] p5;
		delete[] p6;
		delete[] p7;
		delete[] temp1;
		delete[] temp2;*/
	}
	else
	{
		shNS::calculateMatrix(N, A, B, result, xA, yA, xB, yB, xR, yR);
	}
}