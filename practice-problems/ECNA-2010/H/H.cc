// Chem.cc
//
// Sets up a matrix to solve a system of equations using
// "integer" Gaussian elimination

#include <vector>
#include <iostream>
using namespace std;

#define FOR(i,a,b) for(int i=a; i<b; i++)

int A[20][20];
int n, m, rows, cols;

// data & routines to input terms
struct ptype{
  string sym;
  int mult;
  int term;
};

vector<ptype> T;
vector<ptype> Left;
vector<ptype> Right;

string S;

//get symbol at S[i] and push it onto T
//advance i
void GetSym(int &i){
  ptype P;
  string M=""; 
  M += S[i++];
  if (isalpha(S[i]) && 'a'<=S[i] && S[i]<='z')
    M += S[i++];
  P.sym = M;
  P.mult = 1;
  T.push_back(P);
}

int GetNum(int &i){
  int x=0;
  x = S[i++]-'0';
  while (i<S.length() && isdigit(S[i])){
      x *=10;
      x += S[i] - '0';
      i++;
  }
  return x;
}

void MultDown(int n){
  int i=T.size()-1;
  while(i>=0 && T[i].sym !="("){
    T[i].mult *= n;
    i--;
  }
  if(i<0) {      //shouldn't happen
    cout<< "never found (     ********** error *******"<<endl; 
    return;
  }
  //T[i].sym == "("  erase it 
  T.erase(T.begin()+i);
}

//end of stuff to input terms

int gcd(int a, int b){
  if ( b == 0) return a;
  if (a==0) return 0;
  return gcd (b,a%b);
}

//Gaussian elimination routines

void SwapRows(int a, int b){ //swap A[a][*] and A[b][*]
  int temp;

  if (a==b) return;
  FOR(j,0,cols){
    temp = A[a][j];
    A[a][j] = A[b][j];
    A[b][j] = temp;
  }
}

void CleanUp(int n, int m){   //divide each row by gcd
  int GCD, s, col;

  FOR(r,0,n){
    s = A[r][0];
    col = 0;
    while (A[r][col]==0 && col<m) col++;
    if (col<m){    //find gcd for rest of row
      GCD = A[r][col];
      FOR(c,col+1,m)
        if(A[r][c]!=0)
          GCD = gcd(GCD, A[r][c]);
      if (GCD <0) GCD *= -1;
    //reduce row
      FOR(c,0,m)
        A[r][c] /= GCD;
    }
  }
}

void Pivot(int a){   //pivot on A[a][a]
  int p = A[a][a], p2;
 
  if(A[a][a] == 0) {     //this shouldn't happen
    cout<<a<<" is 0"<<endl;
  }
 
  FOR(r,0,rows)
    if (r!=a){
      p2 = A[r][a];
      FOR(c,0,cols)
        A[r][c] = A[r][c]*p - A[a][c] * p2;
    }
    CleanUp(rows,cols);
}

int Reduce(int n, int m){
  int p=0;             //current pivot row
  int r;

  while(p<n){          //while rows left
    r=p;               //start row
    while(r<n && A[r][p]==0) r++;   //find non-zero entry in column p
    if(r==n) {
      return(p);
    }
    if(A[r][p]<0)
      FOR(c,0,m) A[r][c] *= -1;
    SwapRows(p,r);     //now A[p][p] != 0
    Pivot(p);
    p++;              //go to next column
  }
  return n;   
}

// end of Gaussian elimination routines

void PrintSol(int r, int c){
   int g = A[0][0];

   if(r!= c-1) {
     cout <<" No"<<endl;
     return;
   }
   
   //if any LHS result in neg values, no solution
   FOR(a,0,n){   
     if((A[a][a]>0 && A[a][c-1]<0) ||
       (A[a][a]<0 && A[a][c-1]>0))  {
        cout <<" No"<<endl;
        return;
     } 
   }
   //might have neg values in far right spot;  there should be only if other
   // RH spots are positive    (also check if A[a][c-1]==0: no sol then)
   // conversely if 
   FOR(a,0,r){
     if (A[a][c-1]==0){
       cout<< " No"<<endl;
       return;
     }
     if(A[a][c-1]<0)        //this can only happen if dependent var is RH
       if(a<n){
         cout<<" No"<<endl;
         return;
       }     
     if(A[a][c-1]>0)       //only if a is LH
       if(a>=n){
         cout<<" No"<<endl;
         return;
       }     
   }
 
   //might have neg values in some RH spots; make pos
   FOR(a,0,r)
    FOR(b,0,c)
      if(A[a][b]<0) A[a][b] *= -1;

   int m=1;
   bool ok = false;
   while(!ok){
     ok = true;
     FOR(k,0,c-1)
       //A[k][k] vs A[k][c-1]
       if(A[k][c-1]*m % A[k][k] != 0){
         ok = false;
         break;
       }
     if(!ok) m++;
   }
   // got correct value (m) for A[k][c-1]
   FOR(k,0,c-1)
     cout<<" "<<(A[k][c-1]*m)/A[k][k];
   cout<<" "<<m<<endl;
}

void GetT(){
  ptype P;
  int x;

  cin>>S;

  T.clear();

  int i=0;
  while(i<S.length()){
    if(isalpha(S[i]))
      GetSym(i);
    if(isdigit(S[i])){
      x = GetNum(i);
      T[T.size()-1].mult = x;
    }
    if(S[i] == '('){
      P.sym.clear();
      P.sym += '(';
      T.push_back(P);
      i++;
    }
    if(S[i] == ')'){
      if(isdigit(S[i+1])){
        i++;
        x = GetNum(i);
        MultDown(x);
      }
      else{
       MultDown(1);     // get rid of "("
       i++;
      }
    }
      
  }
} 
//end of GetT()

void EnterLeft(int k){  //enter info from T into Left
  FOR(i,0,T.size()){
    T[i].term = k;
    Left.push_back(T[i]);
  }
}

void EnterRight(int k){  //enter info from T into Right 
  FOR(i,0,T.size()){
    T[i].term = k;
    Right.push_back(T[i]);
  }
}

// build the matrix of equations to solve

void BuildA(){
  cols = n+m;
  vector<string> Symbols;
  bool found;

  //determine # rows by counting symbols
  Symbols.clear();
  int Count = 0;
  FOR(i,0,Left.size()){
    S = Left[i].sym;
    found = false;
    FOR(j,0,Symbols.size())
      if(Symbols[j] == S) found = true;
    if(!found){
      Count++;
      Symbols.push_back(S);
    }
  }
  rows = Count;
  //Build A[rows][cols]
  int num = 0;

  FOR(r,0,rows){
    S = Symbols[r];     // S is symbol for this row
    // there are n columns for LHS
    FOR(c,0,n){
      num = 0;
      //Find symbol S, term c, in Left[]
      FOR(k,0,Left.size()) 
        if(Left[k].sym == S && Left[k].term == c) {
          num = Left[k].mult;
          break;
        }
      A[r][c] = num;
    }
    // now do the m columns for RHS
    FOR(c,0,m){
      num = 0;
      //Find symbol S, term c in Right[]
      FOR(k,0,Right.size())
        if(Right[k].sym == S && Right[k].term==c){
          num = Right[k].mult;
          break;
        }
      A[r][c+n] = num;
    }
  }
}
// end of BuildA[]

int main(){
  int x, CaseNo=1;

  cin>>n>>m;    //get # of terms on left and right

  while(n>0) {
    Left.clear();
    Right.clear();

    FOR(i,0,n){
      GetT();
      EnterLeft(i);     //put entries of T into Left
    }

    FOR(i,0,m){
      GetT();
      EnterRight(i);    //put entries of T into Right
    }
 
    BuildA();
    x = Reduce(rows,cols);         //x = # row rank of A[][]
    cout<<"Case "<<CaseNo++<<':';
    PrintSol(x,cols);

    cin>>n>>m;
  }

  return 0;
}
