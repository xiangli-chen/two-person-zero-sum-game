#ifndef __ZeroSumGame__
#define __ZeroSumGame__

#include <armadillo>

using namespace arma;

class ZeroSumGame
{
public:
    static bool solveGame(const Mat<double> &payoffMat, double &gameValue, Col<double> &p, Col<double> &q, double diffThreshold, bool checkNonnegative);
    static bool maximizePayoff(const Mat<double> &payoffMat, double &maximumGain, Col<double> &p, bool checkNonnegative);
    static bool minimizePayoff(const Mat<double> &payoffMat, double &minimumLoss, Col<double> &q, bool checkNonnegative);
};

#endif
