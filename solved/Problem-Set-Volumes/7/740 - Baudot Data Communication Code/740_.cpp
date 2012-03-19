 #include <iostream>
 #include <sstream>
 #include <string>
 #include <algorithm>
 #include <vector>
 #include <cmath>
 using namespace std;
 
 #define GI ({int _t; scanf("%d", &_t); _t;})
 #define FOR(i, a, b) for (int i=a; i<b; i++)
 #define REP(i, a) FOR(i, 0, a)
 template<class T> string toString(T n){ostringstream ost;ost<<n;ost.flush();return ost.str();}
 int toInt(string s){int r=0;istringstream sin(s);sin>>r;return r;}
 #define DBGV(_v) { REP(_i, _v.size()) { cout << _v[_i] << "\t";} cout << endl;} // DeBuG Vector
 
 int binary2decimal( string bin)
 {
 	int res = 0;
 	for (int i=bin.size()-1, j=0; i>=0; i--, j++)
 		res += (bin[i]-'0')*((int)pow((double)2, (double)j));
 	return res;
 }
 
 int main()
 {
 	string down, up, line;
 	getline (cin, down);
 	getline (cin, up);
 	while (getline(cin, line))
	{
 		bool down_status = true;
 		for (int i =0; i<line.size(); i+=5)
		{
 			string cur = line.substr(i, 5);
 			int num = binary2decimal(cur);
 			if (num == 27) down_status = true;
 			else if (num == 31) down_status = false;
 			else printf("%c", (down_status==true?down[num]:up[num]));
 		}
 		printf("\n");
 	}
 	return 0;
 }
