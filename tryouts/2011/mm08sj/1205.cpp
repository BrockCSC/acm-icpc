#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <set>

using namespace std;

void search(int root, vector<int> weights, map<int,vector<int>*> connections);

int main()
{
	string line;
	int nodes = 0;
	int root;
	cin >> nodes >> root;
	vector<int> weights;
	map<int,vector<int>*> nodelist;
	for(int i =0; i<nodes; i++)
	{
		int val;
		cin >> val;
		weights.push_back(val);
		nodelist[i+1] = new vector<int>();
	}
	while(true)
	{
		int input, output;
		cin >> input;
		cin >> output;
		if(input==0 || output==0)
			break;
		nodelist[input]->push_back(output);
	}
	search(root,weights,nodelist);
	return 0;
}


void search(int root, vector<int> weights, map<int,vector<int>*> connections)
{
	queue<vector<int>*> orders;
	vector<int>* startvect = new vector<int>();
	startvect->push_back(root);
	orders.push(startvect);
	int bestvalue = 0;
	while(!orders.empty())
	{
		vector<int>* order = orders.front();
		orders.pop();
		if(order->size()<weights.size())
		{
		set<int> next;
		for(int i = 0; i<order->size(); i++)
		{
			vector<int>* children = connections[(*order)[i]];
			for(int i = 0; i<children->size(); i++)
			{
				next.insert((*children)[i]);
			}
			set<int>::iterator it;
			for(it = next.begin(); it!=next.end(); it++)
			{
				vector<int>* nextvect = new vector<int>(order->begin(),order->end());
				nextvect->push_back(*it);
				orders.push(nextvect);
			}
		}
		}
		else
		{
		int value = 0;
		for(int i=0; i<order->size(); i++)
		{
			value += (i+1) * weights[(*order)[i]];
		}
		if(bestvalue==0 || value<bestvalue)
		{
			bestvalue = value;
		}
		}
		delete order;
	}
	cout << bestvalue;
}
