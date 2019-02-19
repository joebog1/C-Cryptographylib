#include "histogram.hpp"
#include "functions.h"
int main()
{
	//load the dictionary
	std::vector<std::string> dictionary;
	std::ifstream ictionary("american-english");
	std::string DWord;
	while(ictionary >> DWord)
	{
		dictionary.push_back(DWord);
	}
	histogram histo=histogram();
	
	std::ifstream zafile("inputfile");
	std::string bvaseinput;
	std::string cipher;
	while(zafile >> bvaseinput)
	{
		cipher=cipher+bvaseinput;
	}
	//input is in base64
	std::vector<unsigned char> binaryinput=base2byte(cipher);
	std::vector<double> keylengths= guesskeylength(binaryinput);
	std::vector<int> orderofkeys;
	//orderofkeys[i] is the order in the sorted list such that orderofkeys[0] is min
	//and orderofkeys[orderofkeys.size()-1] is max.
	std::vector<double> copy=keylengths;
	double temp;
	for(int i=1;i<copy.size();i++)
	{
		for(int j=i;j>0 && copy[j-1] > copy[j];j--)
		{
			temp=copy[j-1];
			copy[j-1]=copy[j];
			copy[j]=temp;
		}
	}
	/*
		go into keylenghts[i], find the index of copy such that copy[j]=keylenghts[i], 
		orderofkeys[i]=j
	*/
	for (int i = 0; i < keylengths.size(); ++i)
	{
		for (int j = 0; j < copy.size(); ++j)
		{
			if (copy[j]==keylengths[i])
			{
				orderofkeys.push_back(j);
			}
			//now since copy was =keylengths this should be true every time
		}
	}
	
}