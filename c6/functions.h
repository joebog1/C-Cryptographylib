#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <locale>
class histogram; //prototype class to shut up comipler
int hexdigit2int(unsigned char a);
unsigned char decdigit2hex(int val);
int basedigit2dec(unsigned char a);
unsigned char decdigit2base(int a);
std::vector<unsigned char> vectorappend(std::vector<unsigned char> a,std::vector<unsigned char> b);
int maxv(std::vector<int> v); //depricated, histogram is allways sorted
std::vector<unsigned char> dec2bin(int des,int length);
std::vector<unsigned char> hex2byte(std::string hex);
std::vector<unsigned char> byte2hex(std::vector<unsigned char> v);
std::vector<unsigned char> threebinarydigitstobase(unsigned char a,unsigned char b,unsigned char c);
std::vector<unsigned char> byte2base(std::vector<unsigned char> v);
std::vector<unsigned char> fourbasedigitstobin(unsigned char a,unsigned char b,unsigned char c,unsigned char d);
std::vector<unsigned char> base2byte(std::string base);
std::vector<unsigned char> binxor(std::vector<unsigned char> a,std::vector<unsigned char> b);
std::vector<unsigned char> binxor(std::vector<unsigned char> a,unsigned char b);
std::vector<unsigned char> repeatedbinxor(std::vector<unsigned char> a,std::vector<unsigned char> key);
void printashex(std::vector<unsigned char> v);
void printasbase(std::vector<unsigned char> v);
void print(std::vector<unsigned char> v);
void print(std::vector<double> v);
bool stringcheck(std::string a,std::string b);
bool isadictionary(std::vector<unsigned char> ascii);
unsigned char mostfrequent(std::vector<unsigned char> string);
bool isadictionary(std::vector<unsigned char> ascii,std::vector<std::string> dictionary);
bool lowerorhigher(std::string a,std::string b);
bool binarysearch(std::string words,std::vector<std::string> dictionary,int start,int end);
std::vector<unsigned char> string2vector(std::string string);
int hamming(std::vector<unsigned char> a,std::vector<unsigned char> b);
std::vector<double> guesskeylength(std::vector<unsigned char> cipher);
double histodifference(std::vector<unsigned char> decodedmsg,histogram histo);
std::vector<unsigned char> BreakSingleByteXor(std::vector<unsigned char> cipher,histogram histo);
std::vector<unsigned char> BreakRepeatedKeyXor(std::vector<unsigned char> binaryinput,histogram histo);


class histogram
{
public:
	~histogram();
	histogram();//will generate the entire histogram from this
	histogram(std::string text);//will generate the entire histogram from string	
	std::vector<unsigned char> characterlist; //list will be sorted such that most frequent appears first
	std::vector<int> freq; //frequency[i]=number of times characterlist[i] appears in the given histogram
	std::vector<double> nfreq; //nfreq[i]=frequency[i]/sum(frequency)
};

histogram::~histogram()
{

}//default deconstructor

histogram::histogram()
{
	//assume file to be convert is called histotext
	std::ifstream source("histotext");
	std::string allinoneline;
	std::vector<unsigned char> charfound;
	std::vector<int> frequency;
	std::string line;
	while(source >> line)
	{
		allinoneline=allinoneline+line+" ";
	}
	//start counting
	bool found = false;
	for (int i = 0; i < allinoneline.size(); ++i)
	{
		for (int j = 0; j < charfound.size(); ++j)
		{
			if (charfound[j]==(unsigned char) (allinoneline[i]))
			{
				found=true;
				frequency[j]++;
			}
		}
		if (!found)
		{
			charfound.push_back((unsigned char) (allinoneline[i]));
			frequency.push_back(1);
		}
		found=false;
	}
	//sort the charfound based on how you sort frequency
	int temp;
	unsigned char othertemp;
	for(int i=1;i<frequency.size();i++)
	{
		for(int j=i;j>0 && frequency[j-1] > frequency[j];j--)
		{
			temp=frequency[j-1];
			frequency[j-1]=frequency[j];
			frequency[j]=temp;
			
			othertemp=charfound[j-1];
			charfound[j-1]=charfound[j];
			charfound[j]=othertemp;
		}
	}
	//frequency is sorted and so it charfound
	characterlist=charfound;
	freq=frequency;
	for (int i = 0; i < characterlist.size(); ++i)
	{
		nfreq.push_back((double)frequency[i]/allinoneline.length());
	}
	return;
}

histogram::histogram(std::string text)
{
	//genreates histogram from string
	//for the love of god can we make everything lowercase, it really messes up the histogram otherwise

	std::vector<unsigned char> charfound;
	std::vector<int> frequency;
	std::string allinoneline=text;//im lazy
	//start counting
	bool found = false;
	for (int i = 0; i < allinoneline.size(); ++i)
	{
		for (int j = 0; j < charfound.size(); ++j)
		{
			if (charfound[j]==(unsigned char) (allinoneline[i]))
			{
				found=true;
				frequency[j]++;
			}
		}
		if (!found)
		{
			charfound.push_back((unsigned char) (allinoneline[i]));
			frequency.push_back(1);
		}
		found=false;
	}
	//sort the charfound based on how you sort frequency
	//sort big to small
	int temp;
	unsigned char othertemp;
	for(int i=1;i<frequency.size();i++)
	{
		for(int j=i;j>0 && frequency[j-1] > frequency[j];j--)
		{
			temp=frequency[j-1];
			frequency[j-1]=frequency[j];
			frequency[j]=temp;
			
			othertemp=charfound[j-1];
			charfound[j-1]=charfound[j];
			charfound[j]=othertemp;
		}
	}
	//frequency is sorted and so it charfound
	characterlist=charfound;
	freq=frequency;
	for (int i = 0; i < characterlist.size(); ++i)
	{
		nfreq.push_back((double)frequency[i]/allinoneline.length());
	}
	return;
}







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
	for(int i=0;i<b.size();i++)
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


std::vector<unsigned char> dec2bin(int des,int length)
{
	//overloaded function of dec2bin, meant for specfic lengths of binary up to 32
	//not to be used for crypto just degbugging as these unsigned chars only produce 0's and 1's.
	//to actually convert a dec value to a binary rep simply typecast to unsigned character via unsigned char(int a)
	std::vector<unsigned char> ans;
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
std::vector<unsigned char>hex2byte(std::string hex)
{
	//takes a string of hex unsigned chars
	if (hex.length()%2==1)
	{
		hex='0'+hex;
	}
	std::vector<unsigned char>ans ;
	//2hex unsigned char =1 byte which is a unsigned char
	for (int i = 0; i < hex.length(); i=i+2)
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
	for (int i = 0; i < v.size(); i++)
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
	std::vector<unsigned char> ans;
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


std::vector<unsigned char> byte2base(std::vector<unsigned char> v)
{
	//converts binary into base 64
	//step 1 make sure the length of input s a multiple of 3
	while(v.size()%3!=0)
	{
		v.push_back(0);
	}
	std::vector<unsigned char> ans;
	for (int i = 0; i < v.size(); i=i+3)
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
	for (int i = 0; i < 3; ++i)
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

	for(int i=0;i<base.length();i=i+4)
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
	for (int i = 0; i < a.size(); ++i)
	{
		ans.push_back(a[i]^b[i]);
	}
	return ans;
}

std::vector<unsigned char> binxor(std::vector<unsigned char> a,unsigned char b)
{
	//overloaded to repeat one unsigned character across a
	std::vector<unsigned char> ans;
	for (int i = 0; i < a.size(); ++i)
	{
		ans.push_back(a[i]^b);
	}
	return ans;
}

std::vector<unsigned char> repeatedbinxor(std::vector<unsigned char> a,std::vector<unsigned char> key)
{
	for (int i = 0; i < a.size(); ++i)
	{
		a[i]=a[i]^key[i%(key.size())];
	}
	return a;
}


void printashex(std::vector<unsigned char> v)
{
	v=byte2hex(v);
	//prints bytes as hex values
	for (int i = 0; i < v.size(); ++i)
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
	for (int i = 0; i < v.size(); i++)
	{
		std::cout<<v[i];
	}
	std::cout<<""<<std::endl;
}

void print(std::vector<unsigned char> v)
{
	//prints vector of chars
	for (int i = 0; i < v.size(); i++)
	{
		std::cout<<v[i];
	}
	std::cout<<""<<std::endl;
}

void print(std::vector<double> v)
{
	//prints vector of doubles, //overload shud be ok
	for (int i = 0; i < v.size(); i++)
	{
		std::cout<<v[i];
	}
	std::cout<<""<<std::endl;
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

bool isadictionary(std::vector<unsigned char> ascii)
{
	//does binary search on american english dictionary on the string
	//if the string contains at least 1 englsh word return true else false
	std::string plaintext="";
	for (int i = 0; i < ascii.size(); ++i)
	{
		plaintext=plaintext+char (ascii[i]);
	}
	//we should have a string of actuall ascii values not >127
	std::stringstream stringofinput(plaintext);
	std::string words;
	while(std::getline(stringofinput,words,' '))
	{
		std::ifstream dictionary("american-english");
		std::string DWord;
		while(dictionary >> DWord)
		{
			//uses exaustive search, slow as fuck
			if (stringcheck(words,DWord) && words.length()>2)
			{
				//we found a dictionary word
				std::cout<<words<<" "<<DWord<<" <match"<<std::endl;
				return true;
			}
		}
	}
	return false;
}

unsigned char mostfrequent(std::vector<unsigned char> input)
{
	//finds the most frequently occuring character in a char vector
	std::vector<unsigned char> charfound;
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
	unsigned char mostfreq=charfound[maxv(frequency)];
	return mostfreq;
}

bool isadictionary(std::vector<unsigned char> ascii,std::vector<std::string> dictionary)
{
	//does binary search on american english dictionary on the string
	//if the string contains at least 1 englsh word return true else false
	std::string plaintext="";
	for (int i = 0; i < ascii.size(); ++i)
	{
		plaintext=plaintext+char (ascii[i]);
	}
	//we should have a string of actuall ascii values not >127
	std::stringstream stringofinput(plaintext);
	std::string words;
	while(std::getline(stringofinput,words,' '))
	{
		if (words.length()>2)
		{
			//removes one letter bullshit
			if (binarysearch(words,dictionary,0,dictionary.size()-1))
			{
				//we found it
				return true;
			}
		}
	}
	return false;
}
bool lowerorhigher(std::string a,std::string b)
{
	//compares weather the string is futher then b
	//in alphabeticaly sorted order
	while(b.length()<a.length())
	{
		//case where b is smaller then a
		//pad out @ symbls as they are smaller then every letter
		b=b+'@';
	}
	for (int i = 0; i < a.length(); ++i)
	 {
	 	if (a[i]<b[i])
	 	{
	 		return false;
	 	}
	 	if (a[i]>b[i])
	 	{
	 		return true;
	 	}
	 	//if a[i]=b[i] continue
	 }
	 //at this point either a is b or a is a substring of b
	 //if a=b we shouldnt be here as binary search checks before doing this
	 //otheriwse b is bigger
	 return false;
}

bool binarysearch(std::string words,std::vector<std::string> dictionary,int start,int end)
{
	//do binary search on a dictionary to find word, return true if found false if not
	if(start==end)
		{
			if(stringcheck(dictionary[start],words))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if(end<start)
		{ //we have a problum
			return false;
		}
		int middle=(start+end)/2;
		if (stringcheck(dictionary[middle],words))
	 	{
	 		return true;
	 	}
		if (lowerorhigher(dictionary[middle],words))
		{
			return binarysearch(words,dictionary,start,middle-1);
		}
		else
		{
			return binarysearch(words,dictionary,middle+1,end);
		}
}

std::vector<unsigned char> string2vector(std::string string)
{
	//takes a string and produces the usiged vector of chars
	std::vector<unsigned char> ans;
	for (int i = 0; i < string.length(); ++i)
	{
		ans.push_back(string[i]);
	}
	return ans;
}

std::string vector2string(std::vector<unsigned char> vector)
{
	std::string ans;
	for (int i = 0; i < vector.size(); ++i)
		{
			ans=ans+char (vector[i]);
		}
	return ans;
}


int hamming(std::vector<unsigned char> a,std::vector<unsigned char> b)
{
	//this function returns the number of differing bits between a and b
	//xor returns 1 if the bits are differnt and 0 if they are the same
	//keep in mind that this only exists if a.size()=b.size()
	int ans=0;
	std::vector<unsigned char> diff=binxor(a,b);
	for (int i = 0; i < diff.size(); ++i)
	{
		while(diff[i]!=0)
		{
			ans++;
			//does and equals which will allways remove exactly one 1 from the char
			diff[i]&=diff[i]-1;
		}
	}
	return ans;
}


std::vector<double> guesskeylength(std::vector<unsigned char> cipher)
{
	//guesses the key by finding the smallest normalsed hamming distance for each keysize key
	//assumes key length to be more then 1 but less then 41
	//well returns a vector of 41 with each normalised hamming distance for each length
	std::vector<double> normalisedkeysize;
	for (int keysize = 1; keysize < 41; ++keysize)
	{
	//run through the string in lengths of keysize,
	//grab each keysize of bytes, what if the key isnt a multiple of keysize?
		std::vector<unsigned char> firstbyte;
		std::vector<unsigned char> secondbyte;
		if (keysize*2>cipher.size())
		{
			//the key size is bigger then half the encrtypted test
			//how do we parse it
			//best to just return the vector of normalised hamming lengths
			return normalisedkeysize;
		}
		//we can now assume that keysize*2<=cipher.size() 
		//this grabs the first keysize bytes and compares them
		//not the most relaible method, better to do this through all possiable combonations
		//of keysize pairs and pick the max
		for (int i = 0; i < keysize*2; ++i)
		{
			if (i>=keysize)
			{
				secondbyte.push_back(cipher[i]);
			}
			else
			{
				firstbyte.push_back(cipher[i]);
			}
		}
		normalisedkeysize.push_back(double(hamming(firstbyte,secondbyte))/keysize);
	}
	return normalisedkeysize;
}

double histodifference(std::vector<unsigned char> decodedmsg,histogram histo)//currently doesnt really work
{
	//curretly is a peice of garbage that says gibberish is the histogram
	//given a supposedly decrypted msg, genreate a histogram and
	//return the sum of the differences of nfreq
	histogram decrypt=histogram(vector2string(decodedmsg));
	double ans=0;
	//lets assume the histogram frequency is unlikely to be
	//the same as the histograms if the output is not the plaintext
	int diff=(histo.nfreq.size()-decrypt.nfreq.size());
	diff=std::abs(diff);
	//pad the difference of 0's to the smaller value
	if (histo.nfreq.size()>decrypt.nfreq.size())
	{
		//padd differnece onto decrpt.nfreq
		for (int i = 0; i < diff; ++i)
		{
			decrypt.nfreq.insert(decrypt.nfreq.begin(),0.0);
			decrypt.characterlist.insert(decrypt.characterlist.begin(),(char) 0);//adds null char to characterlist				
		}
	}
	else
	{
		// pad into histo.nfreq, also pad to front as the lowest is at front
		for (int i = 0; i < diff; ++i)
		{
			histo.nfreq.insert(histo.nfreq.begin(),0);
			histo.characterlist.insert(histo.characterlist.begin(),(char) 0);
		}
	}
	//now that we are convinced that they are of the same size
	//we can check element by element
	print(histo.characterlist);
	print(decrypt.characterlist);
	for (int i = 0; i <histo.nfreq.size() ; ++i)
	{
		//c++ doesnt like abs when the inputs are doubles for some reason
		double sum=0;
		if (histo.characterlist[i]==decrypt.characterlist[i])
		{
			if (histo.nfreq[i]>decrypt.nfreq[i])
			{
				sum=histo.nfreq[i]-decrypt.nfreq[i];

			}
			else
			{
				sum=decrypt.nfreq[i]-histo.nfreq[i];
			}
			ans=ans+sum*i;//reward more when more common characters match
		}
		else
		{
			//punish incorrect results
			if (histo.nfreq[i]>decrypt.nfreq[i])
			{
				sum=histo.nfreq[i]-decrypt.nfreq[i];

			}
			else
			{
				sum=decrypt.nfreq[i]-histo.nfreq[i];
			}
			ans=ans-sum;
		}
	}
	if (ans<=0)
	{
		return 100;
	}
	return 1/ans;
}

std::vector<unsigned char> BreakSingleByteXor(std::vector<unsigned char> cipher,histogram histo)
{
	//breaks a cipher (assumed ascii binary) that we know to be xord by a single char
	//usefull helper function for what will be BreakRepeatedKeyXor
	std::vector<double> hacc;//will hold the result of histodifference for each char in histogram
	histogram cipherhisto=histogram(vector2string(cipher));
	//given the most common char of cipher a and most common histogram char h, we assume
	//that a^key=h, hence key=a^h
	std::vector<unsigned char> solved=cipher;
	unsigned char key;
	for (int i = 0; i < 15 && i<cipherhisto.characterlist.size(); ++i)
	{
		//we will use the 10 most popluar chars of histo
		unsigned char key=cipherhisto.characterlist[cipherhisto.characterlist.size()-1-i]^histo.characterlist[histo.characterlist.size()-1-i];
		std::vector<unsigned char> solved=cipher;
		for (int j = 0; j < solved.size(); ++j)
		{
			solved[j]=solved[j]^key;
		}
		std::cout<<"Possiable key > "<<key<<std::endl<<"Possiable plaintext:"<<std::endl;
		print(solved);
		std::cout<<"the histodifference is = "<<histodifference(solved,histo)<<std::endl;
		hacc.push_back(histodifference(solved,histo));
	}
	//find the result that gave the closest histogtam and use that
	int index=0;
	double temp=hacc[0];
	for (int i = 1; i < hacc.size(); ++i)
	{
		if (hacc[i]<temp)
		{
			temp=hacc[i];
			index=i;
		}
	}
	//could be improved for perfomanace and readability but good enough for a first attempt
	key=cipherhisto.characterlist[cipherhisto.characterlist.size()-1-index]^histo.characterlist[histo.characterlist.size()-1-index];
	std::cout<<key<<std::endl;
	for (int j = 0; j < solved.size(); ++j)
	{
		solved[j]=solved[j]^key;
	}
	return solved;
}

std::vector<unsigned char> BreakRepeatedKeyXor(std::vector<unsigned char> binaryinput,histogram histo)
{
	//attempts to break a repeatedkeyXor cipher, also assumes input is in binary, not base64
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
		std::cout<<keyl<<std::endl<<"Here is Input: "<<std::endl;
		print(binaryinput);	
		std::cout<<"we assume a key length of "<<keyl<<std::endl;
		/*
		break up the cipher text based on the assumed keylength
		then break using the histogram 	
		*/
		std::vector<std::vector<unsigned char> > vecOfChar;
		/*
		lets parittion the set of cipher characters
		based on the position it appears in its sequence
		if we have a keylength of keyl then
		cipher[n*keyl+c] where c will be each colmnum
		and n will be the row, n*keyl<=binaryinput.size()
		hopefully we should be able to access specifc partitions
		via vectorOfChar[c][n]
		*/
		std::vector<unsigned char> thekey;//will hold the key by the end
		std::vector<unsigned char> filler;
		for (int j = 0; j < keyl; ++j)
		{
			//push the keylengths worth of vectors (set up coloums of vecOfChar)
			vecOfChar.push_back(filler);
		}
		for (int j = 0; j < binaryinput.size(); ++j)
		{
			vecOfChar[j%keyl].push_back(binaryinput[j]);
		}
		std::cout<<"OUTPUT THE FIRST ROW"<<std::endl;
		for (int j = 0; j < vecOfChar.size(); ++j)
		{
			for (int k = 0; k < vecOfChar[j].size(); ++k)
			{
				std::cout<<vecOfChar[j][k]<<" ";
			}
			std::cout<<""<<std::endl<<"ROW IS COMPLETE"<<std::endl;
		}
		//now each vecOfChar is i%keyl long o vecOfChar[1][1] is binaryinput[keyl+1]
		//solve for each column
		for (int j = 0; j < vecOfChar.size(); ++j)
		{
			vecOfChar[j]=BreakSingleByteXor(vecOfChar[j],histo);
		}
		//for now lets just print the solution
		std::vector<unsigned char> possolution;
		//we understand that the vector of chars is a 2d jagged matrix of characters
		//to go back we traverse the list from top to bottom, left to right
		int counter=0;
		for (int j = 0; j < vecOfChar[0].size(); ++j)
		{
			for (int k = 0; k < vecOfChar.size(); ++k)
			{
				//iterate such that it returns the orgional vector
				if (counter<binaryinput.size())
				{
					possolution.push_back(vecOfChar[j][k]);
				}
				counter++;
			}
		}
		return possolution;
	}
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