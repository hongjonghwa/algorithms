#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

unsigned long long int reverse(unsigned long long int n){
    long long int ret = 0;
    while (n > 0){
        ret *= 10;
        ret += n % 10;
        n /= 10;
    }
    return ret;
}
bool is_palindrome(unsigned long long int n){
    unsigned long long int r = reverse(n);
    return n == r;
}

int main(){
    int answer = 0;
    unsigned long long int n = 196;
    for (int i = 1 ; i < 10000 ; ++i){
        unsigned long long int n = i;
        bool palindrome = false;
        for (int j = 0 ; j < 50 ; ++j){
            n += reverse(n);
            if (is_palindrome(n)){
                palindrome = true;
                break;
            }
        }
        if (palindrome == false) answer++; 
        // printf("%u %u\n", i, palindrome);
    }
    printf("Answer is %u\n", answer);

}



