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
	for (unsigned char i = 0; i < 64; ++i)
	{
		std::cout<<int(i);
		print(threebinarydigitstobase(0,0,i));
	}
	//"SSdtIGtpbGxpbmcgeW0ciBicmFpbiBsaWtlIGEgcGpc1ub2VzIG00c1hyb1t=="
	//"SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
	/*
	for (int keysize = 2; keysize < 41; ++keysize)
	{
		//run through the string in lengths of keysize,
		//grab each keysize of bytes
		for (int i = 0;  i< ; ++i)
		{
			
		}
	}
	*/

	return 0;
}