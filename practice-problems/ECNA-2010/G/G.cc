//Vampires.cc

#include <iostream>
using namespace std;


#define FOR(i,a,b) for(int i=a; i<b; i++)

struct vamps{
  int x, y;
};

vamps Vampires[10000];

int v,  o, m;

char Grid[101][101];

void exchange(int &a,  int  &b){
  int temp = a;
  a = b;
  b = temp;
}

void ClearGrid(){
  FOR(x,0,101)
    FOR(y,0,101)
      Grid[x][y]='*';
}
  
void GetData(){
  int x, y, x1, y1, x2, y2;
  char D;

  ClearGrid();
  FOR(i,0,v)
    cin>>Vampires[i].x>>Vampires[i].y;
  FOR(i,0,o){
    cin>>x>>y;
    Grid[x][y]='H';
  }
  FOR(i,0,m){
    cin>>D;
    cin>>x1>>y1>>x2>>y2;
    if(x1==x2){
      if(y2<y1) exchange(y1,y2);
      FOR(y,y1,y2+1)
        Grid[x1][y]=D;
    }
    else if(y1==y2){
      if(x2<x1) exchange(x1,x2);
      FOR(x,x1,x2+1)
        Grid[x][y1]=D;
    }
    else {  
      cout<<"error on mirror input: ";
      cout<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<endl;
      return;
    }
  }
}

bool IsMirrorEast(int x,  int y){
  x++;
  while(x<=100){
    if(Grid[x][y] == 'H' || Grid[x][y]=='N' || Grid[x][y]=='E'
       || Grid[x][y]=='S')
      return false;
    if(Grid[x][y]=='W')
      return true;
    x++;
  }
  return false;
}

bool IsMirrorNorth(int x,  int y){
  y++;
  while(y<=100){
    if(Grid[x][y] == 'H' || Grid[x][y]=='W' || Grid[x][y]=='E'
       || Grid[x][y]=='N')
      return false;
    if(Grid[x][y]=='S')
      return true;
    y++;
  }
  return false;
}

bool IsMirrorSouth(int x,  int y){
  y--;
  while(y>=0){
    if(Grid[x][y] == 'H' || Grid[x][y]=='W' || Grid[x][y]=='E'
       || Grid[x][y]=='S')
      return false;
    if(Grid[x][y]=='N')
      return true;
    y--;
  }
  return false;
}

bool IsMirrorWest(int x,  int y){
  x--;
  while(x>=0){
    if(Grid[x][y] == 'H' || Grid[x][y]=='N' || Grid[x][y]=='W'
       || Grid[x][y]=='S')
      return false;
    if(Grid[x][y]=='E')
      return true;
    x--;
  }
  return false;
}

int main(){
  int caseNo=1, a, b;

  cin>>v>>o>>m;
  while(v>0 || o>0 || m>0){
    GetData();
    cout<<"Case "<<caseNo++<<':'<<endl;
    bool None = true;
    FOR(i,0,v){
      //see if vampire i is exposed
      bool exposed = false;
      a = Vampires[i].x; b = Vampires[i].y; 
      if(IsMirrorEast(a,b)) exposed = true; 
      if(IsMirrorNorth(a,b))  exposed = true;
      if(IsMirrorSouth(a,b)) exposed=true;
      if(IsMirrorWest(a,b)) exposed=true;
      if (exposed){
        None = false;
        cout<<"vampire "<< i+1;
        if(IsMirrorEast(a,b)) cout<<" east";
        if(IsMirrorNorth(a,b)) cout<<" north";
        if(IsMirrorSouth(a,b)) cout<<" south";
        if(IsMirrorWest(a,b)) cout<<" west";
        cout<<endl;
      }
    }
    if (None) cout<<"none"<<endl;

    cin>>v>>o>>m;
  }
  

  return 0;
}
