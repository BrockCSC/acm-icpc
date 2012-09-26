#include <stdio.h>
#include <math.h>

char sieve[10000001]; // 10^7 is the typical limit for sieve of eratosthenes

main()
{
   unsigned l,u; // data type of int is assumed when keyword 'unsigned' is used on its own
   while (2 == scanf("%u %u ", &l, &u))
   {
      unsigned mindist = 3000000000, maxdist = 0;
      unsigned prev, maxprev, minprev, maxi, mini;
      
      // for as many numbers in the range (inclusive), assume that many primes
      for (int i = l; i <= u; ++i)
      {
        sieve[i-l] = 0; // note that they reversed the true/false
      }
     
      // TODO: This cannot be removed (causes WA). Why is it needed?
      if (l <= 2) // if L is 1 or 2
      {
        prev = 2; // the first prime is 2, so that is the previous prime
        l = 3; // let L be 3, the prime after 2
      }
      else
      {
        prev = 0;
      }
     
      // sieve algorithm
      for (int i = 3; i <= sqrt(static_cast<double>(u)); i += 2)
      {
         unsigned k = sqrt((double)i);
         for (int j = 3; j <= k; j += 2)
         {
           if (i % j == 0ul) goto composite1; // this code must be old
         }
         k = l % i;
         if (k == 0) k = i;
         for (k = i - k; k + l <= u; k += i)
         {
            if (l + k == i) continue;
            sieve[k] = 1;
         }
         continue;
         composite1:;
      }
      
      // some kind of linear scan
      for (int i = l % 2 == 1ul ? l : l + 1ul; i <= u; i += 2ul)
      {
         if (sieve[i-l]) continue;
         if (prev)
         {
            int dist = i - prev;
            if (dist > maxdist)
            {
               maxdist = dist;
               maxprev = prev;
               maxi = i;
            }
            if (dist < mindist)
            {
               mindist = dist;
               minprev = prev;
               mini = i;
            }
         }
         prev = i;
      }
      if (maxdist)
      {
         printf("%d,%d are closest, %d,%d are most distant.\n", minprev, mini, maxprev, maxi);
      }
      else
      {
         printf("There are no adjacent primes.\n");
      }
   }
}
