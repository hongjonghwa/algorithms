#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))


bool is_permutation(int i, int j, int k){
    int cnt1[10] = { 0,0,0,0,0,0,0,0,0,0};
    int cnt2[10];
    while (i>0){
        cnt1[i%10]++;
        i/=10;
    }
    for (int i = 0 ; i < 10 ; ++i) cnt2[i] = cnt1[i];
    while(j>0){
        cnt1[j%10]--;
        j/=10;
    }
    for (int i = 0 ; i < 10 ; ++i) 
        if (cnt1[i] != 0) 
            return false;
    while(k>0){
        cnt2[k%10]--;
        k/=10;
    }
    for (int i = 0 ; i < 10 ; ++i) 
        if (cnt2[i] != 0) 
            return false;
    return true;
}
bool isPrime[10000];
void e(){
    for (int i = 2 ; i < 10000 ; ++i) isPrime[i] = true;
    for (int i = 2 ; i < 100 ; ++i)
        if (isPrime[i])
            for (int j = i * i ; j < 10000 ; j+=i)
                isPrime[j] = false;
}
int P4S[10000];
int P4L = 0;
int main(){
    e();
    for (int i = 1000 ; i < 10000 ; ++i)
        if (isPrime[i])
            P4S[P4L++] = i;
    printf(" 4 digit prime are %d\n", P4L);
    int c = 0;
    for (int i = 0 ; i < P4L ; ++i)
        for (int j = i+1 ; j < P4L ; ++j){
            int diff = P4S[j] - P4S[i];
            int third_p = P4S[j] + diff;
            if (third_p < 10000 && isPrime[third_p]){
                if (is_permutation(P4S[i], P4S[j], third_p))
                    printf("%d: %d - %d - %d\n", ++c, P4S[i], P4S[j], third_p);
            }
        }
    
}



