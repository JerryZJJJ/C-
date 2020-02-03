#include <iostream>
#include <string>
#include <math.h>
#include <cmath>
#include <vector>
#include <boost/random.hpp>
#include <option.h>
#include <boost/math/distributions.hpp>

// this header file contains class dynamic_hedge which is used to calculate all result for delta hedging

class dynamic_hedge{
    private:
    double S;
    double T;
    double mu;
    double sigma;
    double r;
    int N;
    int N_;
    int Seed;
    double K;
    string flag;
    vector<double> path;                    // spot price path
    vector<double> o_path;                  // option price path
    vector<double> e_path;                  // error price path
    vector<double> d_path;                  // delta price path
    vector<double> b_path;                  // bank price path 
    vector<double> s_path;                  // sigma price path 
    vector<double> r_path;                  // interest rate price path
    vector<double> pnl;                     // pnl path
    vector<double> pnl_hedge;               // pnl path with hedging

    public:
    dynamic_hedge(double, double, double, double, double, int, int, string);     // constructor for Q1
    dynamic_hedge(double, double, int, string);                                  // constructor for Q2
    ~dynamic_hedge();
    void spot_path();                       // generate spot paths (Q1)
    void option_path(double);               // calculate option paths (Q1)
    void hedging_error();                   // calculate hedging eroor (Q1 & Q2) 
    void pnl_path();                        // calculate pnl_path (Q2) 
    void set_path(string,vector<double>);   // set specific path manuual (Q2)
    vector<double> get_path(string);        // get specific path (Q1 & Q2)
};

//constructor for Q1
dynamic_hedge::dynamic_hedge(double _S, double _T, double _mu, double _sigma, double _r, int _N, int _Seed, string _Flag){
    S = _S;
    T = _T;
    mu = _mu;
    sigma = _sigma;
    r = _r;
    N = _N;
    N_ = 0;
    Seed = _Seed;
    flag = _Flag;
    path = vector<double>(N+1);
    o_path = vector<double>(N+1);
    e_path = vector<double>(N+1);
    d_path = vector<double>(N+1);
    b_path = vector<double>(N+1);
    s_path = vector<double>(N+1,sigma);
    r_path = vector<double>(N+1,r);
    pnl = vector<double>(N+1);
    pnl_hedge = vector<double>(N+1);
}

// constructor for Q2
dynamic_hedge::dynamic_hedge(double _N_, double _K, int _N, string _Flag){
    T = _N_/252;
    K = _K;
    N = _N;
    N_= _N_;
    flag = _Flag;
    path = vector<double>(N+1);
    o_path = vector<double>(N+1);
    e_path = vector<double>(N+1);
    d_path = vector<double>(N+1);
    b_path = vector<double>(N+1);
    s_path = vector<double>(N+1);
    r_path = vector<double>(N+1);
    pnl = vector<double>(N+1);
    pnl_hedge = vector<double>(N+1);
}

dynamic_hedge::~dynamic_hedge(){}

void dynamic_hedge::spot_path(){
    unsigned long seed = Seed;
    boost::mt19937 rng(seed);                                   // random generator mt19937
    boost::normal_distribution <> norm(0,1);
    boost::variate_generator<boost::mt19937&, boost::normal_distribution<>> unnorm(rng,norm);

    path[0] = S;
    double deltaT = T/N;
    for(int i = 1;i<N+1;i++){
        path[i] = path[i-1] + mu * path[i-1] * deltaT + s_path[i-1] * path[i-1] * sqrt(deltaT) * unnorm();
    }
}

void dynamic_hedge::option_path(double _K){
    K = _K;
    for(int i = 0; i<N+1; i++){
        Option_Price op(K,path[i],s_path[i],T - i * T/N, r_path[i], flag);
        o_path[i] = op.Black_Scholes_Option_Price_boost();      // calculate option price using BS formula
    }
}

void dynamic_hedge::hedging_error(){
    boost::math::normal_distribution<> d(0,1);
    
    if(flag == "c"||flag =="C"){                                    // hedging error for call
        e_path[0] = 0;
        d_path[0] = cdf(d,((r_path[0]+0.5*pow(s_path[0],2))*T - log(K/path[0]))/(s_path[0]*sqrt(T)));
        b_path[0] = o_path[0] - path[0] * d_path[0];
        if(N_ == 0){
            N_ = N;
        }
        for(int i = 1;i<N+1;i++){
            e_path[i] = d_path[i-1] * path[i] + b_path[i-1] * exp(r_path[i]*T/N_) - o_path[i];
            d_path[i] = cdf(d,((r_path[i]+0.5*pow(s_path[i],2))*(T-i*T/N_) - log(K/path[i]))/(s_path[i]*sqrt(T-i*T/N_)));
            b_path[i] = d_path[i-1] * path[i] + b_path[i-1] * exp(r_path[i]*T/N_) - d_path[i] * path[i];
        }
    }else{                                                          // hedging error for put
        e_path[0] = 0;
        d_path[0] = cdf(d,((r_path[0]+0.5*pow(s_path[0],2))*T - log(K/path[0]))/(s_path[0]*sqrt(T)))-1;
        b_path[0] = o_path[0] - path[0] * d_path[0];
        if(N_ == 0){
            N_ = N;
        }
        for(int i = 1;i<N+1;i++){
            e_path[i] = d_path[i-1] * path[i] + b_path[i-1] * exp(r_path[i]*T/N_) - o_path[i];
            d_path[i] = cdf(d,((r_path[i]+0.5*pow(s_path[i],2))*(T-i*T/N_) - log(K/path[i]))/(s_path[i]*sqrt(T-i*T/N_)))-1;
            b_path[i] = d_path[i-1] * path[i] + b_path[i-1] * exp(r_path[i]*T/N_) - d_path[i] * path[i];
        }
    }
}

void dynamic_hedge::pnl_path(){
    for(int i = 0; i<N+1; i++){
        pnl[i] = o_path[0] - o_path[i];
        pnl_hedge[i] = e_path[i];
    }
}

vector<double> dynamic_hedge::get_path(string target){
    if(target == "spot"){
        return path;
    }else if(target == "option"){
        return o_path;
    }else if(target == "sigma"){
        return s_path;
    }else if(target == "rate"){
        return r_path;        
    }else if(target == "delta"){
        return d_path;        
    }else if(target == "hedging_error"){
        return e_path;
    }else if(target == "pnl"){
        return pnl;
    }else if(target == "pnl_hedge"){
        return pnl_hedge;
    }
}

void dynamic_hedge::set_path(string target,vector<double> target_value) {
    if(target == "spot"){
        path = target_value;
    }else if(target == "option"){
        o_path = target_value;
    }else if(target == "sigma"){
        s_path = target_value;
    }else if(target == "rate"){
        r_path = target_value;
    }else if(target == "hedging_error"){
        e_path = target_value;
    }else if(target == "pnl"){
        pnl = target_value;
    }else if(target == "pnl_hedge"){
        pnl_hedge = target_value;
    }
} 



