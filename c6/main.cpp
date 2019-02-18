#include "functions.h"
#include "histogram.hpp"
int main()
{
	std::ifstream zafile("inputfile");
	std::string bvaseinput;
	
	//load the dictionary
	std::vector<std::string> dictionary;
	std::ifstream ictionary("american-english");
	std::string DWord;
	while(ictionary >> DWord)
	{
		dictionary.push_back(DWord);
	}
	histogram histo=histogram();
	//this should generate histogram based off of histotext
	
	return 0;
}