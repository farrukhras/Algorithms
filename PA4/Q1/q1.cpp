#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>

/*
-----Time Complexity: O(n) ~ We only need to traverse and fill the OPT array once---------

------ SubProblems: I am finding the Max Revenue till the ith WEEK each time. So if my initial higharray wasfrom [1,...,n] and low_array from [1,...,n], then I find the max revenue at say the ith day. This divides the problem into subproblems which ensures the "optimal substructure property" as the problem can be solved using solutions to subproblems. --------------

-------- BASE CASES: ------------
1. OPT[0] = 0
2. OPT[1] = Rh of the WEEK 1 (assuming that everytime we chose the high capacity job in WEEK 1, and also assuming that we have the PRIMING done for this high capacity job)

---------- Recurrence Relation: (high_arr, low_array = array of Rh and Rl for all weeks respectively) ----------------

The OPT array stores the MAX revenues after each week so OPT[0] will be 0 because there is 0 revenue after WEEK 0
Similarly, OPT[1] = high_array[0] because the MAX revenue after WEEK 1 can only be the high_capacity_job and nothing else.

OPT[0] = 0
OPT[1] = high_array[0] ----- OPT[1] is always the highest capacity job for WEEK 1
			

After that Base Cases, i = 2 to i < siz+1, OPT[i] will the MAX among:

			 { low_array[i-1] + OPT[i - 1] --- (i-1) is because we do not have any Primining Week before low_capacity_job
OPT[i] = max |
			 { high_aray[i-1] + OPT[i - 2] --- (i-2) is because we have a Primining Week before high_capacity_jobs

---------------------------------------------------------

Since there are n weeks so we'll have "n" subproblems and each sub problem takes O(1) to solve due to memoization
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

void find_optimal_sol(int low_cap_job[], int high_cap_job[], int op_sol[], bool jobs[], string schedule[], int siz)
{
	//BASE CASES
	op_sol[0] = 0; // since optimal solution array stores the max revenue AFTER each week so the revenue at week 0 will be 0 ofcourse
	op_sol[1] = high_cap_job[0]; // We assume that the machines have been primed before WEEK 1, so we choose the HIGH STRESS JOB for WEEK 1 always

	jobs[1] = true;

	// to find the max revenue AFTER the ith week, we simply add the current weeks low_capacity_job value to the op[i-1] and high_capacity_job value to the op[i-2] and see whichever is maximum, is stored in the op_sol[i] index.

	//[i-1] is done for low_capacity_array because we know that we dont need a primed day before it so we simply add the preceding value to the ith low_cap_job value
	//[i-2] is done for high_capacity_array because we know that we need a primed day before it so we simply ignore the preceding value and instead add the second last value from current op_sol[i] to the ith high_cap_job value
	for (int i = 2; i < siz+1; i++) // thus the loop runs from i = 2 to op[siz]
	{
		op_sol[i] = max((low_cap_job[i-1] + op_sol[i-1]), (high_cap_job[i-1] + op_sol[i-2]));

		if ((high_cap_job[i-1] + op_sol[i-2]) > (low_cap_job[i-1] + op_sol[i-1]))
		{
			jobs[i] = true;
		} 
	}

	int rev = siz;
	//vector<string> schedule;

	// we will now be finding the OPTIMAL SOLUTION (in terms of High/Low/Priming)
	// Here we use the jobs array (that has the status of the high_cap_jobs) to determine the actual schedule of jobs in "n" week. 
	// We start from the end of the jobs array and work our way backwards. There are 2 condtions on which we make our schedule array:
	// 1. If jobs[n] == Low, then I take the Low_cap_job into my schedule and continue for jobs[n-1]
	// 2. If jobs[n] == High, then I take the high_cap_job into my schedule, along with the Priming week,and continue for jobs[n-2]
	
	while (rev > 0) 
	{
		if (jobs[rev] == true) 
		{
			if (rev == 1)
			{
				schedule[rev-1] = "High";
				//schedule.push_back("High");
				rev -= 2;
			}
			else 
			{
				schedule[rev-1] = "High";
				schedule[rev-1-1] = "Priming";
				// schedule.push_back("High");
				// schedule.push_back("Priming");
				rev -= 2;
			}
		}
		else 
		{
			schedule[rev-1] = "Low";
			//schedule.push_back("Low");
			rev -= 1;
		}
	}
}

int main(int argc, char** argv)
{
	string n, line;
    int siz, revenue;

    string file_name = argv[1];
    fstream inFile(file_name);
    //fstream inFile("test21.txt");
    inFile>>n>>siz;

    int low_cap_job[siz];
    int high_cap_job[siz];

    while(getline(inFile,line))
    {
    	string temp = line;
        stringstream convert(temp);
        convert >> revenue;

        if (line.substr(0,1) == "R")
        {
     		if (line.substr(1,1) == "H")
     		{
     			//cout<<line.substr(3)<<endl;
     			line = line.substr(2+1);
     			stringstream num(line);
	            int i = 0;
	            while(num >> revenue)
	            {
	                high_cap_job[i] = revenue;   
	                i++;
	            }
     		}

     		else if (line.substr(1,1) == "L")
     		{
     			line = line.substr(2+1);
     			stringstream num(line);
	            int i = 0;
	            while(num >> revenue)
	            {
	                low_cap_job[i] = revenue;   
	                i++;
	            }
     		}
       }
    }

    inFile.close();

    int op_sol[siz+1]; // this array stores the optimal solution after each week so it will hold siz+1 values as first value (before week 1) will be 0 always

    int week_revenue[siz]; // this array stores the revenue of the particular capacity type job that is done each week
    string schedule[siz]; // this array stores the schedule for the solution e.g High or Low or Priming

    bool jobs[siz+1]; // this is a temp bool array to store the state of the high_cap_job per week. It will be 0 if the job for a particular week is low_capacity and 1 if the job for a particulat week is high_capacity

    for (int i = 0; i<siz+1; i++)
    {
    	op_sol[i] = 0;
    	jobs[i] = false;
    }

    find_optimal_sol(low_cap_job, high_cap_job, op_sol, jobs, schedule, siz);

	for (int i = 0; i<siz; i++) // make the week_revenue array depending on the status of job for a particular week
	{
		if(schedule[i] == "High")
		{
			week_revenue[i] = high_cap_job[i];
		}
		else if(schedule[i] == "Priming")
		{
			week_revenue[i] = 0;
		}
		if(schedule[i] == "Low")
		{
			week_revenue[i] = low_cap_job[i];
		}
	}

	//Printing the ANSWER

	string ans = "";

	for (int i = 0; i<siz; i++)
	{
		ans = ans + "Week " + convert_str(i+1) + ": " + schedule[i];
		if (schedule[i] == "Priming")
		{
			ans = ans;
		}
		else 
		{
			ans = ans + " " + convert_str(week_revenue[i]);
		}

		ans = ans + "\n";
 	}

 	ans = ans + "Total Revenue: " + convert_str(op_sol[siz]);

 	cout<<ans;

	return 0;
}