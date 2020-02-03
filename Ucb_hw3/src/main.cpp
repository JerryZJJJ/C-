#include <iostream>
#include <math.h>
#include <iomanip> 
using namespace std;

const double Epsilon = 1e-10;

bool isZero(double x){
    return fabs(x) < Epsilon;
}

double f(double x){
    return (x+2.0)*(x-3.0)*(x-5.0)*(x+5.0);
}

double f_prime(double x){
    return 4*pow(x,3) - 68*x;
}

double FindRootBisection(double x, int iterations){
    double f0 = f(x);
    double x0 = x;
    double x1 = f0>0?4:-6;
    int i = 0;

    double f2 = 1;
    double x2;

    if (f0 > 0) {
        x0 = x1;
        x1 = x;
    }

    while (!isZero(f2) && i < iterations){
        x2 = 0.5*(x0+x1);
        // cout<<x2<<endl;
        f2 = f(x2);
        if (f2<0){
            x0 = x2;
        }else{
            x1 = x2;
        }
        i += 1;
    }
    
    return x2;
}

double FindRootNewtoon(double a, int iterations){
    double f0 = f(a);
    double x0 = a;
    int i = 0;
    while (!isZero(f0) && i < iterations){
        double fp = f_prime(x0);
        if (fabs(fp) > 1e-10){
            x0 = x0 - f0/fp;
            f0 = f(x0);
        }else{
            break;
        }
        i += 1;
        // cout << i <<endl;
    }
    return x0;
}

//Secant Method
double FindRootSecant(double a, int iterations){
    double x0 = a;
	double x1 = a + 0.25;
    double f0 = f(x0);
    double f1 = f(x1);
    int i = 0;
	
    while (!isZero(f0) && i<iterations) {
		double df = f0-f1;
		double dx = x0-x1;
		if (!isZero(df)) {
			double x = x1 - f1*(dx/df);

			f0 = f1;
			x0 = x1;
			x1 = x;
			f1 = f(x1);
		} else {
			break;
		}
        i += 1;
    }
    return x0;
}

int main() {
    double start_points[] = {-12,4.3,-2.2,8};
    int interation[] = {5,20,50};
    for (int j = 0;j<3;j++){
        double Iterations = interation[j];
        cout<<"Iterations = "<<Iterations<<endl;
        for (int i = 0;i<4;i++){
            double es_root_bisection = FindRootBisection(start_points[i],Iterations);
            double es_root_newton = FindRootNewtoon(start_points[i],Iterations);
            double es_root_secant = FindRootSecant(start_points[i],Iterations);
            cout<<"start points = "<<start_points[i]<<" estimated root r (Bisection) = "<<es_root_bisection<<" f(r) = "<<f(es_root_bisection)<<endl;
            cout<<"start points = "<<start_points[i]<<" estimated root r (Newton) = "<<es_root_newton<<" f(r) = "<<f(es_root_newton)<<endl;
            cout<<"start points = "<<start_points[i]<<" estimated root r (Secant) = "<<es_root_secant<<" f(r) = "<<f(es_root_secant)<<endl;
            cout<<endl;
        }
    }
}


