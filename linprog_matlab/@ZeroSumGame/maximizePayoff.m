function [playerI_policy,maximum_gain] = maximizePayoff(payoff_mat,check_nonnegative)
if(check_nonnegative == true)
    min_value_payoff_mat = min(min(payoff_mat));
    if(min_value_payoff_mat<=0)
        msg_ID = 'ZEROSUMGAME:nonetative';
        msg = 'all elements of payoff_mat should be nonnegative';
        zerosumException = MException(msg_ID,msg);
        throw(zerosumException);
    end
end

m = size(payoff_mat,1);
n = size(payoff_mat,2);

options = optimoptions('linprog','Display','off');% no print information
f = ones(m,1);
A = -payoff_mat';
b = -ones(n,1);
lb = zeros(m,1);
x = linprog(f,A,b,[],[],lb,[],[],options);
maximum_gain = 1/sum(x);
playerI_policy = x*maximum_gain;
%display(maximum_gain);
%display(playerI_policy);
