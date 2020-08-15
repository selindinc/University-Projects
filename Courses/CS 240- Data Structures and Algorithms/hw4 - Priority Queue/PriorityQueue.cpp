#include "PriorityQueue.h"
#include <iostream>
#include<cassert>
using namespace std;


PriorityQueue::PriorityQueue(){
	head=nullptr;
	tail=nullptr;
	size=0;
}

PriorityQueue::~PriorityQueue(){
	delete head;			
}
PriorityQueue::PriorityQueue(const PriorityQueue& listToCopy){
	cout << "Constructor called." << endl;
	head=nullptr;
	size=0;
	Node* cur = listToCopy.head;
	Node* end = nullptr;
	
	while(cur){
		Node* n = new Node;
		n->data=cur->data;
		if(!head){
			head=n;
			end=head;
		}
		else{
			end->next=n;
			end=n;
		}
		cur=cur->next;
	}
	
	
	size=(listToCopy.size);

}

bool PriorityQueue::isEmpty() const{

	if(size==0){
		return true;
	}
	else{ return false;}
}
int PriorityQueue::getSize() const{
	
	return size;
}
bool PriorityQueue:: append(const ItemType& c){
	
	Node* p = new Node;
	p->data = c;
	p->next = nullptr;
	if(head == nullptr){
		head = p;
	}
	else{
		tail->next = p;
	}
	tail = p;
	size++;
		
	
}

bool PriorityQueue :: enqueue(int position, const ItemType & c){

	if(position < 1 or position > (size + 1)){
			return false;
		}	
		Node* newNode = new Node;
		newNode->data = c;
		if(position == 1){
			newNode->next = head;
			head = newNode;
		}
		else{
		   Node* p = head;
		   advanceTo(p, position - 1);
			newNode->next = p->next;
			p->next = newNode;
		}
		if(position == size + 1){
			tail = newNode;
		}
		size++;
		return true;
		
}
bool PriorityQueue :: dequeue(int position){
		if(position < 1 or position > size){
			return false;
		}
		Node* p = head;
		advanceTo(p, position - 1);
		if(p == head){
			head = head->next;
			delete p;
			if(head == nullptr){
				tail = nullptr;
			}
		}
		else{
			Node* del = p->next;
			p->next = p->next->next;
			delete del;
			if(position == size){
				tail == p;
			}
		}
		size--;
		return true;
}

ItemType PriorityQueue :: retrieve(int position) const{
	assert (position >= 1 and position <= size);
	Node* p = head;
	advanceTo(p, position);
	return p->data;
}
void PriorityQueue::advanceTo(Node* & p, int pos) const{
	for(int i = 1; i < pos; i++){
		p = p->next;
	}
}


