#include "Stack.h"
#include<iostream>
using namespace std;


Stack::Stack(){
	top=nullptr;
	size=0;
}

Stack::~Stack(){
	Node * temp;
	while(top != nullptr){
		temp = top;
		top = top->next;
		size--;
		delete temp;
	}			
}
bool Stack::isEmpty() const{

	if(size==0){
		return true;
	}
	else{ return false;}
}
int Stack::getLength() const{
	
	return size;
}
void Stack::push(double x){
	
	Node* newNode=new Node;
	Node* curNode=top;

	if(top==nullptr){
		newNode->data=x;
		newNode->next=nullptr;
		top=newNode;
		size++;
		
	}
	else if(curNode==top){
		newNode->data=x;
		newNode->next=curNode;
		top=newNode;
		size++;
		
	}
	
}
double Stack::pop(){
	Node* p=top;
	double t=top->data;
	top=top->next;
	delete p;
	size--;
	return t;
}
double Stack::peek() const{
	
	double t= top->data;
	return t;
}
	
	


	
	
















