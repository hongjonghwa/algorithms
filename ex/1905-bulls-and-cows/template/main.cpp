#include<stdio.h>
#include<time.h>

static unsigned char KEY[200];
static unsigned char GUESS[200];

extern void test(unsigned char guess[200]);

static unsigned int g_seed = 1;
inline int fastrand(){
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}

void build(){
    char used[255] = { 0 };
    for (int i = 0 ; i < 200 ; ++i){
        int p = fastrand() % 255;
        while (used[p]) p = fastrand() % 255;
        used[p] = 1;
        KEY[i] = p+1;
    }
}
int check(unsigned char guess[200]){
    int pos = 0, equal = 0;
    for (register int i = 0; i < 200 ; ++i)
        if (KEY[i] == guess[i]) pos++;

    for (register int i = 0; i < 200 ; ++i)
        for (register int j = 0; j < 200 ; ++j)
            if (KEY[i] == guess[j]) equal++;

    return pos * 256 + equal;
}


int main(){
    int ret = 0;
    int tt= 0;
    for (int t = 1 ; t <= 1 ; ++t){
        build();
        long long int clk = clock();
        test(GUESS);
        ret += (clock()-clk) * 1000 / CLOCKS_PER_SEC;
        for (int i = 0 ; i < 200 ; ++i)
            if (KEY[i] != GUESS[i]) ret += 10000;
        //ret += 
    }
    printf("Score is %d\n", ret);
}
