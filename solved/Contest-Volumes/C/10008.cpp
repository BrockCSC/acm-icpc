#include <stdlib.h> // for exit(0)
#include <algorithm> // for max_element(first,last)
#include <iostream>
using namespace std;

int main(void)
{
 // read n
 // read n amount of lines -- only read in letters
 // convert letters to uppercase (or lowercase, but must be persistent)
 // have a counter for each letter
 // sort letter count list in descending order -- if letters have an equal count, sort those letters in alphabetic order

	int n; // number of lines which follow in the input
	string word; // a "word" is considered anything with no spaces
	char character; // characters from a "word"
	int letters[26]; // array that stores letter count
	int sortedletters[26][2]; // 2D array that will store the letters sorted by count (used max size -> 26)
	
	for(int i=0; i < 26; ++i) // initialize counts to 0
		letters[i] = 0;
	
	cin >> n;
	if(n < 1) exit(0); // terminate if no input lines indicated
	
	// process lines
	while(cin >> word) // read in all input to a string (string gets overwritten after every whitespace)
	{	
		/* need to look at every character of a "word" to check if it's a letter */
		
		// need to iterate through every character in a word, incrementing count of found letters
		for(int i = 0; i < word.size(); ++i)
		{
			character = (char)word.at(i);
			switch (character)
			{
				case 'a': // 1 in alphabet, thus 0 in array
				case 'A':
					letters[0]++; // increment count at given index in array
					break;
				case 'b':
				case 'B':
					letters[1]++;
					break;
				case 'c':
				case 'C':
					letters[2]++;
					break;
				case 'd':
				case 'D':
					letters[3]++;
					break;
				case 'e':
				case 'E':
					letters[4]++;
					break;
				case 'f':
				case 'F':
					letters[5]++;
					break;
				case 'g':
				case 'G':
					letters[6]++;
					break;
				case 'h':
				case 'H':
					letters[7]++;
					break;
				case 'i':
				case 'I':
					letters[8]++;
					break;
				case 'j':
				case 'J':
					letters[9]++;
					break;
				case 'k':
				case 'K':
					letters[10]++;
					break;
				case 'l':
				case 'L':
					letters[11]++;
					break;
				case 'm':
				case 'M':
					letters[12]++;
					break;
				case 'n':
				case 'N':
					letters[13]++;
					break;
				case 'o':
				case 'O':
					letters[14]++;
					break;
				case 'p':
				case 'P':
					letters[15]++;
					break;
				case 'q':
				case 'Q':
					letters[16]++;
					break;
				case 'r':
				case 'R':
					letters[17]++;
					break;
				case 's':
				case 'S':
					letters[18]++;
					break;
				case 't':
				case 'T':
					letters[19]++;
					break;
				case 'u':
				case 'U':
					letters[20]++;
					break;
				case 'v':
				case 'V':
					letters[21]++;
					break;
				case 'w':
				case 'W':
					letters[22]++;
					break;
				case 'x':
				case 'X':
					letters[23]++;
					break;
				case 'y':
				case 'Y':
					letters[24]++;
					break;
				case 'z': // 26 in alphabet, thus 25 in array
				case 'Z':
					letters[25]++;
					break;
			} // switch case
		} // for loop
	} // while loop
	
	// fill 2D array with letters and frequencies (alphabetical order)
	int letter = 65; // start at A
	int count = 0; // used to count number of entries into the sortedletters array, and used for indexing
	for(int i=0; i < 26; ++i, ++letter)
	{
		if(letters[i] > 0)
		{
			sortedletters[count][0] = letter; // store the letter
			sortedletters[count][1] = letters[i]; // store the letter's count
			//cout << (char)sortedletters[count][0] << " " << sortedletters[count][1] << endl; // test--prints out letters with a count in alphabetical order
			count++;
		}
	}
	
	// 2D array already alphabetically sorted, now need to sort (descending) by letter count
	int max, index;
	for(int i = 0; i < count; i++) // find max, then look for match in array, print out letter and frequency, then remove max in array, repeat
	{
		max = *max_element(letters,letters+26); // pass in range values, not 2 values (max() uses 2 values)
		for(int j = 0; j <= count; j++)
		{
			if(sortedletters[j][1] == max)
			{
				cout << (char)sortedletters[j][0] << " " << sortedletters[j][1] << endl; // print out letter and its count
				sortedletters[j][1] = 0; // remove the current max from the array so it won't be printed again

				// also need to remove max from the array you are getting it from (array letters)
				index = sortedletters[j][0] - 65; // array has letters stored in alphabetical order, we can calculate the index (eg A-65 = index 0)
				letters[index] = 0;

				break;
			}
		}
	}

 return 0;
}
