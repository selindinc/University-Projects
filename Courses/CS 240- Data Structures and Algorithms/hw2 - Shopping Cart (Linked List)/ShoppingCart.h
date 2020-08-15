#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H
#include "LinkedList.h"
#include "ItemToPurchase.h"
#include <string>
#include "ListInterface.h"

using namespace std;

class ShoppingCart{

	public:
		ShoppingCart();
		bool AddItemToEnd(ItemType newItem);
		// input: an ItemType
   		// output: return true if the item is added; else false
		// side effects: prompt "Item added" if item added
		bool AddItemToPos(int pos, ItemType newItem);
		// input: an integer,an ItemType
   		// output: return true if the item is added to position; else false
		// side effects: prompt "Item added at position" if item added to position
		bool RemoveItem(int pos);
		// input: an integer
   		// output: return true if the item is removed from position; else false
		// side effects: prompt "Position is out of bound!" if position is out of 			// bound;
		//prompt "Item at position removed" if item is removed from position
		void GetItemPos(int pos) const;
		// input: an integer
   		// output: void
		// side effects: prompt item.GetItemInfo() 
		void GetItems() const;
		// input: none
   		// output: void
		// side effects: prompt "There are no items." if cart is empty; else prompt 			//items
		void GetTotalCostPos(int pos) const;
		// input: an integer
   		// output: void
		// side effects: prompt item.GetItemInfo() at the positon 
		void GetTotalCost() const;
		// input: none
   		// output: void
		// side effects: prompt total cost 
		void GetNumbOfItems() const;
		// input: none
   		// output: void
		// side effects: prompt number of items in the cart
	
	private:
		LinkedList cart;
};


#endif
