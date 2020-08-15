#include "ShoppingCart.h"
#include <string>
#include <iostream>
using namespace std;

ShoppingCart::ShoppingCart(){

	LinkedList cart;

}

bool ShoppingCart:: AddItemToEnd(ItemType newItem){
	if(cart.append(newItem)){
		cout<<"Item added"<<endl;
		return true;
	}
	return false;		
}


bool ShoppingCart:: AddItemToPos(int pos, ItemType newItem){
	if(cart.insert(pos,newItem)){
		cout<<"Item added at position "<<pos<<endl;
		return true;
	}
	return false;
}


bool ShoppingCart:: RemoveItem(int pos){
	if(pos>cart.getLength()){
		cout<<"Position is out of bound!"<<endl;
		return false;
	}
	else if(cart.remove(pos)){
		cout<<"Item at position "<<pos<< " removed."<<endl;
		return true;
	}
	
}


void ShoppingCart:: GetItemPos(int pos) const{
	ItemType item=cart.retrieve(pos);
	cout<< item.GetItemInfo() <<endl;
	

}

void ShoppingCart:: GetItems() const{
	if(cart.getLength()==0){
		cout<<"There are no items."<<endl;
	}
	else{
		cout<< "Items: "<<endl;
		for(int i=1;i<cart.getLength()+1;i++){
			ItemType item =cart.retrieve(i);
			cout<<i<<". "<< item.GetItemInfo()<<endl;
		}
	}
}

void ShoppingCart:: GetTotalCostPos(int pos) const{
	
	ItemType item=cart.retrieve(pos);
	string name = item.GetName();
	double price = item.GetPrice();
	int quantity = item.GetQuantity();
	cout<< item.GetItemInfo() <<endl;

}

void ShoppingCart:: GetTotalCost() const{
	double totalCost=0.0;
	for(int i=1; i<=cart.getLength();i++){

		ItemType item = cart.retrieve(i);
		totalCost=totalCost+item.GetQuantity()*item.GetPrice();
		
	}
	cout<<"Total cost is: $"<<totalCost<<endl;
}

void ShoppingCart::GetNumbOfItems() const{
	
	cout<<"There are "<<cart.getLength()<<" items in the cart."<<endl;

}
