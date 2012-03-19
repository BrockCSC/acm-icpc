#include <iostream>
#include <string>
using namespace std;

const int MAXSIZE = 40;

struct cube {
	bool f, b, l, r, u, d;
	bool empty;
	char move;
} maze[MAXSIZE][MAXSIZE][MAXSIZE];

struct loc
{
	int i, j, k;
	loc *next;
};

void readData(int n)
{
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			for(int k=0; k<n; k++) {
				maze[i][j][k].f = false;
				maze[i][j][k].b = false;
				maze[i][j][k].l = false;
				maze[i][j][k].r = false;
				maze[i][j][k].u = false;
				maze[i][j][k].d = false;
				maze[i][j][k].empty = false;
				maze[i][j][k].move = ' ';
			}
		}
	}
	char ch;
	string s;
							// front face
	cin >> s;					// read in first string
	for(int k=n-2; k>=1; k--) {
		cin >> ch;				// read in first 'X';
		for(int j=n-2; j>=1; j--) {
			cin.get(ch);
			if(ch == ' ') {
				maze[0][j-1][k].l = true;
				maze[0][j+1][k].r = true;
				maze[0][j][k-1].u = true;
				maze[0][j][k+1].d = true;
				maze[0][j][k].empty = true;
			}
		}
		cin >> ch;				// read in last 'X';
	}
	cin >> s;					// read in last string

							// right face
	cin >> s;					// read in first string
	for(int k=n-2; k>=1; k--) {
		cin >> ch;				// read in first 'X';
		for(int i=1; i<n-1; i++) {
			cin.get(ch);
			if(ch == ' ') {
				maze[i][0][k-1].u = true;
				maze[i][0][k+1].d = true;
				maze[i-1][0][k].b = true;
				maze[i+1][0][k].f = true;
				maze[i][0][k].empty = true;
			}
		}
		cin >> ch;				// read in last 'X';
	}
	cin >> s;					// read in last string

							// back face
	cin >> s;					// read in first string
	for(int k=n-2; k>=1; k--) {
		cin >> ch;				// read in first 'X';
		for(int j=1; j<n-1; j++) {
			cin.get(ch);
			if(ch == ' ') {
				maze[n-1][j-1][k].l = true;
				maze[n-1][j+1][k].r = true;
				maze[n-1][j][k-1].u = true;
				maze[n-1][j][k+1].d = true;
				maze[n-1][j][k].empty = true;
			}
		}
		cin >> ch;				// read in last 'X';
	}
	cin >> s;					// read in last string

							// left face
	cin >> s;					// read in first string
	for(int k=n-2; k>=1; k--) {
		cin >> ch;				// read in first 'X';
		for(int i=n-2; i>=1; i--) {
			cin.get(ch);
			if(ch == ' ') {
				maze[i][n-1][k-1].u = true;
				maze[i][n-1][k+1].d = true;
				maze[i-1][n-1][k].b = true;
				maze[i+1][n-1][k].f = true;
				maze[i][n-1][k].empty = true;
			}
		}
		cin >> ch;				// read in last 'X';
	}
	cin >> s;					// read in last string

							// up face
	cin >> s;					// read in first string
	for(int i=n-2; i>=1; i--) {
		cin >> ch;				// read in first 'X';
		for(int j=n-2; j>=1; j--) {
			cin.get(ch);
			if(ch == ' ') {
				maze[i][j-1][n-1].l = true;
				maze[i][j+1][n-1].r = true;
				maze[i-1][j][n-1].b = true;
				maze[i+1][j][n-1].f = true;
				maze[i][j][n-1].empty = true;
			}
		}
		cin >> ch;				// read in last 'X';
	}
	cin >> s;					// read in last string

							// down face
	cin >> s;					// read in first string
	for(int i=1; i<n-1; i++) {
		cin >> ch;				// read in first 'X';
		for(int j=n-2; j>=1; j--) {
			cin.get(ch);
			if(ch == ' ') {
				maze[i][j-1][0].l = true;
				maze[i][j+1][0].r = true;
				maze[i-1][j][0].b = true;
				maze[i+1][j][0].f = true;
				maze[i][j][0].empty = true;
			}
		}
		cin >> ch;				// read in last 'X';
	}
	cin >> s;					// read in last string
}
		
void connect(int n)
{
	for(int i=1; i<n-1; i++) {
		for(int j=1; j<n-1; j++) {
			for(int k=1; k<n-1; k++) {
				if (maze[0][j][k].empty && maze[n-1][j][k].empty &&
					maze[i][0][k].f && maze[i][n-1][k].f &&
					maze[i][j][0].f && maze[i][j][n-1].f)
					maze[i][j][k].f = true;
				if (maze[0][j][k].empty && maze[n-1][j][k].empty &&
					maze[i][0][k].b && maze[i][n-1][k].b &&
					maze[i][j][0].b && maze[i][j][n-1].b)
					maze[i][j][k].b = true;
				if (maze[i][0][k].empty && maze[i][n-1][k].empty &&
					maze[0][j][k].r && maze[n-1][j][k].r &&
					maze[i][j][0].r && maze[i][j][n-1].r)
					maze[i][j][k].r = true;
				if (maze[i][0][k].empty && maze[i][n-1][k].empty &&
					maze[0][j][k].l && maze[n-1][j][k].l &&
					maze[i][j][0].l && maze[i][j][n-1].l)
					maze[i][j][k].l = true;
				if (maze[i][j][0].empty && maze[i][j][n-1].empty &&
					maze[0][j][k].u && maze[n-1][j][k].u &&
					maze[i][0][k].u && maze[i][n-1][k].u)
					maze[i][j][k].u = true;
				if (maze[i][j][0].empty && maze[i][j][n-1].empty &&
					maze[0][j][k].d && maze[n-1][j][k].d &&
					maze[i][0][k].d && maze[i][n-1][k].d)
					maze[i][j][k].d = true;
			}
		}
	}
}

string solve(int n)
{
	loc *phead, *ptail;
	phead = ptail = new loc;
	phead->i = phead->j = phead->k = 1;
	maze[1][1][1].move = 'S';
	while (maze[n-2][n-2][n-2].move == ' ') {
		int i=ptail->i, j=ptail->j, k=ptail->k;
		if (maze[i][j][k].f && maze[i-1][j][k].move==' ') {
			phead = phead->next = new loc;
			phead->i = i-1;
			phead->j = j;
			phead->k = k;
			maze[i-1][j][k].move = 'F';
		}
		if (maze[i][j][k].b && maze[i+1][j][k].move==' ') {
			phead = phead->next = new loc;
			phead->i = i+1;
			phead->j = j;
			phead->k = k;
			maze[i+1][j][k].move = 'B';
		}
		if (maze[i][j][k].l && maze[i][j+1][k].move==' ') {
			phead = phead->next = new loc;
			phead->i = i;
			phead->j = j+1;
			phead->k = k;
			maze[i][j+1][k].move = 'L';
		}
		if (maze[i][j][k].r && maze[i][j-1][k].move==' ') {
			phead = phead->next = new loc;
			phead->i = i;
			phead->j = j-1;
			phead->k = k;
			maze[i][j-1][k].move = 'R';
		}
		if (maze[i][j][k].u && maze[i][j][k+1].move==' ') {
			phead = phead->next = new loc;
			phead->i = i;
			phead->j = j;
			phead->k = k+1;
			maze[i][j][k+1].move = 'U';
		}
		if (maze[i][j][k].d && maze[i][j][k-1].move==' ') {
			phead = phead->next = new loc;
			phead->i = i;
			phead->j = j;
			phead->k = k-1;
			maze[i][j][k-1].move = 'D';
		}
		ptail = ptail->next;
	}
	string ans = "";
	int i=n-2, j=n-2, k=n-2;
	while (maze[i][j][k].move != 'S') {
		char ch = maze[i][j][k].move;
		ans = ch + ans;
		if (ch == 'F')
			i++;
		else if (ch == 'B')
			i--;
		else if (ch == 'L')
			j--;
		else if (ch == 'R')
			j++;
		else if (ch == 'U')
			k--;
		else if (ch == 'D')
			k++;
		else
			cout << "ERROR: bad direction: ch = " << ch <<endl;
	}
	return ans;
}

int main()
{
	int n;
	cin >> n;
	while (n != 0) {
		readData(n);
		connect(n);
		string ans = solve(n);
		cout << ans << endl;
		cin >> n;
	}
	return 0;
}
