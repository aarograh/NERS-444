clear all, close all, clc;
format long;

samples = [250, 1000, 4000, 16000, 64000];
R = [-0.016, 0.05, 0.05, 0.05, 0.5, 0.0;
  0.002, -0.064, 0.0, 0.0, 0.0, 0.0;
  0.004, 0.0, -0.062, 0.0, 0.0, 0.0;
  0.0, 0.004, 0.002, -0.06, 0.0, 0.0;
  0.01, 0.01, 0.01, 0.0, -0.5, 0.0;
  0.0, 0.0, 0.0, 0.01, 0.0, 0.0];
mean = zeros(1,length(samples));
meansq = mean;
variance = mean;
uncertainty = mean;

for N = 1:length(samples)
  for i=1:samples(N)
    state = 1;
    runtime = 0.0;
    while (state ~= 6)
      nexttime = log(rand())/R(state,state);
      runtime = runtime + nexttime;
      tmp = -R(state,state)*rand();
      prob = 0.0;
      for j=1:length(R(:,state))
        if (j ~= state)
          prob = prob + R(j,state);
          if (tmp <= prob)
            state = j;
            break;
          end
        end
      end
    end
    mean(N) = mean(N) + runtime;
    meansq(N) = meansq(N) + runtime*runtime;
  end
  mean(N) = mean(N)/samples(N);
  meansq(N) = meansq(N)/samples(N);
end

variance = meansq - mean.*mean;
mean
uncertainty = sqrt(variance./samples)./mean
