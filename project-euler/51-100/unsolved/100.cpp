/*
    https://www.mathblog.dk/project-euler-100-blue-discs-two-blue/
    https://www.alpertron.com.ar/QUAD.HTM
*/

#include <stdio.h>
#define MOD 100000000
typedef unsigned long long int ull;


int proba_over_half(ull blue, ull red){
  ull s = blue+red;
  ull numerator = blue*(blue-1)*2;
  ull denominator = s*(s-1);
  if (numerator > denominator) return 1;
  if (numerator < denominator) return -1;
  return 0;
}

void mul(ull a, ull b, ull ret[2]){
  ull a_lo = a % MOD;
  ull a_hi = a / MOD;
  ull b_lo = b % MOD;
  ull b_hi = b / MOD;
  ret[0] = a_lo * b_lo;
  ret[1] = a_lo * b_hi + a_hi * b_lo + a_hi * b_hi * MOD;
  ret[1] += ret[0] / MOD;
  ret[0] %= MOD;
}

int compare_ll(ull a[2],  ull b[2]){
  for (int i = 1 ; i >= 0 ; --i){
    if (a[i] > b[i]) return 1;
    if (a[i] < b[i]) return -1;
  }
  return 0;
}

int proba_over_half_overflow(ull blue, ull red){
  ull s = blue+red;

  ull numerator[2];
  ull denominator[2];

  mul(blue, (blue-1)*2, numerator);
  mul(s, (s-1), denominator);

  return compare_ll(numerator, denominator);
}

int main(){
    ull blue, red;

    for (blue = 2, red = 1 ; ; ){
        if (blue+red > 1e11) break;

        int p;
        if (blue < 1e9) p = proba_over_half_overflow(blue, red);
        else p = proba_over_half_overflow(blue, red);
        if (p == 0){
            printf ("Found Blue %I64d, Red %I64d\n", blue, red);
            blue++;
            red++;
            // break;
        }else if ( p>0) red++;
        else blue++;

    }
}
