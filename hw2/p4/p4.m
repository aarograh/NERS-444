close all, clear all, clc;
format long;

N = 1e6;
Ex = [0, 0, 0, 0, 0];
minn = 0;
maxn = 4;

for n = minn:maxn
  % Even n
  if (mod(n,2) == 0)
    for j = 1:N
      tau = sqrt(-log(rand()))*cos(2*pi*rand());
      x = 1;
      for k = 1:(n/2)
        x = x*rand();
      end
      x = sqrt(-log(x) + tau*tau);
      Ex(n+1) = Ex(n+1) + x;
    end
  % Odd n
  else
    for j = 1:N
      x = 1;
      for k = 1:((n+1)/2)
        x = x*rand();
      end
      x = sqrt(-log(x));
      Ex(n+1) = Ex(n+1) + x;
    end
  end
end

Ex = Ex/N
