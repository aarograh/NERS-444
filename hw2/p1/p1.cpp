// NAME       : Aaron Graham
// COURSE     : NERS 544
// ASSIGNMENT : Homework 2
// PROBLEM    : Problem 1
// DATE       : February 23, 2015

#define PI 3.14159265358979323
#define SIGMA 0.35
#define C 1.05078216355812
//#define NORM 1.029149923805585
//#define NORMX2 0.1211987601379424

#include<iostream>
#include<cstdlib>
#include<time.h>
#include<cmath>

using namespace std;

double normRand(void)
{
  return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
}

double sample(void)
{
  return SIGMA*sqrt(-2.0*log(normRand()))*cos(2.0*PI*normRand());
}

double g(double x)
{
  return exp(-(x*x)/(2.0*SIGMA*SIGMA))/(SIGMA*sqrt(2.0*PI));
}

double f(double x)
{
  double tmp = cos(PI*x/2.0);
  return (3.0*PI/8.0)*tmp*tmp*tmp;
}

int main()
{
  srand(time(NULL));

  double x, y, test, bound, Ex2 = 0.0;
  int N = 1e6, i;
  bool picking = false;

  for (i = 0; i < N; i++)
  {
    picking = true;
    while (picking)
    {
      x = sample();
      y = f(x);
      bound = g(x);
      test = normRand()*C*bound;
      if (test <= y) picking = false;
    }
    Ex2 += x*x;
  }

  Ex2 /= static_cast<double>(N);

  cout << "After " << N << " iterations, E[X^2]=" << Ex2 << "." << endl;

  return 0;

}
