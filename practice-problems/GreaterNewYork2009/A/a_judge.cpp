/*
 * A - Nth Largest Value
 * ACM International Collegiate Programming Contest
 * Greater New York Region
 * October 18, 2009
 * solution by John Buck
 *
 * Dennis' Commentary:
 * A clever solution, rather than an array of size 10,
 * an array of size 3 is used because only 3 ints need to be compared.
 */

#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
   // Read number of data sets to process
   int num, nprob;
   cin >> num;

   // Process each data set identically
   for (int i = 1; i <= num; ++i)
   {
      cin >> nprob;
      // (Dynamic) Array containing the three largest elements.
      // We want a[0] > a[1] > a[2]. Then after processing all
      // ten elements a[2] is the answer. We initialize the array
      // to all -1's because we know the inputs are all positive.
      vector<int> a(3, -1);
      for (int j = 0; j < 10; ++j)
      {
         int x;
         cin >> x;
         // Put x in its appropriate location in the array a.
         // Bubble it down to its right location.
         for (int k = 0; k < 3; ++k)
            {
            if (x > a[k])
               {
               const int temp = a[k];
               a[k] = x;
               x = temp;
               }
            }
         // Notice that x falls off the array a and is lost.
      }
      cout << nprob << " " << a[2] << endl;
   }

   // We're done
   return 0;
}
