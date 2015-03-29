close all, clear all, clc;
format long;

z = [2, 1, 0.25, 0];
for t=z
  n = 1e7;
  mu_c = 1/3;
  score = 0;
  cutscore = 0;
  
  for i=1:n
    mu = rand();
    ptrans = exp(-t/mu);
    if (rand() < ptrans)
      score = score + 1/mu;
      if (mu < mu_c)
        cutscore = cutscore + 2/mu_c;
      else
        cutscore = cutscore + 1/mu;
      end
    end
  end
  
  sprintf('Normal mean: %2.12g     Cut-off mean: %1.12g',score/n,cutscore/n)
end
