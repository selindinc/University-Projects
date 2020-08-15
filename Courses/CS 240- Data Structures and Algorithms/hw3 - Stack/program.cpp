#include "Stack.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <iomanip>

using namespace std;

string getInput();
//input: none
//output: returns user's filename
//side effects: prompts user and reads input
int openFile();
//input: none
//output: returns 1 if file could not open else 0
//side effects: none
double mult(double operand1,double operand2);
//input: two doubles
//output: returns the result of multiplication
//side effects: none
double substract(double operand1,double operand2);
//input: two doubles
//output: returns the result of substraction
//side effects: none
double add(double operand1,double operand2);
//input: two doubles
//output: returns the result of addition
//side effects: none
double division(double operand1,double operand2);
//input: two doubles
//output: returns the result of division
//side effects: none
int getResult(vector<string> vec,double result);
//input: a vector and a double
//output: none
//side effects: outputs the result of evaluating
double lookStack(vector<string> vec);
//input: a vector
//output: returns the result
//side effects: none

int main(){
	
	string filename;
	int i = openFile();
	
	
	if(i == 1){
		cout<<"Could not open file "<<filename<<endl;
		return 1;
	}
	
	return 0;
}

string getInput(){
	string filename = "";
	cout<<"Enter filename: "<<endl;
	cin>>filename;

	return filename;
}

int openFile(){
	ifstream inFS;
	istringstream inSS;
	string filename=getInput();
	string line;
	string token;
	vector<string> vec;
	double result;
	
	inFS.open(filename);
	if(!inFS.is_open()){
		return 1;
	}
	while(getline(inFS,line)){
		if(line.size()!=0){ 
			inSS.clear();
			inSS.str(line);
			while(inSS>>token){
				vec.push_back(token);
			}
			result = lookStack(vec);

			getResult(vec,result);
			vec.clear();
		}
	}
	return 0;
}


double lookStack(vector<string> vec){
	Stack stack;
	double operand1=0,operand2=0;
	stringstream libra;
	char oprtr;
	double num, result;

	for(int i=0;i<vec.size();i++){
		string first=vec.at(i);
		oprtr=first.at(first.size()-1);
		string s;
		libra.str(vec.at(i));
		libra>>num;
		libra.clear();
		if(isdigit(oprtr)){
			stack.push(num);
		}
		else if(ispunct(oprtr)){
			if(oprtr=='*'){
				operand1=stack.pop();
				operand2=stack.pop();
				result = mult(operand1,operand2);
				stack.push(result);
			}
			else if(oprtr=='-'){
				operand1=stack.pop();
				operand2=stack.pop();
				result = substract(operand1,operand2);
				stack.push(result);
			}
			else if(oprtr=='+'){
				operand1=stack.pop();
				operand2=stack.pop();
				result = add(operand1,operand2);
				stack.push(result);
			}
			else if(oprtr=='/'){
				operand1=stack.pop();
				operand2=stack.pop();
				result = division(operand1,operand2);
				stack.push(result);
			}
		}
	}
	result = stack.pop();
	return result;
}
			
double mult(double operand1,double operand2){
	double result=operand1*operand2;	
	return result;
}
double substract(double operand1,double operand2){
	double result=operand2-operand1;
	return result;
}
double add(double operand1,double operand2){
	double result=operand1+operand2;
	return result;
}
double division(double operand1,double operand2){
	double result=operand2/operand1;
	return result;
}			


int getResult(vector<string> vec,double result){
	ofstream outFS;
	outFS.clear();
	outFS.open("myoutfile.txt",std::ios_base::app);
	if(!outFS.is_open()){
		cout<<"Could not open file myoutfile.txt."<<endl;
		return 1;
	}
	outFS<<"The result of evaluating:";
	for(int i=0; i<vec.size(); i++){
		outFS<<" "<<vec.at(i);
	}
	outFS<<" is "<<fixed<<setprecision(1)<<result<<endl;
	outFS.close();
}
	
	
	

		
	
