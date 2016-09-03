% first zero-sum game example
% payoff matrix
% 4 1 8
% 2 3 1
% 0 4 3
% player's optimal strategy
% I's  (.25,.75,0)
% II's (.5,.5,0)
% Nash equilibrium value 5/2

% second zero-sum game example
% payoff matrix
% 2 3 1 5
% 4 1 6 0
% player's optimal strategy
% I's  (.7143,.2857)
% II's (0,.7143,.2857,0)
% Nash equilibrium value 2.42857

clear;
%addpath('./gurobi/');
%ZeroSumGame.solveGame([1 2;3 4]);
payoff_mat = [4 1 8;2 3 1;0 4 3];
%payoff_mat = [2 3 1 5;4 1 6 0];
%[pI,max_gain]=ZeroSumGame.maximizePayoff(payoff_mat,false);
%[pII,min_loss]=ZeroSumGame.minimizePayoff(payoff_mat,false);
[playerI_policy,playerII_policy,game_value] = ZeroSumGame.solveGame(payoff_mat,false);
disp('playerI_policy:');
disp(playerI_policy);
disp('playerII_policy:');
disp(playerII_policy);
disp(['game_value: ' num2str(game_value)]);