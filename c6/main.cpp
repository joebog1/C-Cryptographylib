#include "functions.h"

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
	std::vector<unsigned char> histogram=generatehistogram(10);
	for (int i = 0; i < 10; ++i)
	{
		std::cout<<histogram[i]<<" ";
	}
	std::cout<<""<<std::endl;
	while(zafile >> bvaseinput)
	{
		//input is a string of base64 characters
		std::vector<double> hammingdistances=guesskeylength(base2byte(bvaseinput));

	}

	return 0;
}