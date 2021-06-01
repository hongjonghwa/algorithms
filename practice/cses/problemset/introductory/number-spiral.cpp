#include<stdio.h>
#define MAX(a,b) ((a)>(b)?(a):(b))

int main(){
  int n, y, x;
  if (scanf("%d", &n) != 1) return -1;
  for (int i = 0 ; i < n ; ++i){
    if (scanf("%d%d", &y, &x) != 2) return -1;
    int d = MAX(y, x);
    long long int t = (long long int)(d-1)*(d-1)+1;
    if (d & 1) { // odd
      t += x-1;
      t += d-y;
    }
    else{ //even
      t += y-1;
      t += d-x;
    }
    printf("%lld\n", t);
  }
}