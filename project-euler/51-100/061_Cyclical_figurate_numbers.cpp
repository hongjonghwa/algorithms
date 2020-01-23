#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int pn(int base, int n){
    if (base == 3) return n*(n+1)/2;
    if (base == 4) return n*n;
    if (base == 5) return n*(3*n-1)/2;
    if (base == 6) return n*(2*n-1);
    if (base == 7) return n*(5*n-3)/2;
    if (base == 8) return n*(3*n-2);
    return -1;
}
bool is_pn(int base, int n){
    int lo = 0, hi = 150; // pn(3,150) > 1e4
    while(lo+1<hi){
        int mid = (lo+hi)/2;
        if (pn(base, mid) < n) lo = mid;
        else hi = mid;
    }
    return pn(base, hi) == n;
}
int PICK[6];
int BASE[6];
bool USED[6];

void bt(int idx){
    /*
    if (idx == 6) {
        printf("- ANSWER -\n");
        for (int i = 0 ; i < 6; ++i)
            printf("%d P%d\n", PICK[i], BASE[i]);
        return;
    }
    */
    if (idx == 6) {
        if(PICK[5]%100 == PICK[0]/100){
            printf("- ANSWER -\n");
            for (int i = 0 ; i < 6; ++i)
                printf("%d P%d\n", PICK[i], BASE[i]);
        }
        return;
    }
    int s = PICK[idx-1]%100*100;
    if (s < 1000) return; // 4자리 수를 만들지 못하면 break!
    int e = s+100;
    for (int base = 0 ; base < 5 ; ++base){
        BASE[idx] = base+3;
        if (USED[base]) continue;
        USED[base] = true;
        for (int i = 1 ;; ++i){
            int c = pn(base+3, i);
            if (c<s) continue;
            // printf("debug - base :%d  gen: %d \n", base, c);
            if (c>=e) break;
            PICK[idx] = c;
            bt(idx+1);
        }
        USED[base] = false;
    }
    return;
}
bool bt8(){
    USED[5] = true;
    BASE[0] = 8;
    for (int i = 1;;++i){
        int c = pn(8,i);
        if (c > 10000) break;
        if (c >= 1000) {
            PICK[0] = c;
            bt(1);
        }
    }
}
int DEBUG[10001];
int main(){
    // check! - Triangle
    // for (int i = 1; i<= 15; ++i) printf(" %d %d\n", i, is_pn(3,i));
    // check! - Square
    // for (int i = 1; i<= 16; ++i) printf(" %d %d\n", i, is_pn(4,i));
    // return 0;
    for (int i = 3 ; i <=8 ; ++i)
        for (int j = 1;;++j){
            int c = pn(i,j);
            if (c > 10000) break;
            // DEBUG[c]++;
        }
    /*
    for (int i = 1 ; i <= 10000 ; ++i)
        if (DEBUG[i]>1)
            printf(" Dup: %d (%d)\n", i, DEBUG[i]);
    */
    bt8(); // first pick to P8
}

