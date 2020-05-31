#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <tuple>
#include <queue>
using namespace std;

/*
The running time complexity is O(nlogn).

Method: 
I have used a merge sort driven divide and conquer algorithm to solve this problem.
I read the cells from the file and store them in a struct. The struct stores info about each each day: the day number and the number of immune cells on the day. I have used an array of structs for this problem. I divide the this array into 2 parts, namely left sub array and right sub array. I recursively divide these arrays and sort them using Merge sort which tkes O(nlogn) time to sort the array.
Additonally, I have implemented the "Counting Inversions" technique to find the number of Failed Trials. During the merge sort and merhing of the 2 sub arrays, I use 2 indexex, i and j as the starting points for say, arr1 and arr2. At each step (merging of sub arrays), I check wheter or not the cells in the ith index array are greater than twice the cells in jth index sub array. If this condition is true then we have a inverson(Failed Trial). This also means that all the values to the left of the current ith index are also Failed tests as they are:
1. greater than the current ith value so if we compare them with the jth value, they will alwasy be more that twice the jth value.
e.g 
arr1 = (6,7,8)
arr2 = (2,3,5)
we initailly have i = 0; and j = 3

so arr1[i] > 2*(arr2[j]) this tells that we have a Failed test, as we can see 7 and 8 will also Failed tests (as the arrays are in sorted order). Thus we donot check for them and simply add (mid-i) to our failed tests counter. 

This is recursively done whenever any 2 subarrays are merged together and the failed test counter is returned at the end.

Divide and Conquer:
Divide : divide the array in sub arrays
Conquer : recursively merge and count the inversions in those sub arrays
*/

string convert_str(int val)
{
    string str;
    stringstream convert;
    convert << val;
    str = convert.str();
    return str;
}

struct experiment {
    int day;
    int cells;
};

int merge_arrays(experiment results[], experiment sorted_array[], int first_index, int mid_point, int last_index, vector<pair<int, int>> &pairs)
{
	int inversions = 0;

	int i = first_index;
	int k = first_index;
	int j = mid_point;

	while((i <= mid_point - 1) && (j <= last_index)) // this loop counts the number of inversions in an array
	{
		if(results[i].cells > 2*results[j].cells)
		{
			pairs.push_back(make_pair(results[j].day, results[i].day));
			inversions = inversions + (mid_point - i);

            int point = i + 1 ;
            
            while (point < mid_point)
            {
            	cout<<"this = ";//<<results[point].day<<endl;
            	pairs.push_back(make_pair(results[j].day, results[point].day));
                point++ ;
            }

			j++; 
		}

		else
		{
			i++;
			// pairs.push_back(make_pair(results[j].day, results[i].day));
			// inversions = inversions + (mid_point - i);
			// int point = i + 1 ;
            
            //while (point < mid_point)
            //{
            //	pairs.push_back(make_pair(results[j].day, results[point].day));
			//	point++ ;
   			//}
		}
	}

	i = first_index;
	k = first_index;
	j = mid_point;

	while((i <= mid_point - 1) && (j <= last_index))
	{
		if(results[i].cells <= results[j].cells)
		{
			sorted_array[k] = results[i];
			k++;
			i++;
		}
		else
		{
			sorted_array[k] = results[j];
			k++;
			j++;
		}
	}

	// for (int y = 0; y<sorted_array.size(); y++)
	// {
	// 	cout<<sorted_array[y].day<<"   "<<sorted_array[y].cells<<endl;
	// }

	while (i <= mid_point - 1) 
	{
		sorted_array[k] = results[i];
		k++;
		i++;
	}
  
    while (j <= last_index) 
    {
    	sorted_array[k] = results[j];
    	k++;
    	j++;
 	}

 	// for (int y = 0; y<sorted_array.size(); y++)
	// {
	// 	cout<<sorted_array[y].day<<"   "<<sorted_array[y].cells<<endl;
	// }

    for (int x = first_index; x <= last_index; x++) 
    {
    	//cout<<results[y].day<<"   "<<results[y].cells<<endl;
    	results[x] = sorted_array[x];
  	}

	return inversions;
}

int merge_and_count(experiment results[], experiment sorted_array[], int first_index, int last_index, vector<pair<int, int>> &pairs)
{
	int mid_point;
	int inversions = 0;

	if (last_index > first_index)
	{
		mid_point = (last_index + first_index)/2;

		inversions = merge_and_count(results, sorted_array, first_index, mid_point, pairs); // find the inversions in left e

		inversions = inversions + merge_and_count(results, sorted_array, mid_point + 1, last_index, pairs); // find the inversions in right sub_array

		inversions = inversions + merge_arrays(results, sorted_array, first_index, mid_point + 1, last_index, pairs); // find the inversions between left and right sub_arrays
	}

	else
	{

	}

	return inversions;
}

int main(int argc, char** argv)
{
	string n, line;
    int siz, entry;
    int d = 0;

    string file_name = argv[1];
    fstream inFile(file_name);
    //fstream inFile("test12.txt");
    inFile>>n>>siz;

    experiment results[siz];

    while(getline(inFile,line))
    {
        stringstream convert(line);
        while (convert >> entry)
        {
        	results[d].day = d;
        	results[d].cells = entry;
        	d++;
        }
    }

    /*-------END OF FILE READING--------*/

    vector<pair<int, int>> pairs;
    experiment sorted_array[siz];

    int last_index = siz - 1;
    int inversions = merge_and_count(results, sorted_array, 0, last_index, pairs);

    sort(pairs.begin(), pairs.end()); 


    /*-----------Printing the final answer------------*/


    string ans = "Failed Trials " + convert_str(inversions) + "\n";

    if (inversions != 0)
    {
    	for (int i = 0; i< pairs.size(); i++)
	    {
	    	if (i <= 0)
	    	{
	    		ans = ans + "(" + convert_str(pairs[i].first) + "," + convert_str(pairs[i].second) + ") ";
	    	}

	    	else
	    	{
	    		if (pairs[i].first > pairs[i-1].first)
	    		{
	    			ans = ans + "\n";
	    			ans = ans + "(" + convert_str(pairs[i].first) + "," + convert_str(pairs[i].second) + ") "; 
	    		}
	    		else
	    		{
	    			ans = ans + "(" + convert_str(pairs[i].first) + "," + convert_str(pairs[i].second) + ") "; 
	    		}
	    	}
	    }
    }

    ans = ans + "\n";

    cout<<ans;

	return 0;
}