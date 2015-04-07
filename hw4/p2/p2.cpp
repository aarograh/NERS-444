// NAME       : Aaron Graham
// COURSE     : NERS 544
// ASSIGNMENT : Homework 4
// PROBLEM    : Problem 2
// DATE       : April 20, 2015

#define B2 0.079407543572005

#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<time.h>
#include<cmath>

using namespace std;

// Random number generator on [0,1]
double drand(void)
{
  return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
} // End drand()

// Calculates the Klein-Nishina cross-section
double sigma_KN(double C, double mu)
{
  double invC = 1.0/C;
  return B2*invC*invC*(C + invC - (1.0 - mu*mu));
} // End sigma_KN

// Main program
int main(void)
{
  // Seed random number generator
  srand(time(NULL));

  // Declare variables
  const int nSamples = 1e6;
  const double mec2 = 0.511;
  double E, alpha, C, mean, meansq, variance, uncertainty, test;
  double mu, sigma, AL, AR, pL, pR;

  // Get user options
  cout << "Neutron energy in MeV: E=";
  cin >> E;

  // Calculate alpha and decomposition ares
  alpha = E/mec2;
  // A = 1/2 * b * h = 1/2 * 2 * sigma_KN = sigma_KN
  AL = sigma_KN(1.0 + alpha*2.0, -1.0);
  AR = sigma_KN(1.0, 1.0);
  pL = AL/(AL + AR);
  pR = 1.0 - pL;

  for (int i = 0; i < nSamples; i++)
  {
    sigma = 5.0;
    test = 0.0;
    while (sigma > test)
    {
      // Get mu,sigma from trapezoid
      if (drand() < pL)
      {
        mu = 1.0 - 2.0*sqrt(drand());
      }
      else
      {
        mu = 2.0*sqrt(drand()) - 1.0;
      }
      sigma = drand()*(pL*AL*(1.0-mu) + pR*AR*(mu+1.0));
      // evaluate KN distribution at mu
      C = 1.0 + alpha*(1.0 - mu);
      test = sigma_KN(C, mu);
    }
    mean += mu;
    meansq += mu*mu;
  }

  // Calculate statistical quantities
  mean /= nSamples;
  meansq /= nSamples;
  variance = meansq - mean*mean;
  uncertainty = sqrt(variance)/(mean*sqrt(static_cast<double>(nSamples)));

  // Program output
  //TODO: output efficiency, mean relative energy loss (with given omega)
  cout << "Mean        = " << setprecision(10) << mean << endl;
  cout << "Uncertainty = " << setprecision(10) << uncertainty << endl;

  return 0;
} // End main program
