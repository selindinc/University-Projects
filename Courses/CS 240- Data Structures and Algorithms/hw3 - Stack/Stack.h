#ifndef STACK
#define STACK


class Stack{

	public:
			Stack();
			//input: none
			//output: none
			//side effects: constructor
			~Stack();
			//input: none
			//output: none
			//side effects: destructor
			bool isEmpty() const;   
			//input: none
			//output: returns true if stack is empty, else false
			//side effects: none
   			int getLength() const;
			//input: none
			//output: returns the size of stack
			//side effects: none
			void push(double x);
			//input: a double
			//output: none
			//side effects: none
			double pop();
			//input: none
			//output: returns the data at the top of the stack
			//side effects: deletes the top member of the stack
			double peek() const;
			//input: none
			//output: returns the data at the top of the stack
			//side effects: none


	private:
			class Node {
			public:
				double data;
				Node* next;
			};
			Node* top;
			int size;
	};
	#endif


