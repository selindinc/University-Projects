#include "CallCenter.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

CallCenter::CallCenter(){
	PriorityQueue waitList;
	Call call;//
	systime=0;
	wtime=0;
	pri1=0;
	pri2=0;
	pri3=0;
	num1=0;
	num2=0;
	num3=0;
	calltime=0;
	numCallsAnsw=0;
	totcalltime=0;
	
}

bool CallCenter::acceptCall(Call c){
	if (waitList.getSize()==0){
		waitList.enqueue(1,c);
		return true;
	}
	else {
		
		for(int i=1;i<=waitList.getSize();i++){
			if(c<waitList.retrieve(i)){
				if(c.GetPriority()==1){
					waitList.enqueue(i,c);	
					num1++;
					pri1++;
					return true;
				}
				else if(c.GetPriority()==2){
					waitList.enqueue(i,c);
					num2++;
					pri2++;
					return true;
				}
			}
			if(c.GetPriority()==3){
				waitList.enqueue(waitList.getSize(),c);
				num3++;
				pri3++;
				return true;
			}
		}
	}
	
	return false;
}	
		
bool CallCenter::updateCallCenter(){
	systime++;
	if(calltime<=0 && waitList.getSize()==0){return false;}
	if(waitList.getSize()!=0){
		Call c= waitList.retrieve(1);
		if(calltime<=0){
			calltime = c.GetCallTime();
			wtime+=c.GetArrivalTime()-c.GetAnswTime();
			waitList.dequeue(1);
			c.SetAnswTime(1);
			totcalltime+=c.GetCallTime();
			numCallsAnsw++;
		}
	}
	calltime--;

	return true;
}
int CallCenter::GetSysTime() const{
	return systime;
}
int CallCenter::GetTotCallTime() const{
	return totcalltime;
}
		
	
void CallCenter::displayResults() const{
	double avrg=0;
	double avrg1=0;
	double avrg2=0;
	double avrg3=0;

	if(numCallsAnsw!=0){
		avrg=wtime*1.0/numCallsAnsw;
	}
	if(pri1!=0){
		avrg1=num1*1.0/pri1;
	}
	if(pri2!=0){
		avrg2=num2*1.0/pri2;
	}
	if(pri3!=0){
		avrg3= num3*1.0/pri3;
	}
	cout<<endl<<"Total number of calls entered and answered: "<<numCallsAnsw<<endl;
	cout<<"Total time taken to answer calls: "<<totcalltime<<endl;
	cout<<"Average waiting time for a call to be answered: "<<avrg<<endl;
	cout<<"Average wait time for priority 1 calls: "<<avrg1<<endl;
	cout<<"Average wait time for priority 2 calls: "<<avrg2<<endl;
	cout<<"Average wait time for priority 3 calls: "<<avrg3<<endl<<endl;
}

void CallCenter::displayCurStat() const{
	if(systime%5==0){
		cout<<"Current simulation time: "<<systime<<endl;
		cout<<"Number of calls in the waiting list: "<<waitList.getSize()<<endl;
		cout<<"Number of calls completed: "<< numCallsAnsw  <<endl<<endl;
	}
}
	









