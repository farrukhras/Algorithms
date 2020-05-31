#include <iostream> 
#include <string.h>
#include <bits/stdc++.h>
using namespace std; 
#define INF INT_MAX

/*
--------Time Complexity----------

O(mlogm) ----- as we are passing only those indeces on which we can make a cut, e.g if we can cut on m indeces among (n-1).

-------- BASE CASE --------------

OPT[start_index][end_index] != INF -> return OPT[start_index][end_index]

OPT[start_index][end_index] == INF -> return "minimum cost to cut at the respective indeces"

-----Recurrence Relation---------

e.g: Given an array of "indeces" to cut at [1,2,3]:

               { (length - arr[0]) + optimal_ordering(start, length - arr[0], arr[1,2]) + optimal_ordering(length - arr[0], length, arr[1,2])
min_cost = min | (length - arr[1]) + optimal_ordering(start, length - arr[1], arr[0,2]) + optimal_ordering(length - arr[1], length, arr[0,2])
               { (length - arr[2]) + optimal_ordering(start, length - arr[2], arr[0,1]) + optimal_ordering(length - arr[2], length, arr[0,1])

--------- Subproblems -----------

There are logm subproblems since out tree goes m levels and it takes O(1) to solve each problemwith help of memoization.
*/

struct data {
    int index;
    int price;
};

int s = 1000;
data cut[1000][1000];
vector<int> f_answer;

string convert_str(double id)
{
    string str;
    stringstream convert;
    convert << id;
    str = convert.str();
    return str;
}

int optimal_ordering(bool positions[], int s_index, int e_index, int **opt)
{
    int opt_res = opt[s_index][e_index];

    if(opt_res != INF) // if there is already a value at the current indeces then simplt return it
    {
        return opt_res;
    }

    int min_cost = INF;

    // in this for loop, we check each value each cut and see whether cutting at this first will give more optimal cost
    // we check for all possible conditions, like first cutting at each index and then other respectively but we ignore 
    // overlapping sub problems by keeping a memo 2d array where if we have already calculated a vale for a set of indeces
    // then we donot re-calculate it, we simply return it.
    for (int i = s_index + 1; i<e_index; i++) 
    {
        if(positions[i])
        {
            int new_len = e_index - s_index;
            int cost = new_len + optimal_ordering(positions, s_index, i, opt) + optimal_ordering(positions, i, e_index, opt);
            // cout<<"index = "<<i<<" and cost = "<<cost<<endl;    

            if (cost < min_cost)
            {
                data d;
                d.index = i;
                d.price = cost; 

                cut[s_index][e_index] = d;
                min_cost = cost;
            }
        }
    }

    if (min_cost == INF) 
    {
        min_cost = 0;
    }

    opt[s_index][e_index] = min_cost; // push the minimum cost at the desired indeces
    return min_cost;
}

void print(int start, int end) // tracing back the cut 2d array to find the final optimal ordering of the cut indeces
{
    if (cut[start][end].price != -1)
    {
        f_answer.push_back(cut[start][end].index);
    }
    else
    {
        return;
    }
    print(start, cut[start][end].index);
    print(cut[start][end].index, end);
}

int main(int argc, char** argv) 
{ 
    string n, m, line;
    int length, posii;

    //string file_name = argv[1];
    //fstream inFile(file_name);
    fstream inFile("test13.txt");
    inFile>>n>>length;
    getline(inFile, line);

    vector<int> positions;
    getline(inFile, line);

    string temp = line;

    stringstream convert(temp);
    convert >> posii;

    size_t pos = line.find('m');
    line = line.substr(pos + 1);

    stringstream num(line);

    while(num >> posii)
    {
        positions.push_back(posii);
    }

    inFile.close();

    /*----------------------------------------------------------*/
    
    // e.g if index_to_cut[1] = "TRUE" then we have to cut at this index too else we donot have to cut at this index
    bool index_to_cut[length+1]; // a boolean array thar will store the status of indeces to cut at

    for (int i = 0; i<=length; i++)
    {
        index_to_cut[i] = false;
    }

    for (int i = 0; i<positions.size(); i++)
    {
        index_to_cut[positions[i]] = true;
    }

    // ---------------------------------------

    int ** opt = new int*[length + 1]; // the momo(optimal array that will store the min cost and be used to ignore recalcualting same problems again)
    for (int i =0; i <= length; i++)
    {
        opt[i] = new int [length + 1];
    }

    for (int i = 0; i <= length; i++)
    {
        for (int j=0; j <= length; j++)
        {
            opt[i][j] = INF;
        }
    }

    // -------------------------------------------

    for (int i = 0; i<s; i++)
    {
        for (int j = 0; j<s; j++)
        {
            data d;
            d.index = i;
            d.price = -1;
            cut[i][j] = d;
        }
    }

    int res = optimal_ordering(index_to_cut, 0, length, opt); // find the min_cost
    print(0, length); // store the optimal ordering of cutting indeces

    string ans = "";
    ans = ans + "Optimal cut ordering: ";

    for(int i = 0; i<f_answer.size(); i++)
    {
        ans = ans + convert_str(f_answer[i]) + " ";
    }

    ans = ans + "\n";
    ans = ans + "Least cost: " + convert_str(res);

    cout<<ans;
    return 0; 
}  
