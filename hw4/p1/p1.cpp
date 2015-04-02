// NAME       : Aaron Graham
// COURSE     : NERS 544
// ASSIGNMENT : Homework 4
// PROBLEM    : Problem 1
// DATE       : April 20, 2015

#include<iostream>
#include<cstdlib>
#include<time.h>
#include<iomanip>
#include<cmath>
#include<float.h>

using namespace std;

double M = 1.0;
double invM = 1.0;
const double thickness = 3.0;
const double halfthickness = thickness/2.0;
const double c = 0.6;
const double eps = 100.0*DBL_EPSILON;

// Random number generator on [0,1]
double normRand(void)
{
  return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
}

// Define a particle class
class particle {
  public:
    particle(double, double, double);
    double simulate();
    double transport();
    double split();
    double roulette();
    double x, mu, weight;
    bool isAlive;
};

// Particle is always initialized in center of problem with weight
// 1.0 and a random, isotropic mu.
particle::particle (double x_in, double mu_in, double weight_in)
{
  x = x_in;
  mu = mu_in;
  weight = weight_in;
  isAlive = true;
}

// Simulates the entire life of a particle
double particle::simulate ()
{
//cout << endl << "New Particle" << endl;
  double result = 0.0;
//cout << x << " " << mu << endl;
  while (isAlive)
  {
    result = transport();
//cout << setprecision(19) << x << " " << mu << endl;
  }
  return result;
}

// Transport the particle.
//   Determines which is closer: the next surface or next collision.
//     If surface, it moves the particle to that surface, modifies
//       its weight, and returns.
//     If collision, it either kills the particle or picks a new
//       direction.
double particle::transport ()
{
  // Get distances
  double d2surf = x - ((long)x);;
  if(mu > 0.0) d2surf = 1.0 - d2surf;
  double d2coll = -abs(mu)*log(normRand()) ;

  // Particle makes it to next cell
//cout << d2surf << "            " << d2coll << endl;
  if (d2surf < d2coll)
  {
    // Moving left
    if (mu < 0)
    {
//cout << x << "  " << ((double)((long)x)) << " " << eps << endl;
      x = ((double)((long)x)) - eps;
      // Particle escapes the left side of the slab
      if ((long)x == 0)
      {
        isAlive = false;
cout << "Wrong side" << endl;
        return 0.0;
      }
      // Particle is still in the slab
      else
      {
        return roulette();
      }
    }
    // Moving right
    else
    {
      x = ((double)((long)(x+1.0))) + eps;
      // Particle escaped the slab
      if (x > thickness)
      {
        isAlive = false;
cout << "Particle Escaped!" << endl;
        return weight;
      }
      // Particle is still in slab
      else
      {
        return split();
      }
    }
  }
  // Collision occurs within current cell
  else
  {
    x += ((mu > 0.0) - (mu < 0.0))*d2coll;
    // Particle scatters
    if (normRand() < c)
    {
      mu = 2.0*normRand() - 1.0;
      return weight;
    }
    // Particle is absorbed
    else
    {
      isAlive = false;
      return 0.0;
    }
  }
}

double particle::roulette ()
{
  if (normRand() > invM)
  {
    isAlive = false;
    weight = 0.0;
  }
  else
  {
    weight *= M;
  }
  return weight;
}

double particle::split ()
{
  isAlive = false;
  double result = 0.0;
  int nSplits = floor(M + normRand());
  double splitWeight = weight/((double)nSplits);
cout << "splitting into " << nSplits << " particles with weight " << splitWeight << endl;
  for (int i = 0; i < nSplits; i++)
  {
    particle subPart(x,mu,splitWeight);
    result += subPart.simulate();
  }
cout << "splitting results: " << result << endl;
  return result; 
}

int main()
{
  srand(time(NULL));

  int nSamples = 0;
  int result = 0;
  double mean = 0.0;
  double meansq = 0.0;

  cout << "Set number of samples: N=";
  cin >> nSamples;
  cout << "Set a value: M=";
  cin >> M;
  invM = 1.0/M;

  for (int i = 0; i < nSamples; i++)
  {
    if (i%(nSamples/10) == 0)
    {
      cout << "Simulating particle " << i << endl;
    }
    particle part(halfthickness,2.0*normRand()-1.0,1.0);
    result = part.simulate();
    // Accumulate mean and squared mean
    mean += result;
    meansq += result*result;
  }

  mean /= nSamples;
  meansq /= nSamples;
  double variance = meansq - mean*mean;
  double FOM  = sqrt(variance)/(mean*nSamples);
  FOM = 1.0/(FOM*FOM*((double)sqrt(nSamples)));

  cout << "Mean = " << setprecision(10) << mean << endl;
  cout << "Mean^2 = " << setprecision(10) << meansq << endl;
  cout << "Variance = " << setprecision(10) << variance << endl;
  cout << "FOM = " << setprecision(10) << FOM << endl;

  return 0;
}
