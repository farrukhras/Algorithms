#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <queue>

/* 
DESCRIPTION:
Running Time : The insertion takes O(nlogn) time for n elements. Each insertion in the default Max heap(PQ) takes log n time. If in the worst case, we have an unsorted PQ at each insertion then we'll have to sort n elements thus O(nlogn) complexity.

I read the lengths and probabilities of each rack and store them in seperate array of length and prob respectively. Then I have used a struct to store the details of each row. I have used a PRIORITY QUEUE to store the racks based on their priority (max value of prob/length ratio). The priority queue is by default using Max Heap. So the racks are stored in decending order of prob/length ratio. 

--PQ ~ Priority Queue
After storing the row details in the PQ, I know that the PQ has values in descending order, so I simply take the top of the PQ and add its length to the total length of the racks. Then this totallength is used to find the expected timw of each rack. This GREEDY approach of finding the time of each rack once and then summing individual times gives the minimum exected time. 
*/

using namespace std;

string convert_str(double id)
{
	string str;
	stringstream convert;
	convert << id;
	str = convert.str();
	return str;
}

struct rack {
	double length, prob;
	int iden;

	/*
	I overloaded the < operator via a member function operator<(), which shall add this instance (left operand) with the rhs operand, construct a new instance containing comparing the 2 values and and return it by value. 
	The return value is declared const, so as to prevent it from being used as lvalue.

	** Overloading exaample seen online: https://www.ntu.edu.sg/home/ehchua/programming/cpp/cp7_OperatorOverloading.html **
	*/

	bool operator < (const rack& r1) const  
	{
		return prob/length < r1.prob/r1.length;
	}
};

int main(int argc, char** argv)
{
	string n, line;
    int siz;
    double entry;	

    //string file_name = argv[1];
    //fstream inFile(file_name);
    fstream inFile("test12.txt");
    inFile>>n>>siz;

    double length[siz];
    double prob[siz];

    while(getline(inFile,line))
    {
        string temp = line;       

        stringstream convert(temp);
        convert >> entry;

        if (line.substr(0,1) == "L")
        {
            size_t pos = line.find('L');
            line = line.substr(pos + 1);

            stringstream num(line);
            int i = 0;
            while(num >> entry)
            {
                length[i] = entry;   
                i++;
            }
        }
        else if (line.substr(0,1) == "p")
        {
            size_t pos = line.find('p');
            line = line.substr(pos + 1);

            stringstream num(line);
            int i = 0;
            while(num >> entry)
            {
                prob[i] = entry;   
                i++;
            }
        }
    }

    inFile.close();

    // Fill the priority_queue with racks info based on the priority (prob/length ratio).
    priority_queue <rack> pq; 

    for (int i = 0; i < siz; i++)
    {
    	rack r;
    	r.iden = i+1;
    	r.length = length[i];
    	r.prob = prob[i];
    	pq.push(r);
    }

    double r_len = 0;
    double expected_time = 0;
    string ans = "";

    for (int i = 0; i<siz-1; i++)
    {
    	rack t_r = pq.top();
    	r_len = r_len + t_r.length; 
    	expected_time = expected_time + (t_r.prob * r_len);

    	ans = ans + convert_str(t_r.iden) + " ";
    	pq.pop();
    }

    rack t_r = pq.top();
	r_len = r_len + t_r.length; 
	expected_time = expected_time + (t_r.prob * r_len);

	ans = ans + convert_str(t_r.iden);
	pq.pop();

	ans = ans + "\nExpected Time " + convert_str(expected_time);
	cout<<ans;

	return 0;
}