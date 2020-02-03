#ifndef _OPTION_H
#define _OPTION_H
#include <iostream>
#include <string>
#include <math.h>
#include <cmath>
#include <vector>
#include <boost/math/distributions.hpp>
using namespace std;

// this header file contains three class: option, pricing_model, Option_Price

// ------------------------------ class1: option -------------------------------
class option {
    private:
    double K;
    double s;
    double sigma;
    double T;
    double r;

    public:
    ~option();                                                          // destructor
    option();                                                           // default constructor
    option(double, double, double, double, double);                     // constructor
    double get(string);
};
option::~option(){
}
option::option(){
    K = 100;
    s = 140;
    sigma = 0.2;
    T = 1;
    r = 0.05;
}
option::option(double Ki, double si, double sigmai, double Ti, double ri){
    K = Ki;
    s = si;
    sigma = sigmai;
    T = Ti;
    r = ri;
}
double option::get(string target){
      if (target == "K"){
          return K;
      }else if (target == "s")
      {
          return s;
      }else if (target == "sigma")
      {
          return sigma;
      }else if (target == "T")
      {
          return T;
      }else if (target == "r")
      {
          return r;
      }else
      {
          cout<<"please only type one of {K,s,sigma,T,r}"<<endl;
          return 0;
      }
}

// ------------------------------ class2: pricing_model ------------------------------

class pricing_model{
    public:
    virtual double Black_Scholes_Option_Price_boost()=0;                // virtual function for BS model
};

// ------------------------------ class3: Option_price ------------------------------

class Option_Price:public option, public pricing_model{
    public:
    string flag;
    Option_Price();                                                     // default constructor
    Option_Price(double, double, double, double, double, string);       // constructor
    ~Option_Price();                                                    // destructor
    double Black_Scholes_Option_Price_boost();                          // BS model using boost
}; 

Option_Price::Option_Price(){
    flag = "c";
}
Option_Price::Option_Price(double Ki, double si, double sigmai, double Ti, double ri, string fi):option(Ki, si, sigmai, Ti, ri){
    flag = fi;
}
Option_Price::~Option_Price(){}

double Option_Price::Black_Scholes_Option_Price_boost(){
    boost::math::normal_distribution<> nd(0,1);
    double K = get("K");
    double T = get("T");
    double sigma = get("sigma");
    double r = get("r");
    double s = get("s");

    double d1 = ((r+0.5*pow(sigma,2))*T - log(K/s))/(sigma*sqrt(T));
    double d2 = d1 - sigma*sqrt(T);

    double N_d1 = cdf(nd,d1);
    double N_d2 = cdf(nd,d2);

    double call = s*N_d1-K*exp(-r*T)*N_d2;
    double put = call-s+K*exp(-r*T);                                    // use put call parity theorm to calculate put 

    if (flag=="c" || flag == "C"){
        return call;
    }else{
        return put;
    }
}
#endif