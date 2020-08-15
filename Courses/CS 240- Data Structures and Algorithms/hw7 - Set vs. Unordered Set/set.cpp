#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include<set>
#include<ctime>
using namespace std;

string getInput();
//input: none
//output: returns user's filename
//side effects: prompts user and reads input
ifstream openFile();
//input: none
//output: returns inFS
//side effects: none
set<string> ReadWriteInput(set<string> s);
//input: set
//output: returns set
//side effects: none
int ReadDetermineSpam(set<string> s,int& numGood);
//input: set and reference to number of good IPs
//output: returns number of bad IP addresses
//side effects: none
int ReadDetermineRemoveBad(set<string> s);
//input: set
//output: returns number of removed IPs
//side effects: none



int main(){
	set<string> s;
	string filename;
	int numGood=0;
	
	clock_t ticks;
	ticks=clock();
	
	s=ReadWriteInput(s);
	if(s.count("-1")>0){
		cout<<"File not opened."<<endl;
		return 1;
}
	int bads = ReadDetermineSpam(s,numGood);
	if(bads == -1){
		cout<<"File not opened."<<endl;
		return 1;
	}
	int removes=ReadDetermineRemoveBad(s);
	if(removes == -1){
		cout<<"File not opened."<<endl;
		return 1;
	}

	ticks=clock()-ticks;
	float seconds = (float)ticks/CLOCKS_PER_SEC;
	
	int spammers = s.size();

	cout<<"Number of known spammer IP addresses: "<< spammers <<endl;
	cout<<"Number of good IP addresses found: "<<numGood<<endl;
	cout<<"Number of bad IP addresses found: "<< bads <<endl;
	cout<<"Number of IP addresses removed from the set of known spammers: "<< removes <<endl;
	cout<<"Amount of time taken to run the program: "<< seconds <<endl;

	return 0;
	
	
}

string getInput(){

	string filename = ""; // Input filename

	cout<< "Enter filename: "<<endl; //Prompt user for filename
	cin>> filename;

	return filename;
}

ifstream openFile(){
	ifstream inFS;
	istringstream inSS;
	string filename=getInput();
	inFS.open(filename);
	return inFS;
}

set<string> ReadWriteInput(set<string> s){

	ifstream inFS = openFile();
	if(!inFS.is_open()){
		s.emplace("-1");
		return s;
	}
	else{
		string line;
		inFS.clear();
		while(getline(inFS,line)){
				s.emplace(line);
				inFS.clear();
		}
		inFS.close();
		return s;
	}

}
int ReadDetermineSpam(set<string> s, int& numGood){

	ifstream inFS = openFile();
	if(!inFS.is_open()){
		return -1;
	}
	else{
		string line;
		int bad=0;
		int good=0;
		inFS.clear();
		while(getline(inFS,line)){
			if(s.count(line)!=0){
				bad++;
			}
			else{
				good++;
			}
			inFS.clear();
		}
		numGood=good;
		return bad;
	}
}
	
int ReadDetermineRemoveBad(set<string> s){
	
	ifstream inFS = openFile();
	if(!inFS.is_open()){
		return -1;
	}
	else{
		string line;
		int removed=0;
		inFS.clear();
		while(getline(inFS,line)){	
			if(s.count(line)!=0){
				removed++;
				s.erase(line);
			}
			inFS.clear();
		}
		return removed;
	}
}
					
					
					
					
			
	
	














