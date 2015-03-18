// NAME       : Aaron Graham
// COURSE     : NERS 544
// ASSIGNMENT : Homework 2
// PROBLEM    : Problem 1
// DATE       : February 23, 2015

#define PI 3.14159265358979323
#define SIGMA 0.35
#define C 1.033568152688034
#define NORM 1.029149923805585
#define NORMX2 0.1211987601379424

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
  if (normRand() > 0.5)
  {
    return sqrt(-2.0*pow(0.35,2.0)*log(0.35*sqrt(2.0*PI)*normRand()));
  }
  else
  {
    return -sqrt(-2.0*pow(0.35,2.0)*log(0.35*sqrt(2.0*PI)*normRand()));
  }
}

double boundEval(double x)
{
  return exp(-(pow(x,2.0))/(2.0*(pow(SIGMA,2.0))))/(SIGMA*sqrt(2.0*PI));
}

double funcEval(double x)
{
  return pow(cos(PI*x/2.0),3.0);
}

int main()
{
  srand(time(NULL));

  double x, y, test, bound, Ex2 = 0.0;
  int N = 1e6, count = 0, i;

  for (i = 0; i < N; i++)
  {
    x = sample();
    y = funcEval(x);
    bound = boundEval(x);
    test = normRand()*C*bound;
    if (test <= y)
    {
      Ex2 += x*x;
      count++;
    }
//cout << test << "  " << y << "  " << bound << "  " << "  " << x << "  " << Ex2 << endl;
  }

  Ex2 = NORMX2*static_cast<double>(count)/static_cast<double>(N);
//  Ex2 /= static_cast<double>(count);

  cout << "After " << N << " iterations, " << count << " values were accepted "
    << "and give an estimate of E[X^2]=" << Ex2 << "." << endl;

  return 0;

}
