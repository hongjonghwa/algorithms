#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))


bool isPrime[1000000];
void e(){
    for (int i = 2 ; i < 1000000 ; ++i) isPrime[i] = true;
    for (int i = 2 ; i < 1000 ; ++i)
        if (isPrime[i])
            for (int j = i * i ; j < 1000000 ; j+=i)
                isPrime[j] = false;
}

void check(int l, int base, int ast){
    int minimal = 1;
    while(--l){
        minimal *= 10; // 0으로 시작하는 숫자 확인 
    }
    int cnt = 0, smallest = 987654321;
    for (int i = 0 ; i < 10 ; ++i){
        int n = base + ast * i;
        if (isPrime[n] && n>=minimal){
            cnt++;
            if (n < smallest)
                smallest = n;
        }
    }
    if (cnt >= 7)
        printf("cnt:%d base:%d ast:%d minimalPrime:%d\n", cnt, base, ast, smallest);
}


int make_base(int n, int l, int c, int ast){
    int mod = 1;
    int originalN = n;
    for (int i = 0 ; i < l ; ++i){
        if (ast % 10 == 1){
            //printf("!\n");
            int pre = n / mod;
            int suf = n % mod;
            n = pre * mod * 10 + suf;
            mod*=10;
            //if (originalN == 999) printf("!%d %d %d ", pre, suf, mod);
        }else{
            mod *= 10;
            int pre = n / mod;
            int suf = n % mod;
            // if (originalN == 999) printf("?%d %d %d ", pre, suf, mod);
            // n = pre * 10 + suf;
        }
        ast /= 10;
        //if (originalN == 999) printf("= ====>n : %d\n", n);
    }

    return n;
}
void gen2(int l, int c, int ast){
    int digits = l-c;
    int e = 1;
    while(digits--){
        e*=10;
    }
    for (int i = 0 ; i < e ; ++i){
        int base = make_base(i, l, c, ast);
        // if (ast == 101) printf("N:%d , MAKEBASE: %d , ASTERISK: %d \n", i, base, ast);
        check(l, base, ast);
    }

}
void bt1(int idx, int pick, int value, int l, int c){
    if (idx == l){
        // printf("-> %d\n", value);
        gen2(l, c, value);
        return;
    }
    int toPick = c-pick;
    if (toPick>0) bt1(idx+1, pick+1, value*10+1, l, c); // *
    if (l-idx-toPick>0) bt1(idx+1, pick, value*10, l, c); // -(숫자)
}

void gen1(int l, int c){
    // printf("length: %d, numberOfAsterisk: %d\n", l, c);
    bt1(0, 0, 0, l, c);
}
void report(int base, int ast){
    printf("### debug ###\n");
    for (int i = 0 ; i < 10 ; ++i){
        int n = base + ast * i;
        printf("# %d", n);
        if (isPrime[n]) printf(" --> is prime number.");
        printf("\n");
        
    }

}
int main(){
    e();
    // gen1(5,2); // test 
    for (int l = 2 ; l < 7; ++l)
        for (int c = 1 ; c <= l ; ++c)
            gen1(l,c);
        
    report(20303, 101010);
    //printf("%d %d\n", answer_sum, answer_cnt);
}



