% NAME       : Aaron Graham
% COURSE     : NERS 544
% ASSIGNMENT : Homework 1
% PROBLEM    : Problem 5
% DATE       : February 1, 2015

%% Part A

xstt = -1; xstp = 1;
ystt = -1; ystp = 1;
zstt = 0; zstp = 3.4;

Niters = 1e6;
Naccepted = 0;

for i=1:Niters
  x = rand()*(xstp - xstt) + xstt;
  y = rand()*(ystp - ystt) + ystt;
  z = rand()*(zstp - zstt) + zstt;
  if (z <= y^3 - y*x^2 - x + 2)
    Naccepted = Naccepted + 1;
  end
end

volume = (xstp - xstt)*(ystp - ystt)*(zstp - zstt)*Naccepted/Niters
