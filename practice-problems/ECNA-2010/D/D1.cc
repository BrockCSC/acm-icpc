#include <iostream>
#include <cmath>
using namespace std;

const int MAX = 1000;
const double PI = 4.0*atan(1.0);

struct loc
{
	double x, y;
	double angle;
} locs[MAX];

int numCovered[MAX];	// numCovered[i] = # of people in frame if edge of
						//   view starts at loc[i]

double getAngle(int x, int y)
{
	double angle = atan2(y, x) * 180.0/PI;
	if (angle < 0.0)
		angle += 360.0;
	return angle;
}

double angleDiff(int i, int j, int n)
{
	if (i >= n)
		i -= n;
	double angle = locs[i].angle - locs[j].angle;
	if (angle < 0.0)
		angle += 360.0;
	return angle;
}

int main()
{
	int n, x, y, f, icase=0;
	cin >> n >> x >> y >> f;
	while (n > 0) {
		icase++;
		for(int i=0; i<n; i++) {
			loc l;
			cin >> l.x >> l.y;
			l.x -= x;
			l.y -= y;
			l.angle = getAngle(l.x, l.y);
			int j=i;
			while (j > 0 && locs[j-1].angle > l.angle) {
				locs[j] = locs[j-1];
				j--;
			}
			locs[j] = l;
		}
		int last=0;
		for(int i=0; i<n; i++) {
			while (last < i+n && angleDiff(last, i, n) < f) {
				last++;
			}
			numCovered[i] = last-i;
		}
		
		int best = n;
		for(int i=0; i<n; i++) {
			int sum = numCovered[i];
			int next = i+numCovered[i];
			int count = 1;
			while (sum < n) {
				if (next >= n)
					next -= n;
				sum += numCovered[next];
				next += numCovered[next];
				count++;
			}
			if (count < best)
				best = count;
		}
		cout << "Case " << icase << ": " << best << endl;
		cin >> n >> x >> y >> f;
	}
}
