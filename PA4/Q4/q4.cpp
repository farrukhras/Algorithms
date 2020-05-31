#include <iostream>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;

/*
Time Complexity = O(mn) --- where m and n are the lengths of the strings a and b respectively
----------------------------------------------------------
Base case:
if (a.length() == 0 or b.length() == 0) then return the non empty string and return TRUE.

Recurrence: (if a char from either str_A or str_B macthes then:) 

		  { interleaving(a[i, :], b, c[i, :]) --- if char from "a" matches then recursive for [a (matched char removed), b, c (matched char removed)]
OPT[i] =  |
		  { interleaving(a, b[i, :], c[i, :]) --- if char from "b" matches then recursive for [a, b (matched char removed), c (matched char removed)]

Number of subproblems at EACH STEP = 2
i) if A charcter from string "a" or string "b" macthes with the corresponding char from string "c"
ii) if NO charcter from string "a" or string "b" macthes with the corresponding char from string "c"
*/

struct data {
	int pos;
	string val;
};

string ans = "";

bool interleaving(string a, string b, string c)
{
	// if the 3rd string (the string made by merging string a and string b) is empty then simply return false 
	if(c.length() == 0)// && (s1.length()||s2.length()))
	{
		return false;
	}

	// if string "a" or string "b" is empty then we add the non empty estirng to our answer
	else if(a.length() == 0 || b.length() == 0)
	{
		// if string "a" is empty and the first character of string "b" matches the first character of string "c"
		if(a.length() == 0 && b[0] == c[0])
		{
			for (int i = 0; i<b.length(); i++)
			{
				ans = ans + "2";
			}
			//ans = ans + "2";
		}

		// if string "b" is empty and the first character of string "a" matches the first character of string "c"
		if(b.length() == 0 && a[0] == c[0])
		{
			for (int i = 0; i<a.length(); i++)
			{
				ans = ans + "1";
			}
			//ans = ans + "1";
		}

		return true;
	}

	else if(a[0] != c[0] && b[0] != c[0]) // if the first elements of both "a" and "b" do not match "c[0]" then we know that this particular ordrering will be wrong  
	{
		return false;
	}

	else // if none of the strings are empty and first element of either string matches the first element of string "c"
	{
		if(a[0] == c[0] && b[0] == c[0]) // if both 1st char of a and b match c[0] then I chose the first element of "a" to come first in the ordering
		{
			ans = ans + "1";
			string new_a = a.substr(1, a.length()-1);
			string new_b = b.substr(1, b.length()-1);
			string new_c = c.substr(1, c.length()-1);

			bool truth_spoken = interleaving(new_a , b , new_c) || interleaving(a, new_b, new_c);
			return truth_spoken;
		}

		else if(a[0] == c[0] && b[0] != c[0]) // if a matches c and b doesn't matches c
		{
			ans = ans + "1";
			string new_a = a.substr(1, a.length()-1);
			string new_c = c.substr(1, c.length()-1);

			bool truth_spoken = interleaving(new_a , b , new_c);
			return truth_spoken;
		}

		else if(a[0] != c[0] && b[0] == c[0]) // if b matches c and 	 doesn't matches c
		{
			ans = ans + "2";
			string new_b = b.substr(1, b.length()-1);
			string new_c = c.substr(1, c.length()-1);

			bool truth_spoken = interleaving(a, new_b, new_c);
			return truth_spoken;
		}
	}
}

string print_opt_solution(string a, string b, string c)
{	
	string wth_ans = "";

	if (ans.length() == c.length())
    {
    	wth_ans = wth_ans + "VALID\n";

    	int c1 = 0;
	    int c2 = 0;
	    int curr = ans[0]; 

	    if (ans[0] == '1')
	    {
	    	wth_ans = wth_ans + "1:";
	    }
	    else
	    {
	    	wth_ans = wth_ans + "2:";
	    }

	    if (curr == '1')
	    {
	    	wth_ans = wth_ans + a[c1];
	    	c1++;
	    }
	    else 
	    {
	    	wth_ans = wth_ans + b[c2];
	    	c2++;
	    }

	    for (int i = 1; i<c.length(); i++)
	    {
	    	if (curr != ans[i])
	    	{
	    		if (ans[i] == '1')
	    		{
	    			wth_ans = wth_ans + "\n";
	    			wth_ans = wth_ans + "1:";
	    		}
	    		else 
	    		{
	    			wth_ans = wth_ans + "\n";
	    			wth_ans = wth_ans + "2:";
	    		}
	    		curr = ans[i];
	    	}

	    	if (curr == '1')
	    	{
	    		wth_ans = wth_ans + a[c1];
	    		c1++;
	    	}
	    	else
	    	{
	    		wth_ans = wth_ans + b[c2];
	    		c2++;
	    	}
	    }

	    wth_ans = wth_ans + "\n";
    }
    else
    {
    	wth_ans = wth_ans + "INVALID\n";
    }

    return wth_ans;
}

int main(int argc, char** argv)
{
	string a,b,c;

	string file_name = argv[1];
    fstream inFile(file_name);
    //fstream inFile("mytest1.txt");

    getline(inFile, a);
    getline(inFile, b);
    getline(inFile, c);

    // cout<<"s1 = "<<a<<endl;
    // cout<<"s2 = "<<b<<endl;
    // cout<<"s3 = "<<c<<endl;

    string wth_ans = "";
    bool result = interleaving(a,b,c);

    wth_ans = print_opt_solution(a, b, c); 

    cout<<wth_ans;
	return 0;
}