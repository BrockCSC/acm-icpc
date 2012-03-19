#include <iostream>
using namespace std;

int main(void)
{
	int t; // number of test cases
	int n; // number of days ( 7 <= n <= 3650)
	int p; // number of political parties (1 <= p <= 100)
	int hi; // hartel parameter
	int strikedays;
	int * harteldays; // days of strike (Fri and Sat not included)

	cin >> t;
	if(t <= 0) exit(0);
	
	for(int i=0; i < t; i++)
	{
		cin >> n; // read in number of days to simulate
		cin >> p; // read in number of political parties
		
		harteldays = new int[n];
		for(int j=0; j < p; j++)
		{
			cin >> hi;
			
			for(int k=0; k < n; k++) // iterate through array
			{
				if((k+1) % hi == 0)
				{
					if((k+1) % 7 != 0 &&  (k+2)% 7 != 0)
						harteldays[k] = 1;
					else
						harteldays[k] = 0;
				}
			}
		}
		strikedays = 0;
		for(int l=0; l < n; l++)
			strikedays += harteldays[l];
		
		cout << strikedays << endl;
	}

	return(0);
}
