#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

int size_m = 500;
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


void multi(vector<vector<int>> A, vector<vector<int>> B, vector<vector<int>>& C)
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


int main()
{
	vector<vector<int>> A(size_m, vector<int>(size_m));
	vector<vector<int>> B(size_m, vector<int>(size_m));
	vector<vector<int>> C1(size_m, vector<int>(size_m));

	//Inicializaci�n
	srand(time(NULL));
	random(size_m, A);
	random(size_m, B);
	
	//Multi normal
	unsigned t0, t1;
	t0 = clock();

	multi(A, B, C1);

	t1 = clock();

	double time = (double(t1 - t0) / CLOCKS_PER_SEC);
	cout << "Execution Time of 1" << " :" << time << endl;

}
