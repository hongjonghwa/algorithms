#include<stdio.h>

template <class T>
inline void SWAP(T & a, T & b){
  T t = a; a = b; b = t;
}
template <class T>
inline T ABS(T n){
  return n<0?-n:n;
}

int S[2001];

int solv(int y, int x){
  return S[y]*S[x];
  if (y>x) SWAP(y,x);
  if (y == 1 && x == 1) return 1;
  // Divice and conqurer 
}
inline long calc(int y, int x){
  return long(S[y])*S[x];
}
int lower_bound(int n, int l, int h){
  while (l + 1 <h){
    int m = (l+h)/2;
    if (calc(m, n) < 2000000) l = m;
    else h = m;
  }
  return l;
}

int main(){
  for (int i = 1 ; i <= 2000 ; ++i)
    S[i] = S[i-1] + i;
  
  int best = 99999999;
  int l, y, x;
  long c, a;
  for (int i = 2000 ; ; --i){
    l = lower_bound(i, 0, 2000);

    c = calc(i,l);
    a = ABS(c-2000000);
    if (a < best){
      best = a;
      y = i;
      x = l;
      printf ("%d %d %ld %ld\n", y, x, c, a);
    }

    c = calc(i,l+1);
    a = ABS(c-2000000);
    if (a < best){
      best = a;
      y = i;
      x = l + 1;
      printf ("%d %d %ld %ld\n", y, x, c, a);
    }
    if (i<l) break;
  }

  printf("Answer is %d * %d = %d\n", y, x, y*x);
}