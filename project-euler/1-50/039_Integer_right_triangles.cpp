#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int count(int p, bool debug){
    int cnt = 0;
    for (int a = 1 ; a < (p+2)/3 ; ++a)
        for (int b = a+1 ; b < p - a ; ++b){
            int c=p-a-b;
            if (b>c) break;
            if (a*a+b*b==c*c) {
                cnt++;
                if (debug) printf("[%d] %d %d %d --> %dth\n", p, a,b,c, cnt);
            }
        }
    return cnt;
}

int main (){

    int best = 0;
    int pick = -1;
    for (int p = 3; p <= 1000 ; ++p){
        int cnt = count(p, false);
        if (cnt > best){
            best = cnt;
            pick = p;
        }
    }
    count(pick, true);
    
}

