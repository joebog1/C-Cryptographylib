#include <iostream>
#define DEBUG_MODE false 
std::string to2bit(char a){
	std::string result[16]={"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
	if (DEBUG_MODE)
	{
		std::cout<<"to2bit was called with input "<< a<<std::endl;
	}
	switch (a){
		case '0':
		return result[0];
		break;
		case '1':
		return result[1];
		break;
		case '2':
		return result[2];
		break;
		case '3':
		return result[3];
		break;
		case '4':
		return result[4];
		break;
		case '5':
		return result[5];
		break;
		case '6':
		return result[6];
		break;
		case '7':
		return result[7];
		break;
		case '8':
		return result[8];
		case '9':
		return result[9];
		break;
		case 'a':
		return result[10];
		break;
		case 'b':
		return result[11];
		break;
		case 'c':
		return result[12];
		break;
		case 'd':
		return result[13];
		break;
		case 'e':
		return result[14];
		break;
		case 'f':
		return result[15];
	}
}
char bit2hex(std::string binary)
{
	//takes a binary string of length 4 and gives it the char in hex
	if (binary=="0000")
	{
		return '0';
	}
	else if (binary=="0001")
	{
		return '1';
	}
	else if (binary=="0010")
	{
		return '2';	
	}
	else if (binary=="0011")
	{
		return '3';
	}
	else if (binary=="0100")
	{
		return '4';
	}
	else if (binary=="0101")
	{
		return '5';
	}
	else if (binary=="0110")
	{
		return '6';
	}
	else if (binary=="0111")
	{
		return '7';
	}
	else if (binary=="1000")
	{
		return '8';
	}
	else if (binary=="1001")
	{
		return '9';
	}
	else if (binary=="1010")
	{
		return 'a';
	}
	else if (binary=="1011")
	{
		return 'b';
	}
	else if (binary=="1100")
	{
		return 'c';
	}
	else if (binary=="1101")
	{
		return 'd';
	}
	else if (binary=="1110")
	{
		return 'e';
	}
	else if (binary=="1111")
	{
		return 'f';
	} else {
		return '0';
	}
}
std::string compare(char a, char b)
{
	std::string sa=to2bit(a);
	std::string sb=to2bit(b);
	std::string ans="1111";
	//we has 2 strings, xor the prick n leave
	if (DEBUG_MODE)
	{
		std::cout<<"sa> "<<sa<<"sb> "<<sb<<std::endl;
	}
	for (int i = 0; i < 4; ++i)
	{
		if(sa[i]==sb[i])
		{
			ans[i]='0';
		}
	}
	if (DEBUG_MODE)
	{
		std::cout<<"a> "<<a<<" b> "<<b<<" ans> "<<ans<<std::endl;
	}
	return ans;
}

std::string xora(std::string input,std::string against)
{
	//convert each char into a string using compare, then convert back to char
	std::string ans;
	for (int i = 0; i < input.length(); ++i)
	{
		ans.push_back(bit2hex(compare(input[i],against[i])));
	}
	return ans;
}

int main()
{
	std::string input="1c0111001f010100061a024b53535009181c";
	std::string xorg="686974207468652062756c6c277320657965";
	std::cout<<xora(input,xorg)<<std::endl;
	return 0;
	
}

