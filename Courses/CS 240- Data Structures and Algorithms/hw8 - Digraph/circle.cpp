#include "circle.h"
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

	Circle::Circle(){}

	int Circle::AddMembers(string name){
		d.AddVertex(name);
		return 0;
	}

	int Circle::CreateFriendship(string name1,string name2){
		d.AddDirectedEdge(name1,name2);
			return 0;
		
	}

	void Circle::DisplayMembers(){
		vector<string> v=d.retrieveVert();
		int s=v.size();
		for(int i=0;i<s;i++){
			cout<<v.at(i)<<endl;
		}
	}

	void Circle::NumOfMembers(){
		cout<<d.NumOfVertices()<<endl;
	}

	void  Circle::NumOfFriendships(){
		cout<<d.NumOfEdges()<<endl;
	}

	int Circle::IsMember(string name){
		if(d.FindVertex(name)){
			cout<<"Yes"<<endl;
		
		}
		else{
			cout<<"No"<<endl;
		}
		return 0;
		
	}

	void Circle::WhoHasNameAsFriend(string name){
		vector<string> v= d.retrievePre(name);
		int s = v.size();
		for(int i=0;i<s;i++){
			cout<<v.at(i)<<endl;
		}
	}

	int Circle::IsName1DesigName2AsFriend(string name1,string name2){
		if(d.FindDirectedEdge(name1,name2)){
			cout<<"Yes"<<endl;
			
		}
		else{
			cout<<"No"<<endl;
		}
		return 0;
	}

	int Circle::IsName1DesigFriendByName2(string name1,string name2){
		if(d.FindDirectedEdge(name2,name1)){
			cout<<"Yes"<<endl;
			
		}
		else{
			cout<<"No"<<endl;
		}
		return 0;
	}

	int Circle::RemoveName1AsDesigFriOfName2(string name1,string name2){
		d.RemoveEdge(name1,name2);
		return 0;
		
	}

	int Circle::NumOfPeopDesigNameAsFriend(string name){
		cout<<d.NumOfPred(name)<<endl;
		return 0;
	}

	int Circle::Quit(){
		return 1;
		
	}

	
	
