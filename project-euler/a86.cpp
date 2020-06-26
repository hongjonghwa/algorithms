#include <stdio.h>
typedef long long int lint;

int M = 10000;

/* 
Integer square root - digit by digit
https://en.wikipedia.org/wiki/Integer_square_root
https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Digit-by-digit_calculation
*/

/*
 * http://www.codecodex.com/wiki/Calculate_an_integer_square_root#C
 */
unsigned long isqrt(unsigned long x)  
{  
    register unsigned long op, res, one;  
  
    op = x;  
    res = 0;  
  
    /* "one" starts at the highest power of four <= than the argument. */  
    one = 1 << 30;  /* second-to-top bit set */  
    while (one > op) one >>= 2;  
  
    while (one != 0) {  
        if (op >= res + one) {  
            op -= res + one;  
            res += one << 1;  // <-- faster than 2 * one  
        }  
        res >>= 1;  
        one >>= 2;  
    }  
    return res;  
}  
  

bool check(lint x){

  /* 
  lint lo = 0, hi = x;
  while (lo + 1 < hi){
    lint m = (lo+hi)/2;
    if (m*m < x) lo = m;
    else hi = m;
  }
  */
  lint hi = isqrt(x);
  return hi*hi == x;
}

int main(){

  int cnt = 0;
  bool breakflag = false;
  for (lint k = 1; k <= M ; ++k){
    for (lint j = 1 ; j <= k ; ++j){
      for (lint i = 1 ; i <= j ; ++i){
        lint c = i*i + j*j + k*k + 2*i*j;
        // i^2 + j^2 + k^2 + 2ij         
        if (check(c)) cnt++;
        if (cnt >= 1000000){
          printf("%lld %lld %lld %lld %d \n", i, j, k, c, cnt);
          breakflag = true;
          break;
        }
    
        
      }

      if (breakflag) break;
    }

    if (breakflag) break;
  }
    
}