function [playerI_policy, playerII_policy, game_value] = solveGame(payoff_mat,equilibrium_threshold,...
    check_nonnegative)

[playerI_policy,maximum_gain] = ZeroSumGame.maximizePayoff(payoff_mat,check_nonnegative);
[playerII_policy,minimum_loss] = ZeroSumGame.minimizePayoff(payoff_mat,check_nonnegative);

gain_loss_diff = abs(maximum_gain-minimum_loss);
diff_portion = gain_loss_diff/max(abs(maximum_gain),abs(minimum_loss));

if(diff_portion < equilibrium_threshold)
    game_value = (maximum_gain+minimum_loss)/2;
else
    disp(['maximum_gain:' num2str(maximum_gain)]);
    disp(['minimum_loss;' num2str(minimum_loss)]);
    msg_ID = 'ZEROSUMGAME:match';
    msg = ['The different between gain and loss takes more that ' equilibrium_threshold ' percent:'];
    zerosumException = MException(msg_ID,msg);
    throw(zerosumException);
end