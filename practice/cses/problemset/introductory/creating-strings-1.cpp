#include<stdio.h>
#include<assert.h>

char x[9];
int d[26];
int len = 0;
char s[8];

void bt(int idx){
  if (idx == len) {
    for (int i = 0 ; i < idx ; ++i)
      printf("%c", s[i]);
    printf("\n");
    return;
  }

  for (int i = 0 ; i < 26; ++i){
    if (d[i]){
      --d[i];
      s[idx] = i+'a';
      bt(idx+1);
      ++d[i];
    }
  }
}

int fact[9];

int main(){
  fact[0] = 1;
  for (int i = 1 ; i <= 8 ; ++i)
    fact[i] = fact[i-1] * i;

  if (scanf("%s", x) != 1) return -1;
  for (len = 0 ; x[len] ; ++len) {
    assert (x[len] >= 'a' && x[len] <= 'z');
    ++d[x[len]-'a'];
  }

  int count = fact[len];
  for (int i = 0 ; i < 26 ; ++i)
    if (d[i]>1)
      count /= fact[d[i]];
  printf("%d\n", count);

  bt(0);
}