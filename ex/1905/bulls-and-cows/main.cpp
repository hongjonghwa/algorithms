#include<stdio.h>
#include<time.h>

static unsigned char KEY[4];
static unsigned char GUESS[4];

extern void test(unsigned char guess[4]);

static unsigned int g_seed = 1;
inline int fastrand(){
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}

void build(){
    char used[255] = { 0 };
    for (int i = 0 ; i < 4 ; ++i){
        int p = fastrand() % 9;
        while (used[p]) p = fastrand() % 9;
        used[p] = 1;
        KEY[i] = p+1;
    }
}
int check_cnt;
int check(unsigned char guess[4]){
    check_cnt++;
    int pos = 0, equal = 0;
    for (register int i = 0; i < 4 ; ++i)
        if (KEY[i] == guess[i]) pos++;

    for (register int i = 0; i < 4 ; ++i)
        for (register int j = 0; j < 4 ; ++j)
            if (KEY[i] == guess[j]) equal++;

    return pos * 256 + equal;
}


int main(){
    int ret = 0;
    int tt= 0;
    for (int t = 1 ; t <= 1 ; ++t){
        build();
        check_cnt = 0;
        long long int clk = clock();
        test(GUESS);

        printf("[%d] check %d, time %f\n", t, check_cnt, 
                (double(clock())-clk)/CLOCKS_PER_SEC);

        ret += (clock()-clk) * 1000 / CLOCKS_PER_SEC;
        for (int i = 0 ; i < 4 ; ++i)
            if (KEY[i] != GUESS[i]) ret += 10000;
        //ret += 
    }
    printf("Score is %d\n", ret);
}
