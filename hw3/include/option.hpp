#include <iostream>
#include <string>
#include <math.h>
#include <cmath>
#include <vector>
using namespace std;

// this hpp file contains three class: option, pricing_model, Option_Price

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
    virtual double Black_Scholes_Option_Price()=0;                      // virtual function for BS model
    virtual double Binomial_Option_Price()=0;                           // virtual function for Binomial model
};

// ------------------------------ class3: Option_price ------------------------------

class Option_Price:public option, public pricing_model{
    public:
    string flag;
    Option_Price();                                                     // default constructor
    Option_Price(double, double, double, double, double, string);       // constructor
    ~Option_Price();                                                    // destructor
    double Black_Scholes_Option_Price();                                // BS model
    double Binomial_Option_Price();                                     // Binomial model
    double factorial(int);                                              // help function 1 -- calculate factorial
    double combination(int, int);                                       // help function 2 -- calculate combination
}; 

Option_Price::Option_Price(){
    flag = "c";
}
Option_Price::Option_Price(double Ki, double si, double sigmai, double Ti, double ri, string fi):option(Ki, si, sigmai, Ti, ri){
    flag = fi;
}
Option_Price::~Option_Price(){}

double Option_Price::Black_Scholes_Option_Price(){
    double K = get("K");
    double T = get("T");
    double sigma = get("sigma");
    double r = get("r");
    double s = get("s");

    double d1 = ((r+0.5*pow(sigma,2))*T - log(K/s))/(sigma*sqrt(T));
    double d2 = d1 - sigma*sqrt(T);

    int ind1 = 0;                                                       // set indicator for x, if x<0, set ind = 1
    int ind2 = 0;
    
    if (d1<0){
        d1 = -d1;
        ind1 = 1;
    }
    if (d2<0){
        d2 = -d2;
        ind2 = 1;
    }

    double z1 = 1/(1+0.2316419*d1);
    double z2 = 1/(1+0.2316419*d2);
    double R_d1 = 0.319381530*z1-0.356563782*pow(z1,2)+1.781477937*pow(z1,3)-1.821255978*pow(z1,4)+1.330274429*pow(z1,5);
    double R_d2 = 0.319381530*z2-0.356563782*pow(z2,2)+1.781477937*pow(z2,3)-1.821255978*pow(z2,4)+1.330274429*pow(z2,5);
    double N_d1 = 1 - 1/sqrt(2*M_PI)*exp(-pow(d1,2)/2)*R_d1;
    double N_d2 = 1 - 1/sqrt(2*M_PI)*exp(-pow(d2,2)/2)*R_d2;

    if (ind1 == 1){
        N_d1 = 1-N_d1;
    }
    if (ind2 == 1){
        N_d2 = 1-N_d2;
    }

    double call = s*N_d1-K*exp(-r*T)*N_d2;
    double put = call-s+K*exp(-r*T);                                    // use put call parity theorm to calculate put 

    if (flag=="c" || flag == "C"){
        cout<<"\nUsing BS model to calculate call option's price"<<endl;
        return call;
    }else{
        cout<<"\nUsing BS model to calculate put option's price"<<endl;
        return put;
    }
}
double Option_Price::Binomial_Option_Price(){
    double K = get("K");
    double T = get("T");
    double sigma = get("sigma");
    double r = get("r");
    double s = get("s");

    double N = 100.0;
    double delta = T/N;
    double u = exp(sigma*sqrt(delta));
    double d = exp(-sigma*sqrt(delta));
    double p = (exp(r*delta)-d)/(u-d);

    // formula: K*exp(-rT)P(S(T)<=i0)-S*sum_0_to_io(C_N_i*exp(-rT)*pow(up,i)*pow(d*(1-p),N-i))
    //        = K*exp(-rT)*probability - S*value

    double probability = 0;
    double value = 0;
    for(int i = 0;i<N+1;i++){
        if ((s*pow(u,i)*pow(d,N-i))<=K){                                // make sure i won't be larger than i0
            probability += combination(N,i)*pow(p,i)*pow(1-p,N-i);
            value += combination(N,i)*exp(-r*T)*pow(u*p,i)*pow(d*(1-p),N-i);
        }
    }

    double put = K*exp(-r*T)*probability-s*value;
    double call = put+s-K*exp(-r*T);                                    // use put call parity theorm to calculate put 

    if (flag=="c" || flag == "C"){
        cout<<"\nUsing Binomial models to calculate call option's price"<<endl;
        return call;
    }else{
        cout<<"\nUsing Binomial models to calculate put option's price"<<endl;
        return put;
    }
}
double Option_Price::factorial(int i){
    if(i==1 || i==0){
        return 1.0;
    }else{
        return i*factorial(i-1);
    }
}
double Option_Price::combination(int n,int i){
    return factorial(n)/(factorial(i)*factorial(n-i));
}