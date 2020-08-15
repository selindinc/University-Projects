#ifndef linked_List_
#define linked_List_

#include "ListInterface.h"

class LinkedList : public ListInterface { 
                 
public:
   LinkedList();
   // interface methods
   bool isEmpty() const;
   // input: none
   // output: return true if the list is empty; else false    
   int getLength() const;
   // input: none
   // output: returns number of elements currently in the list   
   bool insert(int newPos, const ItemType & newEntry);
   // input: element to be added to the list and position at
   //        which to add it 
   // output: if 1 <= newPos <=  getLength() + 1, newEntry is 
   //         at newPos and true is returned; else false is
   //         returned
   bool remove(int pos); 
   // input: pos is position of element to be removed
   // output: if 1 <= pos <= getLength(), the element at pos is
   //         removed, and true is returned; else false is
   //         returned 
   ItemType retrieve(int position) const;
   // input: position of element to be returned
   // output: element at position is returned
   // precondition: 1 <= position >= getLength()
   bool append(const ItemType & newEntry);
   // input: element to be added to the end of the list
   // output: if newEntry was appended to the list true is
   //         returned; else false is returned

private:
	
	class Node{
		public:
			ItemType data;
			Node* next;
		};
	Node* head=nullptr;
	int num_of_items;

};

#endif
