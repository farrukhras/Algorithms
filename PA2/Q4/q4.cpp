#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

/*
Runnign time complexity is O(kn) where k is the number of distinct doors and n is the number of combinations of door. 
*/

string convert_str(int val)
{
    string str;
    stringstream convert;
    convert << val;
    str = convert.str();
    return str;
}

string result(int k_val, vector<pair<string, bool>> pairs, bool status)
{
	string f_res;
	string wth = "Yes";
	string ohh = "No";

	if(status == true) // if the status of door is true then print which door to open (simple door ya us ka antidoor)
	{
		f_res = wth + "\n";
		vector<string> answers;
		bool found = false;

		for(int i = 0; i<k_val; i++)
		{
			found = false;
			for(int j = 0; j<pairs.size(); j++)
			{
				if(pairs[j].first == 'd' + convert_str(i))
				{
					if(pairs[j].second == false)
					{
						answers.push_back("0");
				    	break;	
				    }

				    else if (pairs[j].second == true)
				    {
				    	found = true;
						answers.push_back("1");
						break;
				    }
				}
				else
				{
					continue;
				}
			}
				
	        if(found == false)
	        {
	        	answers.push_back("0");
	        }
		}

		for(int i = 0; i<k_val-1; i++)
		{
			f_res = f_res + answers[i] + "\n";
		}

		f_res = f_res + answers[k_val-1];
	}

	else // warna print "NO"
	{
		f_res = ohh + "\n";
	}

	return f_res;
}

int main(int argc, char** argv)
{
	string n, k, line, door;
	int siz, k_val;
	int hard = 0;

	vector<pair<string, bool>> pairs;
	vector<int> ratio;
	vector<bool> curr_status; // vector that stores the status of open and closed doors

	string file_name = argv[1];
    fstream inFile(file_name);
    //fstream inFile("test14.txt");
    inFile>>n>>siz;
    inFile>>k>>k_val;

    // getline(inFile, line);
    // getline(inFile, line);

    while(getline(inFile,line))
	{
		stringstream convert(line);

	    while(convert >> door)
	    {
	    	pairs.push_back(make_pair(door,false));
	    }

	}

	// for(int i = 0; i<pairs.size(); i++)
	// {
	// 	cout<<pairs[i].first<<" "<<pairs[i].second<<endl;
	// }

	//**** END OF FILE READING ****

	for(int i = 0; i<k_val ; i++)
	{
		int ratio_val = 0;
		int count1 = 0; // to count simple doors
		int count2 = 0; // to count anti doors

		for(int j = 0; j<pairs.size(); j++)
		{
			if (pairs[j].first == 'd' + convert_str(i))
			{
				count1++;
			}

			else if(pairs[j].first == "da" + convert_str(i))
			{
				count2++;
			}
		}

		ratio_val = count1 - count2;
		ratio.push_back(ratio_val);
	}

	// for each ratio of doors vs antidoors, if the ratio is less than 0 then search for the anti doors in the pairs vector and mark it as true (as open) else mark the simple door as true (as open).
	for(int x = 0 ; x < ratio.size(); x++)
	{
		if(ratio[x] < 0)
		{
			for(int y = 0; y < pairs.size(); y++)
			{
				if(pairs[y].first == "da" + convert_str(hard))
				{
					pairs[y].second = true;
				}
			}
			hard++;
		}

		else if(ratio[x] >= 0)
		{
			for(int z = 0; z < pairs.size(); z++)
			{
				if(pairs[z].first == 'd' + convert_str(hard))
				{
					pairs[z].second = true;
				}
			}
			hard++;	
		}	
	}

	pair <string,bool> bi_array[siz][2]; // making a 2D array of pairs, where each pair stores a door and its state (true = open, false = close)

	for(int i = 0; i<siz; i++) // initialize the 2D array with pairs (door and its status)
	{
		for(int j = 0; j < 2; j++)
		{
			bi_array[i][j] = make_pair(pairs[i].first, pairs[i].second);
		}
	}

	for(int i = 0; i<siz; i++) // here I check whether the door is open or close. In either case I store its status in a curr_status vector.
	{
		for(int j = 0; j<2; j++)
		{
			if(bi_array[i][j].second == false)
			{
				curr_status.push_back(false);
				break;
			}

			else
			{
				curr_status.push_back(true);
				break;
			}
		}
	}

	bool status = true;

	for(int i = 0; i<curr_status.size(); i++)  // update the bool variable status to false if the current status of a door is closed and then use this status to print "No". If the status of current door is true then check is unchanged and we print the pattern in which we can open all doors.
	{
		if(curr_status[i] != true)
		{
			status = false;
			break;
		}
	}

	string res = result(k_val, pairs, status);
	
	cout<<res;

	return 0;
}