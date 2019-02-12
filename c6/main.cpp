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
	std::string hexin="49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	printasbase(hex2byte(hexin));
	
	//"SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t=="
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