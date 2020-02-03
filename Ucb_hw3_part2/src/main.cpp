#include <math.h>
#include <iomanip> 
using namespace std;
#include <iostream>
#include <random>
#include <ctime>
#include "StrategyAnalyzer.h"

int main()
{
    StrategyAnalyzer sa1(1000000,0.08,0.16,0.02,7.34,5.38);
    sa1.writeResults("sa1.csv");
    sa1.analyzeReturns();

    StrategyAnalyzer sa2(1000,0.08,0.16,0.02,7.34,5.38);
    sa2.writeResults("strategy.csv");
    // sa2.analyzeReturns();
    return 0;
}