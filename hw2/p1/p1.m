close all, clear all, clc
format long;

sigma = 0.35;
c = 1.05078216355812;

N = 1e6;
Ex = 0;
Ex2 = 0;
samples = zeros(2,N);

for i=1:N
  picking = 1;
  while (picking)
%     if (rand() > 0.5)
%       x=sqrt(-2*sigma*sigma*log(rand()));
%     else
%       x=-sqrt(-2*sigma*sigma*log(rand()));
%     end
    x = sigma*sqrt(-2*log(rand()))*cos(2*pi*rand());
    tmp = cos(pi*x/2);
    y = (3*pi/8)*tmp*tmp*tmp;
    bound = exp(-x*x/(2*sigma*sigma))/(sigma*sqrt(2*pi));
    test = rand()*c*bound;
    if (test < y)
      picking = 0;
      samples(1,i) = x;
      samples(2,i) = y;
    end
  end
  Ex = Ex + x;
  Ex2 = Ex2 + x*x;
end

Ex = Ex/N
Ex2 = Ex2/N

scatter(samples(1,:),samples(2,:));
