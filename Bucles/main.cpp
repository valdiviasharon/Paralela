#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

const int MAX = 100;
void random(int n, vector<double> & A )
{
  for(int i=0; i<A.size(); i++)
    A[i]=(rand()%n)+1;
}
void print(vector<double> A)
{
  for(int i=0; i<A.size(); i++)
    cout<<A[i]<<" ";
  cout<<endl;
}
void print2(vector<vector<double>> A)
{
  for(int i=0; i<A.size(); i++)
    print(A[i]);
}

vector<double> x(MAX);
vector<double> y(MAX,0);
vector<vector<double>> A(MAX,vector<double>(MAX));

int main() 
{
  srand(time(NULL));

  //Inicialización
  random(MAX,x);
  for(int i=0; i<MAX; i++)
  {
    random(MAX,A[i]);
  }

  //print(x);
  //print(y);
  //cout<<endl;
  //print2(A);
  
  unsigned t0, t1;
  t0=clock();
  
  for(int i=0; i<MAX; i++)
  {
    for(int j=0; j<MAX; j++)
      y[i]+= A[i][j] * x[j];
  }
  t1 = clock();
   
  double time = (double(t1-t0)/CLOCKS_PER_SEC);
  cout << "Execution Time of 1" << " :"<< time << endl;

  //print(y);

  y = vector<double> (MAX,0);
  
  unsigned t2, t3;
  t2=clock();
  
  for(int j=0; j<MAX; j++)
  {
    for(int i=0; i<MAX; i++)
      y[i]+= A[i][j] * x[j];
  }
  t3 = clock();
   
  double time1 = (double(t3-t2)/CLOCKS_PER_SEC);
  cout << "Execution Time of 2" << " :"<< time1 << endl;

  //print(y);
}


