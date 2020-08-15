#ifndef ITEMTOPURCHASE_H
#define ITEMTOPURCHASE_H
#include <string>
using namespace std;

class ItemToPurchase {

	public:

	ItemToPurchase();
	ItemToPurchase(string name, double price,int quantity);
	// input: a string, a double, an integer
        // output: none 
	void SetName(string name);
	// input: a string
        // output: void
   	void SetPrice(double price);
	// input: a double
        // output: void
   	void SetQuantity(int quantity);
	// input: an integer
        // output: void
	string GetItemInfo() ;
	// input: none
        // output: return string
	string GetName() ;
	// input: none
        // output: return a string
	double GetPrice() ;
	// input: none
        // output: return a double
	int GetQuantity() ;
	// input: none
        // output: return an integer
	friend ostream& operator<< (ostream &out,const ItemToPurchase & f);

       
	private:
     
	string Name;
	double Price;
	int Quantity;
};

#endif
