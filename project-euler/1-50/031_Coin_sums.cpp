#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int C[7] = { 200, 100, 50, 20, 10, 5, 2 };

int bt(int total, int sel) {
    if (total < 0) printf("IMPOSSIBLE!!! %d %d \n", total, sel);
    if (sel == 7) return 1;

    int ret = 0;
    int max_number_take = total / C[sel];
    for (int i = 0 ; i <= max_number_take ; ++i){
        ret += bt(total - i*C[sel], sel + 1);
    }
    return ret;
}
int main (){
    int ret = bt(200, 0);
    printf("ret : %d \n", ret);
}

