#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

bool is_cube(unsigned long long int n){
    unsigned long long int lo = 0, hi = 10000;
    while (lo + 1 < hi){
        unsigned long long int mid = (lo+hi)/2;
        if (mid * mid * mid < n) lo = mid;
        else hi = mid;
    }
    return hi*hi*hi == n;
}
int N = 8; // 자릿수
int D[10];
int P[100];
int permute(int idx, int n, bool debug = 0){
    if (idx==n){
        if (P[0] == 0) return 0; // 0으로 시작하면 제외
        unsigned long long int v = 0;
        for (int i = 0 ; i < n ; ++i){
            v= v*10;
            v+=P[i];
            // if (debug) printf(" v trace %llu \n", v);
        }
        // printf("%d\n",v);
        bool cube = is_cube(v);
        if (debug && cube) printf(" %llu is cube.\n", v);
        return cube;
    }
    int ret = 0;
    for (int i = 0 ; i< 10  ; ++i){
        if (D[i]){
            P[idx] = i;
            D[i]--;
            ret += permute(idx+1,n, debug);
            D[i]++;
        }
    }
    return ret;
}
void all_set(int idx, int remain, int n){
    if (idx == 10){
        if (remain != 0) return;
        /* debug */
        int v = 0;
        for (int i = 0 ; i < 10 ; ++i)
            for (int j = 0 ; j < D[i] ; ++j){
                v*=10;
                v+=i;
            }
                
        int cube_cnt = permute(0,n);
        if (cube_cnt > 1) 
            printf("# %3d -> %d \n", v, cube_cnt);
        //if (D[2]==1 && D[5] == 1 && D[7]==1) permute(0,n);
        return;
    }
    for (int i = remain ; i >= 0 ; --i){
        D[idx] += i;
        all_set(idx + 1, remain-i, n);
        D[idx] -= i;
    }
}
int main(){
    // all_set(0, N, N); 
    // faster: 큐브 숫자를 먼저 만들고, permute
    for (unsigned long long int i = 1; ; ++i){
        unsigned long long int c = i*i*i;
        if (c >= 1e12) break;
        for (int j = 0 ; j < 10 ; ++j) D[j] = 0;
        int nn = 0;
        while(c>0){
            D[c%10]++;
            c/=10;
            nn++;
        }
        int cube_cnt = permute(0,nn);
        if (cube_cnt == 5) {
            printf(" !D : %d %llu\n", i, i*i*i);
            permute(0,nn,true);
        }
        if (cube_cnt> 3) printf("# %llu -> %d\n", i*i*i, cube_cnt);
    }
}

