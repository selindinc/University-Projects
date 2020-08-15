#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE
#include "Call.h"
using namespace std;
typedef Call ItemType;
class PriorityQueue{

	public:
			PriorityQueue();
			//input: none
			//output: none
			//side effects: constructor
			~PriorityQueue();
			//input: none
			//output: none
			//side effects: destructor
			PriorityQueue(const PriorityQueue& listToCopy);
			//input: a priority queue copy
			//output: a priority queue copy
			//side effects: copy constructor
			bool isEmpty() const;   
			//input: none
			//output: returns true if priority queue is empty, else false
			//side effects: none
   			int getSize() const;
			//input: none
			//output: returns the size of priority queue
			//side effects: none
			bool append(const ItemType & c);
   			// input: element to be added to the end of the priority queue
   			// output: if call was appended to the list true is
   			// returned; else false is returned
			//side effects: none
			bool enqueue(int position,const ItemType & c);
   			// input: an integer, a copy call object
   			// output: if call was enqueued to the priority queue return true,else false
			//side effects: none
			bool dequeue(int position);
   			// input: an integert
   			// output: if call was dequeued to the priority queue return true,else false
			//side effects: none
			ItemType retrieve(int position) const;
			//input: none
			//output: returns the call at the position from priority queue
			//side effects: none


	private:
			class Node {
			public:
				ItemType data;
				Node* next;
			};
			Node* head;
			Node* tail;
			int size;
			void advanceTo(Node* & p, int pos) const;
	};
	#endif

