#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <list>
#include <stack>
#include <queue>

using namespace std;

/*
The running time complexity is : O(V + E)

First I read the content from the file and store the data in a list of arrays. Each vertex has its edges stored in the the list named adj.
Then we pass the adj list to a function named TopologicalSort. In that I first calculated the in_degree of each node and store them in an in_degree vector.
Then there is an if-else statement such : if there exists no such node with in_degree 0, then there is a cycle and find the cycle else print the topological
sort result which will give us the ordering in which the leaders can be arranged in a line given the grudges they hold.
In topological sort, I find the vertex with 0 indegree and push it into a queue and then run a while(queue is not empty) loop. In that I pop the 
pushed element from the queue and then decrease the value of its adjacent nodes indegrees by 1 and push the new node with indegree 0 in the queue.
To make the leaders sit row-wise, I arrange them based on the in_degrees of the nodes. I find all the nodes with in_degree 0 and place them in one row.
Then I update the in_degrees and new nodes with in_degree 0 are placed in same row. So on and so forth. In the end the row-wise ordering is printed.
*/

string convert_str(int val)
{
	string str ;
	stringstream convert;
	convert << val;
	str = convert.str();
	return str;
}

void TopoogicalSort(list<int>* adj, int siz, string& answer)
{
	vector<int> in_degree(siz, 0); //store in_degree of all the vertices in a vector
	queue<int> q;
	string ans = "";

	for (int i = 0; i < siz; i++) // calcualtes and stores the number of incoming edges of each node in in_degree vector  in O(V + E)
    { 
        for (auto it = adj[i].begin(); it != adj[i].end(); it++) 
        {
       		in_degree[*it]++; 
        }
    } 

    if (std::find(in_degree.begin(), in_degree.end(), 0) != in_degree.end()) // the find operation takes linear time
    {
		vector<int> result;
		int rows = 0;
		string a1 = "";

	   	for (int i = 0; i < siz; i++)
	    {
		   	if (in_degree[i] == 0) // push all the nodes with in_degree 0 in the queue
		   	{
		   		q.push(i);
		   		result.push_back(i);
		   	}
	    }

	    int si1 = result.size();
	    if (si1 == 1)
	    {
	    	a1 = convert_str(result[0]) + "\n";
	    	//rows = 0;
	    }

	    else
	    {
	    	for (int i = 0; i< si1-1; i++)
		    {
		    	a1 = a1 + convert_str(result[i]) + " ";
		    	//cout<<"a1 : "<<a1<<endl;
		    }
		    a1 = a1 + convert_str(result[si1-1]);
		    //rows = 1;
	    }

	    //rows++; // only one row becasue even if more than 1 node with indegree 0, it will be in same row

		while(!q.empty()) //dequeue vertices from queue and then enqueue neighbouring node if its new in_degree is 0
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
		   			rows++;
		   			ans = ans + convert_str(*itr) + " ";
		   		}
		   	}	

		   	ans = ans + "\n";
		}

		string qwe = "Yes\n";
		string qwe1 = "R ";
		string wth = qwe + qwe1;
		ans = wth + convert_str(rows) + "\n" + a1 + ans;
	    answer = ans;
	}

    else
    {
    	answer = "No\n";
    }
}

int main(int argc, char** argv)
{
	string n, line;
    int parent, child, siz;

    string file_name = argv[1];
    fstream inFile(file_name);
    //fstream inFile("test13b.txt");
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

    inFile.close();

    string result = "";
	TopoogicalSort(adj, siz, result);

	cout<<result;
	
	return 0;
}