#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<stack>

using namespace std;

int T, N, X[1000];

int solv(){
    X[N] = 0; // rightest, 다른 모든 펜스의 right 끝을 정의해 줌
    stack<int> remaining; // position of remaining fence
    int ret = 0;
    for (int i = 0 ; i <= N ; ++i){
        while(!remaining.empty() && X[remaining.top()] >= X[i] ){
            int j = remaining.top();
            remaining.pop();
            int width = -1;
            if (remaining.empty()) width = i;
            else width = (i - remaining.top() - 1);
            ret = max(ret, X[j] * width);
        }
        remaining.push(i);
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
