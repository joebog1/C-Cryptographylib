#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "functions.h"
class histogram
{
public:
	~histogram();
	histogram();//will generate the entire histogram from this
	histogram(std::string text);//will generate the entire histogram from string	
	int findnthsmallest(std::vector<double> vect,int n);
	std::vector<unsigned char> generatehistogram(int n);
	std::vector<unsigned char> characterlist; //list will be sorted such that most frequent appears first
	std::vector<int> freq; //frequency[i]=number of times characterlist[i] appears in the given histogram
	std::vector<double> nfreq; //nfreq[i]=frequency[i]/sum(frequency)
};

histogram::~histogram()
{

}//default deconstructor

histogram::histogram()
{
	//assume file to be convert is called histotext
	std::ifstream source("histotext");
	std::string allinoneline;
	std::vector<unsigned char> charfound;
	std::vector<int> frequency;
	std::string line;
	while(source >> line)
	{
		allinoneline=allinoneline+line+" ";
	}
	//start counting
	bool found = false;
	for (int i = 0; i < allinoneline.size(); ++i)
	{
		for (int j = 0; j < charfound.size(); ++j)
		{
			if (charfound[j]==(unsigned char) (allinoneline[i]))
			{
				found=true;
				frequency[j]++;
			}
		}
		if (!found)
		{
			charfound.push_back((unsigned char) (allinoneline[i]));
			frequency.push_back(1);
		}
		found=false;
	}
	//sort the charfound based on how you sort frequency
	int temp;
	unsigned char othertemp;
	for(int i=1;i<frequency.size();i++)
	{
		for(int j=i;j>0 && frequency[j-1] > frequency[j];j--)
		{
			temp=frequency[j-1];
			frequency[j-1]=frequency[j];
			frequency[j]=temp;
			
			othertemp=charfound[j-1];
			charfound[j-1]=charfound[j];
			charfound[j]=othertemp;
		}
	}
	//frequency is sorted and so it charfound
	characterlist=charfound;
	freq=frequency;
	for (int i = 0; i < characterlist.size(); ++i)
	{
		nfreq.push_back((double)frequency[i]/allinoneline.length());
	}
	return;
}

histogram::histogram(std::string text)
{
	//genreates histogram from string
	std::vector<unsigned char> charfound;
	std::vector<int> frequency;
	std::string allinoneline=text;//im lazy
	//start counting
	bool found = false;
	for (int i = 0; i < allinoneline.size(); ++i)
	{
		for (int j = 0; j < charfound.size(); ++j)
		{
			if (charfound[j]==(unsigned char) (allinoneline[i]))
			{
				found=true;
				frequency[j]++;
			}
		}
		if (!found)
		{
			charfound.push_back((unsigned char) (allinoneline[i]));
			frequency.push_back(1);
		}
		found=false;
	}
	//sort the charfound based on how you sort frequency
	int temp;
	unsigned char othertemp;
	for(int i=1;i<frequency.size();i++)
	{
		for(int j=i;j>0 && frequency[j-1] > frequency[j];j--)
		{
			temp=frequency[j-1];
			frequency[j-1]=frequency[j];
			frequency[j]=temp;
			
			othertemp=charfound[j-1];
			charfound[j-1]=charfound[j];
			charfound[j]=othertemp;
		}
	}
	//frequency is sorted and so it charfound
	characterlist=charfound;
	freq=frequency;
	for (int i = 0; i < characterlist.size(); ++i)
	{
		nfreq.push_back((double)frequency[i]/allinoneline.length());
	}
	return;
}
	

#endif