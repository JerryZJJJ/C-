#include <ctime>
#include <fstream>
#include <string.h>
class StrategyAnalyzer{
    public:
    StrategyAnalyzer(int, double, double, double, double ,double);
    ~StrategyAnalyzer();
    void writeResults(const string&);
    double calcStdDev(double* , int);
    double calcMean(double* , int);
    void analyzeReturns();

    private:
    int numSimulations;
    double mu;
    double sigma;
    double r;
    double P_call;
    double P_put;
    double *spot;
    double *arth_return_1;
    double *arth_return_2;
    double *arth_return_3;
};

StrategyAnalyzer::~StrategyAnalyzer(){}

StrategyAnalyzer::StrategyAnalyzer(int _numSimulations, double _mu, double _sigma, double _r, double _P_call ,double _P_put){
    numSimulations = _numSimulations;
    mu = _mu;
    sigma = _sigma;
    r = _r;
    P_call = _P_call;
    P_put = _P_put;
    spot = new double[numSimulations];
    arth_return_1 = new double[numSimulations];
    arth_return_2 = new double[numSimulations];
    arth_return_3 = new double[numSimulations];

    double spot0 = 100.0;

    mt19937 mt_rand(time(0));
    normal_distribution<double> dis_normal(0.0, 1.0);

    for(int i = 0;i<numSimulations;i++){
        double x = dis_normal(mt_rand);
        double r = mu - 0.5*pow(sigma,2) + sigma * x;
        spot[i] = spot0*exp(r);

        arth_return_1[i] = exp(r) - 1;
        arth_return_2[i] = (((1+r)*(spot0 - P_call) + max(spot[i] - spot0, 0.0)) - spot0)/spot0;
        arth_return_3[i] = (((1+r)*(P_put + spot0) - max(0.0,spot0 - spot[i])) - spot0)/spot0;
        // cout<<arth_return_1[i]<<' '<<arth_return_2[i]<<' '<<arth_return_3[i]<<endl;
    }
}

void StrategyAnalyzer::writeResults(const string& filename){
    ofstream outfile;
    outfile.open(filename);

    outfile<<"BuyAndHold,LongCall,Putwrite\n";
    cout << numSimulations<<endl;
    for(int i =0; i<numSimulations-1;i++){
        outfile<<arth_return_1[i]<<","<<arth_return_2[i]<<","<<arth_return_3[i]<<"\n";
    }
    outfile<<arth_return_1[numSimulations-1]<<","<<arth_return_2[numSimulations-1]<<","<<arth_return_3[numSimulations-1];
    outfile.close();
}

double StrategyAnalyzer::calcMean(double* arr, int arrLen){
    double sum = 0;
    double mean = 0;
    for(int i =0;i < arrLen;i++){
        sum += arr[i];
    }
    mean = sum/arrLen;
    return mean;
}

double StrategyAnalyzer::calcStdDev(double* arr, int arrLen){
    double sum2 = 0;
    double mean = calcMean(arr,arrLen);
    for(int i = 0; i <arrLen;i++){
        sum2 += pow(arr[i] - mean,2);
    }
    double sd = pow(sum2 / (arrLen -1),0.5);
    return sd;
}

void StrategyAnalyzer::analyzeReturns(){
    double mean_1 = calcMean(arth_return_1,numSimulations);
    double std_1 = calcStdDev(arth_return_1,numSimulations);
    double sharpe_1 = mean_1 / std_1;

    double mean_2 = calcMean(arth_return_2,numSimulations);
    double std_2 = calcStdDev(arth_return_2,numSimulations);
    double sharpe_2 = mean_2 / std_2;

    double mean_3 = calcMean(arth_return_3,numSimulations);
    double std_3 = calcStdDev(arth_return_3,numSimulations);
    double sharpe_3 = mean_3 / std_3;

    cout<<"Strategy1: Expected Return = "<<mean_1<<" Volatility = "<<std_1<<" Sharpe Ratio = "<<sharpe_1<<endl;
    cout<<"Strategy2: Expected Return = "<<mean_2<<" Volatility = "<<std_2<<" Sharpe Ratio = "<<sharpe_2<<endl;
    cout<<"Strategy3: Expected Return = "<<mean_3<<" Volatility = "<<std_3<<" Sharpe Ratio = "<<sharpe_3<<endl;
}