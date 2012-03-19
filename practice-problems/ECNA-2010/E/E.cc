#include <iostream>
using namespace std;

const int MAXRINGS = 100;
const int MAXSECTORS = 100;

bool table[MAXRINGS][MAXSECTORS];
bool tmp[MAXRINGS][MAXSECTORS];

int getRowCount(int r, int s, int ns)
{
	int count = table[r][s];
	if (s>0)
		count += table[r][s-1];
	else
		count += table[r][ns-1];
	if (s<ns-1)
		count += table[r][s+1];
	else
		count += table[r][0];
	return count;
}

int getCount(int r, int s, int nr, int ns)
{
	int count = getRowCount(r, s, ns);
	if (r == 0)
		count += getRowCount(r, (s+ns/2)%ns, ns);
	else
		count += getRowCount(r-1, s, ns);
	if(r == nr-1)
		count += getRowCount(r, (s+ns/2)%ns, ns);
	else
		count += getRowCount(r+1, s, ns);
	return count;
}
		
int main()
{
	int m, n, k, g, icase=0;
	cin >> m >> n;
	while (m > 0) {
		icase++;
		for(int i=0; i<m; i++)
			for(int j=0; j<n; j++)
				table[i][j] = false;
		cin >> k;
		for(int i=0; i<k; i++) {
			int r, s;
			cin >> r >> s;
			table[r][s] = true;
		}
		cin >> g;

		for(int ig=1; ig<=g; ig++) {
			for(int i=0; i<m; i++) {
				for(int j=0; j<n; j++) {
					int count = getCount(i, j, m, n);
					if(table[i][j]) 
						tmp[i][j] = (count == 3 || count == 4);
					else
						tmp[i][j] = (count == 3);
				}
			}

			for(int i=0; i<m; i++)
				for(int j=0; j<n; j++)
					table[i][j] = tmp[i][j];
		}

	    int count = 0;
		int fr=-1, fs, lr, ls;
		for(int i=0; i<m; i++) {
			for(int j=0; j<n; j++) {
				if (table[i][j]) {
					count++;
					if (fr == -1) {
						fr = i;
						fs = j;
					}
					lr = i;
					ls = j;
				}
			}
		}
		cout << "Case " << icase << ": " << count;
		if (fr != -1)
			cout << ' ' << fr << ' ' << fs << ' '<< lr << ' ' << ls;
		else
			cout << ' ' << -1 << ' ' << -1 << ' '<< -1 << ' ' << -1;
		cout << endl;

		cin >> m >> n;
	}
}

