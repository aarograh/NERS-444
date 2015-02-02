% NAME       : Aaron Graham
% COURSE     : NERS 544
% ASSIGNMENT : Homework 1
% PROBLEM    : Problem 4
% DATE       : February 1, 2015

%% Part B

Niters = 1e6;
H = 3;
results = zeros(Niters,1);

for i=1:Niters
  xi = rand();
  results(i,1) = asin(2*xi - 1)*H/pi;
end

results;
mean = sum(results)/Niters
variance = sum((results - mean).^2)/Niters
