#ifndef CIRCLE_
#define CIRCLE_
#include "digraph.h"
#include <string>
#include <list>
#include <vector>
using namespace std;

class Circle {

public:

		Circle();
	
		int AddMembers(string name);
		// input: a string 
		// output: integer
		// side effects: none
		int CreateFriendship(string name1,string name2);
		// input: two strings
		// output: integer
		// side effects: none
		void DisplayMembers();
		// input: none
		// output: none
		// side effects: display the members of circle
		void NumOfMembers();
		// input: none 
		// output: none
		// side effects: display the number of members
		void  NumOfFriendships();
		// input: none 
		// output: none
		// side effects: display the number of friendships

		int IsMember(string name);
		// input: a string 
		// output: integer
		// side effects: display if the name is member or not

		void WhoHasNameAsFriend(string name);
		// input: a string 
		// output: none
		// side effects: display the members who are friend with the name

		int IsName1DesigName2AsFriend(string name1,string name2);
		// input: two strings 
		// output: integer
		// side effects: display if the name1 designated name2 as friend

		int IsName1DesigFriendByName2(string name1,string name2);
		// input: two strings 
		// output: integer
		// side effects: display if the name1 designated friend by name2

		int RemoveName1AsDesigFriOfName2(string name1,string name2);
		// input: two strings 
		// output: integer
		// side effects: none

		int NumOfPeopDesigNameAsFriend(string name);
		// input: a string 
		// output: integer
		// side effects: none

		int Quit();
		// input: none 
		// output: integer
		// side effects: none

private:
		Digraph d;
};

#endif
		
		
		
		
