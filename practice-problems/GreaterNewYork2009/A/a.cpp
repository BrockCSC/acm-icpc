// http://www.acmgnyr.org/year2009/problems.shtml
// Nth largest value
#include <iostream>
#include <algorithm>
using namespace std;

#define REP(i,a) for(i=0;i<a;i++)
int main()
{
	int p; // # of data sets
	cin >> p;
	int setNum; // dataset number
	int dataSet[p];
	int i;
	REP(i,p)
	{
		cin >> setNum;
		int j;
		REP(j,10)
		{
			cin >> dataSet[j];
		}
		sort(dataSet, dataSet+10);
		cout << setNum << " " << dataSet[7] << endl;
	}
	return 0;
}
