function [playerII_policy,minimum_loss] = minimizePayoff(payoff_mat,check_nonnegative)

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
f = -ones(n,1);
A = payoff_mat;
b = ones(m,1);
lb = zeros(n,1);
x = linprog(f,A,b,[],[],lb,[],[],options);
minimum_loss = 1/sum(x);
playerII_policy = x*minimum_loss;
%display(minimum_loss);
%display(playerII_policy);