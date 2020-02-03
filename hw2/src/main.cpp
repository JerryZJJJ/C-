#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <time.h> 
#include <stdio.h>
#include <boost/date_time.hpp>
#include <iostream>
using namespace boost::gregorian; 
using namespace std;
// double calculate_r(double, double, double, double);
// double find_r(double t);
// double diff_date(string, string);

// class Bond {
//     private:
//     string Expiration_data;
//     double Frequency;
//     double Coupon_rate;
//     public:

//     ~Bond();
//     Bond(const Bond&);
//     Bond(string, double, double);
//     Bond();
//     string ToString();
//     double BondPricing(double, double);
// };
// Bond::Bond(){
//     Expiration_data = "0";
//     Frequency = 0;
//     Coupon_rate = 0;
// }
// Bond::~Bond(){
// }
// Bond::Bond(const Bond& old_bond){
//     Expiration_data = old_bond.Expiration_data;
//     Frequency = old_bond.Frequency;
//     Coupon_rate = old_bond.Coupon_rate;
// }
// Bond::Bond(string input_date, double Freq, double Coup){
//     Expiration_data = input_date;
//     Frequency = Freq;
//     Coupon_rate = Coup;
// }
// string Bond::ToString(){
//     string output;
//     output = "Bond(" + Expiration_data + ","+to_string(Frequency*12)+","+to_string(Coupon_rate)+") could be the reutrn of a bond with expiration date on "+\
//     Expiration_data + ",a payment each "+to_string((int)(Frequency*12))+" months, and "+to_string(100*Coupon_rate)+"% of coupon rate";
//     cout << output<<endl;
//     return output;

// }
// double Bond::BondPricing(double T, double Interest_rate){
//     int n;
//     double left_time;
//     vector<double> CF;
//     vector<double> DF;
//     double PV;
//     int i;

//     n = floor(T/Frequency);                     // Dividend times
//     left_time = (T/Frequency - n)*Frequency;    // Left time  

//     for (i=0;i<n;i++){
//         CF.push_back(100*Coupon_rate*Frequency);
//         DF.push_back(exp(-(i+1)*Frequency*Interest_rate));
//     }
//     CF.push_back(100*Coupon_rate*left_time+100);
//     DF.push_back(exp(-T*Interest_rate));

//     PV = 0;
//     for (i=0;i<n+1;i++){
//         PV += CF[i]*DF[i];
//     }
//     return PV;
//     // cout<<"PV value is: "<<PV<<endl;
// }


// int main() {

// compile with linker option as g++ computeBusinessDays.cpp -l boost_date_time
// this function computes the number of business days between start and end dateslong 
long dateDifference(string start_date, string end_date){
    date _start_date(from_simple_string(start_date));
    date _end_date(from_simple_string(end_date));    // counter for weekdays    
    int count=0;    
    for(day_iterator iter = _start_date; iter!=_end_date; ++iter){        
        // increment counter if it's no saturday and no sunday        
        if(iter->day_of_week() !=  boost::date_time::Saturday            
        && iter->day_of_week() !=  boost::date_time::Sunday)            
        ++count;}    
    return count;
}   
int main(){
    string start_date, end_date;   
    long numOfDays;    
    cout << "Enter the date in yyyy-mm-dd format" << endl;   
    cout << "Enter start date" << endl;    
    cin >> start_date;  
    cout << "Enter end date" << endl;    
    cin >> end_date;    
    numOfDays = dateDifference(start_date,end_date);    
    cout << "Number of business days are " << numOfDays << endl;   
    return 0;}
    // // Q1
    // printf("---------------------------------------------------------------\n");
    // printf("------------------------------  Q1  ---------------------------\n");
    // printf("---------------------------------------------------------------\n");
    // Bond default_bond;
    // string output1;
    // output1 = default_bond.ToString();
    
    // Bond q1_bond("12/19/2035",0.5,0.08);
    // string output2;
    // output2 = q1_bond.ToString();
    
    // // Q2
    // printf("\n");
    // printf("---------------------------------------------------------------\n");
    // printf("------------------------------  Q2  ---------------------------\n");
    // printf("---------------------------------------------------------------\n");
    // double BP;
    // BP = q1_bond.BondPricing(4.2,0.07);
    // printf("Using the BondPricing method to calculate Bond(Exp Date,0.5,0.08) for 4.2 years to maturity and 7% interest rate \n");
    // cout<<"PV value is: "<<BP<<endl;

    // // Q3
    // printf("\n");
    // printf("---------------------------------------------------------------\n");
    // printf("------------------------------  Q3  ---------------------------\n");
    // printf("---------------------------------------------------------------\n");
    // printf("In this problem, I notice that we should use forward pricing method \n");
    // printf("At the same time, after talking with Professor Deng, I use \"12/31/2020\" as the end of Bond instead of \"01/01/2020\" \n");
    // double PV2016;
    // double PV2017;
    // double PV2018;
    // double PV2019;
    // double PV2020;
    // double payment;
    // double t3 = diff_date("08/03/2015","12/31/2020");   //diff(“20150803”,”20201231”)
    // double t4 = diff_date("08/03/2015","01/01/2016");
    // vector <double> t1 = {t4,t4+1,t4+2,t4+3,t4+4};
    // Bond Bond2016("12/31/2020",0.5,0.05);
    // Bond Bond2017("12/31/2020",0.5,0.05);
    // Bond Bond2018("12/31/2020",0.5,0.05);
    // Bond Bond2019("12/31/2020",0.5,0.05);
    // Bond Bond2020("12/31/2020",0.5,0.05);
    // PV2016 = Bond2016.BondPricing(5,calculate_r(t1[0],t3,find_r(t1[0]),find_r(t3)));  
    // PV2017 = Bond2017.BondPricing(4,calculate_r(t1[1],t3,find_r(t1[1]),find_r(t3)));
    // PV2018 = Bond2018.BondPricing(3,calculate_r(t1[2],t3,find_r(t1[2]),find_r(t3)));
    // PV2019 = Bond2019.BondPricing(2,calculate_r(t1[3],t3,find_r(t1[3]),find_r(t3)));
    // PV2020 = Bond2020.BondPricing(1,calculate_r(t1[4],t3,find_r(t1[4]),find_r(t3)));
    // payment = (PV2016+PV2017+PV2018+PV2019+PV2020)/5;
    // cout<<"The PV value is: "<<payment*exp(-t3*find_r(t3))<<" which is great than 98"<<endl;
    // printf("It is a good investment");


// double calculate_r(double t1, double t3, double r1, double r3){
//     double t2 = t3 - t1;
//     double r2;
//     r2 = (r3*t3-r1*t1)/t2;
//     return r2;
// }

// double find_r(double t){
//     ifstream infile("./Bond_Ex3.csv");
     
//     string temp;
//     while(getline(infile,temp)){
//         if (temp<="9"&&temp>="0"){
//             int startLoc = temp.rfind(",");
//             string ytm_str = temp.substr(0,startLoc);
//             string rate_str = temp.substr(startLoc+1);
//             double ytm = atof(ytm_str.c_str());
//             double rate = atof(rate_str.c_str());
//             if (ytm<t){
//                 // cout<<"rate is:"<<rate<<endl;
//                 return rate;
//             }
//         }
//     }
// }

// double diff_date(string data1, string data2){  //diff(“20150803”,”12/31/2020”)
//     int d1,m1,y1;
//     int d2,m2,y2;
//     sscanf(data1.c_str(),"%d/%d/%d",&m1,&d1,&y1);
//     sscanf(data2.c_str(),"%d/%d/%d",&m2,&d2,&y2);

//     struct tm s1 = {0, 0, 0, d1,m1,y1};
//     struct tm s2 = {0, 0, 0, d2,m2,y2};
//     time_t t1 = mktime(&s1);
//     time_t t2 = mktime(&s2);
//     double diff = difftime(t1,t2)/(365*24*3600);
//     if(diff>0){
//         return diff;
//     }
//     else{
//         return -diff;
//     }
// }

