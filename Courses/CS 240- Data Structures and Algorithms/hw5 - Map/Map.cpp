#include <iostream>
#include "Map.h"
using namespace std;

	Map::Map(){
		Size=0;
		head=nullptr;
		tail=nullptr;
	}
	Map::~Map(){
		cout<<"Destructor called."<<endl;
		if(Size==0){
			delete head;
		}
		else{
			Node* n = head -> next;
			Node* h = head;
			while(n!=nullptr){
				delete (h->data).second;
				delete h;
				h = n;
				n=n->next;	
			}
			delete (h->data).second;
			delete h;
			delete n;
		}
	}
	
	Map Map :: operator=(Map& rhs){
		cout<<"Equals operator called."<<endl;
		if(Size==0){
			delete head;
		}
		else{
			Node* a = head -> next;
			Node* h = head;
			while(a!=nullptr){
				delete (h->data).second;
				delete h;
				h = a;
				a=a->next;	
			}
			delete (h->data).second;
			delete h;
			delete a;
		}
		head=nullptr;
		tail=nullptr;
		Node* n=rhs.head;
		while(n){
			KeyType s=(n->data).first;
			ValueType d= new string(*(n->data).second);
			add(make_pair(s,d));
			n=n->next;
		}
		Size=rhs.Size;
		return rhs;
	
	}
	Map::Map(const Map &m){
		cout<<"Copy constructor called."<<endl;
		head=nullptr;
		tail=nullptr;
		Node* n=m.head;
		while(n){
			KeyType s=(n->data).first;
			ValueType d= new string(*(n->data).second);
			add(make_pair(s,d));
			n=n->next;
		}
		Size=m.Size;
		
	}
	bool Map::empty() const{
		if(Size==0){
			return true;
		}
		return false;
	}

		 
	int Map::size() const{
		return Size;
	}


	bool Map::add(ElementType element){
		if(find(element.first)){
			return false;
		}
		Node* p = new Node;
		p->data = element;
		p->next = nullptr;
		if(head == nullptr){
			head = p;
		}
		else{
			tail->next = p;
		}
		tail = p;
		Size++;
		return true;
		
	
	}

		 
	bool Map::find(KeyType key) const{
		Node* p = head;
		if(Size!=0){
			while(p!=nullptr){
				if((p->data).first==key){
			
					return true;
				}
				p=p->next;
			}
		}
		return false;	
	}

	ValueType Map::retrieve(KeyType key) const{
		Node* p = head;
		advanceTo(p, key);
		if(p!=nullptr){
			return (p->data).second;
		}
		else{
			return nullptr;
		}
	}

	bool Map::remove(KeyType key){
		if(!find(key)){
			return false;
		}
		Node* p = head;//prev key
		Node* s = head->next;//key
		if((head->data).first==key){
			delete (head->data).second;
			delete head;
			head=s;
			Size--;
			return true;	
		}
		while((s->data).first != key){
			p = p->next;
			s = s->next;

		}


		Node* del = p->next;
		p->next = p->next->next;
		delete (del->data).second;
		delete del;
		if(s == nullptr){
			tail = p;
		}
		
		Size--;
		return true;


	}
	void Map::advanceTo(Node* & p, KeyType key) const{
		for(int i = 1; i <= Size; i++){
			if((p->data).first==key){
				i=Size;
			}
			else{
				if( p->next!=nullptr){ 
				
				p = p->next;}
			}
		}
	}

	void Map::displayAll() const{
		if(Size==0){
			cout<<"Map is empty! "<<endl;
		}
		else{
			Node* n=head;
			ElementType element;
			for(int i=0;i<Size;i++){
				element=n->data;
				cout<<"Key: "<<element.first<<" Value: "<<*element.second<<endl;
				n=n->next;
			}
		}
		
	}
				

		

