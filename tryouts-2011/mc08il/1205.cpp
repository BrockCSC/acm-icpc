using namespace std;
#include<iostream>
#include<vector>

int main(void)
{
	int N,R;
	cin >>N;
	cin>>R;
	vector<int> hold[N+1];
	int i;
	for(i=1; i<=N;i++)
	{
		int x;
		cin  >> x;
		hold[i].push_back(x);
	}
	for(i=0; i<N-1; i++)
	{
		int x,y;
		cin >> x;
		cin >>y;
		hold[x].push_back(y);
	}
	
	vector<int> temp;
	int c1=hold[R].at(0);
	int Fi=1;
	for(i=1; i<hold[R].size(); i++)
	{
		temp.push_back(hold[R].at(i));	
	}
	for(i=1; i<N;i++)
	{
		int j;
		for (j=1; j<hold[i].size();j++)
		{
			temp.push_back(hold[i].at(j));
		}
		int m=0;
		int mi=0;
		for(j=0;j<temp.size();j++)
		{
			int z =temp.at(j);
			int temp1=hold[z].at(0);
			int h;
			for (h=1; h<hold[z].size();h++)
			{
				temp1+=hold[hold[z].at(h)].at(0);
			}
			if(m<temp1)
			{
				m=temp1;
				mi=j;

			}
		}
		
		int g=hold[temp.at(mi)].at(0);
		
		temp.at(mi)=temp.at(temp.size()-1);
		temp.pop_back();
		Fi+=1;
		
		c1+= Fi*g;
		cout<< c1<<" *  * "<<Fi<<" *  * "<<g<<endl;

		
	}

	cout << c1;

}
