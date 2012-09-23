#include <stdlib.h> // for exit(0)
#include <algorithm> // for max_element(first,last)
#include <iostream>
using namespace std;

int main()
{
 // read n
 // read n lines -- only read in letters
 // convert letters to uppercase (or lowercase, but must be persistent)
 // have a counter for each letter
 // sort letter count list in descending order -- if letters have an equal count, sort those letters in alphabetic order

  int n;
  string word; // a "word" is considered anything with no spaces
  char character;
  int letters[26];
  int sortedletters[26][2];

  for (int i = 0; i < 26; ++i)
    letters[i] = 0;
	
  cin >> n;
  if (n < 1) exit(0);

  while (cin >> word)
  {
    for (int i = 0; i < word.size(); ++i)
    {
      character = (char)word.at(i);
      switch (character)
      {
        case 'a':
        case 'A':
          letters[0]++;
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
        case 'z':
        case 'Z':
          letters[25]++;
          break;
      }
    }
  }

  int letter = 65; // start at 'A'
  int count = 0;
  for (int i = 0; i < 26; ++i, ++letter)
  {
    if (letters[i] > 0)
    {
      sortedletters[count][0] = letter;
      sortedletters[count][1] = letters[i];
      count++;
    }
  }

  int max, index;
  for (int i = 0; i < count; i++)
  {
    max = *max_element(letters, letters+26);
    for (int j = 0; j <= count; j++)
    {
      if (sortedletters[j][1] == max)
      {
        cout << (char)sortedletters[j][0] << " " << sortedletters[j][1] << endl;
        sortedletters[j][1] = 0; // remove the current max
        index = sortedletters[j][0] - 65;
        letters[index] = 0; // also remove max here
        break;
      }
    }
  }
  return 0;
}
