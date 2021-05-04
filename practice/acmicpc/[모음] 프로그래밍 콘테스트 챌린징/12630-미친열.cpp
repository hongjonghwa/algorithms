/* 
영어 해석을 잘못했다.
Your goal is to have all the 1 values in the matrix below or on the main diagonal
대각행렬 아래도 1 을 다 모으면 되는 것이였는데..
*/


#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

int T, N;
int X[40];

int SWAP_CNT = 0;
template<class T>
inline void SWAP(T & a, T & b){
    T tmp = a; a = b; b = tmp;
    SWAP_CNT++;
}

int solv(){
    SWAP_CNT = 0;
    for (int n = 0 ; n < N ; ++n){
        int best = -1;
        for (int i = n ; i < N ; ++i)
            if (X[i] <= n){ // 만족하는 해가 있음을 문제에서 게런티
                best = i;
                break;
            }
        for (int i = best ; i > n ; i-- )
            SWAP(X[i], X[i-1]);
    }

    return SWAP_CNT;
}

int main(){
    if (scanf("%d", &T) != 1) return EXIT_FAILURE;
    for (int t = 0 ; t < T ; ++t){
        if (scanf("%d", &N) != 1) return EXIT_FAILURE;
        for (int i=0 ; i<N ; ++i){
            char t[41];
            if (scanf("%s", t) != 1) return EXIT_FAILURE;

            int &x = X[i];            
            x = N-1;
            while (x >= 0 && t[x]=='0') x--;
        }

        int ans = solv();
        printf("Case #%d: %d\n", t+1, ans);
    }
}
