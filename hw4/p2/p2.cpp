// NAME       : Aaron Graham
// COURSE     : NERS 544
// ASSIGNMENT : Homework 4
// PROBLEM    : Problem 2
// DATE       : April 23, 2015

#define B2 0.079407543572005
#define PI 3.14159265358979323

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
double sigma_KN(double x, double mu)
{
  double invx = 1.0/x;
  return B2*invx*invx*(x + invx - (1.0 - mu*mu));
} // End sigma_KN

// Main program
int main(void)
{
  // Seed random number generator
  srand(time(NULL));

  // Declare variables
  int nSamples = 0;
  const int nAccepted = 1e6;
  const double mec2 = 0.511, oldOmega[3] = {0, 0, 1};
  double E, alpha, x, mean, meansq, variance, uncertainty, test;
  double gamma, mu, sigma, AL, AR, pL, pR, newE, deltaE;
  double efficiency, meanELoss = 0.0, meanELossSq = 0.0;
  double omega[3], Evariance, Euncertainty;

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

  for (int i = 0; i < nAccepted; i++)
  {
    sigma = 5.0;
    test = 0.0;
    while (sigma > test)
    {
      nSamples++;
      // Get mu,sigma from trapezoid
      if (drand() < pL)
      {
        mu = 1.0 - 2.0*sqrt(drand());
      }
      else
      {
        mu = 2.0*sqrt(drand()) - 1.0;
      }
      sigma = drand()*(AL*(1.0-mu) + AR*(mu+1.0))/2.0;
      // evaluate KN distribution at mu
      x = 1.0 + alpha*(1.0 - mu);
      test = sigma_KN(x, mu);
    }
    mean += mu;
    meansq += mu*mu;
    gamma = 2.0*PI*drand();
    omega[0] = mu*oldOmega[0] + (oldOmega[0]*oldOmega[2]*cos(gamma) -
      oldOmega[1]*sin(gamma))*sqrt((1.0 - mu*mu)/(1.0 - 
      oldOmega[2]*oldOmega[2]));
    omega[1] = mu*oldOmega[1] + (oldOmega[1]*oldOmega[2]*cos(gamma) +
      oldOmega[0]*sin(gamma))*sqrt((1.0 - mu*mu)/(1.0 - 
      oldOmega[2]*oldOmega[2]));
    omega[2] = mu*oldOmega[2] + cos(gamma)*sqrt((1.0 - mu*mu)*
      (1.0 - oldOmega[2]*oldOmega[2]));
//    newE = HC/E + (1.0 - mu)*H/mec2;
 //   newE = HC/newE;
    newE = mec2*E/(mec2 + (1.0 - mu)*E);
    deltaE = (E - newE)/E;
    meanELoss += deltaE;
    meanELossSq += deltaE*deltaE;
  }

  // Calculate statistical quantities
  mean /= nAccepted;
  meansq /= nAccepted;
  variance = meansq - mean*mean;
  uncertainty = sqrt(variance)/(mean*sqrt(static_cast<double>(nAccepted)));
  efficiency = static_cast<double>(nAccepted)/static_cast<double>(nSamples);
  meanELoss /= nAccepted;
  meanELossSq /= nAccepted;
  Evariance = meanELossSq - meanELoss*meanELoss;
  Euncertainty = sqrt(Evariance)/(
    meanELoss*sqrt(static_cast<double>(nAccepted)));

  // Program output
  cout << "Mean        = " << setprecision(10) << mean << endl;
  cout << "Uncertainty = " << setprecision(10) << uncertainty << endl;
  cout << "Efficiency  = " << setprecision(10) << efficiency << endl;
  cout << "Mean Energy Loss = " << setprecision(10) << 
    meanELoss << endl;
  cout << "Energy Loss Uncertainty = " << setprecision(10) << 
    Euncertainty << endl;

  return 0;
} // End main program
