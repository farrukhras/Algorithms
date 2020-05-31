#include <iostream> 
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
using namespace std; 

/*
Running Time Complexity: O(n^2)

Method:
I make a 2D array and initialize the box (given to us in file, using the indexes) as -1.

Then I split the 2D matrix into 4 Quadrants by finding the mid of the 2D array. Once I have the mid point:
I use this mid point to add a boomerang (L shaped) in the middle of the 2d matrix. I add this boomerang such that a number, associated with boomerang, is not in that Quadrant in which we had that block which we first read from the file. 
After this step, I now have one block in each quadrant, such that i cannot add a value in that block. 
I am also passing the size of the quadrant.

So I recursively use the above approach for each of the 4 Quadrants (1,2,3,4) and add a bomomerang at the center of each Quadrant. 
I do the above until I hit the base case.

Base Case : if the size of the quadrant is 2x2 (i have a 2x2 matrix), then I know that there is one block which already has a value in it, so I simply fill the remaining 3 blocks with a boomerang. In this way each quadrant is filled with different boomerangs and no block is left empty, except for the one which was passed to us in the file reading. 

*************************************************
Recurrence Relation =>> T(n) = 4T(n/2) + c
*************************************************
*/

string convert_str(int val)
{
    string str;
    stringstream convert;
    convert << val;
    str = convert.str();
    return str;
}

struct Point{
    int x_index;
    int y_index;
};

struct BOOMERANGS {
    Point pair1,pair2,pair3;
    int num;
};

int i = 1;

vector<BOOMERANGS> ans;

void fill_array(int **arr, int row_start, int mid_row, int col_start, int mid_col, Point p, int siz) //Point P is the point we are given in the file where kuch nahi dalna
{
    Point p1, p2, p3, p4;
    
    if (siz == 2) // BASE CASE (if block is a 2x2, then we just have to add a boomerang!!!])
    {
        if (p.x_index >= mid_row) // Point is in Q3 or Q4
        {
            if (p.y_index < mid_col) // Quadrant 3
            {
                arr[mid_row][mid_col] = i;
                arr[mid_row-1][mid_col-1] = i;
                arr[mid_row-1][mid_col] = i;    

                p1.x_index = mid_row-1;
                p1.y_index = mid_col-1;

                p2.x_index = mid_row-1;
                p2.y_index = mid_col;

                p3 = p;

                p4.x_index = mid_row;
                p4.y_index = mid_col;

                BOOMERANGS b;
                b.pair1 = p1;
                b.pair2 = p2;
                b.pair3 = p4;
                b.num = i;

                ans.push_back(b);
            }

            else if (p.y_index >= mid_col) // Quadrant 4
            {
                arr[mid_row][mid_col-1] = i;
                arr[mid_row-1][mid_col-1] = i;
                arr[mid_row-1][mid_col] = i; 

                p1.x_index = mid_row-1;
                p1.y_index = mid_col-1;

                p2.x_index = mid_row-1;
                p2.y_index = mid_col;

                p3.x_index = mid_row;
                p3.y_index = mid_col-1;

                p4 = p;

                BOOMERANGS b;
                b.pair1 = p1;
                b.pair2 = p2;
                b.pair3 = p3;
                b.num = i;

                ans.push_back(b);
            }
        }

        else if (p.x_index < mid_row) // Point is in Q1 or Q2
        {
            if (p.y_index < mid_col) // Quadrant 1
            {
                arr[mid_row][mid_col] = i;
                arr[mid_row][mid_col-1] = i;
                arr[mid_row-1][mid_col] = i; 

                p1 = p;

                p2.x_index = mid_row-1;
                p2.y_index = mid_col;

                p3.x_index = mid_row;
                p3.y_index = mid_col-1;

                p4.x_index = mid_row;
                p4.y_index = mid_col;

                BOOMERANGS b;
                b.pair1 = p2;
                b.pair2 = p3;
                b.pair3 = p4;
                b.num = i;

                ans.push_back(b);
            }

            else if (p.y_index >= mid_col) // Quadrant 2
            {
                arr[mid_row][mid_col] = i;
                arr[mid_row][mid_col-1] = i;
                arr[mid_row-1][mid_col-1] = i; 

                p1.x_index = mid_row-1;
                p1.y_index = mid_col-1;

                p2 = p;

                p3.x_index = mid_row;
                p3.y_index = mid_col-1;

                p4.x_index = mid_row;
                p4.y_index = mid_col;

                BOOMERANGS b;
                b.pair1 = p1;
                b.pair2 = p3;
                b.pair3 = p4;
                b.num = i;

                ans.push_back(b);
            }
        }

        i++;
        return;
    }

    else //IF NOT BASE CASE THEN THIS
    {
        if (p.x_index >= mid_row) // Point is in Q3 or Q4
        {
            if (p.y_index < mid_col) // Quadrant 3
            {
                arr[mid_row][mid_col] = i;
                arr[mid_row-1][mid_col-1] = i;
                arr[mid_row-1][mid_col] = i;    

                p1.x_index = mid_row-1;
                p1.y_index = mid_col-1;

                p2.x_index = mid_row-1;
                p2.y_index = mid_col;

                p3 = p;

                p4.x_index = mid_row;
                p4.y_index = mid_col;

                BOOMERANGS b;
                b.pair1 = p1;
                b.pair2 = p2;
                b.pair3 = p4;
                b.num = i;

                ans.push_back(b);
            }

            else if (p.y_index >= mid_col) // Quadrant 4
            {
                arr[mid_row][mid_col-1] = i;
                arr[mid_row-1][mid_col-1] = i;
                arr[mid_row-1][mid_col] = i; 

                p1.x_index = mid_row-1;
                p1.y_index = mid_col-1;

                p2.x_index = mid_row-1;
                p2.y_index = mid_col;

                p3.x_index = mid_row;
                p3.y_index = mid_col-1;

                p4 = p;

                BOOMERANGS b;
                b.pair1 = p1;
                b.pair2 = p2;
                b.pair3 = p3;
                b.num = i;

                ans.push_back(b);
            }
        }

        else if (p.x_index < mid_row) // Point is in Q1 or Q2
        {
            if (p.y_index < mid_col) // Quadrant 1
            {
                arr[mid_row][mid_col] = i;
                arr[mid_row][mid_col-1] = i;
                arr[mid_row-1][mid_col] = i; 

                p1 = p;

                p2.x_index = mid_row-1;
                p2.y_index = mid_col;

                p3.x_index = mid_row;
                p3.y_index = mid_col-1;

                p4.x_index = mid_row;
                p4.y_index = mid_col;

                BOOMERANGS b;
                b.pair1 = p2;
                b.pair2 = p3;
                b.pair3 = p4;
                b.num = i;

                ans.push_back(b);
            }

            else if (p.y_index >= mid_col) // Quadrant 2
            {
                arr[mid_row][mid_col] = i;
                arr[mid_row][mid_col-1] = i;
                arr[mid_row-1][mid_col-1] = i; 

                p1.x_index = mid_row-1;
                p1.y_index = mid_col-1;

                p2 = p;

                p3.x_index = mid_row;
                p3.y_index = mid_col-1;

                p4.x_index = mid_row;
                p4.y_index = mid_col;

                BOOMERANGS b;
                b.pair1 = p1;
                b.pair2 = p3;
                b.pair3 = p4;
                b.num = i;

                ans.push_back(b);
            }
        }
    }

    i++;
    int n_siz = siz/2;

    fill_array(arr, row_start, (mid_row+row_start)/2, col_start, (mid_col + col_start)/2, p1, n_siz);
    fill_array(arr, row_start, (mid_row+row_start)/2, mid_col, (mid_col - col_start)/2 + mid_col, p2, n_siz); 
    fill_array(arr, mid_row, (mid_row-row_start)/2 + mid_row, col_start, (col_start + mid_col)/2, p3, n_siz); 
    fill_array(arr, mid_row, (mid_row-row_start)/2 + mid_row, mid_col, (mid_col - col_start)/2 + mid_col, p4, n_siz);           
}

int main(int argc, char** argv) 
{ 
    string n, line;
    char bra1, comma, bra2;
    int siz, index1, index2;

    string file_name = argv[1];
    fstream inFile(file_name);
    //fstream inFile("test13.txt");
    inFile>>n>>siz;

    getline(inFile, line);
    getline(inFile, line);
    
    //cout<<line<<endl;
    stringstream ss(line);
    ss >> bra1 >> index1 >> comma >> index2 >> bra2;

    /* ---- END OF FILE READ ------*/

    Point read_p;
    read_p.x_index = index1;
    read_p.y_index = index2;

    // Make a 2d Array
    int **arr;
    arr = new int *[siz];
    for(int x = 0; x <siz; x++)
    {
        arr[x] = new int[siz];
    }

    for (int x = 0; x<siz; x++)
    {
        for (int y = 0; y<siz; y++)
        {
            arr[x][y] = 0;
        }
    }

    arr[index1][index2] = -1;
    int mid_point = siz /2;

    string result = "";

    fill_array(arr, 0, mid_point, 0, mid_point, read_p, siz); // MAIN FUNCTION CALL

    for (int f = 0; f < ans.size(); f++)
    {
        result = result + convert_str(ans[f].num) + " (" + convert_str(ans[f].pair1.x_index) + "," + convert_str(ans[f].pair1.y_index) + ") ";
        result = result + "(" + convert_str(ans[f].pair2.x_index) + "," + convert_str(ans[f].pair2.y_index) + ") ";
        result = result + "(" + convert_str(ans[f].pair3.x_index) + "," + convert_str(ans[f].pair3.y_index) + ")\n";  
    }

    cout<<result;

    return 0; 
} 
