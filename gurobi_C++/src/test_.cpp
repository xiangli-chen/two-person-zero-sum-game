/* a zero-sum game example
 payoff matrix
 4 1 8
 2 3 1
 0 4 3
 player's optimal strategy
 I's  (.25,.75,0)
 II's (.5,.5,0)
 Nash equilibrium value 5/2
 
 Another zero-sum game example
 payoff matrix
 2 3 1 5
 4 1 6 0
 player's optimal strategy
 I's  (0.7143,0.2857)
 II's (0,0.7143,0.2857,0)
 Nash equilibrium value 2.42857
*/

#include <armadillo>
#include "zeroSumGame.h"

using namespace arma;
using namespace std;

int main()
{
//    Mat<double> payoffMat(3,3);
//    payoffMat << 4 << 1 << 8 << endr
//    << 2 << 3 << 1 << endr
//    << 0 << 4 << 3 << endr;
    
    Mat<double> payoffMat(2,4);
    payoffMat << 2 << 3 << 1 << 5 << endr
              << 4 << 1 << 6 << 0 << endr;
    
    double gameValue = 0;
    //Col<double> p(payoffMat.n_rows);
    //p.fill(0.0);
    //Col<double> q(payoffMat.n_cols);
    //q.fill(0.0);
    Col<double> p;
    Col<double> q;
    double equilibriumThreshold = 1e-4;
    bool checkNonnegative = true;
    
    double maxAbsValue = max(max(abs(payoffMat)));
    Mat<double> normPayoffMat = payoffMat/maxAbsValue+1.0;
    if(ZeroSumGame::solveGame(normPayoffMat,gameValue,p,q,equilibriumThreshold,checkNonnegative)){
        gameValue = (gameValue-1)*maxAbsValue;
        cout << gameValue << endl;
        p.print("p:");
        q.print("q:");
    }
    return 0;
}