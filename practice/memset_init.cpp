#include<cstdio>
#include<cstring>

int X[10000];

void test(int n){
    memset(X, n, sizeof(X));
    printf("%d -> %d\n", n, X[0]);
}
int main(){

    test(0x3f); // 적당한 값
    test(63);
    // 63 -> 1061109567

    test(127); // 거의 한계까지 큰 값
    test(0x7f);
    // 127 -> 2139062143

    test(-63); // 적당한 음수
    // -63 -> -1044266559
    test(-127); // 극단적인 음수
    // -127 -> -2122219135


    test(0); // 0 초기화
    // 0 -> 0
    test(-1); // -1 초기화
    // -1 -> -1

    test(1);
    test(42);
    test(127/3);
    test(-127);
}
