#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "ShoppingCart.h"
#include "ItemToPurchase.h"
#include "LinkedList.h"


using namespace std;

string getInput();
//input: none
//output: returns user's filename
//side effects: prompts user and reads input
void openFile();
//input: none
//output: void
//side effects: none
int splitLineToWords();
//input: none
//output: return int to test file
//side effects: none
bool performOperationA1();
//input: none
//output: return true, return false
//side effects: none
bool performOperationA2();
//input: none
//output: return true, return false
//side effects: none
bool performOperationR();
//input: none
//output: return true, return false
//side effects: none
bool performOperationDPos();
//input: none
//output: return true, return false
//side effects: none
bool performOperationDA();
//input: none
//output: return true, return false
//side effects: none
bool performOperationDCPos();
//input: none
//output: return true, return false
//side effects: none
bool performOperationDC();
//input: none
//output: return true, return false
//side effects: none
bool performOperationDN();
//input: none
//output: return true, return false
//side effects: none


vector<string> word;
ShoppingCart cart;

int main(){
	openFile();
	
}

string getInput(){

	string filename = ""; // Input filename

	cout<< "Enter filename: "<<endl; //Prompt user for filename
	cin>> filename;

	return filename;
}
void openFile(){
	ifstream inFS;
	int i = splitLineToWords();
	inFS.close();
	if(i == 1){cout<<"Empty file."<<endl;}
}
	
int splitLineToWords(){
	ifstream inFS;
	istringstream inSS;
	string line;
	int a=0;
	string file=getInput();
	inFS.open(file);
	while(getline(inFS,line)){			
		if(line.size()!=0){ 
			inSS.clear();
			inSS.str(line);	
			string temp;
			int i=0;
			while(inSS>>temp){
				word.push_back(temp);
			if(word.size()!=0){
				a=1;
			}	
				i++;
			}
			
			performOperationA1();
			performOperationA2();
			performOperationR();
			performOperationDPos();
			performOperationDA();
			performOperationDCPos();
			performOperationDC();
			performOperationDN();
			word.clear();
		}
	
		
	}
	if(a==0){return 1;}
	return 0;
}
bool performOperationA1(){
	int quant;
	double prays;
	stringstream libra;
	if(word.at(0)=="A"&& word.size()==4){
		ItemType s;
		s.SetName(word.at(1));
		libra.str(word.at(2));
		libra>>quant;
		s.SetQuantity(quant);
		libra.clear();
		libra.str(word.at(3));
		libra>>prays;
		s.SetPrice(prays);
		cart.AddItemToEnd(s);	
		libra.clear();
		return true;
				
	}
	return false;
}	


bool performOperationA2(){
	stringstream libra;
	if(word.at(0)=="A"&& word.size()==5){
		ItemType s;
		s.SetName(word.at(1));
		libra.str(word.at(2));
		int quant;
		libra>>quant;
		s.SetQuantity(quant);
		libra.clear();
		libra.str(word.at(3));
		double prays;
		libra>>prays;
		s.SetPrice(prays);
		libra.clear();
		libra.str(word.at(4));
		int pos;
		libra>>pos;
		cart.AddItemToPos(pos,s);
		libra.clear();	
		return true;
	}
	return false;
}
bool performOperationR(){
	if(word.at(0)=="R"){
		int r;
		stringstream libra(word.at(1));
		libra>>r;
		cart.RemoveItem(r);
		return true;
	}
	return false;
}
bool performOperationDPos(){
	if(word.at(0)=="D"&&word.size()==2){
		
		int d;
		stringstream libra(word.at(1));
		libra>>d;
		cart.GetItemPos(d);
		return true;
	}	
	return false;
}
bool performOperationDA(){
	if(word.at(0)=="DA"){
		cart.GetItems();
		return true;
	}
	return false;

}
bool performOperationDCPos(){
	if(word.at(0)=="DC"&&word.size()==2){
		
		int dc;
		stringstream libra(word.at(1));
		libra>>dc;
		cart.GetTotalCostPos(dc);
		return true;
	}
	return false;
}
bool performOperationDC(){
	
	if(word.at(0)=="DC"&&word.size()==1){
		cart.GetTotalCost();
		return true;
	}
	return false;	
}
bool performOperationDN(){
	if(word.at(0)=="DN"){
		cart.GetNumbOfItems();
		return true;
	}
	return false;
}
 

