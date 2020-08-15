#ifndef DIGRAPH_
#define DIGRAPH_
#include <algorithm>
#include <string>
#include <list>
#include <vector>


using namespace std;

class Digraph {

public:

	Digraph();

	~Digraph();

	bool AddVertex(string ver);
	// input: a string 
	// output: boolean
	// side effects: none

	bool AddDirectedEdge(string ver1,string ver2);
	// input: two strings
	// output: boolean
	// side effects: none

	bool RemoveEdge(string ver1,string ver2);
	// input: two strings
	// output: boolean
	// side effects: none

	bool FindDirectedEdge(string ver1,string ver2);
	// input: two strings
	// output: boolean
	// side effects: none

	bool FindVertex(string ver);
	// input: a string
	// output: boolean
	// side effects: none

	int NumOfVertices();
	// input: none
	// output: integer
	// side effects: none

	int NumOfEdges();
	// input: none
	// output: integer
	// side effects: none

	vector<string> retrieveVert();
	// input: none
	// output: vector
	// side effects: none

	vector<string> retrieveSuc(string ver);
	// input: a string
	// output: vector
	// side effects: none
	
	vector<string> retrievePre(string ver);
	// input: a string
	// output: vector
	// side effects: none

	int NumOfPred(string ver);
	// input: a string
	// output: integer
	// side effects: none

private:
	class Node {
		public:
			list<string> suc;
			list<string> pre;
	};
	vector<Node> digraph;
	vector<string> names;
};
#endif

