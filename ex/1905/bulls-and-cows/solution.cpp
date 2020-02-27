#include<stdio.h>
extern int check(unsigned char guess[4]);

void report(unsigned char guess[4]){
    printf("%d %d %d %d\n", guess[0], guess[1], guess[2], guess[3]);
}

void test(unsigned char guess[4]){
    for (int i = 0 ; i < 4 ; ++i) guess[i] = 0;
    for (int i = 0 ; i < 4 ; ++i){
        for (int j = 1 ; j <= 9 ; ++j){
           guess[i] = j;
           int ret = check(guess);
           int pos = ret >> 8; 
           if (pos == i + 1) break;
        }
    }
    report(guess);
}


// 200 * 255 * 1/2 = 25500
void test1(unsigned char guess[200]){
    for (int i = 0 ; i < 200 ; ++i) guess[i] = 0;
    for (int i = 0 ; i < 200 ; ++i){
        for (int j = 1 ; j <= 255 ; ++j){
           guess[i] = j;
           int ret = check(guess);
           int pos = ret >> 8; 
           if (pos == i + 1) break;
        }
    }
    report(guess);
}
