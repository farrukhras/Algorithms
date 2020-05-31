#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

/*
--------Time Complexity----------

O(V+E)

-------- BASE CASES: ------------

1. curr_node == NULL -> return 0
2. only 1 node -> return 0 
3. if we are at a leaf node(node that only has an edge to its parent) -> return 0

-----Recurrence Relation: -------

                 { 1 + find_min_lights(curr_node, is_ka_parent) --- if we add light at the current node
min_lights = min |
                 { find_min_lights(curr_node_cCHILD, is_ka_parent) --- if we donot add light at the current node

-----------Subproblems------------

There are "n" subproblems because there are "n" nodes in graph and each sub problem takes O(1) to resolve.
*/

string convert_str(int val)
{
    string str;
    stringstream convert;
    convert << val;
    str = convert.str();
    return str;
}

struct child;

struct node {
    int index = -1; 
    int par = -1; // parent of this node
    int bulb_counter = 0;
    vector<child> children_list;
};

struct child {
    node* baap = NULL;
    node* bacha = NULL;
};

int find_min_lights(node* curr_node, node* mera_baap);
vector <node*> result;
string ans = "";

// if we add a light at current node, then +1 to min_lights variable and check for the children of current node ke whether they should/should not have a light on them
int light_at_node(node* curr_node, node* mera_baap)
{
    int light_ON = 1;
    for (int i = 0; i< curr_node->children_list.size(); i++)
    {
        node* duniya = curr_node->children_list[i].baap;
        node* akhirat = curr_node->children_list[i].bacha;

        if(akhirat != mera_baap)
        {
            light_ON = light_ON + find_min_lights(akhirat, duniya);
        }
    }

    return light_ON;
}

// if we donot add a light at current node, then we check for the children of current node and they must have lights
int light_not_at_node(node* curr_node, node* mera_baap)
{
    int light_OFF = 0;

    for (int i = 0; i<curr_node->children_list.size(); i++)
    {
        child a1 = curr_node->children_list[i];
        if (a1.bacha != mera_baap) 
        {
            light_OFF += 1 ;

            for (int j = 0; j<a1.bacha->children_list.size(); j++)
            {
                child a2 = a1.bacha->children_list[j];
                if (a1.baap != a2.bacha) 
                {
                    light_OFF += find_min_lights(a2.bacha, a2.baap) ;
                }
            }
        }   
    }

    return light_OFF;
}

int find_min_lights(node* curr_node, node *mera_baap)
{
    if (curr_node == NULL)
    {
        return 0;
    }

    if (curr_node->par = -1)
    {
        if (curr_node->children_list.size() == 0)
        {
            return 0;
        }
    }

    if (curr_node->children_list.size() == 1)
    {
        if (mera_baap)
        {
            return 0;
        }
    }

    if (curr_node->bulb_counter != 0)
    {
        return curr_node->bulb_counter;
    }

    // Now we have 2 cases:
    // 1. If the current node does not have a light in it
    // 2. If the current node has a light in it
    // we check both cases and then compare which case will result in minimum number of lights to be added

    // For (1.)
    // if light on curr_node then we do check the edges of curr_node and find the minimum tobe lighed nodes
    // For (2.)
    // we do the same as (1.) except that we do +1 also

    // 1.
    int light_added = light_at_node(curr_node, mera_baap);
    // 2.
    int light_not_added = light_not_at_node(curr_node, mera_baap);

    // take the min lights required
    int min_lights = min(light_added, light_not_added);

    curr_node->bulb_counter = min_lights;

    if(min_lights == light_added)
    {
        result.push_back(curr_node);
    }

    return curr_node->bulb_counter;
}

int main(int argc, char** argv)
{
    string n, line;
    int parent111, beta, siz, curr, later;
    bool c1 = false;
    bool c2 = false;

    string myfile = argv[1];
    fstream inFile(myfile);
    //fstream inFile("test22.txt");
    inFile>>n>>siz;

    vector<node*> nodes_list;
    for (int i = 0; i<siz; i++)
    {
        node* this1 = new node;
        this1->index = i;
        nodes_list.push_back(this1);
    }

    while(getline(inFile,line))
    {
        vector<int> temp1;
        c1 = false;
        string temp = line;

        stringstream convert(temp);
        convert >> parent111;
        temp1.push_back(parent111);

        size_t pos = line.find(':');
        line = line.substr(pos + 1);

        stringstream num(line);

        while(num >> beta)
        {
            temp1.push_back(beta);
        }

        for(int k = 0; k<temp1.size(); k++)
        {
            // cout<<temp1[k]<<endl;
            if (c1 == false)
            {
                curr = temp1[k];
            } else {
                later = temp1[k];
            }

            c1 = true;
            if (c2 == true)
            {
                node *temp_node = new node;
                for (int i = 0; i<nodes_list.size(); i++)
                {
                    int my_index = nodes_list[i]->index;
                    if (my_index == later)
                    {
                        temp_node = nodes_list[i];
                        break;
                    }
                }

                // cout<<"adding edge between : "<<nodes_list[curr]->index<<" and "<<temp_node->index<<endl;
                child son;
                son.baap = nodes_list[curr];
                son.bacha = temp_node;

                nodes_list[curr]->children_list.push_back(son);
            }
            c2 = true;
        }

        // change the c2 to false for the next row nodes edges to be added to the corresnding node children list
        c2 = false;
    }

    inFile.close();

    node* root = nodes_list[0]; // take the first element as the root node

    int min_ligh = find_min_lights(root, NULL);
    
    ans = ans + "Minimum Lights " + convert_str(min_ligh) + "\n";

    ans = ans + "{";
    for (int i = 0; i<result.size() - 1; i++)
    {
        ans = ans + convert_str(result[i]->index) + ",";
    }
    ans = ans + convert_str(result[result.size()-1]->index) + "}";

    cout<<ans;

    return 0;
}