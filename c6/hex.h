#ifndef HEX_H
#define HEX_H
#include "functions.h"

int hexdigit2int(unsigned char a)
{
	//takes a hex digit to dec number
	if(int (a) <58)
	{
		//assume inputs are valid, hence input is 0-9
		return int(a)-'0';
	}else 
	return int(a)-'a'+10;
}

unsigned char decdigit2hex(int val)
{
	//returns the hex unsigned character NOT THE BYTE of decimal value
	//value is at most 15
	if (val <10)
	{
		return char(val+48);
	}else 
	return char(val+'a'-10);
}

int basedigit2dec(unsigned char a)
{
	//takes a base 64 digit and return the decimal digit
	if (a=='=')
	{
		//its the padding char, its treated as null however
		//that is ambigious but oh well we will figure out what its supposed to do
		return 0;
	}
	if(a>='a')
	{
		//case where input>26<52
		return int(a-'a')+26;
	}
	if(a>'@')
	{
		return int(a-'A');
	}
	if (a>'/')
	{
		return int(a-'0')+52;
	}
	if (a>'.')
	{
		return 63;
	}
	if(a=='+')
	{
		return 62;
	}
 	//not sure how u got here
 	return 0;
}

unsigned char decdigit2base(int a)
{
	//takes an int between 0-63 returns ascii unsigned character of the base64 symbol that is the value of the int
	if (a<26)
	{
		return char(a+'A');
	}
	if(a<52)
	{
		return char(a+'a'-26);
	}
	if(a<62)
	{
		return char(a+'0'-52);
	}
	//not sure why but when we get 61 it doesnt work
	if (a==62)
	{
		return '+';
	}
	else return '/';
}

std::vector<unsigned char> vectorappend(std::vector<unsigned char> a,std::vector<unsigned char> b)
{
	//appends vector b to vector a
	for(unsigned int i=0;i<b.size();i++)
	{
		a.push_back(b[i]);
	}
	return a;
}

int maxv(std::vector<int> v) //pretty depricated thanks to histogam.hpp
{
	//returns the index of the max value of a vector of ints
	//0 otherwise
	if (v.empty())
	{
		return 0;
	}
	int index=0;
	int max=v[0];
	for ( unsigned int i = 1; i < v.size(); ++i)
	{
		if (v[i]>max)
		{
			max=v[i];
			index=i;
		}
	}
	return index;
}


std::vector<unsigned char> dec2bin(int des,int length)
{
	//overloaded function of dec2bin, meant for specfic lengths of binary up to 32
	//not to be used for crypto just degbugging as these unsigned chars only produce 0's and 1's.
	//to actually convert a dec value to a binary rep simply typecast to unsigned character via unsigned char(int a)
	std::vector<unsigned char> ans;
	for ( int i = 0; i < length; ++i)
	{
		ans.push_back('0');
	}
	int counter=0;
	for ( int i = ans.size()-1; i > -1; i--)
	{
		int copy=des;
		if (copy/int(pow(2,i))!=0)
		{
			des=des-pow(2,i);
			ans[counter]++;
		}
		counter++;
	}
	return ans;
}
std::vector<unsigned char>hex2byte(std::string hex)
{
	//takes a string of hex unsigned chars
	if (hex.length()%2==1)
	{
		hex='0'+hex;
	}
	std::vector<unsigned char>ans ;
	//2hex unsigned char =1 byte which is a unsigned char
	for ( unsigned int i = 0; i < hex.length(); i=i+2)
	{
		ans.push_back(char(16*hexdigit2int(hex[i])+hexdigit2int(hex[i+1])));
	}
	return ans;
}

std::vector<unsigned char> byte2hex(std::vector<unsigned char> v)
{
	//takes the byte and returns the hex string of it
	//input size is allways a multiple of 8, hence no size change needed
	std::vector<unsigned char> ans;
	for ( unsigned int i = 0; i < v.size(); i++)
	{
		//convert each byte into an int
		int dec=int(v[i]);
		//this value is between 0-255
		int firstdigit=0;//count how many times above 16
		while(dec>=16)
		{
			firstdigit++;
			dec-=16;
		}
		ans.push_back(decdigit2hex(firstdigit));
		ans.push_back(decdigit2hex(dec));
	}
	//remove leading 0's
	while(ans[0]==0 && ans.size()>0)
	{
		ans.erase(ans.begin());
	}
	return ans;
}


std::vector<unsigned char> threebinarydigitstobase(unsigned char a,unsigned char b,unsigned char c)
{
	//helper function for byte to base, takes 3 bytes and produces the 4 base 64 digits that equal that number
	//we cant just convert from unsigned char to int as the binary for b starts at 2^8 but will be read as 2^0, giving wrong result
	//INPUT MUST BE IN BYTE DECNDING ORDER, ABC
	int decimal=int(c);
	//B starts at 2^8
	int conversionmule=int(b);
	for ( int i = 7; i > -1; i--)
	{
		if (conversionmule-pow(2,i)>=0)
		{
			decimal=decimal+pow(2,i+8);
			conversionmule=conversionmule-pow(2,i);
		}
	}
	//C starts at 2^16 and ends at 2^23
	conversionmule=int(a);
	for (  int i = 7; i > -1; i--)
	{
		if (conversionmule-pow(2,i)>=0)
		{
			decimal=decimal+pow(2,i+16);
			conversionmule=conversionmule-pow(2,i);
		}
	}
	//now we pray it works
	std::vector<unsigned char> ans;
	//we have the decimal representation of 3 bytes of data
	//MAKE 4 digits of base 64 to handle this
	int digits [3]={0,0,0};
	int counter=0;
	for ( unsigned int i = 3; i >0; i--)
	{
		while (decimal>=pow(64,i))
		{
			decimal=decimal-pow(64,i);
			digits[counter]++;
		}
		//this will push leading A's that can be wiped out in bin2base
		ans.push_back(decdigit2base(digits[counter]));
		counter++;
	}
	//the last digit is the remainder of decimal
	ans.push_back(decdigit2base(decimal));
	return ans;
}


std::vector<unsigned char> byte2base(std::vector<unsigned char> v)
{
	//converts binary into base 64
	//step 1 make sure the length of input s a multiple of 3
	while(v.size()%3!=0)
	{
		v.push_back(0);
	}
	std::vector<unsigned char> ans;
	for ( unsigned int i = 0; i < v.size(); i=i+3)
	{
		//read 3 bytes at a time and produce 4 bytes of base 64 code
		unsigned char firstbyte=v[i];
		unsigned char secondbyte=v[i+1];
		unsigned char thridbyte=v[i+2];
		ans=vectorappend(ans,threebinarydigitstobase(firstbyte,secondbyte,thridbyte));
	}
	//there might be leading A's from size of input being shit
	return ans;
}

std::vector<unsigned char> fourbasedigitstobin(unsigned char a,unsigned char b,unsigned char c,unsigned char d)
{
	//takes 4 base numbers from 0-63 and converts them to 3 binary equlviant bytes
	//the inputs are supposed to be six bits long but unsigned char allocates 8 bits for each input,
	//this leaves 2 0's out the front that make this harder then it needs to be
	std::vector<unsigned char> digits;
	for ( unsigned int i = 0; i < 3; ++i)
	{
		digits.push_back(0);
	}
	digits[0]=a*4+b/16;
	digits[1]=b*16+c/4;
	digits[2]=c*64+d; //uses how the c++ handles overflow(rather how it doesnt handle overflow)
	return digits;
}


std::vector<unsigned char> base2byte(std::string base)
{
	//read 4 chars at a time, generate 3 chars equal to 4 base
	int deletepadding=0;
	while(base.length()%4!=0)
	{
		deletepadding++;//to delete padded 0's after
		base=base+'=';//i gotta accept this stupid method of padding
	}
	//ad my own padding
	std::vector<unsigned char> ans;
	if (base.length()==0)
	{
		//empty input
		return ans;
	}

	for(unsigned int i=0;i<base.length();i=i+4)
	{
		unsigned char a=basedigit2dec(base[i]);
		unsigned char b=basedigit2dec(base[i+1]);
		unsigned char c=basedigit2dec(base[i+2]);
		unsigned char d=basedigit2dec(base[i+3]);
		ans=vectorappend(ans,fourbasedigitstobin(a,b,c,d));
	}
	return ans;
}




std::vector<unsigned char> binxor(std::vector<unsigned char> a,std::vector<unsigned char> b)
{
	//does a bitwise xor on two unsigned character arrays
	//for now we will assume lengths of a and b are =
	std::vector<unsigned char> ans;
	for ( unsigned int i = 0; i < a.size(); ++i)
	{
		ans.push_back(a[i]^b[i]);
	}
	return ans;
}

std::vector<unsigned char> binxor(std::vector<unsigned char> a,unsigned char b)
{
	//overloaded to repeat one unsigned character across a
	std::vector<unsigned char> ans;
	for ( unsigned int i = 0; i < a.size(); ++i)
	{
		ans.push_back(a[i]^b);
	}
	return ans;
}

std::vector<unsigned char> repeatedbinxor(std::vector<unsigned char> a,std::vector<unsigned char> key)
{
	for ( unsigned int i = 0; i < a.size(); ++i)
	{
		a[i]=a[i]^key[i%(key.size())];
	}
	return a;
}


void printashex(std::vector<unsigned char> v)
{
	v=byte2hex(v);
	//prints bytes as hex values
	for ( unsigned int i = 0; i < v.size(); ++i)
	{
		std::cout<<v[i];
	}
	std::cout<<""<<std::endl;
}

void printasbase(std::vector<unsigned char> v)
{
	//prints bytes as base 64 values
	//read 24 bits at a time 24/8=3
	v=byte2base(v);
	for ( unsigned int i = 0; i < v.size(); i++)
	{
		std::cout<<v[i];
	}
	std::cout<<""<<std::endl;
}

#endif