classdef ZeroSumGame
    methods(Static)
        [playerI_policy,playerII_policy,game_value] = solveGame(payoff_mat,equilibrium,check_nonnegative)
        [playerI_policy,maximum_gain] = maximizePayoff(payoff_mat,check_nonnegative)
        [playerII_policy,minimum_loss] = minimizePayoff(payoff_mat,check_nonnegative)
    end
end