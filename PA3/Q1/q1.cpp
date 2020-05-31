#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
Running Time Complexity = O(n^2)
In the worst case, each team might have to visit all the other locations before getting a unique final destination. We have n teams and n locations, so atmost there can be (n x n) pairs that we may have to see to deduce a stable ordering. 

---------------------------------------------------
File reading: I have made a 2D vector. The number of rows is the equal to the (number of teams) and the number of columns is equal to (2*number of teams + 1). +1 is to add the team number also. 

I have then made 2 preference lists, or 2 2D arrays to store the preferences of both the Teams and the Locations. Once I have these 2 preference lists, I simply apply the Stable Matchinng Gale–Shapley algorithm to find the most stable ordering of the teams and their final destinatins. 
The teams preferneces are stored as being least to most preffered.
The location preferences are stored as being most to lest preferred.
*/

typedef vector<tuple<int, int, int>> my_tuple;

string convert_str(int val)
{
    string str;
    stringstream convert;
    convert << val;
    str = convert.str();
    return str;
}

bool sortbysec(const tuple<int, int, int>& a, const tuple<int, int, int>& b) // sort the temp_vec on basis of the column number, so that i can get the ordering, e.g, the position when they appear in a particular team's preferrred final position
{ 
    return (get<1>(a) > get<1>(b)); 
} 

void make_loc_pref_list(int** loc_pref, int siz, my_tuple loc_indices, int curr_loc, int row_num)
{
	my_tuple temp_vec;

	if (curr_loc > siz)
	{
		return;
	}

	for(auto it = loc_indices.begin(); it != loc_indices.end(); it++)
	{
		if (get<2>(*it) == curr_loc)
		{
			temp_vec.push_back(*it);
		}
	}

	sort(temp_vec.begin(), temp_vec.end(), sortbysec); 
	
	curr_loc++;

	int var = 0;
	for (int j = 0; j < siz; j++)
	{
		loc_pref[row_num][j] = get<0>(temp_vec[var]) + 1;
        var++;
	}

	make_loc_pref_list(loc_pref, siz, loc_indices, curr_loc, row_num+1);
}

bool check_preference(int **team_pref, int **loc_pref, int pref_loc, int cft, int cet, int siz)
{
    for (int i = 0; i<siz; i++)
    {
        if (loc_pref[pref_loc][i] == cet) // if the location prefers the cet over the cft then return true and cft remains free
        {
            return true;
        }
         
        if (loc_pref[pref_loc][i] == cft) // if the location prefers the cft over the cet then return false and cet will become free
        {
            return false;
        }
    }
}

// TEAMS_PREF = LEAST TO MOST PREFFERED LOCATION
// LOC_PREF = MOST TO LEAST PREFFERED TEAM 

string stable_matching(int **team_pref, int **loc_pref, int siz)
{
    bool teams_free_list[siz]; // Initially all teams are free and not travelling thus false means that the teams are free
    for (int i = siz-1; i>= 0; i--)
    {
        teams_free_list[i] = false; 
    }

    int loc_free_list[siz]; // Initially all locations are also free -1 means that the location are free
    for (int i = 0; i<siz; i++)
    {
        loc_free_list[i] = -1;
    }

    int free_teams = siz; // Initilly all teams are free

    while(free_teams > 0) // until there exists a team that is free
    {
        int cft; // cft = Current Free Team ------ select any free team
        for (int x = 0; x < siz; x++)
        {
            if (teams_free_list[x] == false)
            {
                cft = x;
                break;
            }
        }

        for (int i = siz-1; i >= 0; i--) // visit the current team's preference list and choose the location that has the highest prefernce and that has not yet been visited
        {
            if (teams_free_list[cft] == false)  
            {   
                int pref_loc = team_pref[cft][i]; // MOST PREFFERRED LOCATION OF CURRENT TEAM THAT HAS NOT ALREADY BEEN APPROACHED

                int pl_index = pref_loc;// - 1;

                if (loc_free_list[pl_index] == -1) // IF THE LOCATION IS FREE
                // IF THE LOCATION, that the current team is trying to approach, is free(-1), then make enagge them
                {
                    loc_free_list[pl_index] = cft; // change -1 to the index of current free team (NOTE: Might need to do +1 to get 1 instead of 0 and so on)
                    teams_free_list[cft] = true; // CURRENT team is engaged so change it to true meaning it is not free
                    free_teams--;
                }

                else // IF THE LOCATION IS NOT FREE AND HAS SOME OTHER TEAM ON IT
                {
                    int cet = loc_free_list[pref_loc]; // cet = CURRENT ENGAGED TEAMstore the index of the current team that is engaged with the location

                    bool checker = check_preference(team_pref, loc_pref, pref_loc, cft, cet, siz);

                    if(checker == true) //(make a function to check whether location prefers cet over cft and return bool ans) 
                    //if ans == TRUE meaning location prefers cet over cft then no nothing
                    {
                        // do nothing as cft reamins free
                    }

                    else // MAKE cft enaged with the location and free the cet
                    {
                        teams_free_list[cet] = false;
                        teams_free_list[cft] = true;
                        loc_free_list[pref_loc] = cft;
                    }
                }
            }
        }
    }

    string ans = "";
    ans = "Final Destinations: ";
    for (int i = 0; i < siz; i++) 
    {
        ans = ans + "L" + convert_str(loc_free_list[i] + 1) + "T" + convert_str(i + 1) + ", ";
    }

    ans = ans.substr(0, ans.length()-2); // remove the extra spave and comma
    ans = ans + "\n";

    return ans;
}

int** make_list(vector<vector<string>> sched, int team_count, int loc_count)
{
    int** teams_details;
    teams_details = new int *[team_count];

    for(int x = 0; x <team_count; x++)
    {
        teams_details[x] = new int[loc_count];
    }    

    for (int i = 0; i<team_count; i++)
    {
        for (int j = 0; j<loc_count; j++)
        {
            teams_details[i][j] = 0;
        }
    }

    for (int x = 0; x<team_count; x++)
    {
        //int col = 1; // the column number from where locations start is 1 and further(increasing)

        for (int y = 0; y<loc_count; y++)
        {
            if (sched[x][y+1].substr(0,1) == "-")
            {
                teams_details[x][y] = -1;
            }

            else
            {
                int var = stoi(sched[x][y+1].substr(1,1));
                teams_details[x][y] = var;
            }
        }
    }

    return teams_details;
}

int find_diff(int diff)
{
    if (diff % 2 != 0)
    {
        diff =  diff + 2;
    }

    else
    {
        diff--;
    }

    return diff;
}

int* compare_final_dest(int** teams_details, int team_count, int loc_count, int* team_list)
{
    bool* location_list = new bool[team_count];
    int* result = new int[team_count];
    int diff = 2; // every team visits a loction after one day, so every travelling day or locations_visited are apart by a factor of 2
    int checker1 = 1;

    for(int i = 0; i<team_count; i++)
    {
        result[i] = -1;
        location_list[i] = true;
    }

    while(checker1)
    {
        for (int i = 0; i<team_count; i++)
        {   
            int pl_index = loc_count - diff;
            int pref_location = teams_details[i][pl_index];

            if(pref_location != -1)
            {
                if(location_list[pref_location - 1] == true)
                {
                    location_list[pref_location - 1] = false;
                    result[i] = pref_location;
                }
                else if (location_list[pref_location - 1] == true)
                {
                    // do nothing
                }
            }
        }

        diff = find_diff(diff);

        if(diff > loc_count || diff < 0)
        {
            break;
        }
    }

    for(int x = 0; x <team_count; x++)
    {
        for(int y = 0; y< team_count; y++)
        {
            int t_num1 = team_list[x];
            int t_num2 = team_list[y];

            int loc1 = result[t_num1];
            int loc2 = result[t_num2];

            if (loc1 >= loc2)
            {
                // do nothing 
            }
            
            else if(loc1 < loc2)
            {
                int substitute = team_list[x];
                team_list[x] = team_list[y];
                team_list[y] = substitute; 
            }
        }
    }

    return result;
}

int main(int argc, char** argv)
{
	string n, line, team, loc;
	int team_count, loc_count;
    string final_ans = "";

	string file_name = argv[1];
    fstream inFile(file_name);
    //fstream inFile("test21.txt");
    inFile>>n>>team_count;

    loc_count = 2*team_count;

    getline(inFile, line);

    vector<vector<string>> sched(team_count, vector<string>(loc_count + 1, "a")); // +1 to increase column size by 1 so that we store the team number also

    for (int i = 0; i<sched.size(); i++)
    {
    	for (int j = 0; j<sched[i].size(); j++)
    	{
    		sched[i][j] = "a ";
    	}
    }

	while(getline(inFile,line))
    {
        stringstream convert(line);
        convert >> team;

        int team_num = stoi(team.substr(1,1)); // get the team number in INT 
        
        sched[team_num-1][0] = team;

        size_t pos = line.find(':');
        line = line.substr(pos + 1);

        stringstream locati(line);
		int x = 1;     
        while(locati >> loc)
        {
        	sched[team_num -1][x] = loc;
        	x++;
        }
    }

    inFile.close();

    // ------------------**END OF FILE READING**------------------------

    //Making Prefernce Lists for both Teams and Locations

    // 1. Making Preference list for TEAMS
    int **team_pref; // PREFERENCE LIST OF THE TEAMS

    team_pref = new int *[team_count];

    for(int x = 0; x <team_count; x++)
    {
        team_pref[x] = new int[team_count];
    }

    for (int x = 0; x<team_count; x++)
    {
    	int col = 1; // the column number from where locations start is 1 and further(increasing)

        for (int y = 0; y<team_count; y++)
        {
        	if (col >= (2*team_count))
        	{
        		break;
        	}

        	else if (sched[x][col].substr(1,1) == "")
        	{
        		col++;
        	}

    		int loc_num = stoi(sched[x][col].substr(1,1));
    		team_pref[x][y] = loc_num;
    		col++;
        }
    }

    // 2. Making Preference list for LOCATIONS
    int **loc_pref; // PREFERENCE LIST OF THE LOCATIONS

    loc_pref = new int *[team_count];

    for(int q = 0; q <team_count; q++)
    {
        loc_pref[q] = new int[team_count];
    }

    for (int x = 0; x < team_count; x++)
    {
    	for (int y = 0; y < team_count; y++)
    	{
    		loc_pref[x][y] = -1;
    	}
    }

    my_tuple loc_indices;

    for (int x = 0; x<sched.size(); x++)
    {
    	int col = 1; // the column number from where locations start is 1 and further(increasing)

        for (int y = 0; y<sched[x].size(); y++)
        {
        	if (col >= (2*team_count))
        	{
        		break;
        	}

        	else if (sched[x][col].substr(1,1) == "")
        	{
        		col++;
        	}

        	int num = stoi(sched[x][col].substr(1,1));
        	loc_indices.push_back(tuple<int, int, int>(x, col, num));
    		col++;
        }
    }

    int row_num = 0;
    make_loc_pref_list(loc_pref, team_count, loc_indices, 1, row_num);

    // CALL THE STABLE MATCHING FUNCTION

    for (int i = 0; i<team_count; i++)
    {
        for(int j = 0; j<team_count; j++)
        {
            team_pref[i][j] = team_pref[i][j] -1;
            loc_pref[i][j] = loc_pref[i][j] -1;
        }
    }

    string answr = stable_matching(team_pref, loc_pref, team_count); // call the function

    int** teams_details = make_list(sched, team_count, loc_count);

    int* team_list = new int[team_count];

    for(int i = 0; i <team_count; i++)
    {
        team_list[i] = i;
    }

    int* result = compare_final_dest(teams_details, team_count, loc_count, team_list);

    final_ans = "Final Destinations: ";
    
    for(int i = 0; i < team_count; i++)
    {
        final_ans = final_ans + "L" + convert_str(result[team_list[i]]) + " T" + convert_str(team_list[i] + 1) + ", ";
    }

    int end = final_ans.length() - 2;

    final_ans = final_ans.substr(0, end);
    final_ans = final_ans + "\n";   

    cout<<final_ans;

	return 0;
}