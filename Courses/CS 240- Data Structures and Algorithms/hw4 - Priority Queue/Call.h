#ifndef CALL_H
#define CALL_H
using namespace std;

class Call {

	public:
		Call();

		Call(int arrive);
		//input: an integer
		//output: none
		//side effects: constructor

		Call(const Call& c);
		//input: a call object
		//output: a call object
		//side effects: copy constructor
		
	   	void SetArrivalTime(int t);
		//input: an integer
		//output: none
		//side effects: none
	
		void SetAnswTime(int t);
		//input: an integer
		//output: none
		//side effects: none

		int GetCallTime() ;
		//input: none
		//output: return call time
		//side effects: none
	
		int GetArrivalTime() ;
		//input: none
		//output: return arrival time
		//side effects: none
		
		int GetPriority() ;
		//input: none
		//output: return priority
		//side effects: none
	
		int GetAnswTime();
		//input: none
		//output: return answer time
		//side effects: none
		
		bool operator>(const Call& c);
		//input: a copy of a call object
		//output: return true if >,else false
		//side effects: none
		bool operator<(const Call& c);
		//input: a copy of a call object
		//output: return true if <,else false
		//side effects: none
		bool operator==(const Call& c);
		//input: a copy of a call object
		//output: return true if ==,else false
		//side effects: none
		bool operator!=(const Call& c);
		//input: a copy of a call object
		//output: return true if !=,else false
		//side effects: none
       
	private:
     
		int Pri;//priority
		int atime; //arrival time
		int ctime; //call time
		int answtime;
		
		
};

#endif
