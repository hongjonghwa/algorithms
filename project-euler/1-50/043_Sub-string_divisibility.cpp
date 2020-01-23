#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int D[10];
long long int SUM = 0;
void report(){
    for (int i = 0 ; i < 10 ; ++i)
        printf("%d", D[i]);
    printf("\n");
}
bool check(){
    if ((D[1]*100+D[2]*10+D[3]) % 2 != 0) return false;
    if ((D[2]*100+D[3]*10+D[4]) % 3 != 0) return false;
    if ((D[3]*100+D[4]*10+D[5]) % 5 != 0) return false;
    if ((D[4]*100+D[5]*10+D[6]) % 7 != 0) return false;
    if ((D[5]*100+D[6]*10+D[7]) % 11 != 0) return false;
    if ((D[6]*100+D[7]*10+D[8]) % 13 != 0) return false;
    if ((D[7]*100+D[8]*10+D[9]) % 17 != 0) return false;
    return true;
}
long long int getValue(){
    long long int ret = 0;
    for (int i = 0 ; i < 10 ; ++i){
        ret *= 10;
        ret += D[i];
    }
    return ret;
}
void pandigital(int idx){
    if(idx==10){
        if (check()) {
            report();
            SUM+=getValue();
        }
        return;
    }
    int s = idx == 0 ? 1 : 0;
    for (int i = s ; i < 10 ; ++i){
        bool used = false;
        for (int j = 0 ; j < idx ; ++j)
            if (D[j] == i) {
                used = true;
                break;
            }
        if (!used){
            D[idx] = i;
            pandigital(idx+1);
        }   
    }

}

int main(){
    pandigital(0);
    printf("sum is %lld\n", SUM);
}



