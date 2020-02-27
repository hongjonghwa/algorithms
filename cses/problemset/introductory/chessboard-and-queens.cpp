#include<stdio.h>

char t[8][9];
bool col[8], inc[15], dec[15];

int bt(int idx){
  if (idx == 8) return 1;

  int ret = 0;
  for (int i = 0; i < 8 ; ++i)
    if (t[idx][i]=='.' && !col[i] && !inc[i+idx] && !dec[i-idx+7] ){
      col[i]  = inc[i+idx] = dec[i-idx+7] = true;
      t[idx][i] = '+';
      ret += bt(idx+1);
      t[idx][i] = '.';
      col[i]  = inc[i+idx] = dec[i-idx+7] = false;
    }
  return ret;
}

int main(){
  for (int i = 0 ; i < 8 ; ++i)
    if (scanf("%s", t[i]) != 1) return -1;

  printf("%d", bt(0));
}