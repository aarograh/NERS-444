close all, clear all, clc;
format long;

N = 10;
z = 8;
samples = 1e8;
probz2 = exp(-z/2);
probz = probz2*probz2;
tally(1:N) = 0;
sqtally(1:N) = 0;

for n=1:N
  score = 1/n;
  score2 = score*score;
  for i=1:samples
    if rand() < probz2
      tmp = 0;
      for j=1:n
        if rand() < probz2
          tally(n) = tally(n) + score;
          tmp = tmp + score;
        end
      end
      sqtally(n) = sqtally(n) + tmp*tmp;
    end
  end
end

mean = tally/samples;
mean2 = sqtally/samples;
var = mean2 - mean.*mean;
R = sqrt(var)./(mean*sqrt(samples));
FOM = 1./(R.*R);

display(sprintf('n       mean       variance      R        FOM
  analytic FOM'))
for n=1:N
  FOM(n) = FOM(n)/(samples*(n+1));
  analyticFOM = probz/((n+1)/n * (1 + (n-1)*probz2 - n*probz));
  display(sprintf('%3i  %1.6g  %1.6g  %1.6g  %1.6g  %1.6g',...
    n,mean(n),var(n),R(n),FOM(n),analyticFOM))
end
