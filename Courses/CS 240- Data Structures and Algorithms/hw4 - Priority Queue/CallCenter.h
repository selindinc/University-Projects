#ifndef CALLCENTER_H
#define CALLCENTER_H
#include "PriorityQueue.h"
#include "Call.h"
#include <string>
#include <vector>

using namespace std;

class CallCenter{

	public:
		CallCenter();

		bool acceptCall(Call c);
		// input: a Call 
   		// output: return true if the call acceppted; else false
		// side effects: none
		bool updateCallCenter();//dk artir, konusma bittiyse yeni konusma al
		// input: none
   		// output: none
		// side effects: none
		void displayResults() const;
		// input: none
   		// output: none
		// side effects: prompts total number of calls entered and answered,
		//total call time, average waiting time for a call,average wait
		//time for priority 1,2 and 3 calls

		void displayCurStat() const;
		// input: none
   		// output: none
		// side effects: prompts current simulation time, number of calls in
		// the waiting list, number of calls completed
		
		int GetSysTime() const; 
		// input: none
   		// output: returns system time
		// side effects: none

		int GetTotCallTime() const;
		// input: none
   		// output: returns total call time 
		// side effects: none

	private:
		PriorityQueue waitList;	
		int systime;
		int wtime;
		int pri1;
		int pri2;
		int pri3;
		int num1;
		int num2;
		int num3;
		int calltime;
		int numCallsAnsw;
		int totcalltime;
		Call call;//
};


#endif
