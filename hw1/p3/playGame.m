function [ turns, score, firstScore ] = playGame(  )
%playGame Plays one round of NERS-544/hw1/p3 dice game
%   This function takes turns repeatedly by rolling 2 dice.  As long as
%   the sum of the two dice is greater than or equal to the mean of the
%   previous rolls.  When the rolling is done, the total number of rolls
%   and the sum of all the rolls are returned.

turns = 1;
thisScore = roll() + roll();

score = thisScore;
firstScore = thisScore;
mean = thisScore;

while(thisScore >= mean)
  turns = turns + 1;
  thisScore = roll() + roll();
  score = score + thisScore;
  mean = ((turns-1)*mean + thisScore)/turns;
end

end

function [ result ] = roll(  )

result = floor(rand()*6) + 1;

end

