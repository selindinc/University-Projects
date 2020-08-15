#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

string getInput();
//input: none
//output: returns user's filename
//side effects: prompts user and reads input

double avgNumWordsPerNonBlankLine(int numOfWords,int numOfNonBlankLines);
//input: number of the words, number of the non blank lines
//output: returns average number of words per non blank line
//side effects: none

bool isAlphas(string word);
//input: a string word from data
//output: returns if the string is word or not
//side effects: none

double avgAlphasPerWord(int numOfAlphas,int numOfWords);
//input: number of alphas,number of words
//output: returns average number of alphas per word
//side effects: none

void displayResult(int numOfNonBlankLines, int numOfWords,int numOfAlphas);
//input: number of non blank lines,number of words, number of alphas
//output: displays results
//side effects: none


int main(){

	ifstream inFS;
	string line;
	string word;
	vector<string> data;	
	int numOfNonBlankLines=0;
	int numOfWords=0;
	int w=0;
	double Average1;
	int numOfAlphas=0;
	
	
	string filename=getInput();
	inFS.open(filename); //Try to open file
	if(!inFS.is_open()) { //Check if file opened
		cout<<"Could not open file "<<filename<<endl;
		return 1;
	}
	
	while(getline(inFS,line)){

			istringstream inSS(line);
			data.push_back(line);//write data to a vector
			if(line.size()!=0){ 
				numOfNonBlankLines++;
				if(!isAlphas(line)){
					numOfNonBlankLines--;
				}
			}
			while(inSS>>word){
				if(isAlphas(word)){
					numOfWords++;
				}
				for(int i=0;i<word.size();i++){
					if(isalpha(word.at(i))){
						numOfAlphas++;
					}
				}
			}
	}
	inFS.close();
	displayResult(numOfNonBlankLines, numOfWords, numOfAlphas);
}
string getInput(){

	string filename = ""; // Input filename

	cout<< "Enter filename: "<<endl; //Prompt user for filename
	cin>> filename;

	return filename;
}

bool isAlphas(string word){

	char alpha;
	unsigned int i;
	for(i=0;i<word.size();i++){
		alpha=word.at(i);
		if(isalpha(alpha)){
			return true;
		}
	}
	return false;
}

double avgNumWordsPerNonBlankLine(int numOfWords,int numOfNonBlankLines){

	double avgWordsNonBlankLine= numOfWords*1.0/numOfNonBlankLines;
	return avgWordsNonBlankLine;
}

double avgAlphasPerWord(int numOfAlphas,int numOfWords){

	double avgWordsNonBlankLine= numOfAlphas*1.0/numOfWords;
	return avgWordsNonBlankLine;
}

void displayResult(int numOfNonBlankLines, int numOfWords, int numOfAlphas){

	double Average1, Average2;

	Average1=avgNumWordsPerNonBlankLine(numOfWords,numOfNonBlankLines);
	Average2=avgAlphasPerWord(numOfAlphas,numOfWords);

	cout<<"Number of non blank lines: "<<numOfNonBlankLines<<endl;
	cout<<"Number of words: "<< numOfWords<< endl;
	cout<<"Number of alphas: "<<numOfAlphas<<endl;
	cout<<"Average words/non-blank line: "<<Average1<<endl;
	cout<<"Average alphas/word: "<<Average2<<endl;
}

