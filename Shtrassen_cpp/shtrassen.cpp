#include "header.h"
#include <stack>

namespace shNS {
	//natural power of two
	unsigned int naturalDegreeOfTwo[16] = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 };

	//optimum dimension of the matrix to move to the ordinary multiplication
	const unsigned int optimalN = 32; //32

	/*	The sum of two matrices

		int N			- dimension of the matrix;
		int ** A		- matrix A with pre-allocated dynamiñ memory (size not less than [x + N] [y + N]);
		int ** B		- üatrix B with pre-allocated dynamic memory (size is not less than [x + N] [y + N]);
		int ** result	- result matrix pre-allocated dynamic memory (size is not less than [x + N] [y + N]);
		int xA			- initial position of the rows of the matrix A (top);
		int yA			- initial position in any column of the matrix A (top);
		int xB			- initial position of the rows of the matrix B (top);
		int yB			- initial position in any column of the matrix B (top);
		int xR			- initial position in lines at the result of the matrix (top);
		int yR			- initial position in any column at the result of the matrix (top);
	*/
	void additionMatrix(unsigned const int N, shType** A, shType** B, shType** result, unsigned const int xA = 0, unsigned const int yA = 0, unsigned const int xB = 0, unsigned const int yB = 0, unsigned const int xR = 0, unsigned const int yR = 0)
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
	//version with SIMD
	void _additionMatrix(unsigned const int N, shType** A, shType** B, shType** result, unsigned const int xA = 0, unsigned const int yA = 0, unsigned const int xB = 0, unsigned const int yB = 0, unsigned const int xR = 0, unsigned const int yR = 0)
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
				//zeroing
				PackedData = _mm_setzero_ps();
				//Loading data
				dA = _mm_loadu_ps(pA + j);
				dB = _mm_loadu_ps(pB + j);
				//addition of 4 pairs of integers
				PackedData = _mm_add_ps(dA, dB);
				//write result
				_mm_storeu_ps(pR + j, PackedData);
				//increase counter additions
				algCounter(4);
			}
			iR++;
			iA++;
			iB++;
		}
	}

	/*	The difference between the two matrices

		int N			- dimension of the matrix;
		int ** A		- matrix A with pre-allocated dynamiñ memory (size not less than [x + N] [y + N]);
		int ** B		- üatrix B with pre-allocated dynamic memory (size is not less than [x + N] [y + N]);
		int ** result	- result matrix pre-allocated dynamic memory (size is not less than [x + N] [y + N]);
		int xA			- initial position of the rows of the matrix A (top);
		int yA			- initial position in any column of the matrix A (top);
		int xB			- initial position of the rows of the matrix B (top);
		int yB			- initial position in any column of the matrix B (top);
		int xR			- initial position in lines at the result of the matrix (top);
		int yR			- initial position in any column at the result of the matrix (top);
	*/
	void subtractionMatrix(unsigned const int N, shType** A, shType** B, shType** result, unsigned const int xA = 0, unsigned const int yA = 0, unsigned const int xB = 0, unsigned const int yB = 0, unsigned const int xR = 0, unsigned const int yR = 0)
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
	//version with SIMD
	void _subtractionMatrix(unsigned const int N, shType** A, shType** B, shType** result, unsigned const int xA = 0, unsigned const int yA = 0, unsigned const int xB = 0, unsigned const int yB = 0, unsigned const int xR = 0, unsigned const int yR = 0)
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
				//zeroing
				PackedData = _mm_setzero_ps();
				//Loading data
				dA = _mm_loadu_ps(pA + j);
				dB = _mm_loadu_ps(pB + j);
				//Subtract 4 pairs of integers
				PackedData = _mm_sub_ps(dA, dB);
				//write result
				_mm_storeu_ps(pR + j, PackedData);
				//increase counter subtractions
				algCounter(0, 4);
			}
			iR++;
			iA++;
			iB++;
		}
	}

	/*	The product of two matrices

		int N			- dimension of processed values
		int ** A		- matrix A with pre-allocated dynamic memory (size not less than [x + N] [y + N]);
		int ** B		- matrix B with pre-allocated allocated dynamic memory (size is not less than [x + N] [y + N]);
		int ** result	- matrix result pre-allocated dynamic memory (size is not less than [x + N] [y + N]);
		int xA			- initial position of the rows of the matrix A (top);
		int yA			- initial position in any column of the matrix A (top);
		int xB			- initial position of the rows of the matrix B (top);
		int yB			- initial position in any column of the matrix B (top);
		int xR			- initial position in lines at the result of the matrix (top);
		int yR			- initial position in any column at the result of the matrix (top);
	*/
	void calculateMatrix(unsigned const int N, shType** A, shType** B, shType** result, unsigned const int xA = 0, unsigned const int yA = 0, unsigned const int xB = 0, unsigned const int yB = 0, unsigned const int xR = 0, unsigned const int yR = 0)
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
	//version with SIMD
	void _calculateMatrix(unsigned const int N, shType** A, shType** B, shType** result, unsigned const int xA = 0, unsigned const int yA = 0, unsigned const int xB = 0, unsigned const int yB = 0, unsigned const int xR = 0, unsigned const int yR = 0)
	{
		unsigned int iR = yR;
		unsigned int iA = yA;
		__m128 dA, dB, PackedData;
		shType *pA, *pB, *pVR;
		shType sum;
		unsigned int lyB;
		pVR = new shType[4];
		for (unsigned int i = 0; i < N; i++)
		{
			for (unsigned int l = 0; l < N; l++)
			{
				sum = 0;
				lyB = l + yB;
				pA = A[iA] + xA;
				for (unsigned int j = 0; j < N; j += 4)
				{
					//zeroing
					PackedData = _mm_setzero_ps();
					//Loading data
					dA = _mm_loadu_ps(pA + j);
					dB = _mm_set_ps(B[j + xB][lyB], B[j + 1 + xB][lyB], B[j + 2 + xB][lyB], B[j + 3 + xB][lyB]);
					//Subtract 4 pairs of integers
					PackedData = _mm_mul_ps(dA, dB);
					//write result
					_mm_storeu_ps(pVR, PackedData);
					//add the amount of multiplications
					sum += pVR[0] + pVR[1] + pVR[2] + pVR[3];
					//increase counter subtractions
					algCounter(4, 0, 4);
				}

				result[iR][l + xR] = sum;
			}
			iR++;
			iA++;
		}
	}
}

void shtrassen(unsigned const int N, shType** A, shType** B, shType** result, bool const useSIMD, unsigned const int xA, unsigned const int yA, unsigned const int xB, unsigned const int yB, unsigned const int xR, unsigned const int yR)
{
	unsigned int n = N;

	shType** A_;
	shType** B_;

	//checking for compliance with the dimension of the natural power of 2
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

	//if need to expand a matrix
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

	//if not optimal size of matrix
	if (N > shNS::optimalN)
	{
		//size of half part matrix
		unsigned int halfN = N / 2;

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

		if (useSIMD)
		{
			//p1 = (A_11 + A_22) * (B_11 + B_22)
			shNS::_additionMatrix(halfN, A, A, temp1, xA, yA, xA + halfN, yA + halfN);
			shNS::_additionMatrix(halfN, B, B, temp2, xB, yB, xB + halfN, yB + halfN);
			shtrassen(halfN, temp1, temp2, p1);
			//p2 = (A_21 + A_22) * B_11
			shNS::_additionMatrix(halfN, A, A, temp1, xA, yA + halfN, xA + halfN, yA + halfN);
			shtrassen(halfN, temp1, B, p2, true, 0, 0, xB, yB);
			//p3 = A_11 * (B_12 - B_22)
			shNS::_subtractionMatrix(halfN, B, B, temp1, xB + halfN, yB, xB + halfN, yB + halfN);
			shtrassen(halfN, A, temp1, p3, true, xA, yA);
			//p4 = A_22 * (B_21 - B_11)
			shNS::_subtractionMatrix(halfN, B, B, temp1, xB, yB + halfN, xB, yB);
			shtrassen(halfN, A, temp1, p4, true, xA + halfN, yA + halfN);
			//p5 = (A_11 + A_12) * B_22
			shNS::_additionMatrix(halfN, A, A, temp1, xA, yA, xA + halfN, yA);
			shtrassen(halfN, temp1, B, p5, true, 0, 0, xB + halfN, yB + halfN);
			//p6 = (A_21 - A_11) * (B_11 + B_12)
			shNS::_subtractionMatrix(halfN, A, A, temp1, xA, yA + halfN, xA, yA);
			shNS::_additionMatrix(halfN, B, B, temp2, xB, yB, xB + halfN, yB);
			shtrassen(halfN, temp1, temp2, p6);
			//p7 = (A_12 - A_22) * (B_21 + B_22)
			shNS::_subtractionMatrix(halfN, A, A, temp1, xA + halfN, yA, xA + halfN, yA + halfN);
			shNS::_additionMatrix(halfN, B, B, temp2, xB, yB + halfN, xB + halfN, yB + halfN);
			shtrassen(halfN, temp1, temp2, p7);

			//c11 = p1 + p4 - p5 + p7
			shNS::_additionMatrix(halfN, p1, p4, temp1);
			shNS::_subtractionMatrix(halfN, temp1, p5, temp2);
			shNS::_additionMatrix(halfN, temp2, p7, result, 0, 0, 0, 0, xR, yR);
			//c12 = p3 + p5
			shNS::_additionMatrix(halfN, p3, p5, result, 0, 0, 0, 0, xR + halfN, yR);
			//c21 = p2 + p4
			shNS::_additionMatrix(halfN, p2, p4, result, 0, 0, 0, 0, xR, yR + halfN);
			//c22 = p1 - p2
			shNS::_subtractionMatrix(halfN, p1, p2, temp1);
			shNS::_additionMatrix(halfN, temp1, p3, temp2);
			shNS::_additionMatrix(halfN, temp2, p6, result, 0, 0, 0, 0, xR + halfN, yR + halfN);
		}
		else
		{
			//p1 = (A_11 + A_22) * (B_11 + B_22)
			shNS::additionMatrix(halfN, A, A, temp1, xA, yA, xA + halfN, yA + halfN);
			shNS::additionMatrix(halfN, B, B, temp2, xB, yB, xB + halfN, yB + halfN);
			shtrassen(halfN, temp1, temp2, p1, false);
			//p2 = (A_21 + A_22) * B_11
			shNS::additionMatrix(halfN, A, A, temp1, xA, yA + halfN, xA + halfN, yA + halfN);
			shtrassen(halfN, temp1, B, p2, false, 0, 0, xB, yB);
			//p3 = A_11 * (B_12 - B_22)
			shNS::subtractionMatrix(halfN, B, B, temp1, xB + halfN, yB, xB + halfN, yB + halfN);
			shtrassen(halfN, A, temp1, p3, false, xA, yA);
			//p4 = A_22 * (B_21 - B_11)
			shNS::subtractionMatrix(halfN, B, B, temp1, xB, yB + halfN, xB, yB);
			shtrassen(halfN, A, temp1, p4, false, xA + halfN, yA + halfN);
			//p5 = (A_11 + A_12) * B_22
			shNS::additionMatrix(halfN, A, A, temp1, xA, yA, xA + halfN, yA);
			shtrassen(halfN, temp1, B, p5, false, 0, 0, xB + halfN, yB + halfN);
			//p6 = (A_21 - A_11) * (B_11 + B_12)
			shNS::subtractionMatrix(halfN, A, A, temp1, xA, yA + halfN, xA, yA);
			shNS::additionMatrix(halfN, B, B, temp2, xB, yB, xB + halfN, yB);
			shtrassen(halfN, temp1, temp2, p6, false);
			//p7 = (A_12 - A_22) * (B_21 + B_22)
			shNS::subtractionMatrix(halfN, A, A, temp1, xA + halfN, yA, xA + halfN, yA + halfN);
			shNS::additionMatrix(halfN, B, B, temp2, xB, yB + halfN, xB + halfN, yB + halfN);
			shtrassen(halfN, temp1, temp2, p7, false);

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
		}

		//memory cleaning
		delete[] p1;
		delete[] p2;
		delete[] p3;
		delete[] p4;
		delete[] p5;
		delete[] p6;
		delete[] p7;
		delete[] temp1;
		delete[] temp2;
	}
	else if (useSIMD)
	{
		shNS::_calculateMatrix(N, A, B, result, xA, yA, xB, yB, xR, yR);
	}
	else
	{
		shNS::calculateMatrix(N, A, B, result, xA, yA, xB, yB, xR, yR);
	}
}