
#include <iostream>
#include <string>
#include <math.h>
#include <cmath>
#include <vector>
#include <option.h>
using namespace std;

// this header file contains class bisection which is used to calculate sigam

class bisection{
    private:
    double S;
    double K;
    double r;
    double T;
    double C;
    string flag;
    public:
    bisection(double,double,double,double,double,string);           // constructor
    ~bisection();
    double f(double);                                               // object function (Option_theory_price - Option_real_price) 
    double find_root(double, double);                               // find the root of object function
};

bisection::bisection(double Si, double Ki, double ri, double Ti, double Ci, string _Flag){
    S = Si;
    K = Ki;
    r = ri;
    T = Ti;
    C = Ci;
    flag = _Flag;
}
bisection::~bisection(){}

double bisection::f(double x){
    Option_Price op(K,S,x,T,r,flag);
    double C_BS = op.Black_Scholes_Option_Price_boost();
    return  C_BS - C;
}

double bisection::find_root(double start, double end){
    double tol = 0.0000000001;                                      // tolerance
    int max_iter = 10000;                                           // max iteration
    double a = start;
    double b = end;
    for(int i=1;i<max_iter;i++){
        double c = (a+b)/2;
        if (f(c) == 0 || b-a < tol){
            return c;
        }else if(f(c)*f(a)>0){
            a = c;
        }else{
            b = c;
        }
    }
    cout<<"Method failed";
    return 0;
}


