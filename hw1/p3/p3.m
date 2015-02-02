% NAME       : Aaron Graham
% COURSE     : NERS 544
% ASSIGNMENT : Homework 1
% PROBLEM    : Problem 3
% DATE       : February 1, 2015

%% Part B

NturnsGT2 = 0;
Nplays = 1e6;
totalScore = 0;
NscoreGT30 = 0;

parfor i=1:Nplays
  [turns, score, ~] = playGame();
  totalScore = totalScore + score
  if (turns > 2)
    NturnsGT2 = NturnsGT2 + 1;
  end
  if (score > 30)
    NscoreGT30 = NscoreGT30 + 1;
  end
end

pNturnsGT2 = NturnsGT2/Nplays

%% Part C

expectedScore = totalScore/Nplays

%% Part D

pScoreGT30 = NscoreGT30/Nplays

%% Part E

firstScore = zeros(11,2);

for i=1:Nplays
  [turns1, score1, first1] = playGame();
  [turns2, score2, first2] = playGame();
  if (score1 > score2)
    firstScore(first1-1,1) = firstScore(first1-1,1) + 1;
    firstScore(first2-1,2) = firstScore(first2-1,2) + 1;
  elseif (score2 > score1)
    firstScore(first2-1,1) = firstScore(first2-1,1) + 1;
    firstScore(first1-1,2) = firstScore(first1-1,2) + 1;
  end
end

pWinLoss = firstScore/Nplays
