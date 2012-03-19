// Polar.cc

#include <iostream>
using namespace std;

#define FOR(i,a,b) for(int i=a;i<b;i++)

int m,n;    //m=#rings, n= # radii (even)
bool A[100][100];

void init(){
  FOR(i,0,m)
    FOR(j,0,n)
      A[i][j] = false;
}

void GetCells(){
  int k, a, b;
  cin>>k;
  FOR(i,0,k){
    cin>>a>>b;
    A[a][b] = true;
  }
}

// count the neighbors
// g = ring, d = radii
int Nbrs(int g, int d){  //count neighbors of A[g][d]
  int count = 0;
  
  if (g>0 && g<m-1){   //not on inner or outer ring
   if(A[g][(d+1) % n]) count++; 
   if(A[g][(d+n-1) % n]) count++; 
   if(A[(g+1) % m][d]) count++; 
   if(A[(g+1) % m][(d+1) % n]) count++; 
   if(A[(g+1) % m][(d+n-1) % n]) count++; 
   if(A[(g+m-1) % m][d]) count++; 
   if(A[(g+m-1) % m][(d+1) % n]) count++; 
   if(A[(g+m-1) % m][(d+n-1) % n]) count++; 
  }
  else if(g==m-1){      //inner ring
   if(A[m-1][(d+1) % n]) count++; 
   if(A[m-1][(d+n-1) % n]) count++; 
   if(A[m-2][d]) count++; 
   if(A[m-2][(d+1) % n]) count++; 
   if(A[m-2][(d+n-1) % n]) count++; 
   if(A[m-1][(d+n/2)%n]) count++; 
   if(A[m-1][(d+n/2+1) % n]) count++; 
   if(A[m-1][(d+n/2+n-1) % n]) count++; 
  }
  else if(g==0){     //outer ring
   if(A[0][(d+1) % n]) count++; 
   if(A[0][(d+n-1) % n]) count++; 
   if(A[1][d]) count++; 
   if(A[1][(d+1) % n]) count++; 
   if(A[1][(d+n-1) % n]) count++; 
   if(A[0][(d+n/2) % n]) count++; 
   if(A[0][(d+n/2+1) % n]) count++; 
   if(A[0][(d+n/2+n-1) % n]) count++; 
  }
  return count;
}

void MakeMove(){   // get next generation 
  bool Temp[m][n];
  FOR(i,0,m)
    FOR(j,0,n)
      if(A[i][j] && Nbrs(i,j)==2)
        Temp[i][j] = true;
      else if (Nbrs(i,j)==3)
        Temp[i][j] = true;
      else
        Temp[i][j] = false;

   //copy Temp[][] to A[][]
   FOR(i,0,m)
     FOR(j,0,n)
       A[i][j] = Temp[i][j];
}

void PrintLiveOnes(){  //output living cells
   int count = 0;
   int counter=0;

   FOR(i,0,m)
     FOR(j,0,n)
      if(A[i][j]) count++;

   cout<<count;
   if(count>0){
     FOR(i,0,m)
       FOR(j,0,n)
         if(A[i][j]){
           counter++;
           if (counter == 1) cout<<' '<<i<<' '<<j; 
           if(counter == count) cout<<' '<<i<<' '<<j;
         }
   } 
   else {   //count ==0
     cout<<" -1 -1 -1 -1";
   }
   cout<<endl; 
}

int main(){
  int gens;
  int CaseNo=1;

  cin>>m>>n;
  while(n>0){
    bool A[m][n];
    init ();
    GetCells();

    cin>>gens;
    FOR(i,0,gens){
      MakeMove();
    } 
    cout<<"Case "<<CaseNo++<<": ";
    PrintLiveOnes();
    
    cin>>m>>n;
  }

  return 0;
}
