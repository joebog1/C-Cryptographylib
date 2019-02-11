#include "functions.h"
int main()
{
	std::string code="1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	std::vector<char> input=hex2byte(code);
	std::vector<char> charfound;
	std::vector<int> frequency;
	bool found = false;
	for (int i = 0; i < input.size(); ++i)
	{
		for (int j = 0; j < charfound.size(); ++j)
		{
			if (charfound[j]==input[i])
			{
				found=true;
				frequency[j]++;
			}
		}
		if (!found)
		{
			charfound.push_back(input[i]);
			frequency.push_back(1);
		}
		found=false;
	}
	char mostfreq=charfound[maxv(frequency)];
	char frequent [13]={'e','t','a','o','i','n',' ','s','h','r','d','l','u'};
	std::vector<char> output;
	for (int i = 0; i < 13; ++i)
	{
		//find the key via xor
		//take the most frequent char, assume it is frequent[i] xor key
		//if it is when whe xor it by frequent[i] it should give us the key
		char key=mostfreq^frequent[i];
		output=binxor(input,key);
		for (int j = 0; j < output.size(); ++j)
		{
			std::cout<<output[j];
		}
		std::cout<<"i= "<<i<<std::endl;
	}
}