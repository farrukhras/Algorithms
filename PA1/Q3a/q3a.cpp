#include <iostream> 
#include <string.h>
#include <fstream>
#include <list> 
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std; 

/*
The running time complexity is : O(n)

First I read the content from the file and store the data in a list of arrays. Each vertex has its edges stored in the the list named adj.
Then we pass the adj list to a function named TopologicalSort. In that I first calculated the in_degree of each node and store them in an in_degree vector.
Then there is an if-else statement such : if there exists no such node with in_degree 0, then there is a cycle and find the cycle else print the topological
sort result which will give us the ordering in which the leaders can be arranged in a line given the grudges they hold.
In topological sort, I find the vertex with 0 indegree and push it into a queue and then run a while(queue is not empty) loop. In that I pop the 
pushed element from the queue and then decrease the value of its adjacent nodes indegrees by 1 and push the new node with indegree 0 in the queue.
Once there is no node with indegree 0 then I print the sorted order.

If there is a cycle then I run DFS on the graph using coloring. Initially marking all vertices as not visited and then running DFS on each node until I found
a node which had already been visited. In that case I store the result in a string and output the cycle which wont result in any ordering where the leaders can be 
arranged given the grudges they hold.
*/

enum Color {WHITE, GRAY};

string convert_str(int val)
{
	string str ;
	stringstream convert;
	convert << val;
	str = convert.str();
	return str;
}

bool dfs(int curr, list<int>* adj, int siz, int color[], vector<int> arr, string& answer)
{
	color[curr] = GRAY; // the current node is now being tested with DFS

	arr.push_back(curr);

	for (auto it = adj[curr].begin(); it != adj[curr].end(); it++)
	{
		//cout<<"curr: "<<curr<<endl;
		int next = *it;
		//cout<<"next: "<<next<<endl;

		if (color[next] == GRAY) // there is a cycle in the graph
		{
			arr.push_back(next);
			int siz1 = arr.size();

			for (int i = 0;  i< siz1-1; i++)
			{
				answer = answer + convert_str(arr[i]) + "->"; 
			}
			answer = answer + convert_str(arr[siz1 - 1]);
			break;
		}

		if (color[next] == WHITE && dfs(next, adj, siz, color, arr, answer))
		{
			break;
		}
	}
}

void cycle(list<int>* adj, int siz, string& answer)
{
	vector<int> arr;
	int* color = new int[siz];

	for (int i = 0; i< siz; i++) // initialize color of all the vertices to WHITE
	{
		color[i] = WHITE;
	}

	dfs(1, adj, siz, color, arr, answer);
}

void TopoogicalSort(list<int>* adj, int siz, string& answer)
{
	vector<int> in_degree(siz, 0); //store in_degree of all the vertices in a vector
	queue<int> q;
	string ans = "";

	for (int i = 0; i < siz; i++) // calcualtes and stores the number of incoming edges of each node in in_degree vector 
    { 
        for (auto it = adj[i].begin(); it != adj[i].end(); it++) 
        {
       		in_degree[*it]++; 
        }
    } 

    if (std::find(in_degree.begin(), in_degree.end(),0) != in_degree.end()) // takes linear time
    {
	   	for (int i = 0; i < siz; i++)
	    {
		   	if (in_degree[i] == 0)
		   	{
		   		q.push(i);
		   	}
	    }

	    int counter = 0;
		vector<int> result;

		while(!q.empty()) //dequeue vertices from queue and then enqueue neighbouring node if its new in_degree is 0 (runs O(n) times)
	    {
		   	int val = q.front();
		   	//cout<<val<<endl;
		   	q.pop();
		   	result.push_back(val);
		  
		   	for (auto itr = adj[val].begin(); itr != adj[val].end(); itr++) // decrease the neighbour's in_degree see if it is 0
		   	{
		    	//cout<<in_degree[*itr]<<endl;
		   		in_degree[*itr] -= 1;
		    	//cout<<in_degree[*itr]<<endl;
		    		
		   		if (in_degree[*itr] == 0)
		   		{
		   			q.push(*itr);
		   		}
		   	}	

		   	counter++;
		}

		ans = ans + "Yes" + "\n";
		int siz2 = result.size();

		for (int i = 0; i< siz2-1; i++)
		{
			ans = ans + convert_str(result[i]) + " ";
		}
		ans = ans + convert_str(result[siz2-1]);

	    ans = ans +"\n";
	    answer = ans;
	}

    else
    {
    	cycle(adj, siz, answer);
    	answer = "No\n" + answer + "\n";
    }
}

int main(int argc, char** argv) 
{
	string n, line;
	int parent, child, siz;

	string file_name = argv[1];
	fstream inFile(file_name);
	//fstream inFile("test13a.txt");
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

	vector<string> cyc_res;
	string result = "";
	TopoogicalSort(adj, siz, result);

	cout<<result;

    return 0; 
} 
