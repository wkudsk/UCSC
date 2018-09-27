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
static unsigned int numCores = 0;
RadixSort::RadixSort(const unsigned int cores) { 
    numCores = cores;
}

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
void RadixSort::msd(std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists) { 
    // your implementation goes here :)
    
    //http://www.cplusplus.com/reference/thread/thread/thread/
    vector<thread> threads;
    for(vector<unsigned int> &list : lists)
    {
    	//cout << &list << endl;
    	//sortList(&list);
    	if(threads.size() == numCores)
    	{	
    		threads[threads.size() - 1].join();
    		threads.pop_back();
    		threads.push_back(thread(sortList, &list));
    	}
    	else threads.push_back(thread(sortList, &list));		
    }
    for(auto& th : threads) th.join(); 
}
