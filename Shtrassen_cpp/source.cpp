#include "header.h"

namespace algCounters {
	int multiplication—_ = 0;
	int addition—_ = 0;
	int subtraction—_ = 0;
}

void algCounter(unsigned __int8 addition, unsigned __int8 subtraction, unsigned __int8 multiplication)
{
	algCounters::addition—_ += addition;
	algCounters::subtraction—_ += subtraction;
	algCounters::multiplication—_ += multiplication;
}

int main(int argc, char *argv[])
{
	try
	{
		setlocale(LC_ALL, "Russian");

		string command;
		bool alreadyHaveCommand = false;
		char answer;
		unsigned int start_time;

		ifstream in;
		ofstream out;

		unsigned int N;
		shType** A = NULL;
		shType** B = NULL;
		shType** result = NULL;

		while (true)
		{
			if (!alreadyHaveCommand)
			{
				std::cout << "write command> ";
				std::cin >> command;
			}
			else
			{
				alreadyHaveCommand = false;
			}

			//commands
			if (command == "-exit" || command == "-e")
			{
				break;
			}
			else if (command == "-help" || command == "-h")
			{
				std::cout	<< "Commmands list:\n"
							<< " -help, -h\t\thelp\n"
							<< " -openIn, -oI\t\topen file for input and read data\n"
							<< " -openOut, -oO\t\topen file for out\n"
							<< " -closeIn, -cI\t\tclose file for input\n"
							<< " -closeOut, -cO\t\tclose file for out\n"
							<< " -generate, -g\t\tgenerate data to opened file\n"
							<< " -readIn, -rI\t\tread data from opened file\n"
							<< " -writeOut, -wO\t\twrite result to file\n"
							<< " -shtrassen, -s\t\trun shtrassen algorithm\n"
							<< "\nFor debugging:\n"
							<< " -test, -t\t\trun test\n";
			}
			else if (command == "-openIn" || command == "-oI")
			{
				std::cout << "Enter file name: ";

				string fileName;
				std::cin >> fileName;

				out.close();
				in.open(fileName);

				std::cout << "File opened successfully! Do you want to read data from it? (y/n)\n";
				std::cin >> answer;
				if (answer == 'y')
				{
					command = "-readIn";
					alreadyHaveCommand = true;
				}
			}
			else if (command == "-openOut" || command == "-oO")
			{
				std::cout << "Enter file name: ";

				string fileName;
				std::cin >> fileName;

				out.close();
				out.open(fileName);

				std::cout << "File opened successfully!\n";
			}
			else if (command == "-closeIn" || command == "-cI")
			{
				in.close();
				std::cout << "File closed successfully!\n";
			}
			else if (command == "-closeOut" || command == "-cO")
			{
				out.close();
				std::cout << "File closed successfully!\n";
			}
			else if (command == "-generate" || command == "-g")
			{
				if (!out.is_open())
				{
					std::cout << "File not opened! Do you want to open file now? (y/n)\n";
					std::cin >> answer;
					if (answer == 'y')
					{
						command = "-openOut";
						alreadyHaveCommand = true;
					}
					continue;
				}

				unsigned int size;
				int min, max;

				std::cout << "Enter matrices size: ";
				std::cin >> size;
				std::cout << "Enter min/max values: ";
				std::cin >> min >> max;

				start_time = clock(); //set timer

				genMatrix(out, size, min, max);

				std::cout << "Generat successfully in " << (clock() - start_time) << "ms!\n";
			}
			else if (command == "-readIn" || command == "-rI")
			{
				if (!in.is_open())
				{
					std::cout << "File not opened! Do you want to open file now? (y/n)\n";
					std::cin >> answer;
					if (answer == 'y')
					{
						command = "-openIn";
						alreadyHaveCommand = true;
					}
					continue;
				}

				start_time = clock(); //set timer

				in >> N;

				A = new shType*[N];
				B = new shType*[N];
				for (int i = 0; i < N; i++)
				{
					A[i] = new shType[N];
					B[i] = new shType[N];
				}

				readMatrix(in, N, A);
				readMatrix(in, N, B);

				std::cout << "Read successfully in " << (clock() - start_time) << "ms!\n";
			}
			else if (command == "-writeOut" || command == "-wO")
			{
				if (result == NULL)
				{
					std::cout << "The algorithm has not worked! Do you want to run it now? (y/n)\n";
					std::cin >> answer;
					if (answer == 'y')
					{
						command = "-shtrassen";
						alreadyHaveCommand = true;
					}
					continue;
				}
				if (!out.is_open())
				{
					std::cout << "File not opened! Do you want to open file now? (y/n)\n";
					std::cin >> answer;
					if (answer == 'y')
					{
						command = "-openOut";
						alreadyHaveCommand = true;
					}
					continue;
				}

				start_time = clock(); //set timer

				writeMatrix(out, N, result);

				std::cout << "Write successfully in " << (clock() - start_time) << "ms!\n";
			}
			else if (command == "-shtrassen" || command == "-s")
			{
				if (A == NULL)
				{
					std::cout << "Algorithm did`n have input data! Do you want to read it from file now? (y/n)\n";
					std::cin >> answer;
					if (answer == 'y')
					{
						command = "-readIn";
						alreadyHaveCommand = true;
					}
					continue;
				}

				std::cout << "Use SIMD? (y/n)\n";
				std::cin >> answer;
				bool useSIMD = (answer == 'y');

				result = new shType*[N];
				for (int i = 0; i < N; i++)
				{
					result[i] = new shType[N];
				}

				start_time = clock(); //set timer
				shtrassen(N, A, B, result, useSIMD);

				std::cout	<< "\nResult:\n"
							<< " multiplication—: " << algCounters::multiplication—_ << "\n"
							<< " addition—: " << algCounters::addition—_ << "\n"
							<< " subtraction—: " << algCounters::subtraction—_ << "\n"
							<< " time: " << (clock() - start_time) << "ms\n\n";


				std::cout << "The algorithm successfully operated! Do you want to write result to file now? (y/n)\n";
				std::cin >> answer;
				if (answer == 'y')
				{
					command = "-writeOut";
					alreadyHaveCommand = true;
				}
			}
			else if (command == "-test" || command == "-t")
			{
				char testN[5];

				std::cout << "Enter test number: ";
				std::cin >> testN;

				std::cout << "Use SIMD? (y/n)\n";
				std::cin >> answer;
				bool useSIMD = (answer == 'y');

				string inputFile = "input_test";
				inputFile += testN;
				inputFile += ".txt";
				in.open(inputFile);
				string outFile = "output_test";
				outFile += testN;
				if (useSIMD)
				{
					outFile += "_SIMD";
				}
				outFile += ".txt";
				out.open(outFile);

				std::cout << "Files opened successfully!\n";

				/* reading */

				start_time = clock(); //set timer

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

				in.close();

				std::cout << "Read successfully in " << (clock() - start_time) << "ms!\n";

				/* shtrassen */

				start_time = clock(); //set timer

				shtrassen(N, A, B, result, useSIMD);

				std::cout << "\nResult:\n"
					<< " multiplication—: " << algCounters::multiplication—_ << "\n"
					<< " addition—: " << algCounters::addition—_ << "\n"
					<< " subtraction—: " << algCounters::subtraction—_ << "\n"
					<< " time: " << (clock() - start_time) << "ms\n\n";

				/* writing */

				start_time = clock(); //set timer

				writeMatrix(out, N, result);

				out.close();

				std::cout << "Write successfully in " << (clock() - start_time) << "ms!\n";

			}
			else
			{
				std::cout << "Wrong command! Use help(-h)\n";
			}
		}

		return 1;
	}
	catch (...)
	{
		cerr << "error!";
		system("Pause");
		return 0;
	}
}