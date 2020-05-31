#include <iostream>
#include <string.h>
#include <cstdio>
#include <cmath>
#include <queue> 
#include <fstream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

/*
Time Complexity : O(n)

After reading the tree nodes from the file, I have stored them in a vector and I constructed a Binary Tree from the given vector that stored the nodes in a level_order manner. The time complexity of Construct inga complete binary tree from given array in level order fashion is O(n). I have made a struct for each node. The struct stores the following details for each node:
1. Its value
2. Its x_value (this is stored so that I can assign the x1,x2....xn value to the leaf nodes as shown in the pdf).
3. Its left child pointer
4. Its right child pointer

After constructing the tree, I DIVIDE the tree into left and right sub trees, given the root node. Once I hve the left and right suntrees, I recusively divide them and find the path that gives the max sum(adding the values of the nodes). This process of finding the max path sum also takes O(n) time. 

Once I have this sum, I find the next path that will give me the MAX value of the Ancestory. Again O(n) time. 

Once I have the two paths that give me the MAX Ancestory, I simply add both nodes in both paths to a set<int>, to take their UNION, and sum the set values (the duplicate values are catered here).

***********************************************
Recurrence Relation =>> T(n) = 2T(n/2) + c
***********************************************
*/

typedef vector<tuple<int, int>> my_tuple;

string convert_str(int val)
{
    string str;
    stringstream convert;
    convert << val;
    str = convert.str();
    return str;
}

struct Node {
    int val;
    int level_number;
    bool visit_status;
    int x_val;
    Node* left;
    Node* right;
};

Node* newnode(int data, int l_num) // make a new node
{ 
    Node* node = new Node;//(Node*)malloc(sizeof(Node)); 
    node->val = data;
    node->level_number = l_num;
    node->visit_status = false;
    node->x_val = 0;
    node->left = NULL;
    node->right = NULL; 
    return node; 
} 

Node* insertLevelOrder(vector<int> arr, Node* root, int i, int siz, int l_num) // make a tree using the level order traversal(given to us in an array). 
{
    if (i < siz)
    {
        Node* temp = newnode(arr[i], l_num);
        root = temp;

        l_num++;
        root->left = insertLevelOrder(arr, root->left, 2*i+1, siz, l_num);
        root->right = insertLevelOrder(arr, root->right, 2*i+2, siz, l_num);
    }
    return root;
}

void assign_x_value_to_leaf(Node* root, int& x) // this function assigns the x values to the leaf nodes
{
    if (root == NULL)
    {
        return;
    }

    if (root->left == NULL && root->right == NULL)
    {
        root->x_val = x;
        x++;
        return;
    }

    if(root->left)
    {
        assign_x_value_to_leaf(root->left, x);   
    }

    if(root->right)
    {
        assign_x_value_to_leaf(root->right, x);
    }
}

// void printLevelorder(Node* root, my_tuple& result)
// {
//     if (root == NULL)
//     {
//         return;
//     }

//     queue<Node *> q;
//     q.push(root);

//     while(q.empty() == false)
//     {
//         Node* nod = q.front();

//         //------------------------------------------------------
//         //YE SARI KHAWARI IS LIYE KI HAI SO THAT LEVEL WISE STORE KARTE HUWE REPETITIONS NA AJAIYAIN BHARWI

//         auto t = make_tuple(nod->val, nod->level_number);        

//         auto it = find_if(result.begin(), result.end(), [&t](const auto& item) 
//         {
//             return get<0>(t) == get<0>(item) && get<1>(t) == get<1>(item);
//         });
        
//         if (it != result.end()) 
//         {
//           //cout << "This node already exists with given level number" <<endl;
//         }

//         else
//         {
//             result.push_back( tuple<int, int>(nod->val, nod->level_number));
//         }
//         // ---------------------------------------------------------

//         q.pop();

//         Node* left_child = nod->left;
//         Node* right_child = nod->right;

//         if(left_child != NULL)
//         {
//             q.push(left_child);
//             result.push_back(tuple<int, int>(left_child->val, left_child->level_number));
//         }

//         if (right_child != NULL)
//         {
//             q.push(right_child);
//             result.push_back(tuple<int, int>(right_child->val, right_child->level_number));
//         }
//     }
// }

int find_max_ancestor_sum(Node* root) // find the path with the max sum
{
    if (root == NULL)
    {
        return 0;
    }

    int left_max_sum = find_max_ancestor_sum(root->left);
    int right_max_sum = find_max_ancestor_sum(root->right);

    if (left_max_sum > right_max_sum)
    {   
        return left_max_sum + root->val;
    }

    else
    {
        return right_max_sum + root->val;
    }
}

bool max_path_print(Node* root, int sum, vector<int>& max_path) // store the nodes that appear in the max path ina vector
{
    if (sum == 0)
    {
        return true;
    }

    if (root == NULL)
    {
        //cout<<"root null"<<endl;
        return false;
    }

    int new_sum = sum - root->val;
    //cout<<"new sum = "<<sum<<" - "<<root->val<<" = "<<new_sum<<endl<<endl;
    Node* left_child = root->left;
    Node* right_child = root->right;

    // if (left_child == NULL || right_child == NULL)
    // {
    //     cout<<"child is null"<<endl;
    // }

    bool left_tree = max_path_print(left_child, new_sum, max_path);
    bool right_tree = max_path_print(right_child, new_sum, max_path);

    if(left_tree || right_tree)
    {
        max_path.push_back(root->val);
    }
    
    return left_tree || right_tree;
}

int max_ancestory_one_node(Node* root) // return the sum of the max path
{
    int sum = find_max_ancestor_sum(root);

    return sum;
}

bool find_node(Node* root, int val, int sum) // FIND THE NODE TO CHANGE THE VALUE OF THE MAX LEAF NODE, SO THAT WE CAN FIND THE SECOND MAX
{
    if(root == NULL)
    {
        //cout<<"root null"<<endl;
        return false;
    }
    if (root->val == val)
    {
        root->visit_status = true;
        root->val = sum - 2*sum;
        return true;
    }

    bool left_check = find_node(root->left, val, sum);
    bool right_check = find_node(root->right, val, sum);

    return left_check || right_check;
}

bool find_node_xvalue(Node* root, int val, int& x_val_ans) // FIND A GIVEN NODE AND GET ITS X VALUE
{
    if(root == NULL)
    {
        return false;
    }

    if (root->val == val)
    {
        x_val_ans = root->x_val;
        return true;
    }

    bool left_check = find_node_xvalue(root->left, val, x_val_ans);
    bool right_check = find_node_xvalue(root->right, val, x_val_ans);

    return left_check || right_check;
}

int main(int argc, char** argv)
{
    string h, line;
    int height, node;

    string file_name = argv[1];
    fstream inFile(file_name);
    //fstream inFile("test24.txt");
    inFile>>h>>height;

    int num_leaf_nodes = pow(2, height);

    int siz = (2*num_leaf_nodes) - 1; // total number of nodes in the tree

    vector<int> level_order;

    getline(inFile, line);
    getline(inFile, line);

    stringstream ss(line);
    for (int i = 0; i<siz; i++)
    {
        ss>>node;
        level_order.push_back(node);
    }

    // ------------END OF FILE READING-----------------

    int k = 0;
    int x = 0;
    vector<int> temp; // to store the inorder traversal

    my_tuple result;
    int l_num = 1;

    Node* root = insertLevelOrder(level_order, root, 0, siz, l_num);

    int x_v = 1;
    assign_x_value_to_leaf(root, x_v);

    // ***********************************************************************************************

    int sum = max_ancestory_one_node(root);

    vector<int> max_path;
    max_path_print(root, sum, max_path); // Finding the first MAXIMUM PATH IN THE TREE

    int value_to_be_found = max_path[0];

    int x_val_max1 = 0;  // THE X_VALUE OF THE FIRST MAX LEAF NODE
    find_node_xvalue(root, value_to_be_found, x_val_max1);

    find_node(root, value_to_be_found, sum);

    // ***********************************************************************************************

    int sum1 = max_ancestory_one_node(root);

    vector<int> max_path1;
    max_path_print(root, sum1, max_path1); // Finding the second MAXIMUM PATH IN THE TREE

    int x_val_max2 = 0;  // THE X_VALUE OF THE FIRST MAX LEAF NODE
    find_node_xvalue(root, max_path1[0], x_val_max2);

    // ***********************************************************************************************

    // CONVERTING TO THE GIVEN FORMAT

    set<int> s;

    for (int i = 0; i < max_path.size(); i++)
    {
        s.insert(max_path[i]);
    }

    for (int i = 0; i < max_path1.size(); i++)
    {
        s.insert(max_path1[i]);
    }

    string ans = "";

    ans = ans + "(xi,xj) = ";
    ans = ans + "(" + "x" + convert_str(x_val_max2) + "," + "x" + convert_str(x_val_max1) + ")\n";

    ans = ans + "Ancestry x" + convert_str(x_val_max2) + " = "  + "{";

    for (int i = 0; i < max_path1.size() - 1; i++)
    {
        ans = ans + convert_str(max_path1[i]) + ", ";
    }

    ans = ans + convert_str(max_path[max_path1.size()-1]) + "}\n";

    ans = ans + "Ancestry x" + convert_str(x_val_max1) + " = "  + "{";

    for (int i = 0; i < max_path.size() - 1; i++)
    {
        ans = ans + convert_str(max_path[i]) + ", ";
    }

    ans = ans + convert_str(max_path[max_path.size()-1]) + "}\n";

    ans = ans + "Value of Max Ancestry " + "(x" + convert_str(x_val_max2) + ",x" + convert_str(x_val_max1) + ") = ";

    int sum_resu = 0;

    for (auto it = s.begin(); it != s.end(); it++) 
    {
        sum_resu = sum_resu + *it;
    }

    ans = ans + convert_str(sum_resu) + "\n";

    cout<<ans;

    return 0;
}