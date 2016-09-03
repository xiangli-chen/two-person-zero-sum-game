#include <armadillo>
#include "zeroSumGame.h"
#include "gurobi_c++.h"

using namespace arma;
using namespace std;


bool ZeroSumGame::solveGame(const Mat<double> &payoffMat, double &gameValue, Col<double> &p, Col<double> &q, double diffThreshold, bool checkNonnegative)
{
    double maximumGain = 0;
    double minimumLoss = 0;
    if(!maximizePayoff(payoffMat,maximumGain,p,checkNonnegative)) return false;
    if(!minimizePayoff(payoffMat,minimumLoss,q,checkNonnegative)) return false;
    
    Col<double> absValues(2);
    absValues(0) = abs(maximumGain);
    absValues(1) = abs(minimumLoss);
    
    double abs_gain_loss_diff = abs(maximumGain-minimumLoss);
    double diff_portion = abs_gain_loss_diff/max(absValues);
    if (diff_portion < diffThreshold) {
        gameValue = (maximumGain+minimumLoss)/2;
        return true;
    }
    return false;
}

bool ZeroSumGame::maximizePayoff(const Mat<double> &payoffMat, double &maximumGain, Col<double> &p, bool checkNonnegative)
{
    if (checkNonnegative==true) {
        double minValuePayoffMat = min(min(payoffMat));
        if (minValuePayoffMat <= 0) {
            cout << "all elements of the payoffMat must be positive!" << endl;
            throw 2;
        }
    }
    
    int numRows = payoffMat.n_rows;
    int numCols = payoffMat.n_cols;
    
    bool success = false;
    GRBEnv* env = 0;
    try{
    env = new GRBEnv();
    GRBModel model = GRBModel(*env);
    /* No solving information printed */
    model.getEnv().set(GRB_IntParam_OutputFlag, 0);
    /* Add varialbe to the model */
    /* first NULL means low bound is 0.0 and seconde NULL means up bound is infinite by default */
    GRBVar* vars = model.addVars(NULL,NULL,NULL,NULL,NULL,numRows);
    model.update();
    
    /* Populate payoffMat matrix */
    for (int j = 0; j < numCols; j++) {
        GRBLinExpr lhs = 0;
        for (int i = 0; i < numRows; i++)
            if(payoffMat(i,j) != 0)
                lhs += payoffMat(i,j)*vars[i];
        model.addConstr(lhs,GRB_GREATER_EQUAL,1.0);
    }
    
    GRBLinExpr obj = 0;
    
    for (int i = 0; i<numRows; i++)
        obj += 1.0*vars[i];

    model.setObjective(obj,GRB_MINIMIZE);
    model.update();
    model.optimize();
    
    if (model.get(GRB_IntAttr_Status) == GRB_OPTIMAL) {
        maximumGain = 1.0/model.get(GRB_DoubleAttr_ObjVal);
        p = zeros< Col<double> >(numRows);
        for (int i = 0; i < numRows; i++)
            p(i) = vars[i].get(GRB_DoubleAttr_X)*maximumGain;
        success = true;
    }
        
    //cout << "maximum gain:" << maximumGain << endl;
    delete [] vars;
        
    }catch(GRBException e) {
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
    } catch(...) {
        cout << "Exception during optimization" << endl;
    }
    delete env;
    return success;
}

bool ZeroSumGame::minimizePayoff(const Mat<double> &payoffMat, double &minimumLoss, Col<double> &q, bool checkNonnegative)
{
    if (checkNonnegative==true) {
        double minValuePayoffMat = min(min(payoffMat));
        if (minValuePayoffMat <= 0) {
            cout << "all elements of the payoffMat must be positive!" << endl;
            throw 2;
        }
    }
    int numRows = payoffMat.n_rows;
    int numCols = payoffMat.n_cols;
    
    bool success = false;
    GRBEnv* env = 0;
    try{
        env = new GRBEnv();
        GRBModel model = GRBModel(*env);
        /* No solving information printed */
        model.getEnv().set(GRB_IntParam_OutputFlag, 0);
        /* Add varialbe to the model */
        /* first NULL means low bound is 0.0 and seconde NULL means up bound is infinite by default */
        GRBVar* vars = model.addVars(NULL,NULL,NULL,NULL,NULL,numCols);
        model.update();
        
        /* Populate A matrix */
        for (int i = 0; i < numRows; i++) {
            GRBLinExpr lhs = 0;
            for (int j = 0; j < numCols; j++)
                if(payoffMat(i,j) != 0)
                    lhs += payoffMat(i,j)*vars[j];
            model.addConstr(lhs,GRB_LESS_EQUAL,1.0);
        }
        
        GRBLinExpr obj = 0;
        
        for (int j = 0; j<numCols; j++)
            obj += 1.0*vars[j];
        
        model.setObjective(obj,GRB_MAXIMIZE);
        model.update();
        model.optimize();
        
        if (model.get(GRB_IntAttr_Status) == GRB_OPTIMAL) {
            minimumLoss = 1.0/model.get(GRB_DoubleAttr_ObjVal);
            q = zeros< Col<double> >(numCols);
            for (int j = 0; j < numCols; j++)
                q(j) = vars[j].get(GRB_DoubleAttr_X)*minimumLoss;
            success = true;
        }
        
        //cout << "minimum loss:" << minimumLoss << endl;
        
        delete [] vars;
        
    }catch(GRBException e) {
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
    } catch(...) {
        cout << "Exception during optimization" << endl;
    }
    delete env;
    return success;
}
