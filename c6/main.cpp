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
	for (int i = 0; i < keylengths.size(); ++i)
	{
		orderofkeys.push_back(i);
	}
	//orderofkeys[i] is the order in the sorted list such that orderofkeys[0] is min
	//and orderofkeys[orderofkeys.size()-1] is max.
	std::vector<double> copy=keylengths;
	double temp;
	int itemp;
	for(int i=1;i<copy.size();i++)
	{
		for(int j=i;j>0 && copy[j-1] > copy[j];j--)
		{
			temp=copy[j-1];
			copy[j-1]=copy[j];
			copy[j]=temp;

			itemp=orderofkeys[j-1];
			orderofkeys[j-1]=orderofkeys[j];
			orderofkeys[j]=itemp;
		}
	}
	/*keylenghts[i]=j, j is the normalised hamming distance of 2
	keylengths of length j, the keylength is i+1 as you cant have a keylength of 0;
	we want a sorted keylengths such that we can both find the smallest hamming
	distance and get the value of i in a not garbage complexity.
	we have a copy of keylengths that has been sorted.
	we need to have an array of indexes of key length (by extension that would be an array of key length values)
	such that we can read it via keylenghts[oderofkeys[i]]=j
	so oderofkeys[i]+1 is keylength and j is hopefully the smallest hamming distance
	go into keylenghts[i], find the index of copy such that copy[j]=keylenghts[i], 
	orderofkeys[i]=j
	*/
	//now if we want to find the keysize with the minimum length
	//orderofkeys[0]+1 should be the smallest nromalised hamming distance using that keylength
	for (int i = 0; i < orderofkeys.size(); ++i)
	{
		int keyl=orderofkeys[i]+1;
		/*
		break up the cipher text based on the assumed keylength
		then break using the histogram 	
		*/
		
	}
}