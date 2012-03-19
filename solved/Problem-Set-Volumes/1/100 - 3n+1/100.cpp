/* problem #: 100
 * 3n+1 
 *
 * for all the integers between i and j (i,j inclusive)
 * calculate the hillstone sequence and find the longest
 * sequence, keep track of its length.
 *
 * "All integers will be less than 1,000,000 and greater than 0" */

#include <iostream>
using namespace std;

int main()
{
	int i, j, k, seqLength, maxLength, n, iCpy, jCpy; // seqLength is sequence length

	while (cin >> i)
	{
 		cin >> j;
		maxLength = 0; // reset max length for every i,j-set

		// need to make sure it computes the sequences even if i and j are given in descending order
		if (i > j)
		{
			iCpy = j;
			jCpy = i;
		}
		else
		{
			iCpy = i;
			jCpy = j;
		}

  		for (k = iCpy; k <= jCpy; k++)
  		{
			n = k; // cannot use n in loop condition, since value of n changes here
  			seqLength = 1; // integers are always greater than 0, thus start at 1
   
   			while(n > 1)
   			{
    				if (n%2 == 0) n = n / 2;
    				else n = n * 3 + 1;
    				seqLength++;
   			}
   
   			if (seqLength > maxLength) maxLength = seqLength;
  		}
  		cout << i << " " << j << " " << maxLength << endl;
 	}
 	return 0;
}
