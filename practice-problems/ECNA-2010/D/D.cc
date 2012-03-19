// Photo.cc

#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define PI 3.14159265;
#define FOR(i, a, b) for(int i=a; i<b; i++)

int n, f;
double x,y;

vector<double> Angles;

void PrintAngles(){
  FOR(i,0,n)
   cout<<Angles[i]<<' ';
  cout<<endl;
}

void GetAngles(){
  double a,b;
  double result;
  
  Angles.clear();
  FOR(i,0,n){
    cin>>a>>b;
    a -= x;
    b -= y;
    result = atan2(b,a) * 180 / PI;
    if (result<0) result += 360;      // all angles >= 0
    Angles.push_back(result);
  }
  sort(Angles.begin(), Angles.end());
  // for debugging: 
  // check if angles distinct
  FOR(i,1,n)
    if(Angles[i-1]==Angles[i]) cout <<"two angles equal " <<i<<' '<<Angles[i]<<' '<<Angles[i-1]<<endl;
   // now check for angles that are f apart
   FOR(i,0,n)
     FOR(j,i+1,n)
       if (fabs(fabs(Angles[j]-Angles[i])-f)<0.01 || fabs(fabs(Angles[j]-Angles[i])-(360-f))<0.01)
         cout<<"angles "<<i<<"("<<Angles[i]<<") and "<<j<<"("<<Angles[j]<<") nearly equal to f="<<f<<endl; 
}

//returns angle from x to y (in degrees)
double Tween(double x, double y){
  double diff = y - x;
  if (diff <  0) diff += 360.0;
  return diff;
}

//return # shots if first guy in pic is start (@ Angle[start])
int CountShots(int start){
  int shots = 0;
  int i=start;
  double angle = Angles[start];
  double lastangle;

  while(1){
    shots++;
    
    i = (i+1) % n;    //next person
    while ( i != start && Tween(angle, Angles[i]) <= f)
      i = (i+1) % n; 
    if (i == start) return shots;

    angle = Angles[i];     //get next starting angle
  }
}

int main(){
  int bestshots, shots;
  int caseNo = 1;

  cin>>n>>x>>y>>f;
  while(n>0){
if (n>100) cout<<" n too large: "<<n<<endl;
    GetAngles();
    bestshots = n;
    FOR(i,0,n){
      shots = CountShots(i);
      if (shots < bestshots) bestshots = shots;
    }

    cout<<"Case "<<caseNo++<<": "<<bestshots<<endl;

    cin>>n>>x>>y>>f;
  }

  return 0;
}
