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
    for(vector<unsigned int> &list : lists)
    {
    	//https://www.quora.com/How-do-I-declare-an-array-of-vectors-of-5-integers-in-C++
    	vector<vector<unsigned int>> bins (9);
		fill(bins.begin(), bins.end(), vector<unsigned int>(0));
    	for(unsigned int i : list)
    	{
    		string i_toString = to_string(i);
    		//cout << i_toString << endl;
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

    	unsigned binAVG = 0;
    	unsigned binSD = 0;
    	unsigned binAVGSQ = 0;
    	for(unsigned i = 0; i < bins.size(); i++)
    	{
    		binAVG = binAVG + bins[i].size();
    		binAVGSQ = binAVGSQ + (bins[i].size()*bins[i].size());
    	}
    	binAVG = binAVG/bins.size();
    	binAVGSQ = binAVGSQ/bins.size();
    	binSD = (unsigned)sqrt((binAVGSQ - (binAVG*binAVG))/bins.size());

		//cout << "avg: " + to_string(binAVG) << " sd: " + to_string(binSD) << endl;
        if(bins[0].size() <= binAVG - (2*binSD) && bins[1].size() >=  binAVG +(4*binSD))
        {
            for(unsigned int k = 0; k < bins[1].size(); k++)
            {
                unsigned int j = bins[1][k];
                string j_toString = to_string(j);

                if(j >= 10 && j_toString.substr(1,1) == "0")
                { 
                    bins[0].push_back(j);
                    bins[1].erase(bins[1].begin() + k);
                }
                else if(j >= 10 && j_toString.substr(1,1) == "1") 
                {
                    bins[0].push_back(j);
                    bins[1].erase(bins[1].begin() + k);
                }
                else if(j >= 10 && j_toString.substr(1,1) == "2") 
                {
                    bins[0].push_back(j);
                    bins[1].erase(bins[1].begin() + k);
                }
                else if(j < 10)
                {
                    bins[0].push_back(j);
                    bins[1].erase(bins[1].begin() + k);
                }
            }
        }
        for(unsigned i = 1; i < bins.size() - 1; i++)
        {
            if(bins[i].size() <= binAVG - (2*binSD) && bins[i + 1].size() >=  binAVG +(4*binSD))
            {
                for(unsigned int k = 0; k < bins[i + 1].size(); k++)
                {
                    unsigned int j = bins[i + 1][k];
                    string j_toString = to_string(j);

                    if(j >= 10 && j_toString.substr(1,1) == "0")
                    { 
                        bins[i].push_back(j);
                        bins[i + 1].erase(bins[i + 1].begin() + k);
                    }
                    else if(j >= 10 && j_toString.substr(1,1) == "1") 
                    {
                        bins[i].push_back(j);
                        bins[i + 1].erase(bins[i + 1].begin() + k);
                    }
                    else if(j >= 10 && j_toString.substr(1,1) == "2") 
                    {
                        bins[i].push_back(j);
                        bins[i + 1].erase(bins[i + 1].begin() + k);
                    }
                    else if(j < 10)
                    {
                        bins[i].push_back(j);
                        bins[i + 1].erase(bins[i + 1].begin() + k);
                    }
                }
            }
            if(bins[i].size() <= binAVG - (2*binSD) && bins[i - 1].size() >=  binAVG +(4*binSD))
            {
                for(unsigned int k = 0; k < bins[i - 1].size(); k++)
                {
                    unsigned int j = bins[i - 1][k];
                    string j_toString = to_string(j);

                    if(j >= 10 && j_toString.substr(1,1) == "9")
                    { 
                        bins[i].push_back(j);
                        bins[i - 1].erase(bins[i - 1].begin() + k);
                    }
                    else if(j >= 10 && j_toString.substr(1,1) == "8") 
                    {
                        bins[i].push_back(j);
                        bins[i - 1].erase(bins[i - 1].begin() + k);
                    }
                    else if(j >= 10 && j_toString.substr(1,1) == "7") 
                    {
                        bins[bins.size() - 1].push_back(j);
                        bins[bins.size() - 2].erase(bins[bins.size() - 2].begin() + k);
                    }
                }
            }
        }
        //cout << "Size: " + to_string(bins[i].size()) << " i: " + to_string(i + 1) << endl;
        if(bins[bins.size() - 1].size() <= binAVG - (2*binSD) && bins[bins.size() - 2].size() >=  binAVG + (4*binSD))
        {
            for(unsigned int k = 0; k < bins[bins.size() - 2].size(); k++)
            {
                unsigned int j = bins[bins.size() - 2][k];
                string j_toString = to_string(j);

                if(j >= 10 && j_toString.substr(1,1) == "9")
                { 
                    bins[bins.size() - 1].push_back(j);
                    bins[bins.size() - 2].erase(bins[bins.size() - 2].begin() + k);
                }
                else if(j >= 10 && j_toString.substr(1,1) == "8") 
                {
                    bins[bins.size() - 1].push_back(j);
                    bins[bins.size() - 2].erase(bins[bins.size() - 2].begin() + k);
                }
                else if(j >= 10 && j_toString.substr(1,1) == "7") 
                {
                    bins[bins.size() - 1].push_back(j);
                    bins[bins.size() - 2].erase(bins[bins.size() - 2].begin() + k);
                }
            }
        }
        for(unsigned i = 0; i < bins.size(); i++)
    	{
            //cout << "Size: " + to_string(bins[i].size()) << " i: " + to_string(i + 1) << endl;
    		if(bins[i].size() >= binAVG + (4*binSD))
    		{

    			//cout << "I found a big one! " + to_string(bins[i].size()) << " " + to_string(i) << endl;
    			vector<unsigned int> binABC (0);
    			vector<unsigned int> binDEF (0);
    			vector<unsigned int> binGHI (0);
    			for(unsigned int j : bins[i])
    			{
    				string j_toString = to_string(j);
    				//cout << j_toString << endl;
    				if(j >= 10)
    				{
    					if(j_toString.substr(1,1) == "0") binABC.push_back(j);
	    				else if(j_toString.substr(1,1) == "1") binABC.push_back(j);
	    				else if(j_toString.substr(1,1) == "2") binABC.push_back(j);
						else if(j_toString.substr(1,1) == "3") binDEF.push_back(j);
						else if(j_toString.substr(1,1) == "4") binDEF.push_back(j);
						else if(j_toString.substr(1,1) == "5") binDEF.push_back(j);
						else if(j_toString.substr(1,1) == "6") binGHI.push_back(j);
						else if(j_toString.substr(1,1) == "7") binGHI.push_back(j);
						else if(j_toString.substr(1,1) == "8") binGHI.push_back(j);
						else if(j_toString.substr(1,1) == "9") binGHI.push_back(j);
		    		}
		    		else binABC.push_back(j);
		    	}
		    	//for(unsigned int k = 0; k < binABC.size(); k++) cout << "ABC: " << to_string(binABC[k]) << endl;
		    	//for(unsigned int k = 0; k < binDEF.size(); k++) cout << "DEF: " << to_string(binDEF[k]) << endl;
	    		//for(unsigned int k = 0; k < binGHI.size(); k++)cout << "GHI: " << to_string(binGHI[k]) << endl;
		    	bins.erase(bins.begin() + i);
    	    	bins.insert(bins.begin() + i, binGHI);
    	    	bins.insert(bins.begin() + i, binDEF);
    	    	bins.insert(bins.begin() + i, binABC);
    		}
    	}  
    	//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=1a952c7b-5ebd-4215-a514-78fb6adfdb29
    	vector<thread> threads;
    	unsigned int total = 0;
        list.clear();
    	for(unsigned i = 0; i < bins.size(); i++)
    	{
    		threads.push_back(thread(sortList, &bins[i]));
    		total++;
    		if(threads.size() == cores)
    		{	
    			while(threads.size() == cores)
                {
                    for(unsigned int i = 0; i < threads.size(); i++)
                    {
                        if(threads[i].joinable())
                        {
                            threads[i].join();
                            threads.erase(threads.begin() + i);
                        }
                    }
                }
                
	    	}
            if(total == bins.size())
            {
                for(auto& th : threads) th.join();
                threads.clear();
            }
    	}
    	
    	
    	//cout << to_string(bins.size()) << endl;
    	for(unsigned i = 0; i < bins.size(); i++)
    	{
    		//http://www.cplusplus.com/reference/vector/vector/insert/
    		list.insert(list.end(), bins[i].begin(), bins[i].end());
    	}
    }    
}
