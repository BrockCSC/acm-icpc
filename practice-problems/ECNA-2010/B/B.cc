// FlipIt.cc

#include <vector>
#include <iostream>
using namespace std;

#define FOR(i,a,b) for(int i=a;i<b;i++)

int Left, Right, Bottom, Top;
int CaseNo=1;
int n, m;
vector<int> A[20][20];

void init(){
  Left=Top=0;
  Bottom = n-1;
  Right = m-1;
}

void GetArray(){
  int x;
  FOR(i,0,n)
   FOR(j,0,m)
     A[i][j].clear();
  FOR(i,0,n)
   FOR(j,0,m){
    cin>>x;
    A[i][j].push_back(x);
   }
}

void MakeFlip(char c){
  if(c=='L'){   //A[*][Left] -> A[*][Left+1]
   FOR(j,Top,Bottom+1){
    for(int k=A[j][Left].size()-1; k>=0; k--){
      A[j][Left+1].push_back(A[j][Left][k] * -1);
    }
  }
   Left++;
   return;
  }
  if(c=='R'){   //A[*][Right] -> A[*][Right-1]
   FOR(j,Top,Bottom+1){
    for(int k=A[j][Right].size()-1; k>=0; k--){
      A[j][Right-1].push_back(A[j][Right][k] * -1);
    }
  }
   Right--;
   return;
  }
  if(c=='B'){    //A[Bottom][*] -> A[Bottom-1][*]
    FOR(i,Left,Right+1){
      for(int k=A[Bottom][i].size()-1; k>=0;k--){
        A[Bottom-1][i].push_back(A[Bottom][i][k] * -1);
      }
    }
    Bottom--;
    return;
  }
  if(c=='T'){    //A[Top][*] -> A[Top+1][*]
    FOR(i,Left,Right+1){
      for(int k=A[Top][i].size()-1; k>=0;k--){
        A[Top+1][i].push_back(A[Top][i][k] * -1);
      }
    }
    Top++;
    return;
  }
}

int main(){
  char c;

  cin>>n>>m;
  while(n>0){
    GetArray();
    init();

    FOR(i,0,n+m-2){
      cin>>c;
      MakeFlip(c);
    }
    cout<<"Case "<<CaseNo++<<":";
    FOR(k,0,A[Bottom][Left].size())
      if(A[Bottom][Left][k]>0)
        cout<<' '<<A[Bottom][Left][k];
    cout<<endl;

    cin>>n>>m;
  }

  return 0;
}
