/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include "radix.h"

RadixSort::RadixSort(const unsigned int cores) { 
    int ununsed = 0; // to fail complier warming test, remove
}

void RadixSort::msd(std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists) { 
    // your implementation goes here :)
    for(int i = 0; i < lists.size(); i++)
    {
    	std::vector<unsigned int> list = lists[i];
    	for(int j = 0; j < list.size(); j++)
    	{
    		std::cout << list[j] << endl
    	}
    }
}
