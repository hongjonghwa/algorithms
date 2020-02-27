#include <stdio.h>

bool x[200001];
int main(){
    int n, t;

    if (scanf("%d", &n) != 1) return -1;
    for (int i = 0 ; i < n -1 ; ++i){
        if (scanf("%d", &t) != 1) return -1;
        x[t] = true;
    }
    for (int i = 1 ; i <= n ; ++i)
        if (!x[i]) printf("%d ", i);
}
