#include<cstdio>
#include<cassert>
#include<cstring>

int N;
char X[5000];
int end[5001];
void solv(){
    int backward_cnt = 0;
    for (int i =0 ; i < N ; ++i)
        if (X[i]) backward_cnt++;
    int k = 1, m = backward_cnt;

    for (int candidate = 2 ; candidate <= N ; ++candidate){
        memset(end, 0, sizeof(end[0])*(N+1));

        int flip_cnt = 0, delta = 0;
        for (int i = 0 ; i <= N-candidate ; ++i){
            if (end[i]) delta--;
            if ( (X[i]+delta) & 1 ){
                delta++;
                end[i+candidate] = 1;
                flip_cnt++;
            }
        }

        bool possible = true;
        for (int i = N-candidate+1 ; i < N ; ++i){
            if (end[i]) delta--;
            if ( (X[i]+delta) & 1 ){
                possible = false;
                break;
            }
        }

        // printf("- candidate %d cnt %d impossible %d, (nk-1) %d \n", candidate, flip_cnt, impossible, N-candidate+1);
        if (possible && flip_cnt < m){
            // printf("k m is %d %d \n", k, m);
            k = candidate;
            m = flip_cnt;
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