#include <cstdlib>
#include <cstdio>
#include <cassert>

int N;
char X[2000];
char ret[2001];

int comp(int a, int b){
    if (X[a]<X[b]) return -1;
    if (X[a]>X[b]) return 1;
    return 0;
}

void solv(){
    int i = 0, j = N-1, k = 0;
    while (i <= j){
        int c = 0, t = 0;
        while ( (t = comp(i+c, j-c)) == 0 && i+c+1 < j-c)
            c++;
        
        if (t>0)
            ret[k++] = X[j--];
        else
            ret[k++] = X[i++];
    }
    assert(i == j+1 && k == N);
}

int main(){
    if (scanf("%d\n", &N) != 1)
        return EXIT_FAILURE;
    for (int i = 0 ; i < N ; ++i)
        if (scanf("%c\n", &X[i]) != 1) 
            return EXIT_FAILURE;

    solv();
    for (int i = 0 ; ret[i] != 0 ; ++i){
        if (i>0 && i%80==0) printf("\n");
        printf("%c", ret[i]);
    }
    printf("\n");
}