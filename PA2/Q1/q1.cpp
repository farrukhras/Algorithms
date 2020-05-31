#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <tuple>
#include <queue>

/* 
DESCRIPTION:
Running Time : The insertion takes O(n^2logn) time for n elements. Each insertion in the default Max heap(PQ) takes O(logn) time. 
I have n rows and n columns. So in the orst case I might need to fill the enitire nxn grid thus each insertion would count up to a total complexity of O(n^2logn).

Space Complexity : 

I read the rows and column peices and stored them in seperate arrays of rows and columns respectively. Then I have used a struct to store the details of each column (column index and the no. of peices in each column). I have used a PRIORITY QUEUE to store the columns based on their priority (max of value of peices in a particular row). The priority queue is by default using Max Heap. So the columns are stored in decending order of no. of peices. 
The GREEDY approach is that we select the max peices column each time we want to add peices.

--PQ ~ Priority Queue
After storing the column details in the PQ, I know that the PQ has values in descending order, so I simply 
1. take the top of the PQ and add the current row and current column index in a tuple. 
2. Then I decrement the value of peices for each column that has stored a peice and push it in a temp priority_queue.
3. Once the row is filled with the designated number of peices, I copy the remainging column details to the temp PQ. 
   **THIS IS  DONE TO TACKLE THE ISSUE OF A SAME (ROW, COL) BEING ASSIGNED A PEICE AGAIN.**
4. Then i repeat this process for all rows. 
5. At the end if the value of each column peice is 0 then that means an ordering can be achieved and I print the ordering.
6. If any column_peie value is non zero then an ordering is not possible and i output "Not Possible".
*/

using namespace std;

typedef vector<tuple<int, int>> my_tuple;

string convert_str(int val)
{
    string str;
    stringstream convert;
    convert << val;
    str = convert.str();
    return str;
}

struct columns {
    int c_index;
    int c_pieces;

    bool operator< (columns const& c1) const
    {
       return c_pieces < c1.c_pieces;
    }
};

bool sortbysec(const tuple<int, int>& a, const tuple<int, int>& b) 
{ 
    return (get<1>(a) < get<1>(b)); 
} 

int main(int argc, char** argv)
{
	string n, line;
    int siz, entry;

    string file_name = argv[1];
    fstream inFile(file_name);
    //fstream inFile("test21.txt");
    inFile>>n>>siz;

    int arr_row[siz];
    int arr_col[siz];

    while(getline(inFile,line))
    {
        string temp = line;       

        stringstream convert(temp);
        convert >> entry;

        if (line.substr(0,1) == "R")
        {
            size_t pos = line.find('w');
            line = line.substr(pos + 1);

            stringstream num(line);
            int i = 0;
            while(num >> entry)
            {
                arr_row[i] = entry;   
                i++;
            }
        }
        else if (line.substr(0,1) == "C")
        {
            size_t pos = line.find('l');
            line = line.substr(pos + 1);

            stringstream num(line);
            int i = 0;
            while(num >> entry)
            {
                arr_col[i] = entry;   
                i++;
            }
        }
    }

    inFile.close();

    priority_queue<columns> col;

    for (int i = 0 ; i< siz; i++)
    {
        columns c;
        c.c_pieces = arr_col[i];
        c.c_index = i + 1;
        col.push(c);
    } 

    string ans = "";
    priority_queue<columns> temp1;
    my_tuple tl;
    vector<int> tuple_first_index; 

    for (int i = 0; i<siz; i++)
    {
        int row_num = arr_row[i];

        if (!temp1.empty())
        {
            col = temp1;
            while (!temp1.empty())
            {
                temp1.pop();
            }
        }

        tuple_first_index.push_back(i+1);
        for (int j = 0; j<row_num; j++)
        {
            columns c = col.top();

            int fs = i+1;
            tl.emplace_back(tuple<int, int>(fs,c.c_index));

            c.c_pieces = c.c_pieces - 1;
            temp1.push(c);
            col.pop();
        }

        while (!col.empty())
        {
            columns c = col.top();
            temp1.push(c);
            col.pop();
        }     
    }

    std::sort(tl.begin(), tl.end());
    int x = 0;
    col = temp1;

    for (int i = 0; i<siz; i++)
    {
        int r_num = arr_row[i];
        for(int j = 0; j <r_num; j++)
        {
            ans = ans + "(" + convert_str(get<0>(tl[x])) + "," + convert_str(get<1>(tl[x])) + ") ";
            x++;
        }
        ans = ans + "\n";
    }

    int sum  = 0;
    for (int i = 0; i< col.size(); i++)
    {
        columns c = col.top();
        sum = sum + c.c_pieces;
    }

    if (sum == 0)
    {
        ans = ans;
    }

    else 
    {
        ans = "Not Possible\n";
    }

    cout<<ans;

	return 0;
}