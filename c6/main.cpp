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
	for (int i = 0; i < 63; ++i)
	{
		for (int j = 0; j < 63; ++j)
		{
			for (int k = 0; k < 63; ++k)
			{
				for (int n = 0; n < 63; ++n)
				{
					std::cout<<i<<" "<<j<<" "<<k<<" "<<n<<std::endl;
					std::vector<unsigned char> v = fourbasedigitstobin(i,j,k,n);
					for (int a = 0; a < v.size(); ++a)
					{
						std::cout<<int(v[a])<<" ";
					}
					std::cout<<""<<std::endl;
				}
			}
		}
	}
		


	//"SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t=="
	//"SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
	//"498fb30020ceef0084deef00868aa60091f715008a0628008a162f008607320081ceeb002012260088f60f008bf714008757790020d7f5008b9fb80087f71300"
	//"49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
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