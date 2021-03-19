#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
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
    My Codes
    - stack 1m
    - using function move, clean, check

*/

char tmp[N*2];
struct range{
    int lo, hi;
    range(int l, int h){lo=l; hi=h;}
    int count(){ return hi-lo + 1;}
};
range batch_move(range r){ // appending
    range ret(r.hi+1, r.hi);
    for (int i = r.lo ; i+1 <= r.hi ; i+=2){
        move(i, i+1, ++ret.hi); 
    }
    return ret;
}
void expand(){
    // first loop 

    int trays = N;
    int start = 0, end = trays-1;
    int nexttrays = trays/2;
    while (nexttrays){
        printf("%d %d %d %d\n", trays, start, end, nexttrays);
        for (int i = 0 ; i < nexttrays ; ++i){
            move(start + i*2 , start + i*2 + 1, end + i + 1);
        }
        // next turn
        trays = nexttrays;
        start = end+1;
        end = end + trays;
        nexttrays = trays/2;
    }
    printf ("last tray is : %d\n", end);


    // second 
    range n(0, N-1);
    while (n.count()>1){
        range nn = batch_move(n);
        printf("%d %d %d %d \n", n.lo, n.hi, nn.lo, nn.hi);
        n = nn;
    }

}
void recur(range r, range prev){
    if (r.count() == 0) return;

    recur(range (r.hi+1, r.hi + r.count()/2), r);

    if (prev.hi == -1) return;


    printf("OUT: r(j) %d~%d , prev(i) %d~%d\n", 
            r.lo, r.hi, prev.lo, prev.hi);

    for (int i = prev.lo, j = r.lo ; i <= prev.hi ; i+=2, ++j){
        if (i+1 <= prev.hi){ // 2개씩 짝이 맞는다 
            if (tmp[j] == -1) tmp[j] = check(j);
            if (tmp[j]==1){
                tmp[i] = check(i);
                if (tmp[i] == 0) tmp[i+1] = 1;
            }else{
                tmp[i] = tmp[i+1] = 0;
            }
        }else{ // 하나만 남았다
            assert(j==r.hi+1);
            tmp[j] = check(j);
        }
    }
}

void test(){
    expand();

    for (register int i = 0 ; i < N*2 ; ++i) tmp[i] = -1;
    recur(range(0,N-1), range(-1,-1));   

    for (register int i = 0 ; i < N ; ++i)
        if (tmp[i] == -1) tmp[i] = check(i);

    for (register int i = 0 ; i < N ; ++i)
        if (tmp[i] == 1) clean(i);
    
}


// naive 
/*
void test(){
    for (int i = 0 ; i < N ; ++i) if (check(i)) clean(i);
} 
*/
