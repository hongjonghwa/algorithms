#include <stdio.h>

int x[200001];
int main(){
    int n, t, prev;
    if (scanf("%d", &n) != 1) return -1;

    if (scanf("%d", &prev) != 1) return -1;
    unsigned long long int ans = 0;
    for (int i = 1 ; i < n ; ++i){

        if (scanf("%d", &t) != 1) return -1;
        if (t < prev) ans += prev - t;
        if (t > prev) prev = t;
    }
    printf("%llu", ans);
}
