#include "Call.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

Call::Call(){
	int p = rand()%10;
	if(p==0){
		Pri=1;
	}
	else if(p==1||p==2||p==3){
		Pri=2;
	}
	else{
		Pri=3;
	}
	atime=0;
	int c=(rand()%6)+3;
	ctime=c;
	answtime=0;
	
}
	
Call :: Call(int arrive){

	int p = rand()%10;
	if(p==0){
		Pri=1;
	}
	else if(p==1||p==2||p==3){
		Pri=2;
	}
	else{
		Pri=3;
	}
	atime=arrive;
	int c=(rand()%6)+3;
	ctime=c;
	answtime=0;
	
}

Call :: Call(const Call& c){

	Pri=c.Pri;
	atime=c.atime;
	ctime=c.ctime;
	answtime=c.answtime;
	
}

void Call::SetArrivalTime(int t){
	atime=t;
	return;
}

void Call::SetAnswTime(int t){
	answtime=t;
	return;

}

int Call::GetCallTime() {
	return ctime;
}

int Call::GetArrivalTime() {
	return atime;
}

int Call::GetPriority(){
	return Pri;	
}
int Call::GetAnswTime(){
	return answtime;
}
bool Call:: operator< (const Call& c) {
	if(Pri<c.Pri){
		return true;
	}
	else{
		return true;
	}
	
}
bool Call:: operator> (const Call& c) {
	if(Pri>c.Pri){
		return true;
	}
	else{
		return true;
	}
	
}
bool Call:: operator== (const Call& c) {
	if(Pri==c.Pri){
		return true;
	}
	else{
		return false;
	}
	
}
bool Call:: operator!= (const Call& c) {
	if(Pri!=c.Pri){
		return true;
	}
	else{
		return false;
	}
	
}



