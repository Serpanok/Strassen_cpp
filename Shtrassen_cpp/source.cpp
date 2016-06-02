#include "header.h"

namespace algCounters {
	int multiplication�_ = 0;
	int addition�_ = 0;
	int subtraction�_ = 0;
}

void algCounter(unsigned __int8 addition, unsigned __int8 subtraction, unsigned __int8 multiplication)
{
	algCounters::addition�_ += addition;
	algCounters::subtraction�_ += subtraction;
	algCounters::multiplication�_ += multiplication;
}

int main(int argc, char *argv[])
{
	try
	{
		setlocale(LC_ALL, "Russian");

		//ifstream in("input_test2.txt");
		ifstream in("input_test5.txt");
		//ofstream out("input_test6.txt");
		ofstream resOut("result_test5.txt");

		//genMatrix( out, 8 );
		//return 0;

		unsigned int N;
		shType** A;
		shType** B;
		shType** result;

		in >> N;

		A = new shType*[N];
		B = new shType*[N];
		result = new shType*[N];
		for (int i = 0; i < N; i++)
		{
			A[i] = new shType[N];
			B[i] = new shType[N];
			result[i] = new shType[N];
		}
		readMatrix(in, N, A);
		readMatrix(in, N, B);

		unsigned int start_time = clock(); // ��������� �����
		shtrassen(N, A, B, result);
		unsigned int end_time = clock(); // �������� �����
		unsigned int search_time = end_time - start_time; // ������� �����

														  //shtrassen(N, A, B, result);
														  //calculateMatrix(N, A, B, result);

		writeMatrix(resOut, N, result);

		cout << "Result:\n multiplication�: " << algCounters::multiplication�_ << "\n addition�: " << algCounters::addition�_ << "\n subtraction�: " << algCounters::subtraction�_ << "\n time: " << search_time << "\n\n";

		//cout << endl << endl;

		//writeMatrix( cout, N, A );
		//writeMatrix( cout, N, B );

		//writeMatrix(cout, N, result);

		system("Pause");
		return 1;
	}
	catch (...)
	{
		cerr << "error!";
		system("Pause");
		return 0;
	}
}