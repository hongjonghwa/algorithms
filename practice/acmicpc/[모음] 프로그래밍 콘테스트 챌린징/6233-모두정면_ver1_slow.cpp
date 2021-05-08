#include<cstdio>
#include<cassert>
#include<cstring>

int N;
char X[5000], XX[5000];

void solv(){
    int backward_cnt = 0;
    for (int i =0 ; i < N ; ++i)
        if (X[i]) backward_cnt++;
    
    int k = 1, m = backward_cnt;
    for (int candidate = 2 ; candidate <= N ; ++candidate){
        memcpy(XX, X, sizeof(X[0])*N);
        int cnt = 0;
        bool impossible = false;
        for (int i = 0 ; i <= N-candidate ; ++i){
            if (XX[i]){
                for (int j = 0 ; j < candidate ; ++j)
                    XX[i+j] = !XX[i+j];
                cnt++;
                if (cnt > m){
                    impossible = true;
                    break;
                }
                // for (int _d = 0 ; _d < N ; _d++) {printf("%d ", xx[_d]);} printf("\n");
            }
        }

        if (!impossible){
            for (int i = N-candidate+1 ; i < N ; ++i){
                if (XX[i]){
                    impossible = true;
                    break;
                }
            }
        }
        // printf("- candidate %d cnt %d impossible %d, (nk-1) %d \n", candidate, cnt, impossible, N-candidate+1);
        if (!impossible && cnt < m){
            // printf("k m is %d %d \n", k, m);
            k = candidate;
            m = cnt;
        }
        /*
        */
    }
    
    printf("%d %d\n", k, m);
}

int main(){
    if (scanf("%d\n", &N) != 1) return 1;
    for (int i = 0 ; i < N ; ++i){
        char t;
        if (scanf("%c\n", &t) != 1) return 1;
        assert(t == 'F' || t == 'B');
        X[i] = t == 'B';
    }
    
    solv();
}