// program to test the behavior of the ItemToPurchase class
#include <iostream>
#include "ItemToPurchase.h"
#include <string>
using namespace std;

           

ItemToPurchase :: ItemToPurchase(){

	Name="";
	Price=0.0;
	Quantity=0;
}
ItemToPurchase :: ItemToPurchase(string name, double price,int quantity){

	Name=name;
	Price=price;
	Quantity=quantity;
}

void ItemToPurchase::SetName(string name){
	Name=name;
	return;	
}

void ItemToPurchase::SetPrice(double price){
	Price=price;
	return;
}

void ItemToPurchase::SetQuantity(int quantity){
	Quantity=quantity;
	return;
}

string ItemToPurchase::GetName(){
	return Name;
}

double ItemToPurchase::GetPrice(){
	return Price;
}

int ItemToPurchase::GetQuantity(){
	return Quantity;	
}
ostream & operator<< (ostream & out,const ItemToPurchase & f) {
	string price=to_string(f.Price);
	string quantity=to_string(f.Quantity);
	double totalPrice=f.Price*f.Quantity;
	string Total_price=to_string(totalPrice);
	out<<f.Name + " " + quantity + " @ $" + price + " = $" + Total_price;
	return out;
}

string ItemToPurchase::GetItemInfo(){
	string price=to_string(Price);
	string quantity=to_string(Quantity);
	double totalPrice=Price*Quantity;
	string Total_price=to_string(totalPrice);
	return(Name + " " + quantity + " @ $" + price + " = $" + Total_price);
	
}

