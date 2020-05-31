#include <iostream> 
#include <string.h>
#include <fstream>
#include <list> 
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <tuple>
using namespace std;

/*
The running time complexity is O(V + E); where V = number of vertexes and E = number of edges. This makes the underlying algorithm linear time.

First I read the content from the file and store the data in a list of arrays. Each vertex has its edges stored in the the list named adj.
After file reading we pass the adj list to a find_edges function whihch, esentially finds the number of vulnerable edges in the graph.
In the find_edge function we initialie a visited array which marks all the vertices as not visited and then runs DFS on all the unvisited vertices.
This find_edge function returns a tuple where each element of a tuple is a vulnerable edge.
In the DFS we mark the current vertex visited and look at its adjacent nodes. And see if they are not visited then we run the DFS again on them.
We maintain 2 addition vectors to check for the vulnerable edges. 
We then check if the adjacent vertex (v) of current node (u) has any edge with an ancestor of current node (u). If no such edge exists then 
this edge is a vulnerable edge.
*/

/*
FACT:
Let's say we are in the DFS, looking through the edges starting from vertex u. 
The current edge (u, v) is a vulnerable edge if and only if none of the vertices 'v'
and its descendants in the DFS traversal tree has a back-edge to vertex u or any of its ancestors. 
Indeed, this condition means that there is no other way from u to v except for edge (u,v).
*/

typedef vector<tuple<int, int>> my_tuple;

string convert_str(int val)
{
	string str ;
	stringstream convert;
	convert << val;
	str = convert.str();
	return str;
}

// FINDS THE VULNERABLE EDGES USING DFS
void dfs(int curr, list<int>* adj, int siz, vector<bool>& visited, vector<int>& tin, vector<int>& fmt, vector<int>& temp, int& t, my_tuple& tl)
{
	visited[curr] = true;
	tin[curr] = t++; 
	fmt[curr] = t++;

	for (auto itr = adj[curr].begin(); itr != adj[curr].end(); itr++)
	{
	// *itr is the adjacent node of the current visited node
		if (!visited[*itr]) // if the adj node has not yet been visited then run DFS on it again
		{
			temp[*itr] = curr;
			dfs(*itr, adj, siz, visited, tin, fmt, temp, t, tl);

			// fmt[curr] = min(fmt[curr], fmt[*itr]) 
			// *itr is an ancestor of curr 
	        // and there is a back edge from a descendant of curr to *itr

			fmt[curr] = min(fmt[curr], fmt[*itr]);

			if (fmt[*itr] > tin[curr]) // a vulnerable edge has been found
			{
				tl.push_back(tuple<int, int>(curr, *itr));
			}
		}

		else if (*itr != temp[curr]) // if the adjacent node has been visited and *itr is not the parent of current node
		{
			fmt[curr] = min(fmt[curr], tin[*itr]);
		}
	}
}


my_tuple find_edge(list<int>* adj, int siz)
{
	my_tuple tl;
	int t = 0;
	vector<bool> visited(siz, false); // visited vertices are stored here
	vector<int> temp(siz, -1); // stores the parent of a vertex, e.g. parent[u] stores parent of vertex u 
	vector<int> tin(siz, -1);
	vector<int> fmt(siz, -1); // fmt = find_min_time; helps us to find the time taken to reach a vertex from current node in the MINIMUM time.

	for (int i = 0; i < siz; i++) // run DFS on each unvisited vertex and find all possible vulnerable edges
	{
		if (!visited[i])
		{
			dfs(i, adj, siz, visited, tin, fmt, temp, t, tl);
		}
	}
	return tl;
}

int main(int argc, char** argv)
{
	// FILE READING
	string n, line;
	int parent, child, siz;
	string myfile = argv[1];
	fstream inFile(myfile);
	//fstream inFile("test22.txt");
	inFile>>n>>siz;

	list<int>* adj = new list<int>[siz];

	while(getline(inFile,line))
	{
	    string temp = line;

	    stringstream convert(temp);
	    convert >> parent;

	    size_t pos = line.find(':');
	    line = line.substr(pos + 1);

	    stringstream num(line);

	    while(num >> child)
	    {
	    	adj[parent].push_back(child);
	    }
	}

	// FIND THE VULNERABLE EDGES
	my_tuple tl = find_edge(adj, siz);
	string ans = "";

	if(tl.size() != 0) // the vulnerable edges are stored in a tuple and the result is printed accordingly
	{		
		string siz1 = convert_str(tl.size());
		ans = ans + siz1 + "\n";

		for(auto it = tl.begin(); it != tl.end(); it++)
		{
			ans = ans + "(" + convert_str(get<0>(*it)) + "," + convert_str(get<1>(*it)) + ")\n";
		}
	}
	
	else
	{
		ans = "0\n";
	}

	cout<<ans;

	return 0;
}
