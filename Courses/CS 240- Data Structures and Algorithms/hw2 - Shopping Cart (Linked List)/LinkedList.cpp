#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList(){
	head=nullptr;
	num_of_items=0;
}

bool LinkedList::isEmpty() const{

	if(num_of_items==0){
		return true;
	}
	else{ return false;}
}

int LinkedList::getLength() const{
	
	return num_of_items;
}

bool LinkedList:: append(const ItemType& newEntry){
	
	Node* p= new Node;
	if(head==nullptr)	{
		p->data=newEntry;
		p->next=nullptr;
		head=p;
		num_of_items++;
		return true;
	}
	else{
		Node* curNod=head;
	
		while(curNod->next!=nullptr){
			curNod=curNod->next;
		}
			p->data=newEntry;
			p->next=nullptr;
			curNod->next=p;
			num_of_items++;
			return true;
		
	}
		

}
bool LinkedList :: insert(int newPos, const ItemType & newEntry){

	Node* newNod=new Node;
	Node* curNod= head;
	Node* preNod=head;
	
	for(int i=1;i<newPos;i++){
		curNod=curNod->next;
	}
	for(int j=1;j<newPos-1;j++){
		preNod=preNod->next;
	}

	if(head==nullptr){
		newNod->data=newEntry;
		newNod->next=nullptr;
		head=newNod;
		num_of_items++;
		return true;
	}
	else if(curNod==head){
		newNod->data=newEntry;
		newNod->next=curNod;
		head=newNod;
		num_of_items++;
		return true;
	}
	else{
		newNod->data=newEntry;
		newNod->next=curNod;
		preNod->next=newNod;
		num_of_items++;
		return true;
	}
	return false;	
		
}
bool LinkedList :: remove(int pos){
	Node* curNod=head;
	if(pos>getLength()){
		return false;
	}
	num_of_items--;
	for(int i=1;i<pos-1;i++){
		curNod=curNod->next;
	}
	if(pos==1){
		head=head->next;
		return true;
	}
	else{
		curNod->next=curNod->next->next;
		return true;
	}
	return false;
	
}

ItemType LinkedList :: retrieve(int position) const{
	ItemType item;
	Node* curNod=head;
	
	for(int i=1;i<position;i++){
		curNod=curNod->next;
	}
	if(curNod!=nullptr){
		item=curNod->data;
		return item;
	}
}

	
