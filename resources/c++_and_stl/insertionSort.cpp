#include <iostream>
using namespace std;

#define ELEMENTS 6

void insertion_sort(int x[], int length)
{
  int key, i, j;
  for(j=1; j < length; j++)
  {
     key = x[j];
     i = j-1;
     while(x[i] > key && i >= 0) // if the next element is smaller
     {
		x[i+1] = x[i]; // move larger element up
        i--;
     }
     x[i+1] = key;
  }
}

int main()
{
  int A[ELEMENTS]={5,2,4,6,1,3};
  int i;
  
  cout << "NON SORTED LIST:" << endl;
  for(i=0; i < ELEMENTS; i++)
       cout << A[i] << " ";
  
  insertion_sort(A,ELEMENTS);
  
  cout << "\n\nSORTED LIST" << endl;
  for(i=0; i < ELEMENTS; i++)
       cout << A[i] << " ";
  cout << endl;
  
  return 0;
}
