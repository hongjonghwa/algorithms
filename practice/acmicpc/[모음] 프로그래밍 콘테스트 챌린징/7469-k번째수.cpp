#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;

int N, M; // 1 ≤ n ≤ 100,000, 1 ≤ m ≤ 5,000
int ST[18][100001];
int X[100001];

void init(int lvl, int left, int right){
    if (left == right) {
        ST[lvl][left] = X[left]; 
        return;
    }
    int mid = (left+right)/2;

    init(lvl+1, left, mid);
    init(lvl+1, mid+1, right);

    int i = left, j = mid+1, k = left;
    while(i <= mid && j <= right){
        if (ST[lvl+1][i] <= ST[lvl+1][j]) ST[lvl][k++] = ST[lvl+1][i++];
        else ST[lvl][k++] = ST[lvl+1][j++];
    }
    while (i<=mid) ST[lvl][k++] = ST[lvl+1][i++];
    while (j<=right) ST[lvl][k++] = ST[lvl+1][j++];
}

int count_lte(int n, int lvl, int left, int right){ // 적거나 같은 갯수를 센다.
    int l = left-1, r = right + 1;
    while (l+1<r){
        int m = (l+r)/2;
        if (ST[lvl][m]>n) r = m; // upper_bound
        else l = m;
    } // st[][l+1] 은 n 보다 크다
    return r-left ;
}

int query(int l, int r, int n, int lvl, int left, int right){
    if (r < left || right < l) return 0;
    if (l <= left && right <= r) return count_lte(n, lvl, left, right);
    int mid = (left+right)/2;
    return query(l, r, n, lvl+1, left, mid) + query(l, r, n, lvl+1, mid+1, right);
}

int main(){
    if (scanf("%d%d", &N, &M) != 2) return 1;
    for (int i =  1 ; i < N+1 ; ++i)
        if (scanf("%d", &X[i]) != 1) return 1;
    init(0, 1, N);
    std::sort(X+1, X+N+1);

    while (M--){
        int i, j, k;
        if (scanf("%d%d%d", &i, &j, &k) != 3) return 1;

        int l = 0, u = N; // X[l] 갯수가 k 보다 작으면 x[u] 가 답이다
        while(l+1 < u) {
            int m = (l + u) >> 1;
            int cnt = query(i, j, X[m], 0, 1, N);
            if (cnt < k) l = m;
            else u = m;
        }
        std::cout << X[u] << std::endl;
    }
    return 0;
}