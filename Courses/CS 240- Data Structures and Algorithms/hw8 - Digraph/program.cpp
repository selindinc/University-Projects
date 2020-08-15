#include "circle.h"
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void Menu();
// input: none 
// output: none
// side effects: prompt the menu
int SwitchMenu(Circle& c);
// input: a circle object 
// output: integer
// side effects: take input from user

int main(){
	Circle c;
	c.AddMembers("Selin");
	c.AddMembers("Sinem");
	c.AddMembers("Mehmet");
	c.AddMembers("Egemen");
	c.AddMembers("Ege");
	c.AddMembers("Hilal");
	c.AddMembers("Yavyu");
	c.AddMembers("Pepek");
		
	c.CreateFriendship("Selin","Sinem");
	c.CreateFriendship("Sinem","Selin");
	c.CreateFriendship("Selin","Mehmet");
	c.CreateFriendship("Mehmet","Selin");
	c.CreateFriendship("Selin","Yavyu");
	c.CreateFriendship("Yavyu","Selin");
	c.CreateFriendship("Selin","Pepek");
	c.CreateFriendship("Pepek","Selin");
	c.CreateFriendship("Selin","Hilal");
	c.CreateFriendship("Hilal","Selin");
	c.CreateFriendship("Hilal","Sinem");
	c.CreateFriendship("Sinem","Hilal");
	c.CreateFriendship("Selin","Egemen");
	c.CreateFriendship("Egemen","Selin");
	c.CreateFriendship("Egemen","Ege");
	c.CreateFriendship("Yavyu","Pepek");
	c.CreateFriendship("Pepek","Yavyu");
	c.CreateFriendship("Ege","Sinem");
	c.CreateFriendship("Mehmet","Ege");
	c.CreateFriendship("Mehmet","Egemen");
	int a;
	do{
		Menu();
		a=SwitchMenu(c);
	}
	while(a!=1);
	

}

void Menu(){

	cout<<"who are the members of the circle of friends? : "<< "Press A"<<endl;
	cout<<"how many people belong to the circle of friends? : "<< "Press B"<<endl;
	cout<<"how many friendships are part of the circle of friends? : "<< "Press C"<<endl;
	cout<<"is name a member of the circle of friends? : "<< "Press D"<<endl;
	cout<<"who has name designated as a friend? : "<<"Press E"<<endl;
	cout<<"has name1 designated name2 as a friend? : "<<"Press F"<<endl;
	cout<<"has name1 been designated by name2 as a friend? : "<<"Press G"<<endl;
	cout<<"remove name1 as a designated friend of name2 : "<<"Press H"<<endl;
	cout<<"how many people have designated name as a friend? : "<<"Press I"<<endl;
	cout<<"For quit please press Q. "<<endl;

}
int SwitchMenu(Circle& c){
	char choice='A';
	cin>>choice;
	string name1;
	string name2;
	int q=0;
	switch(choice){
		case 'A':
			c.DisplayMembers();
			break;
		case 'B':
			c.NumOfMembers();
			break;
		case 'C':
			c.NumOfFriendships();
			break;
		case 'D':
			cout<<"Enter a member name: "<<endl;
			cin>>name1;
			c.IsMember(name1);
			break;
		case 'E':
			cout<<"Enter a member name: "<<endl;
			cin>>name1;
			c.WhoHasNameAsFriend(name1);
			break;
		case 'F':
			cout<<"Enter two member names: "<<endl;
			cin>>name1;
			cin>>name2;
			c.IsName1DesigName2AsFriend(name1,name2);
			break;
		case 'G':
			cout<<"Enter two member names: "<<endl;
			cin>>name1;
			cin>>name2;
			c.IsName1DesigFriendByName2(name1,name2);
			break;
		case 'H':
			cout<<"Enter a member to remove: "<<endl;
			cin>>name1;
			cout<<"Enter a member to removed from: "<<endl;
			cin>>name2;
			c.RemoveName1AsDesigFriOfName2(name1,name2); 
			break;
		case 'I':
			cout<<"Enter a member: "<<endl;
			cin>>name1;
			c.NumOfPeopDesigNameAsFriend(name1);
			break;
		case 'Q':
			q=c.Quit();
			break;
		default:
			cout<<"Invalid letter!"<<endl;
			break;
	}
	return q;
}
























