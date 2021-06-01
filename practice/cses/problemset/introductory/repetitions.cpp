#include<stdio.h>
#define MAX(a,b) ((a)>(b)?(a):(b))

char x[1000001];
int main(){
    if ( scanf("%s", x) != 1) return -1;
    char last = 0;
    int best = 0, cur = 0;
    for (int i = 0 ; x[i] ; ++i){
        if (x[i] == last){
            cur++;
        }else{
            if (cur > best) best = cur;
            last = x[i];
            cur = 1;
        }
    }
    printf("%d", MAX(cur, best));

}
