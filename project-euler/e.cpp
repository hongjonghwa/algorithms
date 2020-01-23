#include<stdio.h>

bool P[1000001];
void e(){
    for (int i = 2 ; i <= 1000000 ; ++i) P[i] = true;
    for (int i = 2; i <= 1000 ; ++i)
        if (P[i])
            for (int j = i * i ; j <= 1000000 ; j += i)
                P[j] = false;
}

int main() {
    e();
    int cnt = 0;
    for (int i = 2 ; i <= 100 ; ++i)
        if (P[i]) {
            cnt++;
            // printf("%d] %d \n", cnt, i);
        }
    printf("counts : %d\n", cnt);
}
