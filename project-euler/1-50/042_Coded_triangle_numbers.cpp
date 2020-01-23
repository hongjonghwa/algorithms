#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))



bool isTriangleNumber(int n){
    int lo = 0, hi = 1000;
    while ( lo+1 < hi ) {
        int mid = (lo+hi)/2;
        if ( mid*(mid+1)/2 < n) lo = mid;
        else hi = mid;
    }
    return hi*(hi+1)/2 == n;
}
int main(){
    freopen("p042_words.txt", "rt", stdin);
    char c;
    char buf[1024*8];
    int bidx = 0;
    int cnt = 0;
    bool open_quote = false;
    int value = 0;
    int tn_cnt = 0;
    while(scanf("%c", &c)){
        if (c == '"'){
            if (open_quote){ // closing
                cnt++;
                buf[bidx] = 0;
                //printf("%d %s %d\n", cnt, buf, value);
                if (isTriangleNumber(value)){
                    tn_cnt++;
                    printf("[%d] l:%d w:%s v:%d\n", tn_cnt, cnt, buf, value);
                }
            }else{ // opening
                bidx = 0;
                value = 0;
            }
            open_quote = !open_quote;
        }else if (c == ','){
            // ignore
        }else{
            buf[bidx++] = c;
            value += c-'A'+1;
        }
        // if (cnt == 10) break;
    }
}



