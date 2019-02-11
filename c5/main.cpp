#include "functions.h"

int main()
{
	std::string a="b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
	//since the input is allready in ascii we dont need to convert
	//however we do need to convert to vector of unsigned chars before proceeding
	std::vector<unsigned char> listOWords=hex2byte(a);
	//ok so now we have the list of words as ascii characters
	//run it through the xor with key "ICE"
	std::vector<unsigned char> key;
	key.push_back('I');
	key.push_back('C');
	key.push_back('E');
	std::vector<unsigned char> output=repeatedbinxor(listOWords,key);
	for (int i = 0; i < output.size(); ++i)
	{
		std::cout<<output[i];
	};
	std::cout<<""<<std::endl;
	return 0;
}