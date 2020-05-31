#include <iostream> 
#include <string.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <queue>
#include <list>
using namespace std;
# define INF 0x3f3f3f3f 

struct edge {
	int root;
	int child;
	double weight;

	// bool operator > (edge const& e1) const//, const edge& e2)
	// {
	// 	return weight > e1.weight;
	// }
};

struct compare
{
	bool operator () (const edge& e1, const edge& e2)
	{
		return e1.weight > e2.weight;
	}
};

int main(int argc, char** argv) 
{ 
	string n, line;
	char colon, semi_colon, b1, b2;
	int parent, child, siz, num;
	double num3;

	//string file_name = argv[1];
	//fstream inFile(file_name);
	fstream inFile("test13a.txt");
	inFile>>n>>siz;

	cout<<n<<" "<<siz<<endl;

	vector<edge> edge_list;
	priority_queue<edge, vector<edge>, compare	> pq;

	getline(inFile, line);
	int count = 0;

	while(getline(inFile,line) && count < siz)
	{
	    stringstream convert(line);
	    convert >> parent >> colon;
	    
	    while (convert >> num){
	    	convert >> semi_colon;
	    	convert >> num3;

	    	edge e;
	    	e.root = parent;
	    	e.child = num;
	    	e.weight = num3;
	    	edge_list.push_back(e);
	    	pq.push(e);
	    }

	    count++;
	}

	// **** THE EDGE TO BE REMOVED ****
	getline(inFile, line);
	stringstream ss(line);
	ss >> b1 >> num >> colon >> num3 >> b2;

	// for (int i = 0; i<edge_list.size(); i++)
	// {
	// 	edge e = edge_list[i];
	// 	cout<<e.root.vertex<<":"<<e.child.vertex<<endl;
	// }

	while (!pq.empty())
	{
		edge e = pq.top();
		cout<<e.root<<":"<<e.child<<endl;
		pq.pop();
	}
   
    return 0; 
} 
