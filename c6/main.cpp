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
	std::vector<unsigned char> binary=base2byte(cipher);
	std::vector<unsigned char> testrepeatedkey=string2vector("Cooking mc's like a pound if bacon, ice ice baby ice ice, corey Noden aint got no nodens");
	testrepeatedkey=binxor(testrepeatedkey,'2');
	std::vector<unsigned char> sol=BreakSingleByteXor(testrepeatedkey,histo);
	std::cout<<"HERE IS THE ANSWER"<<std::endl;
	print(sol);
}