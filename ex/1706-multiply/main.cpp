#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define BASE 36


void mul(char a[128], char b[128], char c[256]);
void test_run(char a[128], char b[128]);

char a[128], b[128];

inline char itoa(int n){
    if (n < 10) return '0' + n;
    else return 'A' + n - 10;
}

void randStr(char x[128]){
    int len = rand() % 64 + 64 + 1; // 65 ~ 128;
    // int len = rand() % 4 + 4 + 1; // 5 ~ 8
    for (int i = 0 ; i < len ; ++i)
        x[i] = itoa(rand()%BASE);
    if (len != 128) x[len] = 0;
    
}

int main(){
    char a[128], b[128], c[256];
    for (int i = 0 ; i < 10 ; ++i){
        randStr(a);
        randStr(b);
        test_run(a, b);

    }

    // return 0;

    long long int clk = clock();
    for (int t = 0 ; t < 10 ; ++t){
        for (int i = 0 ; i < 100000; ++i){
            randStr(a);
            randStr(b);
            mul(a,b,c);
        }
    }
    printf("Execution time - %f\n", double(clock()-clk)/CLOCKS_PER_SEC);


}