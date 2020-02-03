#include <iostream>
using namespace std;
double calcCallIntrinsicValue(double spot, double strike){
	double diff = spot - strike;
	if (diff >0){
		return diff; 
	} else {
		return 0;
	}	 
}

double calcPutIntrinsicValue(double spot, double strike){
	double diff = strike - spot;
	if (diff >0){
		return diff; 
	} else {
		return 0;
	}
}

int main() {
	double spot,strike;
	cout<<"Task i:User input"<<endl;
	cout<<"Please first entrer the spot price:";
	cin>>spot;
	cout<<"Please enter the strike price:";
    cin>>strike;
	
	double intri_call = calcCallIntrinsicValue(spot,strike);
	double intri_put = calcPutIntrinsicValue(spot,strike);
	
	cout<<"Intrisic value for call is : "<<intri_call<<endl;
	cout<<"Intrisic value for put is : "<<intri_put<<endl;
	cin.get();
	
	cout<<"Task ii:"<<endl;
	for (int i =85;i<=115;i++){
		cout<<"Spot: "<<i<<", Strike: 100, Intrisic value for call: "<<calcCallIntrinsicValue(i,100)<<", Intrisic value for put: "<<calcPutIntrinsicValue(i,100)<<endl;		
	}
	cout<<"\n";
	cin.get();
	

	cout<<"Task iii:"<<endl;
	for (int j =90;j<=110;j++){
		cout<<"Spot: 105, Strike: "<<j<<", Intrisic value for call: "<<calcCallIntrinsicValue(105,j)<<", Intrisic value for put: "<<calcPutIntrinsicValue(105,j)<<endl;		
	}
	cout<<"\n";
	cin.get();

	cout<<"Task iv: "<<endl;
	cout<<"Please enter flag 0/1: ";
	int flag;
	cin>>flag;
	if (flag == 0){
		double spot_4;
		cout<<"Please input a spot price: ";
		cin>>spot_4;
		cout<<"Spot: "<<spot_4<<", Strike: 100, Intrisic value for put: "<<calcPutIntrinsicValue(spot_4,100)<<endl;
	} else if(flag ==1){
		double strike_4;
		cout<<"Please input a spot price: ";
		cin>>strike_4;
		cout<<"Spot: 63.50, Strike"<<strike_4<<", Intrisic value for put: "<<calcCallIntrinsicValue(63.50,strike_4)<<endl;
	} else {
		cout <<"Invalid input!"<<endl;
	}
	
	
	
	
	
}





























