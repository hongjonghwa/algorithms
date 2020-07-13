#include<stdio.h>

int main(){
    int N = 50;
    int answer = 0;

    for (int y1 = 0 ; y1 <= N ; ++y1)
        for (int x1 = 0 ; x1 <= N ; ++x1)
            for (int y2 = 0 ; y2 <= N ; ++y2)
                for (int x2 = 0 ; x2 <= N ; ++x2){
                    if (y1 == 0 && x1 == 0) continue;
                    if (y2 == 0 && x2 == 0) continue;
                    if (y1 == y2 && x1 == x2) continue;
                    int ccw = x1*y2 - x2*y1;
                    if (ccw == 0) continue;

                    int a=y1*y1 + x1*x1;
                    int b=y2*y2 + x2*x2;
                    int c=(y2-y1)*(y2-y1) + (x2-x1)*(x2-x1);
                    if (a+b == c || a+c == b || b+c==a) ++answer;
                }
    printf("Answer is %d\n", answer/2);


}
