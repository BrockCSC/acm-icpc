// Voting.cc

#include <cmath>
#include <iostream>
using namespace std;


#define FOR(i, low, hi) for(int i=low; i<hi;i++)

int V[10001][100];      //dynamic table
int Spent[100001][100];  //money spent on precinct [][i]
int m, n;               //n = # precincts, m= money
int Pop[100];
double Init_perc[100];
double Delta_perc[100];

void GetInfo(){   //we put precinct 0 in slot n-1, prec in n-2,...
  FOR(i,0,n){
    cin >> Pop[n-1-i]>>Init_perc[n-1-i]>>Delta_perc[n-1-i];
    Init_perc[n-1-i] *= 0.01;
    Delta_perc[n-1-i] *= 0.01;
  }
}

void init(){
  FOR(i,0,n)
    FOR(j,0,m+1)
      V[j][i]=Spent[j][i]=0; 

  V[0][0]=round(Pop[0]*Init_perc[0]);        //no money spent

  //figure values for precinct 0
  FOR(j,1,m+1){
    V[j][0] = round( Pop[0]*(Init_perc[0]+(Delta_perc[0]*j)/((double)(10.1+j))));
    Spent[j][0] = j;
  }
}

void PrintPrecinctInfo(){
  int money = m;
  FOR(i,0,n){
    if(i>0) cout<<' ';
    cout<<i<<':'<<Spent[money][n-1-i];
    money -= Spent[money][n-1-i];
  }
}


int main(){
   int CaseNo=1;

  cin>>m>>n;
  while(m>0){
    //m /= 100;
    GetInfo();
    init();

    FOR(i,1,n){
      FOR(j,0,m+1){     //j=money spent on precincts 0..i
        int MaxVotes=V[0][i];     //default is to spend no money
        int LocalSpent = 0;
        FOR(k,0,j+1){           //spend k (out of j) on prec i
          int Vo =       //spend k on prec i and j-k on prec 0..i-1
             round (Pop[i]*(Init_perc[i]+(Delta_perc[i]*k)/((double) 10.1+k)))
             + V[j-k][i-1];
          if(Vo >= MaxVotes){
            LocalSpent = k;
            MaxVotes = Vo;
          }
        }
        V[j][i] = MaxVotes;
        Spent[j][i] = LocalSpent;
      }
    }

    //V[m][n-1] is the best we can do 
    cout << "Case "<< CaseNo++<<": "<< V[m][n-1]<< endl;
    //PrintPrecinctInfo(n-1, m);
    PrintPrecinctInfo();
    cout<<endl;

    cin>>m>>n;
  }

  return 0;
}

