#include<stdio.h>
#include<stdlib.h>
#define N 50000000

char TRAY[N*2];
int fail_count = 0;
int check_count = 0;
int move_count = 0;
int clean_count = 0;

void test();

char check(int n){
  ++check_count;
  if (n < 0 && n >= N*2) return 0;
  return TRAY[n] == 1;
}


void clean(int n){
  ++clean_count;
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
    if (TRAY[c]== 1) ++fail_count;

  printf("Fail count is %d\n", fail_count);
  printf("Clean count is %d\n", clean_count);
  printf("Check count is %d\n", check_count);
  printf("Move count is %d\n", move_count);
  long long int score = (long long int)fail_count*100000 + clean_count*10 + check_count;
  printf("### SCORE : %lld ###\n", score);
}


/*
    My Code
    - stack 1m
    - using function move, clean, check

*/

void test(){

}