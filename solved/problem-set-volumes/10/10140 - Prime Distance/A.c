#include <stdio.h>
#include <math.h>

char seive[10000001];

main(){
   unsigned a,b;
   while (2 == scanf("%u %u ",&a,&b)){
      unsigned i,j,k,m;
      unsigned min=3000000000,max=0,prev,maxprev,minprev,maxi,mini;
      for (i=a;i<=b;i++) seive[i-a] = 0;
      if (a <= 2) {prev = 2;a = 3;} else prev = 0;
      m = sqrt((double)b);
      for (i=3;i<=m;i+=2){
         k = sqrt((double)i);
         for (j=3;j<=k;j+=2) if (i%j == 0ul) goto composite1;
         k = a % i;
         if (k == 0) k = i;
         for (k=i-k;k+a<=b;k+=i) {
            if (a+k == i) continue;
            seive[k] = 1;
         }
         continue;
         composite1:;
      }
         
      for (i=a%2==1ul?a:a+1ul;i<=b;i+=2ul){
         if (seive[i-a]) continue;
         if (prev) {
            if (i-prev > max) {
               max = i-prev;
               maxprev = prev;
               maxi = i;
            }
            if (i-prev < min) {
               min = i-prev;
               minprev = prev;
               mini = i;
            }
         }
         prev = i;
      }
      if (max){
         printf("%d,%d are closest, %d,%d are most distant.\n",minprev,
                          mini,maxprev,maxi);
      }else{
         printf("There are no adjacent primes.\n");
      }
   }
}
