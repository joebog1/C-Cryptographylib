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
	std::vector<unsigned char> key;
	key.push_back(0);
	key.push_back(255);
	std::vector<unsigned char> binary=base2byte(cipher);
	std::vector<unsigned char> testrepeatedkey=string2vector("welcome to group theory today we will talk about what is a set");
	testrepeatedkey=repeatedbinxor(testrepeatedkey,string2vector("ab"));
	std::vector<unsigned char> sol=BreakRepeatedKeyXor(testrepeatedkey,histo);
	std::cout<<"HERE IS THE ANSWER"<<std::endl;
	print(sol);
}