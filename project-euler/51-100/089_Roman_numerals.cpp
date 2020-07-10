/* 
  ! 89

  I = 1
  V = 5
  X = 10
  L = 50
  C = 100
  D = 500
  M = 1000
  
  Only one I, X, and C can be used as the leading numeral in part of a subtractive pair.
  I can only be placed before V and X.
  X can only be placed before L and C.
  C can only be placed before D and M.
*/
#include<stdio.h>
#include<assert.h>

int ASCII[] = {
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0, // 10 
  0,0,0,0,0,0,0,0,0,0, // 20
  0,0,0,0,0,0,0,0,0,0, // 30
  0,0,0,0,0,0,0,0,0,0, // 40
  0,0,0,0,0,0,0,0,0,0, // 50
  0,0,0,0,0,0,0,100,500,0, // 60
  0,0,0,1,0,0,50,1000,0,0, // 70
  0,0,0,0,0,0,5,0,10,0 // 80
};

inline int min_len(int digit){
  /*
    9 = IX         => 2
    8 = VIII       => 4
    7 = VII        => 3
    6 = VI         => 2
    5 = V          => 1
    4 = IV         => 2
    3 = III        => 3
    2 = II         => 2
    1 = I          => 1
  */
  if (digit == 4 || digit ==9) return 2;
  if (digit > 4) return digit-4;
  return digit;
}

int solv(char *c, int len){
  // number
  for (int i = 0 ; i < len ; ++i) printf("%c", c[i]);
  int number = 0;
  int last_denomination = 9999;
  int continuous = 0;
  for (int i = 0 ; i < len ; ++i){
    int x = ASCII[((int)c[i])];   
    if ( last_denomination < x ) {
      number -= last_denomination*continuous*2;
    }
    number += x;
    // printf("   %c %d %d %d     \t%d \n", c[i], x, last_denomination, continuous, sum);
    if ( last_denomination == x ) continuous ++;
    else {
      last_denomination = x;
      continuous = 1;
    }
  }
  // minimal form length
  int n = number;
  int minimal_len = n/1000;
  n -= (n/1000)*1000;
  minimal_len += min_len(n/100);
  n -= (n/100)*100;
  minimal_len += min_len(n/10);
  n -= (n/10)*10;
  minimal_len += min_len(n);

  printf("\t%d\t%d\n", len, minimal_len);
  return len - minimal_len;
}

int main(){
  /*
  printf("I = 1 %d %d \n", 'I', ASCII['I']);
  printf("V = 5 %d %d \n", 'V', ASCII['V']);
  printf("X = 10 %d %d \n", 'X', ASCII['X']);
  printf("L = 50 %d %d \n", 'L', ASCII['L']);
  printf("C = 100 %d %d \n", 'C', ASCII['C']);
  printf("D = 500 %d %d \n", 'D', ASCII['D']);
  printf("M = 1000 %d %d \n", 'M', ASCII['M']);
  */
  freopen("p089_roman.txt", "r", stdin);
  char t[20];
  int l;
  int answer = 0;
  for (int i = 0 ; i < 1000 ; ++i){
    scanf("%s", t);
    for ( l = 0 ; t[l] ; ++l);
    int c = solv(t, l);
    assert(c >= 0);
    answer += c;
  }
  printf("Answer is %d\n", answer);
}