#include<cstdio>
#include<algorithm>

int N;
int X[4][4000];
int XX[2][4000*4000];
long long solv(){
    int i, j, k;

    k = 0;
    for (i = 0 ; i < N ; ++i)
        for (j = 0 ; j < N ; ++j){
            XX[0][k] = X[0][i]+X[1][j];
            XX[1][k++] = - (X[2][i]+X[3][j]) ; // 하나는 마이너스 부호로
        }

    int N2 = N * N;
    std::sort(XX[0], XX[0] + N2);
    std::sort(XX[1], XX[1] + N2);

    long long ret = 0;
    i = j = 0;
    while (i < N2 && j < N2){
        if (XX[0][i]==XX[1][j]){ // 같은 수 연속 고려
            int cnt1 = 1, cnt2 = 1;
            while (i+cnt1<N2 && XX[0][i]==XX[0][i+cnt1]) cnt1++;
            while (j+cnt2<N2 && XX[1][j]==XX[1][j+cnt2]) cnt2++;
            ret += (long long)cnt1*(long long)cnt2;
            i += cnt1;
            j += cnt2;
        }else if (XX[0][i] < XX[1][j]) i++;
        else j++;
    }
    
    return ret;
}
int main(){
    if (scanf("%d", &N) != 1) return 1;
    for (int i = 0 ; i < N ; ++i)
        if (scanf("%d%d%d%d", &X[0][i], &X[1][i], &X[2][i], &X[3][i]) != 4) return 1;
    printf("%lld\n", solv());
}