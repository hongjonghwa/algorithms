#include <stdio.h>

int X[210];
int X_LEN = 0;
int X_ORI[210];

void bt(int x, int idx, int pick, int nopick){
  if (idx == 10){  
    X[X_LEN++] = x;
    return;
  }

  if (pick > 0){
    x |= (1<<idx);
    bt (x, idx + 1, pick-1, nopick);
  } 
  if (nopick > 0){
    x &= ~(1<<idx);
    bt (x, idx + 1, pick, nopick-1);
  } 
}

void dsp(int x){
  for (int i = 0 ; i < 10 ; ++i)
    if (x&(1<<i))
      printf("%d ", i);
}
bool check (int x, int y){
  for (int i = 1 ; i <= 9 ; ++i){
    int sqr = i*i;
    int d1 = sqr / 10;
    int d2 = sqr % 10;
    if ( x & (1<<d1) && y & (1<<d2) ) continue;
    if ( y & (1<<d1) && x & (1<<d2) ) continue;
    return false;
  }
  return true;
}

int main(){
  bt(0, 0, 6, 4);
  for (int i = 0 ; i < X_LEN ; ++i){
    X_ORI[i] = X[i];
    if (X[i] & (1<<6)) 
      X[i] |= (1<<9); 
    if (X[i] & (1<<9)) 
      X[i] |= (1<<6);
  }
  int answer = 0;
  for (int i = 0 ; i < X_LEN ; ++i)
    for (int j = 0 ; j < X_LEN ; ++j){
      bool chk = check (X[i], X[j]);
      answer += chk;
      if (chk){
        printf("[%4d] " , answer);
        dsp(X_ORI[i]);
        printf("\t");
        dsp(X_ORI[j]);
        printf("\n");
      }
    }
  printf("\nAnswer is %d\n", answer/2);
}

