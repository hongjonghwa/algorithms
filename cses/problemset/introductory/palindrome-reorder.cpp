#include<stdio.h>

char X[1000 * 1000 + 1];
int C[26];

int main(){
  if (scanf("%s", X) != 1) return -1;
  int len;
  for (len = 0 ; X[len] ; ++len)
    C[X[len] - 'A']++;
  
  bool odd = len & 1;
  int odd_cnt = 0, odd_char_idx = 0;

  for (int i = 0 ;i< 26 ; ++i)
    if (C[i]  & 1){
      odd_cnt++;
      odd_char_idx = i;
      C[i] = (C[i]-1) / 2;
    }else{
      C[i] /= 2;
    }

  if ( (odd_cnt == 1 && odd) ||  (odd_cnt == 0 && !odd) ){
    for (int i = 0 ; i < 26 ; ++i)
      for (int j = 0 ; j < C[i] ; ++j)
        printf("%c", 'A'+i);
    if (odd) printf("%c", 'A' + odd_char_idx);
    for (int i = 25 ; i >= 0 ; --i)
      for (int j = 0 ; j < C[i] ; ++j)
        printf("%c", 'A'+i);
  }else{
    printf("NO SOLUTION");
  }
}