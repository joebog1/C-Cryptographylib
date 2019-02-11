#include <iostream>
#include <math.h>
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

std::string dec2bin(int des)
{
	//takes a decimal int and returns a 4 bit binary of it
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

std::string dec2bin(int des,int length)
{
	//overloaded function of dec2bin, meant for specfic lengths of binary up to 32
	std::string ans="";
	for (int i = 0; i < length; ++i)
	{
		ans=ans+'0';
	}
	int counter=0;
	for (int i = ans.length()-1; i > -1; i--)
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
	//takes hex char and returns the binary string rep of it
	return dec2bin(hexdigit2int(a));
}


int bin2dec(std::string bin)
{
	//meant to convert binary to decimal, cant handle anything where int would overflow
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
	//takes decimal and returns base 64 rep of it
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
	//takes binary string of length 6  and returns corresponding base 64 value
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


std::string hex2b64(std::string input)
{
	//converts a hex string to base 64
	std::string bin="";
	for (int i = 0; i < input.length(); ++i)
	{
		bin=bin+hex2bin(input[i]);
	}
	return bin2b64(bin);
}

char dec2hex(int dec)
{
	if (dec<10)
	{
		return char(48+dec);
	}else return char(dec+97-10);
}

char bin2hex(std::string binary)
{
	//takes a binary string of length 4 and gives it the char in hex
	return dec2hex(bin2dec(binary));
}
std::string compare(char a, char b)
{
	//performs an xor on two digits of a hex char
	std::string sa=hex2bin(a);
	std::string sb=hex2bin(b);
	std::string ans="1111";
	//we has 2 strings, xor the prick n leave
	for (int i = 0; i < 4; ++i)
	{
		if(sa[i]==sb[i])
		{
			ans[i]='0';
		}
	}
	return ans;
}


std::string binxor(std::string input,std::string against)
{
	//does simple binary xor bitwise on string a and b
	//assumes input is of same length
	std::string ans="";
	for (int i = 0; i < input.length(); ++i)
	{
		ans=ans+'1';
		if (input[i]==against[i])
		{
			ans[i]='0';
		}
	}
	std::cout<<"a> "<<input<<std::endl;
	std::cout<<"b> "<<against<<std::endl;
	std::cout<<"ans> "<<ans<<std::endl;
	return ans;
}


std::string xora(std::string input,std::string against)
{
	//takes 2 hex strings and xors input against against to get result
	std::string ans="";
	for (int i = 0; i < input.length(); ++i)
	{
		ans.push_back(bin2hex(compare(input[i],against[i])));
	}
	return ans;
}

std::string singlebytexor(std::string input, char b)
{
	std::string ans;
	std::string against="";
	for (int i = 0; i < input.length(); ++i)
	{
		against=against+b;
	}
	for (int i = 0; i < input.length(); ++i)
	{
		ans.push_back(bin2hex(compare(input[i],against[i])));
	}
	return ans;
}


int base2dec(char input)
{
	//converts a base 64 char to its corresponding decimal value
	//usefull when done with dec2bin(int,6)
	//since the ascii is scatterd as fuck for b64 digits compared to value
	//best to search based on the ascii value itself starting with the highest
	if (int (input)>96)
	{
		//input is withitn the a-z range of 26-51
		return int (input)-97+26;
	}
	if (int (input)>64)
	{
		// input is within A-Z range of 0-25
		return int(input)-65+0;
	}
	if (int (input) >47)
	{
		//input is between 0-9 range of 52-61
		return int (input)-48+52;
	}
	if (int(input)==47)
	{
		return 63;
	}else return 62;
}

char decdigit2b64(int value)
{
	//takes a decimal digit and prodcues the ascii character for b64
	//range 0-63
	if (value<26)
	{
		return char(value)+65;
	}
	if(value<52)
	{
		return char(value)+97-26;
	}
	if (value<62)
	{
		return char(value)+48-52;
	}
	if(value==62)
	{
		return '+';
	}
	return '/';
}

std::string base2bin(std::string base)
{
	//converts base 64 to binary
	std::string bin="";
	for (int i = 0; i < base.length(); ++i)
	{
		bin=bin+dec2bin(base2dec(base[i]));
	}
	return bin;
}

bool stringcheck(std::string a,std::string b)
{
	//returns true if strings r the same
	if (a.length()!=b.length())
	{
		return false;
	}
	for (int i = 0; i < a.length(); ++i)
	{
		if (a[i]!=b[i])
		{
			return false;
		}
	}
	return true;
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