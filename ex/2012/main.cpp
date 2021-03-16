#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define N 50000000

char TRAY[N*2];
int fail_cnt = 0;
int check_cnt = 0;
int move_cnt = 0;
int clean_cnt = 0;

void test();

char check(int n){
  ++check_cnt;
  if (n < 0 && n >= N*2) return 0;
  return TRAY[n] == 1;
}

void clean(int n){
  ++clean_cnt;
  if (n>=0 && n < N*2)
    TRAY[n] = 0;
}

void move(int a, int b, int c){
  if (a<0 || a >= N*2) return;
  if (b<0 || b >= N*2) return;
  if (c<0 || c >= N*2) return;
  TRAY[c] = TRAY[a] | TRAY[b];
}

int main(){
  srand(42);
  for (int c = 0 ; c < 50000 ; ++c)
    TRAY[rand()%N] = 1;
  
  test();
  
  for (int c = 0 ; c < N ; ++c)
    if (TRAY[c]== 1) ++fail_cnt;

  printf("Fail cnt is %d\n", fail_cnt);
  printf("Clean cnt is %d\n", clean_cnt);
  printf("Check cnt is %d\n", check_cnt);
  printf("Move cnt is %d\n", move_cnt);
  long long int score = (long long int)fail_cnt*100000 + clean_cnt*10 + check_cnt;
  printf("### SCORE : %lld ###\n", score);
}


/*
    My Codes
    - stack 1m
    - using function move, clean, check

*/

char tmp[N*2];

void solv (int l, int h){
    int c = h - l + 1;

    /* 종료 조건 */
    if (c==1) {
        assert(l == h);
        tmp[l] = 1; // 무조건 있다
        return;
    }

    int next_l = h + 1;
    int next_h = h + c/2;

    /* 전처리 */
    int i,j;
    for (i = l, j = next_l ; i+1 <= h;  i+=2, ++j )
        move (i, i+1, j);

    assert (j - 1 == next_h);
    printf("DEBUG] pre %d ~ %d => %d ~ %d\n", l, h, next_l, next_h);
    
    /* 재귀 */
    solv(next_l, next_h);

    /* 후처리 */
    for (i = l, j = next_l ; i <= h;  i+=2, ++j ){
        if (i+1 <= h){ // 페어 ( i , i+1 ) ~ j
            
            // if (tmp[j] == -1) tmp[j] = check(j); // 불필요!
            if (tmp[j] == 1){
                tmp[i] = check(i);
                if (tmp[i] == 0) tmp[i+1] = 1;
                else tmp[i+1] = check(i+1);
            }else{
                tmp[i] = tmp[i+1] = 0;
            }
        } 
        else{ // 나머지 (i) 만 존재``
            assert(i==next_l - 1);
            tmp[i] = check(i);
        }
    }

    printf("DEBUG] post %d ~ %d => %d ~ %d\n", next_l, next_h, l, h);

}

void test(){
    for (register int i = 0 ; i < N*2 ; ++i) tmp[i] = -1;
    solv(0, N-1);
    
    for (register int i = 0 ; i < N ; ++i)
        if (tmp[i] == 1) clean(i);
}
