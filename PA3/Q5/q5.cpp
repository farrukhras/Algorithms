#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <iterator>

/*

Time Complexity: O(nlogn) ~~~~ O(logn) recursive steps times the O(n) taken to compare the neighbours.

When I divide an array and then find the dominant specie among that array, the number of recursive steps turn out to be logn.

The approach is much like a Binary Search. I divide the array in halves and solve for the left and right halves recursively. 
Once I hit the base case, I pass that base value to dominant_species function which counts the number of similar species by decoding it. The maximum among the results of the left and right sub arrays is the output. 

METHOD: I store the species_types in an array and then I divide that array into 2 halves. I didvide the new subarrays also recusively until the base case is hit. In the base case (if there is only one specie in the array then I simply return that specie struct).

When I return the above mentioned struct, I recursively get its neighbour too. 

-----------------------------------------------------------------------------------------------------------------------------------
****The below mentioned comparison takes O(n) time*******.
So then I call the decode () on 1. the returned specie1 and 2. the ith element of the arr. If they are equal then I incremenet the counter for returned val1. Then I call the decode () on 1. the returned specie2 and 2. the ith element of the arr.
-----------------------------------------------------------------------------------------------------------------------------------

If they are equal then I incremenet the counter for returned val2. In this way I am checking the neighbours of each specie. I then compare these counters and choose the specie which was dominant (in terms of appearing more times) in the sub array. Then I use this result and find the next dominant specie in the remerged sub arrays. This, recursively, finds all the dominant species from each subarray and then finds the dominant specie among all the dominant species. This goes on until I am left with only 1 dominat specie(based on the number of times it appeared in the array). I then return that count and print the result.

Recurrence Relation => T(n) = 2T(n/2) + 2n
*/

using namespace std;

string convert_str(int val)
{
    string str;
    stringstream convert;
    convert << val;
    str = convert.str();
    return str;
}

struct specie_struct{
	int specie_type;
	int specie_index;
};

char decode (int a, int b) // DECODE FUNCTION THAT TAKES IN TWO SPECIES AND CHECKS IF THEY ARE SAME THEN RETURNS "Y" ELSE "N"
{
	if (a == b)
	{
		return 'Y';
	}

	return 'N';
}

/* This function dominant_specie: finds the specie that has appeared more number of time by comparing it with its neighbour 
and returns that specie struct and then this struct is used to find the next dominat specie recursively*/
specie_struct dominant_specie(vector<specie_struct> arr, int start_index, int end_index, int& domi_count, specie_struct val1, specie_struct val2, int c1, int c2)
{
	for (int i = start_index; i<end_index; i++)
	{
		char val1_comp = decode(arr[i].specie_type, val1.specie_type); // returns Y if specie type is same as the one in arr
		char val2_comp = decode(arr[i].specie_type, val2.specie_type); // returns Y if specie type is same as the one in arr
		
		if (val1_comp == 'Y')
		{
			//cout<<"compring arr val = ("<<arr[i].specie_type<<","<<arr[i].specie_index<<") with val1 = ("<<val1.specie_type<<","<<val1.specie_index<<")   ";
			c1++;
			//cout<<"c1 = "<<c1<<"    c2 = "<<c2<<endl;
		}

		if (val2_comp == 'Y')
		{
			//cout<<"compring arr val = ("<<arr[i].specie_type<<","<<arr[i].specie_index<<") with val2 = ("<<val2.specie_type<<","<<val2.specie_index<<")   ";
			c2++;
			//cout<<"c1 = "<<c1<<"    c2 = "<<c2<<endl;
		}
	}

	if(c1 <= c2)
	{
		domi_count = c2;
		//cout<<"val2 = "<<val2.specie_type<<"index : "<<val2.specie_index<<endl;
		return val2;
	}

	else
	{
		domi_count = c1;
		//cout<<"val1 = "<<val1.specie_type<<"index : "<<val1.specie_index<<endl;
		return val1;
	}
}

specie_struct find_species(vector<specie_struct> arr, int start_index, int end_index, int& domi_count)
{
	if (start_index == end_index-1) // BASE CASE (when we only have an array with one element we simply return it)
	{
		return arr[start_index];
	}

	int mid_point = (start_index + end_index) / 2;

	specie_struct val1 = find_species(arr, start_index, mid_point, domi_count);
	//cout<<"type val1 = "<<val1.specie_type<<endl;
	specie_struct val2 = find_species(arr, mid_point, end_index, domi_count);
	//cout<<"type val2 = "<<val1.specie_type<<endl;

	int c1 = 0, c2 = 0; 

	return dominant_specie(arr, start_index, end_index, domi_count, val1, val2, c1, c2);
}

int main(int argc, char** argv)
{
	string n, m, line;
    int siz, species_kinds, kind;

    string file_name = argv[1];
    fstream inFile(file_name.c_str());
    //fstream inFile("test15.txt");
    inFile>>n>>siz;
    inFile>>m>>species_kinds;

    // cout<<n<<" "<<siz<<endl;
    // cout<<m<<" "<<species_kinds<<endl;

    vector<specie_struct> arr;

    getline(inFile, line);
    getline(inFile, line);
  	
  	stringstream ss(line);
	for (int i = 0; i<siz; i++)
	{
		ss>>kind;
		specie_struct sp;
		sp.specie_type = kind;
		sp.specie_index = i;
		arr.push_back(sp);
	}
  	
  	/*--- END OF FILE READING*/

	int domi_count = 0;
	string ans = "";
	vector<int> species_indeces;

  	specie_struct r = find_species(arr, 0, siz, domi_count);

  	for (int itr = 0; itr<siz; itr++)
  	{
  		if (arr[itr].specie_type == r.specie_type)
  		{
  			species_indeces.push_back(arr[itr].specie_index);
  		}
  	}

  	// cout<<domi_count<<endl;
  	// cout<<r.specie_type<<endl;
  	
  	if (domi_count > (siz/2))
  	{
  		ans = ans + "Success\n";
  		ans = ans + "Dominant Species Count " + convert_str(domi_count) + "\n";
  		ans = ans + "Dominant Species Indices ";

  		for (int i = 0;i<species_indeces.size(); i++)
  		{
  			ans = ans + convert_str(species_indeces[i]) + " ";
  		}
		ans = ans.substr(0,ans.length()-1) + "\n";
  	}
  	else 
  	{
  		ans = ans + "Failure\n";
  	}

  	cout<<ans;

	return 0;
}
