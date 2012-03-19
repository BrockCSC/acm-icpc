// Tri.cc

#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

const double PI = 3.141591828;

#define FOR(i,a,b) for(int i=a;i<b;i++)

int n,CaseNo=1;
bool done;

void GetTriangleSides(double &D1, double &D2, double &D3){
  double x1,y1,x2,y2,x3,y3;
  double a,b,D,temp;

  cin>>x1>>y1>>x2>>y2>>x3>>y3;
  a = x1;  b=y1;           //translate so (x1,y1) -> origin
  x1 -= a;
  y1 -= b;
  x2 -= a;
  y2 -= b;
  x3 -= a;
  y3 -= b;
  D = sqrt(x2*x2 + y2*y2);   //now rotate so (x2,y2) is on pos x-axis
  a = x2;
  b = y2;
  x2 = D;
  y2 = 0.0;                 // = (-b*x2+a*y2)/D
  temp = (a*x3+b*y3)/D;
  y3 = (-b*x3+a*y3)/D;
  x3 = temp;

  //computer length of each side
  D1 = x2;
  D2 = sqrt((x2-x3)*(x2-x3)+y3*y3);
  D3 = sqrt(x3*x3+y3*y3);

  //now see if input was oriented cw or ccw
  if(y3>0){     //ccw, so switch D! and D3
    temp = D1;  D1 = D3;  D3 = temp;
  }
}

struct holeType{
  double A[3];      //sides of tri, cw oriented
};

struct triType{
  double A[3];    //sides
  double a[3];    //angles
};

holeType Holes[20];
triType Tri[40];

struct pairType{
  int a,b;
};

vector<pairType> Fit[20];
pairType Pair,P,X[20];

bool IsEqual(double a, double b){
  if(abs(a-b) < 0.1) return true;
  return false;
}

bool SumToPi(double a,  double b){ //sum to PI?
  if(abs((a+b)-PI)<0.01) return true;
  return false;
}

//true if tri D1,D2,D3 matches with Holes[k]
bool ItMatches(int k, double D1, double D2, double D3){
  if(IsEqual(D1,Holes[k].A[0]) && IsEqual(D2,Holes[k].A[1]) &&
    IsEqual(D3,Holes[k].A[2]))   return true;
  if(IsEqual(D2,Holes[k].A[0]) && IsEqual(D3,Holes[k].A[1]) &&
    IsEqual(D1,Holes[k].A[2]))   return true;
  if(IsEqual(D3,Holes[k].A[0]) && IsEqual(D1,Holes[k].A[1]) &&
    IsEqual(D2,Holes[k].A[2]))   return true;
  return false;
}

//add pair i,j  to Fit[k]
void AddTris(int k, int i,  int j){
  pairType P;
  P.a = i; P.b=j;
  FOR(i,0,(int)Fit[k].size())
    if(Fit[k][i].a == P.a && Fit[k][i].b == P.b) return;     //(i,j) already in there
  Fit[k].push_back(P);
}

bool OK(pairType P,  int k){  //check X[0..k-1]
  FOR(i,0,k-1)
    if(X[i].a==P.a || X[i].b==P.b || X[i].b==P.a || X[i].a==P.b) return false;
  return true;
}

void PrintSolution(){ //print X[0..n-1]
  if(CaseNo>1) cout<<endl;

  cout<<"Case "<<CaseNo++<<":"<<endl;
  FOR(i,0,n){
    cout<<"Hole "<<i+1<<": ";
    cout<<X[i].a+1<<", "<<X[i].b+1<<endl;
  }
}

void FindFit(int k){  //BT
  pairType P;
  FOR(i,0,Fit[k].size()){
    if(done) return;
    P = Fit[k][i];
    if (OK(P,k)){
      X[k] = P;
      if(k==n-1) {  // done
        PrintSolution();
        done = true;
      }
      else // more work to do
        FindFit(k+1);
    }    
  }
}

int main(){
  double D1, D2, D3, angle;

  while(cin>>n && n){
    FOR(i,0,n) Fit[i].clear();
    FOR(i,0,n){
      GetTriangleSides(D1,D2,D3);
      Holes[i].A[0]=D1;
      Holes[i].A[1]=D2;
      Holes[i].A[2]=D3;
    }
    //now get 2n triangles
    FOR(i,0,2*n){
      GetTriangleSides(D1,D2,D3);
      Tri[i].A[0]=D1; Tri[i].A[1]=D2; Tri[i].A[2]=D3;
      Tri[i].a[0] = acos((D2*D2+D3*D3-D1*D1)/(2*D2*D3));
      Tri[i].a[2] = acos((D2*D2+D1*D1-D3*D3)/(2*D2*D1));
      Tri[i].a[1] = acos((D1*D1+D3*D3-D2*D2)/(2*D1*D3));
    }

   //for all pairs of triangles and each hole, see if 
   // the triangles can fill the hole
   // if so, add this info to the Fit[] vectors

  FOR(i,0,2*n-1)
    FOR(j,i+1,2*n){
      //try all ways of fitting together Tri[i] and Tri[j]
      FOR(t,0,3){
        FOR(s,0,3){
          //see if Tri[i].A[t] matches with Tri[j].A[s]
          //check if "top" angles matches (i on left)
          if(IsEqual(Tri[i].A[t], Tri[j].A[s]) && SumToPi(Tri[i].a[(t+1)%3],Tri[j].a[(s+2)%3]))
          {  //match on top - make big tri
             D1 = Tri[i].A[(t+2)%3]+Tri[j].A[(s+1)%3];
             D2 = Tri[j].A[(s+2)%3];
             D3 = Tri[i].A[(t+1)%3];
             //now  find a hole this fits in
             FOR(k,0,n)
               if(ItMatches(k,D1,D2,D3))
                 AddTris(k,i,j);
          }
          //check if "bottom" angles matches (i on left)
          if(IsEqual(Tri[i].A[t], Tri[j].A[s]) && SumToPi(Tri[i].a[(t+2)%3],Tri[j].a[(s+1)%3]))
          {  //match on top - make big tri
             D3 = Tri[i].A[(t+1)%3]+Tri[j].A[(s+2)%3];
             D2 = Tri[j].A[(s+1)%3];
             D1 = Tri[i].A[(t+2)%3];
             //now  find a hole this fits in
             FOR(k,0,n)
               if(ItMatches(k,D1,D2,D3))
                 AddTris(k,i,j);
          }
        }
      }
    }

   //Now Fit[] has the buckets of tri pairs. Use BT to find a total match.
   done = false;
   
   FindFit(0);

  }

  return 0;
}
