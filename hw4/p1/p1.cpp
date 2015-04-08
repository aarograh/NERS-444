// NAME       : Aaron Graham
// COURSE     : NERS 544
// ASSIGNMENT : Homework 4
// PROBLEM    : Problem 1
// DATE       : April 20, 2015

#define PI 3.14159265358979323

#include<iostream>
#include<cstdlib>
#include<time.h>
#include<iomanip>
#include<cmath>
#include<float.h>

using namespace std;

bool implicitCapture = false;
bool weightRoulette = false;
double M = 1.0;
double invM = 1.0;
const double thickness = 51.0;
const int nCells = static_cast<int>(thickness);
const double halfthickness = thickness/2.0;
const double c = 0.6;
const double eps = 100.0*DBL_EPSILON;
double importances[51];

// Random number generator on [0,1]
double drand(void)
{
  return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
} // End drand()

// Define a particle class
class particle {
  public:
    // Public methods:
    particle(double, double, double);
    double simulate();
    // Other public attributes
    int nTracks;
  private:
    // Private methods
    double transport();
    double split();
    void roulette();
    void weight_roulette();
    void scatter();
    // Other private attributes
    bool isAlive;
    double x, omegaZ, weight;
}; // End class particle

// Particle is always initialized in center of problem with weight
// 1.0 and a random, isotropic mu.
particle::particle (double x_in, double omegaZ_in, double weight_in)
{
  x = x_in;
  omegaZ = omegaZ_in;
  weight = weight_in;
  nTracks = 1;
  isAlive = true;
} // End particle::particle

// Simulates the entire life of a particle
double particle::simulate ()
{
  double result = 0.0;
  // Loop over the particle's life
  while (isAlive)
  {
    // Simulate a single track of the particle's life
    result = transport();
    // Perform weight rouletting if requested by user
    if (weightRoulette) 
    {
      weight_roulette();
    }
  }
  return result;
} // End particle::simulate

// Transport the particle.
//   Determines which is closer: the next surface or next collision.
//     If surface, it moves the particle to that surface, modifies
//       its weight, and returns.
//     If collision, it either kills the particle or picks a new
//       direction.
double particle::transport ()
{
  nTracks++; // Increment the number of tracks for this particle
  double result = 0.0;
  // Get distances
  double d2surf = x - ((long)x);
  if(omegaZ > 0.0) d2surf = 1.0 - d2surf;
  double d2coll = -abs(omegaZ)*log(drand());

  // Particle makes it to next cell
  if (d2surf < d2coll)
  {
    // Moving left
    if (omegaZ < 0)
    {
      x = ((double)((long)x)) - eps;
      // Particle escapes the left side of the slab
      if ((long)x == 0)
      {
        isAlive = false;
      }
      // Particle is still in the slab
      else
      {
        roulette();
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
        result = weight;
      }
      // Particle is still in slab
      else
      {
        result = split();
      }
    }
  }
  // Collision occurs within current cell
  else
  {
    x += ((omegaZ > 0.0) - (omegaZ < 0.0))*d2coll;
    // Implicit capture is turned on
    if (implicitCapture)
    {
      scatter();
      weight = weight*c;
    }
    else
    {
      // Particle scatters
      if (drand() < c)
      {
        scatter();
      }
      // Particle is absorbed
      else
      {
        isAlive = false;
      }
    }
  }

  return result;
}  // End particle::transport

//Performs isotropic lab-frame scattering
void particle::scatter()
{
  double gamma = drand()*PI; //Gamma
  double mu = drand()*2.0 - 1.0; //mu
  omegaZ = mu*omegaZ + cos(gamma)*sqrt((1.0 - mu*mu)*(1.0-omegaZ*omegaZ));
} // End particle::scatter

// Performs rouletting based on cell importances
void particle::roulette ()
{
  if (drand() > invM)
  {
    isAlive = false;
    weight = 0.0;
  }
  else
  {
    weight *= M;
  }
} // End particle::roulette

// Performs splitting based on cell importances
double particle::split ()
{
  isAlive = false;
  double result = 0.0;
  int nSplits = floor(M + drand());
  double splitWeight = weight/((double)nSplits);
  for (int i = 0; i < nSplits; i++)
  {
    particle subPart(x,omegaZ,splitWeight);
    result += subPart.simulate();
    nTracks += subPart.nTracks;
  }
  return result; 
} // End particle::split

// Performs weight rouletting
void particle::weight_roulette ()
{ 
  if (weight < 0.1/importances[(int) x])
  {
    double weight_survive = 0.4/importances[(int) x];
    double prob_survive = weight/weight_survive;
    // Particle survives
    if (drand() < prob_survive)
    {
      weight = weight_survive;
    }
    else
    {
      isAlive = false;
      weight = 0.0;
    }
  }
} // End particle::weight_roulette

int main()
{
  // Seed Random Number Generator
  srand(time(NULL));

  // Declare variables
  int nSamples = 0;
  long nTracks = 0;
  double result = 0.0;
  double mean = 0.0;
  double meansq = 0.0;
  double variance = 0.0;
  double FOM = 0.0;

  // Read in input values
  cout << "Set number of samples: N=";
  cin >> nSamples;
  cout << "Set a value: M=";
  cin >> M;
  invM = 1.0/M;
  cout << "Use implicit capture (1 == on, 0 == off)? ";
  cin >> implicitCapture;
  cout << "Use weight rouletting (1 == on, 0 == off)? ";
  cin >> weightRoulette;

  // Setup array of cell importances
  importances[nCells/2] = 1.0;
  for (int i = nCells/2 + 1; i < nCells; i++)
  {
    importances[i] = importances[i-1]*M;
  }
  for (int i = nCells/2 - 1; i >= 0; i--)
  {
    importances[i] = importances[i+1]*invM;
  }

  // Sample neutrons
  for (int i = 0; i < nSamples; i++)
  {
    if (i%(nSamples/1000) == 0)
    {
      cout << "Simulating particle " << i << endl;
    }
    particle part(halfthickness,2.0*drand()-1.0,1.0);
    result = part.simulate();
    // Accumulate results
    mean += result;
    meansq += result*result;
    nTracks += part.nTracks;
  }

  // Calculate mean, variance, and figure of merit
  mean /= nSamples;
  meansq /= nSamples;
  variance = meansq - mean*mean;
  FOM  = sqrt(variance)/(mean*nSamples);
  FOM = 1.0/(FOM*FOM*nTracks);

  cout << "Mean = " << setprecision(10) << mean << endl;
  cout << "Mean^2 = " << setprecision(10) << meansq << endl;
  cout << "Number of tracks = " << nTracks << endl;
  cout << "Variance = " << setprecision(10) << variance << endl;
  cout << "Relative Uncertainty = " << setprecision(10) <<
    sqrt(variance)/(mean*sqrt(static_cast<double>(nSamples))) << endl;
  cout << "FOM = " << setprecision(10) << FOM << endl;

  return 0;
} // End main
