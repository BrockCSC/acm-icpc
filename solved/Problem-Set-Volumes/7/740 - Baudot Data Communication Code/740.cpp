#include <iostream>
#include <string>
#include <sstream> // for (c++) string conversions
#include <cmath>
#include <bitset> // for binary to decimal
using namespace std;

#define REP(i,a)	for(i=0;i<a;i++)
#define FOR(i,a,b)	for(i=a;i<b;i++)
#define reg		register int // e.g. reg i = 0
//memset(arr, 0, sizeof arr); // clear array of integers

int str2int(const string &str)
{
	stringstream ss(str);
	int n;
	ss >> n;
	return n;
}

string int2str(int n)
{
	stringstream ss;
	ss << n;
	return ss.str();
}

int bin2dec(string bin)
{
        int res = 0;
        for (int i=bin.size()-1, j=0; i>=0; i--, j++)
                res += (bin[i]-'0') * ((int) pow( (double) 2, (double) j)); // raise bits to appropriate power of 2
        return res;
}

int main()
{
	string down, up, line;
	getline(cin, down);
	getline(cin, up);
	while(getline(cin, line))
	{
		bool downshift = true;
		for(int i=0; i < line.length(); i+=5)
		{
			string code = line.substr(i, 5);
			int index = bin2dec(code);
			// unsigned long index = bitset<32>(codeStr).to_ulong(); // Alternate binary to decimal conversion
			if(code == "11111") downshift = false;
			else if(code == "11011") downshift = true;
			else if(downshift) putchar(down[index]);
			else putchar(up[index]);
		}
		putchar('\n');
	}
	return 0;
}

