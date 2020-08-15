#include <iostream>
#include "map.h"
using namespace std;


Map::Map(){

	Size=0;
	root=nullptr;

}

Map::~Map(){
	Node* p=root;
	Size=0;
	Clear(p);// call recursive helper method

	
}

bool Map::Clear(Node* & p){
	if(p==nullptr){
		return false;
	}
	Clear(p->left);
	Clear(p->right);
	delete (p->data).second;
	delete p;
	return true;
}
Map::Map(const Map &m){

	root=nullptr;
	Node*n = m.root;
	Size=0;
	AddCopy(n);
	Size=m.Size;

}

bool Map::AddCopy(Node* & p){

	if(p==nullptr){
		return false;
	}
	KeyType k = (p->data).first;
	ValueType v = new string (*(p->data).second);
	add(make_pair(k,v));

	AddCopy(p->left);
	AddCopy(p->right);
	return true;
}
	


Map Map::operator=(Map& rhs){
	if(Size==0){
		delete root;
	}
	else{
		Node* n= root;
		Clear(n);
	}
	root=nullptr;
	Node* s=rhs.root;
	AddCopy(s);
	Size=rhs.Size;
	return rhs;

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
		delete element.second;
		return false;
	}

	Node* p = new Node;
	p->data = element;
	p->left = nullptr;
	p->right=nullptr;
	if(root == nullptr){
		root = p;
	}
	else{
		Node* curnode = root;
		
		while(curnode!=nullptr){
			if(element.first < (curnode->data).first){
				if(curnode->left==nullptr){
					curnode->left=p;
					curnode=nullptr;
			
				}
				else{
					curnode=curnode->left;

				}
			}
			else{
				if(curnode->right==nullptr){
					curnode->right=p;
					curnode=nullptr;
		
				}
				else{
					curnode=curnode->right;
				}
			}
		}
	}
	Size++;
	return true;
}


bool Map::find(KeyType key) const{

	Node* cur=root;
	while(cur!=nullptr){
		if(key==(cur->data).first){
			return true;
		}
		else if(key<(cur->data).first){
			cur=cur->left;
		}
		else{
			cur=cur->right;
		}
		return false;
	}
}



ValueType Map::retrieve(KeyType key) const{

	Node* cur=root;
	while(cur!=nullptr){
		if(key==(cur->data).first){
			return (cur->data).second;
		}
		else if(key<(cur->data).first){
			cur=cur->left;
		}
		else{
			cur=cur->right;
		}	
	}
	return nullptr;
}

bool Map::remove(KeyType key){

	Node* parent = root;
	Node* cur = root;
	
	while(cur!=nullptr){
		if((cur->data).first==key){
			if(cur->left==nullptr && cur->right==nullptr){
				if(cur == root){
					root=nullptr;
				}
				else if(parent->left==cur){
					parent->left=nullptr;
				}
				else{
					parent->right=nullptr;
				}
				delete (cur->data).second;
				delete cur;
			}
			else if(cur->left!=nullptr && cur->right==nullptr){
				if(cur == root){
					root=cur->left->left;
				}
				else if(parent->left==cur){
					parent->left=cur->left;
				}
				else{
					parent->right=cur->left;
				}
				delete (cur->data).second;
				delete cur;
			}
			else if(cur->left==nullptr && cur->right){
				if(cur == root){
					root=cur->right;
				}
				else if(parent->left==cur){
					parent->left=cur->right;
				}
				else{
					parent->right=cur->right;
				}
				delete (cur->data).second;
				delete cur;
			}
			else{
				Node* suc=cur->right;
				while(suc->left!=nullptr){
					suc=suc->left;
				}
				cur=suc;
				remove((suc->data).first);
			}
			Size--;
			return true;
		}
		else if((cur->data).first < key){
			parent=cur;
			cur=cur->right;
		}
		else{
			parent=cur;
			cur=cur->left;
		}
	}
	return false;
}


int Map::height() const{
	Node* p = root;
	int Height=treeHeight(p);
	return Height;

}

int Map::treeHeight(Node* p) const{
	if(p==nullptr){
		return -1;
	}
	int hleft = treeHeight(p->left);
	int hright = treeHeight(p->right);

	if(hleft>hright){
		return hleft+1;
	}
	else{
		return hright+1;
	}
}
	

void Map::displayAll() const{
	if(Size==0){
		cout<<"Tree is empty!"<<endl;
	}
	else{
		Node* cur = root;
		display(cur);
	}
}
bool Map::display(Node* cur) const{

	if(cur==nullptr){
		return false;
	}
	display(cur->left);
	cout<<"Key: "<<(cur->data).first<<" Value: "<<*(cur->data).second<<endl;
	display(cur->right);
	return true;
}





