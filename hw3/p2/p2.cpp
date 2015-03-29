// NAME       : Aaron Graham
// COURSE     : NERS 544
// ASSIGNMENT : Homework 3
// PROBLEM    : Problem 2
// DATE       : March 30, 2015

#include<iostream>
#include<cstdlib>
#include<time.h>
#include<cmath>

using namespace std;

double normRand(void)
{
  return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
}

int main()
{
  srand(time(NULL));

  int nSamples = 0;
  cout << "Please enter the number of samples:";
  cin >> nSamples;

  const double R[6][5] = {{-0.016,   0.05,   0.05,  0.05,  0.5},
                          { 0.002, -0.064,    0.0,   0.0,  0.0},
                          { 0.004,    0.0, -0.062,   0.0,  0.0},
                          {   0.0,  0.004,  0.002, -0.06,  0.0},
                          {  0.01,   0.01,   0.01,   0.0, -0.5},
                          {   0.0,    0.0,    0.0,  0.01,  0.0}};
  bool working = false;
  int state = 0;
  double nextEvent = 0.0;
  double stateType = 0.0;
  double tmp = 0.0;
  double average = 0.0;

  for (int i = 0; i < nSamples; i++)
  {
    working = true;
    state = 0;
    while (working)
    {
      nextEvent = log(-R[state][state]*normRand())/R[state][state];
      average += nextEvent;
      stateType = -R[state][state]*normRand();
      tmp = 0.0;
      for (int j = 0; j < 6; j++)
      {
        if (j == state) continue;
        tmp += R[j][state];
        if (stateType <= tmp)
        {
          state = j;
          break;
        } // Condition to set even
      }
      if (state == 5) working = false;
    }
  }

  average /= static_cast<double>(nSamples);

  cout << "Average time to failure is " << average << " days." << endl;

  return 0;
}
