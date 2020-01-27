#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int T, N, X[1000];

template <class T>
inline T MAX(T a, T b){
    return a > b ? a : b;
}

int S[1000], len;

int solv(){
    X[N] = 0;
    len = 0; // stack position, length
    int ret = 0;
    for (int i = 0 ; i <= N ; ++i){
        while(len > 0 && X[S[len-1]] >= X[i]){ // 앞에 더 큰 놈이 있으면, 전부 계산한 후 뺀다
            int width;
            if (len == 1) width = i; // left 가 왼쪽 끝이면
            else if (len >= 2) width = i - S[len-2] - 1; // right pos - left pos - 1
            ret = MAX(ret, width * X[S[len-1]]);
            len--; // stack 에서 감소
        }
        S[len++] = i;
    }
    return ret;
}

int main() {
    freopen("fence.txt", "rt", stdin);
    cin >> T;
    for (int t = 0 ; t < T ; ++t){
        cin >> N;
        for (int i = 0 ; i < N ; ++i) cin >> X[i];

        cout << "data:";
        for (int i = 0 ; i < N ; ++i) cout << " " << X[i];
        cout << endl;
        cout.flush();

        cout << "answer: " << solv();
        cout << endl << flush;
    }
}
