#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

double average(vector<double> v)
{
    int i;
    double sum=0;
    for(i=0;i<v.size();i++){
        sum += v[i];
    }
    return sum/v.size();
}

double find_rate(vector<double> rate_vec, vector<string> date_vec, string date)
{
    int i;
    for(i=0;i<rate_vec.size();i++){
        if(date==date_vec[i]){
            return rate_vec[i];
        }
    }
}

int main()
{
    vector<double> rate;
    vector<string> date;
    ifstream infile("./hw1_H.15_Baa_Data.csv");
    
// code for loading rate and date vectors from the file hw1_H.15_Baa_Data.csv
// the headers should be handled properly. do not delete them manually


    int i; 
    string temp;
    string temp1;
    for (i = 0;i<2000;i++){
        infile>>temp;

        if(temp==temp1){  // notes: avoid infile the last line several times
            break;
        }
        temp1 = temp;

        if (temp<"3"&&"0"<temp){   // notes: delete useless data 
            string left = temp.substr(0,7);
            string right = temp.substr(8,temp.length()-7);

            double dd;     //notes: convert string type rate to double type
            sscanf(right.c_str(),"%lf",&dd);

            rate.push_back(dd);
            date.push_back(left);
        }
    }
    int j;
    
    for(j=0;j<rate.size();j++){
        cout<<"Date is:"<<date[j]<<"  and Rate is:"<<rate[j]<<endl;
        // break;
    }

    infile.close();

// code for prompting user for a date and returning the rate
// and the difference between the rate for that date and the
// average rate
    string search_date;

    while(1){
        cin>>search_date;
        double result = find_rate(rate,date,search_date);
        cout<<"Rate for date:"<<search_date<<" is:"<<result<<endl;
        cout<<"Average for vector v is:"<<average(rate)<<endl;
        cout<<"Difference between rate and average rate is"<<result-average(rate)<<endl;
    }

//
// This code should allow the user to continue to input dates
// until the user inputs the EOF (End-of-file), namely control-d (in linux/mac) or control-z (in windows)
// This should not crash if a bad date is entered.

   return 0.0; // program end
}

