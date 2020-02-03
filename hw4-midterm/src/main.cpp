#include <iostream>
#include <boost/random.hpp>
#include <boost_learn.h>
#include <dynamic_hedge.h>
#include <bisection.h>
#include <boost/date_time.hpp>
#include <cstring>
#include <fstream>

using namespace std;
using namespace boost::gregorian; // compile with linker option as g++ computeBusinessDays.cpp -l boost_date_time

// this function computes the number of business days between start and end dates
long dateDifference( string start_date, string end_date )
{
    date _start_date(from_simple_string(start_date));
    date _end_date(from_simple_string(end_date));

    // counter for weekdays
    int count=0;
    for(day_iterator iter = _start_date; iter!=_end_date; ++iter)
    {
        // increment counter if it's no saturday and no sunday
        if(    iter->day_of_week() !=  boost::date_time::Saturday
            && iter->day_of_week() !=  boost::date_time::Sunday)
            ++count;
    }
    return count;
}

int main() {
    cout<<"--------------------------------------------------------------------\n";
    cout<<"--------Welcome to Zijie Li's delta hedging midterm program!--------\n";
    cout<<"--------------------------------------------------------------------\n";
    cout<<"This program consist of three parts:\n";
    cout<<"part1: Question1.1 : plot 100 spot path \n";
    cout<<"part2: Question1.2 : plot 1000 hedging error path and histgram of HE_n \n";
    cout<<"part3: Question2 : dynamic delta heding for GOOG \n";
    cout<<"press Enter to go to Q1.1\n";
    cin.get();


    //------------------------------------------------------------------
    //------------------------ Q1.1: plot spot path --------------------
    //------------------------------------------------------------------
    cout<<"Part1: plot 100 spot path\n";
    cout<<"Parameters: \n";
    cout<<"Type = Call, S = 100, T = 0.4, mu = 0.05, sigma = 0.24, r = 0.025, N = 100\n";
    cout<<"Random Number Generator: mt19937, seed = 12411\n";
    cout << "--press Enter to continue--";
    cin.get();

    // random number generator
    unsigned long seed = 12411;
    boost::mt19937 rng(seed);
    boost::uniform_int <> six(1,10000000);
    boost::variate_generator<boost::mt19937&,boost::uniform_int<>> unsix(rng,six);

    int num_q11=100;                                // number of path
    fstream fout11;
    fout11.open("./data/resultQ11.csv",ios::out|ios::app);

    vector<double> q1_spot_path;

    for(int j=0;j<num_q11;j++){
        q1_spot_path.clear();
        dynamic_hedge test1(100,0.4,0.05,0.24,0.025,100,unsix(),"c");
        test1.spot_path();
        q1_spot_path = test1.get_path("spot");
        for(int i=0;i<100;i++){
            fout11<<q1_spot_path[i]<<",";
            cout<<q1_spot_path[i]<<",";
        }
        fout11<<q1_spot_path[100]<<endl;
        cout<<q1_spot_path[100]<<endl;
    }
    cout << "\nProcess Success! Save resultQ11.csv to local\n";
    cout << "--press Enter to go to Q1.2--\n";
    cin.get();

    //------------------------------------------------------------------
    //--------------------- Q1.2: plot hedging error -------------------
    //------------------------------------------------------------------
    cout<<"Part2: plot 1000 hedging error path and histgram of HE_n \n";
    cout<<"Parameters: \n";
    cout<<"Type = Call S = 100, T = 0.4, mu = 0.05, sigma = 0.24, r = 0.025, N = 100\n";
    cout<<"Random Number Generator: mt19937, seed = 12411\n";
    cout<<"--press continue to generate spot path--\n";
    cin.get();

    int num_q12=1000;                               //number of path
    vector<vector<double>> multi_path(num_q12);
    vector<double> t1_hedge_error;

    fstream fout12;
    fout12.open("./data/resultQ12.csv",ios::out|ios::app);

    for(int j=0;j<num_q12;j++){
        t1_hedge_error.clear();
        dynamic_hedge test1(100,0.4,0.05,0.24,0.025,100,unsix(),"c");
        test1.spot_path();
        test1.option_path(105);
        test1.hedging_error();
        multi_path[j]=test1.get_path("hedging_error");
        for(int i=0;i<100;i++){
            fout12<<multi_path[j][i]<<",";
        }
        fout12<<multi_path[j][100]<<endl;
    }
    cout << " \nProcess Success! Save resultQ12.csv to local\n";
    cout << "--press Enter to go to Q2--\n";
    cin.get();

    //------------------------------------------------------------------
    //------------------- Q2: delta hedging for GOOG -------------------
    //------------------------------------------------------------------
    cout<<"Part3: delta hedging for GOOG\n";
    cout<<"It has five steps: \n";
    cout<<"   step1 : Input start_date, end_date, mature_date \n";
    cout<<"   step2 : Input interest.csv op_GOOG.csv sec_GOOG.csv \n";
    cout<<"   step3 : Calculate sigma using bisection method \n";
    cout<<"   step4 : Run delta hedge \n";
    cout<<"   step5 : Output resultQ2.csv to local \n";
    cout << "   --press Enter to continue--\n";
    cin.get();

    // step 1: input t0_date, tN_date, T_date, K && calculate N & T : 
    string t0_date, tN_date, T_date,flag;
    double K, N, N_;
    
    cout<<"Please input start date (recommend 2011-07-05): ";
    cin>>t0_date;
    cout<<"\nPlease input end date (recommend 2011-07-29): ";
    cin>>tN_date;
    cout<<"\nPlease input mature date (recommend 2011-09-17): ";
    cin>>T_date;
    cout<<"\nPlease input strike price (recommend 500): ";
    cin>>K;
    cout<<"\nPlease input option type (recommend C/c): ";
    cin>>flag;

    N = double(dateDifference(t0_date,tN_date)+1);
    N_ = double(dateDifference(t0_date,T_date));

    cout << "\nPart3: Step 1 Input start_date, end_date, mature_date success!\n";
    cout <<"   option tpye: "<<flag<<"\n   start date: "<<t0_date<<"\n   end_date: "<<tN_date<<"\n   mature date: "<<T_date
        <<"\n   strike price: "<<K<<"\n   time difference from start to end(N): "<<N
        <<"\n   time difference from start to mature(N_): "<<N_<<endl;
    cout << "   --press Enter to continue--\n";
    cin.get();

    // step 2: import interest.csv op_GOOG.csv sec_GOOG.csv 
    vector<string> date_path;                   //date path
    vector<double> path;                        //spot path
    vector<double> v_path;                      //option price path
    vector<double> r_path;                      //interest path
    
    ifstream i1("./data/sec_GOOG.csv");
    ifstream i2("./data/interest.csv");
    string temp1,temp2;
    while(getline(i1,temp1) && getline(i2,temp2)){
        if (temp1<="9"&&temp1>="0"){
            int startLoc = temp1.rfind(",");
            string ytm_str = temp1.substr(0,startLoc);
            
            string s_str = temp1.substr(startLoc+1);
            double s_ = atof(s_str.c_str());
            
            string r_str = temp2.substr(startLoc+1);
            double r_ = atof(r_str.c_str())/100;

            if (ytm_str >= t0_date && ytm_str <= tN_date){
                date_path.push_back(ytm_str);
                path.push_back(s_);
                r_path.push_back(r_);
                // cout<<ytm_str<<" "<<s_<<" "<<r_<<endl;
            }
        }
    }

    ifstream i3("./data/op_GOOG.csv");
    vector <string> row;
    string temp3,word,flag_r;
    if(flag=="c"||flag=="C"){
        flag_r = "C";
    }else{
        flag_r = "P";
    }

    while (getline(i3,temp3)){
        row.clear();
        stringstream s(temp3);
        if (temp1<="9"&&temp1>="0"){
            while(getline(s,word,',')){
                row.push_back(word);
            }    
            if (row[0] >= t0_date && row[0] <= tN_date && row[1] == T_date && row[2] == flag_r&& stod(row[3]) == K){
                double v_ = (stod(row[4]) + stod(row[5]))/2;
                v_path.push_back(v_);
            }
        }
    }

    cout << "\nPart3: Step 2 Input interest.csv op_GOOG.csv sec_GOOG.csv success!\n";
    cout << "   --press Enter to continue--\n";
    cin.get();
    
    // step 3: calculate sigma
    vector<double> s_path;       //sigma path
    for(int i = 0;i<N;i++){
        bisection bis(path[i],K,r_path[i],(N_ - double(i))/252,v_path[i],flag);
        double sigma = bis.find_root(0,1);
        s_path.push_back(sigma);
    }

    cout << "Part3: Step 3 Calculate sigma using bisection method success!\n" ;
    cout << "   Parameters for bisection: \n";
    cout << "   Tolerance(tol): 0.0000000001, Max Iteration(max_iter): 10000\n";
    cout << "   --press Enter to continue--\n";
    cin.get();

    // step 4: run delta_hedge
    dynamic_hedge goog(N_,K,N-1,flag);
    goog.set_path("spot",path);
    goog.set_path("option",v_path);
    goog.set_path("rate",r_path);
    goog.set_path("sigma",s_path);
    goog.hedging_error();
    goog.pnl_path();
    
    vector<double> d_path = goog.get_path("delta"); 
    vector<double> e_path = goog.get_path("hedging_error");
    vector<double> pnl = goog.get_path("pnl");
    // vector<double> pnl_hedge = goog.get_path("pnl_hedge");

    cout << "Part3: Step 4 Run delta hedge success!\n" ;
    cout << "   --press Enter to continue--\n";
    cin.get();

    // step 5: output resultQ2.csv
    fstream fout;
    fout.open("./data/resultQ2.csv",ios::out|ios::app);
    fout<<"date, "<<"spot price, "<<"option price, "<<"sigma, "<< "delta, "<<"hedging error, "
        <<"pnl, "<<endl;

    cout<<"\nResult: \n";
    cout<<"date, "<<"spot price, "<<"option price, "<<"sigma, "<< "delta, "<<"hedging error, "
        <<"pnl, "<<endl;
    for(int i =0;i<N;i++){
        cout<<date_path[i]<<" ";
        cout<<path[i]<<" ";
        cout<<v_path[i]<<" ";
        // cout<<r_path[i]<<" ";
        cout<<s_path[i]<<" ";
        cout<<d_path[i]<<" ";
        cout<<e_path[i]<<" ";
        cout<<pnl[i]<<endl;
        // cout<<pnl_hedge[i]<<endl;

        fout<<date_path[i]<<", ";
        fout<<path[i]<<", ";
        fout<<v_path[i]<<", ";
        fout<<s_path[i]<<", ";
        fout<<d_path[i]<<", ";
        fout<<e_path[i]<<", ";
        fout<<pnl[i]<<endl;
        // fout<<pnl_hedge[i]<<endl;
    }
    cout << "Part3: Step 5 Output resultQ2.csv success!";
}