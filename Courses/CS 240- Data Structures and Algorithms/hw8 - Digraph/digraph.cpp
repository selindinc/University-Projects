#include <string>
#include "digraph.h"
#include <vector>
#include <list>
#include <algorithm>
using namespace std;


	Digraph::Digraph(){}

	Digraph:: ~Digraph(){}


	bool Digraph:: AddVertex(string ver){
		
		if(FindVertex(ver)){
			return false;
		}
		else{
			Node* p = new Node;
			digraph.push_back(*p);
			names.push_back(ver);
			return true;
		}
	}

	bool Digraph:: AddDirectedEdge(string ver1,string ver2){

		if(FindDirectedEdge(ver1,ver2)){
			return false;
		}
		else{
			auto v1=find(names.begin(),names.end(),ver1);
			auto v2=find(names.begin(),names.end(),ver2);
			int indx1=v1-names.begin();
			int indx2=v2-names.begin();
			digraph.at(indx1).suc.push_back(ver2);
			digraph.at(indx2).pre.push_back(ver1);
			return true;
		}
	}

	bool Digraph:: RemoveEdge(string ver1,string ver2){

		if(!FindDirectedEdge(ver1,ver2)){
			return false;
		}
		else{
			auto v1=find(names.begin(),names.end(),ver1);
			auto v2=find(names.begin(),names.end(),ver2);
			int indx1=v1-names.begin();
			int indx2=v2-names.begin();
			digraph.at(indx1).suc.remove(ver2);
			digraph.at(indx2).pre.remove(ver1);
			return true;
		}
	
	}

	bool Digraph:: FindDirectedEdge(string ver1,string ver2){
		auto i=find(names.begin(),names.end(),ver1);
		auto j=find(names.begin(),names.end(),ver2);
		if(i==names.end()){
			return false;
		}
		if(j==names.end()){
			return false;
		}
		int indxi=i-names.begin();
		if(*find(digraph.at(indxi).suc.begin(),digraph.at(indxi).suc.end(),ver2)==ver2){
			return true;
		}
		return false;
		
	}

	bool Digraph::FindVertex(string ver){

		auto v=find(names.begin(),names.end(),ver);
		if(v==names.end()){
			return false;
		}
		int indxv=v-names.begin();
		if((digraph.at(indxv).suc.begin(),digraph.at(indxv).suc.end(),ver)==ver){
			return true;
		}
		return false;
	}

	int Digraph:: NumOfVertices(){
		return digraph.size();
	}

	int Digraph:: NumOfEdges(){
		int Number=0;
		for(auto i : digraph){
			Number+=i.suc.size();
		}
		return Number;
	}	

	vector<string> Digraph:: retrieveVert(){

		return names;

	}

	vector<string> Digraph:: retrieveSuc(string ver){
		vector<string> ret;
		auto v=find(names.begin(),names.end(),ver);
		if(v==names.end()){ return ret;}
		int indxv=v-names.begin(); 
		for(auto i:digraph.at(indxv).suc){
			ret.push_back(i);
		}
			
		return ret;
	}
	vector<string> Digraph:: retrievePre(string ver){
		vector<string> ret;
		auto v=find(names.begin(),names.end(),ver);
		if(v==names.end()){ return ret;}
		int indxv=v-names.begin(); 
		for(auto i:digraph.at(indxv).pre){
			ret.push_back(i);
		}
			
		return ret;
	}
		

	int Digraph:: NumOfPred(string ver){
		int Number=0;
		auto v=find(names.begin(),names.end(),ver);
		int indxv=v-names.begin();
		if (v!=names.end())
			Number=digraph.at(indxv).pre.size();
		
		
		return Number;

	}










