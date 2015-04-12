// NAME       : Aaron Graham
// COURSE     : NERS 544
// ASSIGNMENT : Homework 4
// PROBLEM    : Problem 3
// DATE       : April 23, 2015

#define PI    3.14159265358979323
#define X0    1.0
#define D     0.33333333333333333
#define KAPPA 0.5

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

// Sample the normal distribution
double sampleNormal(double mu, double sigma)
{
  return mu + sigma*sqrt(-2.0*log(drand()))*cos(2.0*PI*drand());
} // End sampleNormal

// Evaluate the reference solution
double analytic(double x, double t)
{
  return (1.0/sqrt(4.0*PI*D*t))*(exp(-(x-X0)*(x-X0)/(4.0*D*t)) + 
    exp(-(x+X0)*(x+X0)/(4.0*D*t))) - (KAPPA/D)*exp(KAPPA*
    (x+X0+KAPPA*t)/D)*erfc((x+X0+2*KAPPA*t)/sqrt(4.0*D*t));
} // End analytic

// Begin main program
int main(void)
{
  // Seed random number generator
  srand(time(NULL));

  // Declare variables
  const int nbins = 100, nSamples = 1e6;
  int nsteps = 0;
  const double xEnd = 5.0, tEnd = 5.0;
  double dt, sigma, prefl, position, weight, norm;
  double mean[nbins], meansq[nbins], uncertainty[nbins], reference[nbins];
  fill_n(mean, nbins, 0.0);
  fill_n(meansq, nbins, 0.0);

  // Read in delta t
  cout << "Input value for delta t = ";
  cin >> dt;

  // Perform some preliminary calculations
  sigma = sqrt(2.0*D*dt);
  prefl = 1.0 - KAPPA*sqrt(PI*dt/D);
  nsteps = ((int) (tEnd + 0.5*dt)/dt);

  // Perform simulation
  for (int i = 0; i < nSamples; i++)
  {
    if (i%(nSamples/10) == 0)
    {
      cout << "Simulating particles " << i << endl;
    }
    position = X0;
    weight = 1.0;
    for (int j = 0; j < nsteps; j++)
    {
      position += sampleNormal(0.0, sigma);
      if (position <= 0.0)
      {
        position = -position;
        weight *= prefl;
      }
    }
    if(position < xEnd)
    {
      mean[(int)(position*((double)nbins)/xEnd)] += weight;
      meansq[(int)(position*((double)nbins)/xEnd)] += weight*weight;
    }
  }

  for (int i = 0; i < nbins; i++)
  {
    position = static_cast<double>(i)/static_cast<double>(nbins)*xEnd+0.025;
    mean[i] /= static_cast<double>(nSamples);
    meansq[i] /= static_cast<double>(nSamples);
    uncertainty[i] = sqrt(meansq[i] - mean[i]*mean[i])/
      (mean[i]*sqrt((double)nSamples));
    reference[i] = analytic(position,tEnd);
    if (i == 0) norm = reference[0]/mean[0];
    mean[i] *= norm;
    cout << "x = " << position << " : Reference = " << reference[i] << 
      ",  Mean = " << mean[i] << ", Uncertainty = " << uncertainty[i] << endl;
  }

  return 0;
} // End main program
