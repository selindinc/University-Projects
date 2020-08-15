#include<iostream>
#include<utility>
#include <string>
#include "map.h"
using namespace std;

void testMap(Map  mymap);
//input: a map object
//output: none
//side effects: displays Size and if map is empty or not



int main(){
	Map mymap;
		
	testMap(mymap);		

	return 0;
}



void testMap(Map  mymap){

	Map smap;
	Map dmap;

	mymap.remove(1);
	mymap.retrieve(2);
	
	
	mymap.add(make_pair(3, new string("Selin Sulugoz")));
	
	mymap.add(make_pair(4, new string("Sinem Simit <3")));
	
	mymap.add(make_pair(5, new string("Egemen Ananas")));

	mymap.add(make_pair(2,new string("Misa <3")));
	
	mymap.add(make_pair(1,new string("ATK !!!!")));

	mymap.add(make_pair(6,new string("OABB ?")));

	
	mymap.displayAll();
	cout<<"Height: "<<mymap.height()<<endl;


	smap.add(make_pair(1, new string("S")));
	
	smap.add(make_pair(2, new string("<3")));

	smap.displayAll();
	cout<<"Height: "<<smap.height()<<endl;

	smap=mymap;
	smap.displayAll();
	
	

	cout<<"Size: "<<smap.size()<<endl;

	cout<<"1= "<<*smap.retrieve(1)<<endl;
	cout<<"2= "<<*smap.retrieve(2)<<endl;
	cout<<"3= "<<*smap.retrieve(3)<<endl;
	cout<<"4= "<<*smap.retrieve(4)<<endl;

	
	smap.remove(1);
	if(smap.find(3)){
		cout<<"Key found!"<<endl;
	}
	else{
		cout<<"Key could not found!!!!!"<<endl;
	}

	
	if(smap.empty()){
		cout<<"Empty!"<<endl;
	}
	else{
		cout<<"Not empty!"<<endl;
	}
	

	smap.displayAll();
	cout<<"Size: "<<smap.size()<<endl; 

	
	smap.remove(2);
	smap.remove(4);
	if(smap.find(4)){
		cout<<"Key found!"<<endl;
	}
	else{
		cout<<"Key could not found!!!!!"<<endl;
	}
		

	if(smap.empty()){
		cout<<"Empty!"<<endl;
	}
	else{
		cout<<"Not empty!"<<endl;
	}

	smap.remove(3);
	smap.remove(6);
	smap.remove(5);

	if(smap.empty()){
		cout<<"Empty!"<<endl;
	}
	else{
		cout<<"Not empty!"<<endl;
	}
	
	cout<<"Size: "<<smap.size()<<endl;
	smap.displayAll();


}


