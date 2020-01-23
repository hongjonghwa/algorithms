#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int U=0;
int len(int n){
    if (n < -1) return -1;
    if (n == 0) return 0;
    int ret = 0;
    while (n>0){
        n /= 10;
        ret++;
    }
    return ret;
}
bool is_pan_digital(int a, int b){
    int c = a * b;
    if (len(a) + len(b) + len(c) != 9) return false;
    // printf("D : %d %d %d %d \n", a, b, c, len(a)+len(b)+len(c));
    int uu = U;
    int cc = c;
    while(cc){
        int t = cc % 10;
        if (t == 0) return false;
        if (uu & (1<<t)) return false;
        uu |= (1<<t);
        cc /= 10;
        // printf( " DD : %d %d %d %d %d\n", U, c, uu, cc, t);
    }
    if (uu == (1<<10)-2) return true;
    return false;
}
void pickb(int n, int a){
    if (n>10000) return;

    if (a > 1 && n > 1 && is_pan_digital(a,n)) {
        // printf("PD : %d %d %d \n", a, n, a*n);
        printf("Pan Digital : %d * %d = %d \n", a, n, a*n);
    }
    for (int i = 1 ; i < 10 ; ++i){
        if (!(U&(1<<i))){
            int offset = 1<<i;
            U |= offset; // 2번 방식 | &
            pickb(n*10+i, a);
            U &= ~offset;
        }
    }
}
void picka(int n){
    if (n>10000) return;
    if (n>1){
        pickb(0, n);
    }
    for (int i = 1 ; i < 10 ; ++i){
        if (!(U&(1<<i))){
            int offset = 1<<i;
            U += offset; // 1번 방식 + -
            picka(n*10+i);
            U -= offset;
        }
    }
}

int main (){
    // printf( " ---: %d :--- \n", (1<<10)-2);
    // printf("%d %d %d %d\n", 39, 186, 39*186, is_pan_digital(39,186));
    /*
    int ret = bt(200, 0);
    printf("ret : %d \n", ret);
    */
    picka(0);
}

