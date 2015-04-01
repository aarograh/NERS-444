// NAME       : Aaron Graham
// COURSE     : NERS 544
// ASSIGNMENT : Homework 2
// PROBLEM    : Problem 4
// DATE       : April 1, 2015

#define PI 3.14159265358979323

#include<iostream>
#include<cstdlib>
#include<time.h>
#include<cmath>
#include<iomanip>

using namespace std;

double normRand(void)
{
  return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
}

int main(void)
{

  const int N=1e6;
  double Ex[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
  double tau, x;

  for (int n = 0; n < 5; n++)
  {
    // Even n
    if (n%2 == 0)
    {
      for (int i = 0; i < N; i++)
      {
        tau = sqrt(-log(normRand()))*cos(2.0*PI*normRand());
        x = 1.0;
        for (int k = 0; k < n/2; k++)
        {
          x *= normRand();
        }
        x = sqrt(-log(x) + tau*tau);
        Ex[n] += x;
      }
    }
    // Odd n
    else
    {
      for (int i = 0; i < N; i++)
      {
        x = 1.0;
        for (int k = 0; k < (n+1)/2; k++)
        {
          x *= normRand();
        }
        x = sqrt(-log(x));
        Ex[n] += x;
      }
    }
    Ex[n] /= N;
    cout << "For n=" << n << ", E[x]=" << setprecision(9) << Ex[n] << endl;
  }

  return 0;

}
