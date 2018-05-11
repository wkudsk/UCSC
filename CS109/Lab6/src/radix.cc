/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include "radix.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <thread>

using namespace std;
//http://www.cplusplus.com/reference/algorithm/sort/
bool compareTo(unsigned int i, unsigned int j)
{
	
	string i_toString = to_string(i);
	string j_toString = to_string(j);
	//http://www.cplusplus.com/reference/string/string/compare/
	return (i_toString.compare(j_toString) <= 0); 
}

void sortList(std::vector<unsigned int>* list)
{
	//http://www.cplusplus.com/reference/algorithm/sort/
	sort(list->begin(), list->end(), compareTo);
}

void ParallelRadixSort::msd(std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists, unsigned int cores) { 
    // your implementation goes here :)
    
    //http://www.cplusplus.com/reference/thread/thread/thread/
    vector<thread> threads;
    for(vector<unsigned int> &list : lists)
    {
    	//https://www.quora.com/How-do-I-declare-an-array-of-vectors-of-5-integers-in-C++
    	vector<unsigned int> bins[9];
		fill(bins, bins + 9, vector<unsigned int>(9));
    	for(unsigned int i : list)
    	{
    		string i_toString = to_string(i);

			if(i_toString.substr(0,1) == "1") bins[0].push_back(i);
			else if(i_toString.substr(0,1) == "2") bins[1].push_back(i);
			else if(i_toString.substr(0,1) == "3") bins[2].push_back(i);
			else if(i_toString.substr(0,1) == "4") bins[3].push_back(i);
			else if(i_toString.substr(0,1) == "5") bins[4].push_back(i);
			else if(i_toString.substr(0,1) == "6") bins[5].push_back(i);
			else if(i_toString.substr(0,1) == "7") bins[6].push_back(i);
			else if(i_toString.substr(0,1) == "8") bins[7].push_back(i);
			else if(i_toString.substr(0,1) == "9") bins[8].push_back(i);
    	}

    	for(int i = 0; i < 9; i++)
    	{
    		if(threads.size() == cores)
    		{	
	    		threads[threads.size() - 1].join();
	    		threads.pop_back();
	    		threads.push_back(thread(sortList, &bins[i]));
	    	}
    		else threads.push_back(thread(sortList, &bins[i]));	
    	}
    	for(auto& th : threads) th.join(); 
    	list.clear();
    	for(int i = 0; i < 9; i++)
    	{
    		std::vector<int>::iterator it;
    		it = list.end();
    		list.insert(it, bins[i].begin(), bins[i].end());
    	}
    }
    
}
