#include <iostream>
#include <string>
#include <option.hpp>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    double K,s,sigma,T,r;
    string flag;
    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"--------------------- Welcome to option pricing calculator -------------------"<<endl;
    cout<<"----------------------------- Author:Zijie Li --------------------------------"<<endl;
    cout<<"------------------------------------------------------------------------------"<<endl;
    
    cout<<"\nPlease input the type of option:"<<endl;                                // input all parameters we need
    cout<<"\"c\" or \"C\" for call option,\"p\" or \"P\" for call option"<<endl;

    cin>>flag;
    cout<<"Please input strike price   -- K:"<<endl;
    cin>>K;
    cout<<"Please input spot price     -- s:"<<endl;
    cin>>s;
    cout<<"Please input volatility     -- sigma:"<<endl;
    cin>>sigma;
    cout<<"Please input time period    -- T:"<<endl;
    cin>>T;
    cout<<"Please input risk free rate -- r:"<<endl;
    cin>>r;
    
    Option_Price test(K,s,sigma,T,r,flag);                                           // create a new Option_Price object
    double price_bs = test.Black_Scholes_Option_Price();                             // call Option_Price's BS model method
    cout<<"price = "<<price_bs<<endl;
    double price_bio = test.Binomial_Option_Price();                                 // call Option_Price's Binomial model method
    cout<<"price = "<<price_bio<<endl;
    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"----------------------------- Thank you for using! ---------------------------"<<endl;
    cout<<"------------------------------------------------------------------------------"<<endl;
    return 0;
}