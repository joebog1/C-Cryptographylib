#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
int hexdigit2int(char a);
char decdigit2hex(int val);
int basedigit2dec(char a);
char decdigit2base(int a);
std::vector<char> vectorappend(std::vector<char> a,std::vector<char> b);
int maxv(std::vector<int> v);
std::vector<char> dec2bin(int des,int length);
std::vector<char> hex2byte(std::string hex);
std::vector<char> byte2hex(std::vector<char> v);
std::vector<char> threebinarydigitstobase(char a,char b,char c);
std::vector<char> byte2base(std::vector<char> v);
std::vector<char> binxor(std::vector<char> a,std::vector<char> b);
std::vector<char> binxor(std::vector<char> a,char b);

void printashex(std::vector<char> v);
void printasbase(std::vector<char> v);

int hexdigit2int(char a)
{
	//takes a hex digit to dec number
	if(int (a) <58)
	{
		//assume inputs are valid, hence input is 0-9
		return int(a)-48;
	}else 
	return int(a)-87;
}

char decdigit2hex(int val)
{
	//returns the hex character NOT THE BYTE of decimal value
	//value is at most 15
	if (val <10)
	{
		return char(val+48);
	}else 
	return char(val+'a'-10);
}

int basedigit2dec(char a)
{
	//takes a base 64 digit and return the decimal digit
	if(a>'@')
	{
		return int(a-'A');//this is legit code i promise
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

}

char decdigit2base(int a)
{
	//takes an int between 0-63 returns ascii character of the base64 symbol that is the value of the int
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
		return char(a+'0'-53);
	}
	if (a==62)
	{
		return '+';
	}
	else return '/';
}

std::vector<char> vectorappend(std::vector<char> a,std::vector<char> b)
{
	//appends vector b to vector a
	for(int i=0;i<b.size();i++)
	{
		a.push_back(b[i]);
	}
	return a;
}

int maxv(std::vector<int> v)
{
	//returns the index of the max value of a vector of ints
	//0 otherwise
	if (v.empty())
	{
		return 0;
	}
	int index=0;
	int max=v[0];
	for (int i = 1; i < v.size(); ++i)
	{
		if (v[i]>max)
		{
			max=v[i];
			index=i;
		}
	}
	return index;
}


std::vector<char> dec2bin(int des,int length)
{
	//overloaded function of dec2bin, meant for specfic lengths of binary up to 32
	//not to be used for crypto just degbugging as these chars only produce 0's and 1's.
	//to actually convert a dec value to a binary rep simply typecast to character via char(int a)
	std::vector<char> ans;
	for (int i = 0; i < length; ++i)
	{
		ans.push_back('0');
	}
	int counter=0;
	for (int i = ans.size()-1; i > -1; i--)
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
std::vector<char>hex2byte(std::string hex)
{
	//takes a string of hex chars
	if (hex.length()%2==1)
	{
		hex='0'+hex;
	}
	int numitter=hex.length()/2;
	std::vector<char>ans ;
	//2hex char =1 byte which is a char
	for (int i = 0; i < hex.length(); i=i+2)
	{
		ans.push_back(char(16*hexdigit2int(hex[i])+hexdigit2int(hex[i+1])));
	}
	return ans;
}

std::vector<char> byte2hex(std::vector<char> v)
{
	//takes the byte and returns the hex string of it
	//input size is allways a multiple of 8, hence no size change needed
	std::vector<char> ans;
	for (int i = 0; i < v.size(); i++)
	{
		//convert each byte into an int
		int dec=int(v[i]);
		//this value is between 0-255
		int firstdigit=0;//count how many times above 16
		while(dec-16>=0)
		{
			firstdigit++;
			dec-=16;
		}
		if (firstdigit!=0)
		{
			//case where the hex value is not a single digit
			ans.push_back(decdigit2hex(firstdigit));
		}
		ans.push_back(decdigit2hex(dec));
	}
	return ans;
}


std::vector<char> threebinarydigitstobase(char a,char b,char c)
{
	//helper function for byte to base, takes 3 bytes and produces the 4 base 64 digits that equal that number
	//we cant just convert from char to int as the binary for b starts at 2^8 but will be read as 2^0, giving wrong result
	//INPUT MUST BE IN BYTE DECNDING ORDER, ABC
	//C is done automaticaly
	int decimal=int(c);
	//B starts at 2^8
	int conversionmule=int(b);
	for (int i = 7; i > -1; i--)
	{
		if (conversionmule-pow(2,i)>=0)
		{
			decimal=decimal+pow(2,i+8);
			conversionmule=conversionmule-pow(2,i);
		}
	}
	//C starts at 2^16 and ends at 2^23
	conversionmule=int(a);
	for (int i = 7; i > -1; i--)
	{
		if (conversionmule-pow(2,i)>=0)
		{
			decimal=decimal+pow(2,i+16);
			conversionmule=conversionmule-pow(2,i);
		}
	}
	//now we pray it works
	std::vector<char> ans;
	//we have the decimal representation of 3 bytes of data
	//MAKE 4 digits of base 64 to handle this
	int digits [3]={0,0,0};
	int counter=0;
	for (int i = 3; i >0; i--)
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


std::vector<char> byte2base(std::vector<char> v)
{
	//converts binary into base 64
	//step 1 make sure the length of input s a multiple of 3
	if (v.size()%3!=0)
	{
		while(v.size()%3!=0)
		{
			v.insert(v.begin(),char(0));
		}
	}
	std::vector<char> ans;
	for (int i = 0; i < v.size(); i=i+3)
	{
		//read 3 bytes at a time and produce 4 bytes of base 64 code
		char firstbyte=v[i];
		char secondbyte=v[i+1];
		char thridbyte=v[i+2];
		ans=vectorappend(ans,threebinarydigitstobase(firstbyte,secondbyte,thridbyte));
	}
	//there might be leading A's from size of input being shit
	while(ans[0]=='A' && ans.size()>0)
	{
		ans.erase(ans.begin());
	}
	return ans;
}


std::vector<char> binxor(std::vector<char> a,std::vector<char> b)
{
	//does a bitwise xor on two character arrays
	//for now we will assume lengths of a and b are =
	std::vector<char> ans;
	for (int i = 0; i < a.size(); ++i)
	{
		ans.push_back(a[i]^b[i]);
	}
	return ans;
}

std::vector<char> binxor(std::vector<char> a,char b)
{
	//overloaded to repeat one character across a
	std::vector<char> ans;
	for (int i = 0; i < a.size(); ++i)
	{
		ans.push_back(a[i]^b);
	}
	return ans;
}


void printashex(std::vector<char> v)
{
	v=byte2hex(v);
	//prints bytes as hex values
	for (int i = 0; i < v.size(); ++i)
	{
		std::cout<<v[i];
	}
	std::cout<<""<<std::endl;
}

void printasbase(std::vector<char> v)
{
	//prints bytes as base 64 values
	//read 24 bits at a time 24/8=3
	v=byte2base(v);
	for (int i = 0; i < v.size(); i++)
	{
		std::cout<<v[i];
	}
	std::cout<<""<<std::endl;
}
/*
Base 64 Index table:
null:=
0:A
1:B
...
25:Z
26:a
27:b
...
51:z
52:0
53:1
54:2
...
61:9
62:+
63:/
*/
#endif