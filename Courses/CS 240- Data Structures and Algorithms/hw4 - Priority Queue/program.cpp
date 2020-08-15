#include "CallCenter.h"
#include <iostream>
using namespace std;

void getUserInput();
//input: none
//output: none 
//side effects: get length and probability of call from user
void conductSim(int length,double probofcall);
//input: an integer, a double
//output: none 
//side effects: none

int main(){
	srand (time(NULL));
	getUserInput();

}

void getUserInput(){
	int length;
	double probofcall;
	cout<<"Enter simulation length: "<<endl;
	cin>>length;
	while(length<0){
		cout<<"Enter a length more than 0!"<<endl;
		cin>>length;
	}
	cout<<"Enter simulation rate: "<<endl;
	cin>>probofcall;
	while(probofcall<0.1||probofcall>1){
		cout<<"Enter a rate between 0.1 and 1!"<<endl;
		cin>>probofcall;
	}
	conductSim(length,probofcall);
}

void conductSim(int length,double probofcall){
	CallCenter cSim; //create a new callcenter object
	probofcall *=10;
	for(int i=0;i<length;i++){
		int x = rand()%10+1;
		if(x<=probofcall){
			cout<<"New obj cre"<<endl;
			Call cObj(i);//create a new call object and send it to Callcenter
			cSim.acceptCall(cObj);
		}
		cSim.displayCurStat();
		cSim.updateCallCenter();//update callcenter
	}
	cout<<endl<<length<<" minutes ended"<<endl<<endl;
	while(cSim.updateCallCenter()){
		cSim.displayCurStat();
	}
	cSim.displayResults();
}

