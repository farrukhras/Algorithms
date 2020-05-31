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
The running time complexity is in O(V + E).

First I read the content from the file and store the data in a list of arrays. Each vertex has its edges stored in the the list named adj.
After file reading we pass the adj list to a find_edges function whihch, esentially finds the number of vulnerable edges in the graph.
We initialize a color to all the vertices in the graph. Then we mark all the nodes as not visited. The we start from a source node and color 
it with a different color than its previous one. We then mark this vertex as visited. We then check that wheter the graph rooted at current node
is biparttite or not. If it is not then we return false. If the adjacent node to the current node have already been visited then we check wheter 
it has the same color as its parent. If both have same colors then that means that the graph is not biparttie.  If above 2 conditions are not true
then that means the graph is bipartitte and thus we return true.
We have simultainiously maintained a color vector. It is initially marked 0 for all vertices. When we start from a node , we mark it, say 1. Then
we check the current nodes adjacent nodes and see 
1. if they have not already been visited, and (we assignit a color opposite to its initial color)
2. if the graph rooted at this node is bipartttie. (if it is biparttie then continue the coloring)
    else return false.
*/

string convert_str(int val)
{
    string str ;
    stringstream convert;
    convert << val;
    str = convert.str();
    return str;
}

bool DFS (list<int>* adj, vector<int>& visited, vector<int>& parent, vector<int>& result, int curr, int odd)
{   
    visited[curr] = 1;
    queue<int> q;

    q.push(curr);

    parent.push_back(curr);
    odd++;
    result.push_back(curr);

    while(!q.empty())
    {
        int counter = 0;
        int temp = q.front();
        q.pop();

        for(auto itr = adj[temp].begin(); itr != adj[temp].end(); itr++)
        {
            int next = *itr;
            if(counter == 1)
            {
                break;
            }

            if (std::find(parent.begin(), parent.end(), next) != parent.end())
            {
                //cout<<"IN IF"<<endl;
                continue;
            }

            else
            {
                if(visited[next] == -1)
                {
                    //counter++;
                    visited[next] = 1; //- visited[curr];
                    q.push(next);
                    parent.push_back(next);
                    odd++;
                }

                else if(visited[next] == 1)
                {
                    //cout<<"here"<<endl;
                    return true;
                }
            }   
        }
    }
               
}

bool bipartitte_graph(list<int>* adj, int curr, vector<bool>& visited, vector<int>& color)
{
    for (auto itr = adj[curr].begin(); itr != adj[curr].end(); itr++) 
    {
        int next = *itr;
        
        if (visited[next] == false) // if the adjacent of the current node have not been visited yet then check if it also forms a bipartitte graph ot not
        {
            visited[next] = true;
            color[next] = !color[curr];

            if (!bipartitte_graph(adj, next, visited, color)) // checks if the graph rooted at the adjacent of the current node is bipartitte or not
            {
                return false;
            }
        }

        else if (color[next] == color[curr]) // if the colors of the root and its neighbour is same then the graph is not bipartitte
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv)
{
    string n, line;
    int parent, child, siz;

    string file_name = argv[1];
    fstream inFile(file_name);
    //fstream inFile("test21.txt");
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

    vector<bool> visited(siz, false);
    vector<int> color(siz, -1);
    int i = 1;

    visited[i] = true;
    color[i] = 0; // initialize the first color
    string ans = "";

    bool result = bipartitte_graph(adj, i, visited, color);

    vector<int> arr;
    vector<int> arr1;

    if (result) 
    {        
        ans = ans + "Yes\n";
        for (int i = 0; i<siz; i++)
        {
            if(color[i] == 1)
            {
                ans = ans + convert_str(i) + " ";
                //arr.push_back(i);
            }
        }

        ans = ans + "\n";

        for (int i = 0; i<siz; i++)
        {
            if(color[i] == 0)
            {
                ans = ans + convert_str(i) + " ";
                //arr1.push_back(i);
            }
        }

        ans = ans + "\n";   
    }

    else 
    {
        ans = ans + "No\n";

        vector<int> visited1(siz, -1);
        vector<int> parent;
        vector<int> result;
        int src = 0;
        int odd = 0;

        bool checker = DFS(adj, visited1, parent, result, src, odd);  

        for (int i= 0; i<parent.size(); i++)
        {
            ans = ans + convert_str(parent[i]) + "->";
        }
        ans = ans + convert_str(src);
    }

    cout<<ans;

    return 0;
}

