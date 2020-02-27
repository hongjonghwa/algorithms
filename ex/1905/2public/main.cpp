#include<stdio.h>
#include<time.h>

int check(unsigned char guess[200]);
void report(unsigned char guess[200]);

/*
 * test 함수만 수정 가능!
 */
void test(unsigned char guess[200]){
    // 최악의 방법 : 200 * 255 * 1/2 ==> 25500
    // 
    for (int i = 0 ; i < 200 ; ++i) guess[i] = 0;
    for (int i = 0 ; i < 200 ; ++i){
        for (int j = 1 ; j <= 255 ; ++j){
           guess[i] = j;
           int ret = check(guess);
           int pos = ret >> 8;
           if (pos == i + 1) break;
        }
    }
    // report(guess);
}


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
int check_cnt;
int check(unsigned char guess[200]){
    check_cnt++;
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
        check_cnt = 0;
        long long int clk = clock();
        test(GUESS);

        printf("[%d] STEP %d, time %f\n", t, check_cnt, 
                (double(clock())-clk)/CLOCKS_PER_SEC);

        ret += (clock()-clk) * 1000 / CLOCKS_PER_SEC;
        for (int i = 0 ; i < 200 ; ++i)
            if (KEY[i] != GUESS[i]) ret += 10000;
        //ret += 
    }
    printf("Score is %d\n", ret);
}

// 화면 출력 (디버깅)
void report(unsigned char guess[200]){
    for (int i = 0 ; i< 200 ; ++i){
        printf("%d\t", guess[i]);
        if (i%10 == 9) printf("\n");
    }
}
