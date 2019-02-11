//code must not use strings other then to convert to int
#include <iostream>
#include <math.h>
#define DEBUG_MODE true
int hexdigit2int(char a)
{
	if(int (a) <58)
	{
		//assume inputs are valid, hence input is 0-9
		return int(a)-48;
	}else 
	return int(a)-87;
}

std::string dec2bin(int des)
{
	std::string ans="0000";
	int counter=0;
	for (int i = 3; i > -1; i--)
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

std::string hex2bin(char a)
{
	return dec2bin(hexdigit2int(a));
}

int bin2dec(std::string bin)
{
	//takes string of length 6 only
	int ans=0;
	int counter=0;
	for (int i = bin.length()-1; i >-1; i--)
	{
		if (bin[i]=='1')
		{
			ans=ans+pow(2,counter);
		}
		counter++;
	}
	return ans;
}

char OTo63Convert(int value)
{
	if (value<26)
	{
		return char(value+65);
	}
	if (value<52)
	{
		return char(value+97-26);
	}
	if (value <62)
	{
		return char(value+48-52);
	}
	if (value==62)
	{
		return '+';
	}else
	{
		return '/';
	}
}


std::string bin2b64(std::string bin)
{
	std::string ans="";
	if (bin.length()%6!=0)
	{
		for (int i = 0; i <bin.length()%6 ; ++i)
		{
			bin="0"+bin; //padding left not right bc that changes the value
		}
	}
	//we must parse the input 6 values at a time 
	int maxitter=bin.length()/6;//shud be a whole number by now
	for (int i = 0; i < maxitter; ++i)
	{
		std::string bite6="";
		for (int j = i*6; j < (i+1)*6; j++)
		{
			//gather that fuckn 6 bits
			bite6=bite6+bin[j];
		}
		//now we have 6bites convert to corresponding ascii
		int sixBitValue=bin2dec(bite6);
		//now to convert this int to corresponding b64 value
		ans=ans+OTo63Convert(sixBitValue);
	}
	return ans;
}

int main()
{
	std::string input="49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	std::string bin="";
	for (int i = 0; i < input.length(); ++i)
	{
		bin=bin+hex2bin(input[i]);
	}
	std::cout<<bin2b64(bin)<<std::endl;
	return 0;
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

/*
string hex2b64(string input)
{
	int NumberToItterate=input.length/3;
	int remainder = input.length%3;
	string ans;

}
*/