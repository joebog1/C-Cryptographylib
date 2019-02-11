#include "functions.h"
int main()
{
	std::ifstream zafile("inputfile");
	std::string hexinput;
	int counter=1;
	//load the dictionary
	std::vector<std::string> dictionary;
	std::ifstream ictionary("american-english");
	std::string DWord;
	while(ictionary >> DWord)
	{
		dictionary.push_back(DWord);
	}

	unsigned char frequent [13]={'e','t','a','o','i','n',' ','s','h','r','d','l','u'};
	while(zafile >> hexinput)
	{
		//should be reading the file line by line and storeing as string
		std::vector<unsigned char> v=hex2byte(hexinput);
		unsigned char common=mostfrequent(v);
		for (int i = 0; i < 13; ++i)
		{
			//itterate through 13 most common keys
			//check as you go
			unsigned char key=common^frequent[i];
			std::vector<unsigned char> plaintext=binxor(v,key);
			if (isadictionary(plaintext,dictionary))
			{
				for (int j = 0; j < plaintext.size(); ++j)
				{
					std::cout<<plaintext[j];
				}
				std::cout<<""<<std::endl;
				std::cout<<"this is line "<<counter<<std::endl;
				return 0;//can be removed to search everything
			}
		}
		counter++;//used to find which line is encrypted
	}
	
	return 0;
	
}