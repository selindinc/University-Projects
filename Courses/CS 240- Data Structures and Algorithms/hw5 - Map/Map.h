
#ifndef MAP_
#define MAP_
#include "mapInterface.h"
using namespace std;


class Map: public MapInterface{

public:	
	Map();
	~Map();
	Map operator=(Map &rhs);
	Map(const Map &m);
	bool empty() const;
	//input: none
	//output: returns true if the Map is empty; else false
	//side effects: none
		 
	int size() const;
	//input: none
	//output: returns the number of elements in the Map
	//side effects: none

	bool add(ElementType element);
	//input: an element (key and its associated value)
	//output: returns true if the key-value pair was 				     	
	//added; else false(the key was found)
	//side effects: Map has one more element (if addition      		     	
	//done)
		 
	bool find(KeyType key) const;
	//input: a key
	//output: return true is an element with this key was 			
	//found; else false
	//side effects: none
		 	
	ValueType retrieve(KeyType key) const;
	//input: a key
	//output: returns the value associated with key (a 			
	//null pointer if the key was not found)
	//side effects: none
		 
	bool remove(KeyType key);
	//input: a key
	//output: returns true if item is removed;
	//else false (key not found)
	//side effects: Map has one less element (if remove 
	//done)
	void displayAll() const; 
	//input: none
	//output: none
	//side effects: displays empty if map is empty, if not displays map content 
private:
	class Node {
	public:
		ElementType data;
		Node* next;
	};
	Node* head;
	Node* tail;
	int Size;
	void advanceTo(Node* & p, int pos) const;
};

#endif
