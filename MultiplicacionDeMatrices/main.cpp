#include <iostream>
#include <time.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

int size_m = 1000;
int bloque_size = 10;

void random(int n, vector<vector<int>>& A)
{
	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < A.size(); j++)
			A[i][j] = (rand() % n) + 1;
	}
		
}
void print(vector<vector<int>> A)
{
	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < A.size(); j++)
			cout << A[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}


int min(int A, int B)
{
	if (A < B)
		return A;
	return B;
}


void multi(vector<vector<int>> A, vector<vector<int>> B, vector<vector<int>> &C)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A.size(); j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < A[i].size(); k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}
void multi_bloques(vector<vector<int>> A, vector<vector<int>> B, vector<vector<int>>& C, int blockSize)
{

	for (int i = 0; i < A.size(); i += blockSize) 
	{
		for (int j = 0; j < C.size(); j += blockSize)
		{
			C[i][j] = 0;
			for (int k = 0; k < B.size(); k += blockSize) 
			{
				for (int ii = i; ii < min(i + blockSize, A.size()); ii++) 
				{
					for (int jj = j; jj < min(j + blockSize, C.size()); jj++) 
					{
						for (int kk = k; kk < min(k + blockSize, B.size()); kk++) 
							C[ii][jj] += A[ii][kk] * B[kk][jj];
					}
				}
			}
		}
	}
}


int main()
{
	vector<vector<int>> A(size_m, vector<int>(size_m));
	vector<vector<int>> B(size_m, vector<int>(size_m));
	vector<vector<int>> C1(size_m, vector<int>(size_m));
	vector<vector<int>> C2(size_m, vector<int>(size_m));

	//Inicialización
	srand(time(NULL));
	random(size_m, A);
	random(size_m, B);

	//Print
	/*
	cout << "Matriz A: " << endl;
	print(A);
	cout << "Matriz B: " << endl;
	print(B);
	*/

	//Resultado
	//Multi normal
	unsigned t0, t1;
	t0 = clock();

	multi(A, B, C1);

	t1 = clock();

	//cout << "Multiplicación clásica " << endl;
	//cout << "Matriz C: " << endl;
	//print(C1);

	double time = (double(t1 - t0) / CLOCKS_PER_SEC);
	cout << "Execution Time of 1" << " :" << time << endl;

	//Multi por bloques

	unsigned t2, t3;
	t2 = clock();

	multi_bloques(A, B, C2,bloque_size);

	t3 = clock();
	
	//cout << "Multiplicación por bloques " << endl;
	//cout << "Matriz C: " << endl;
	//print(C2);

	double time1 = (double(t3 - t2) / CLOCKS_PER_SEC);
	cout << "Execution Time of 2" << " :" << time1 << endl;
}
