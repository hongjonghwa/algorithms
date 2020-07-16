// ! 94

// ! Pell's Equation 이 더 빠른 해답이다 
//   https://www.mathblog.dk/project-euler-94-almost-equilateral-triangles/

#include<stdio.h>
long int sqrt(long int n){
    // n >= 1;
    long long int lo = 0, hi = n+1;
    while (lo + 1 < hi){
        long long int m = (lo+hi)/2;
        if (m*m<=n) lo = m;
        else hi = m;
    }
    return lo;
}
bool check (int sides, int bottom){
    // assert : bottom is always even number
    printf(" ** %d %d\n", sides, bottom);
    bottom /= 2;
    long long int t= ((long long int)sides*sides - (long long int)bottom*bottom)*bottom*bottom;
    printf(" ** %d %d %I64d\n", sides, bottom, t);
    long long int s = sqrt (t);
    if (s*s == t) {
        printf("%d-%d-%d %I64d\n", sides, sides, bottom*2, s);
        return 1;
    } 
    return 0;
}

int main(){
    unsigned long long int a = -1;
    printf("%I64u \n", a); // (Win) I64 --> (Linux) ll

    setbuf(stdout, 0);

    // full scan
    /*
      빗변 s
      밑변 B = s-1 or s+1
      밑변의 절반은 b = B/2 이고 높이가 h라고 할 때
      --> s*s = b*b+h*h
      삼각형의 넓이 h*b = sqrt(s*s-b*b)*b
      만일, 넓이가 integral 하려면 sqrt(s*s - b*b)가 자연수여야 함
            --> B 가 홀수이면 불가, sqrt(s*s - b*b) 는 자연수
    */
    int answer = 0;
    for (int s = 3, x = 1 ; ; s+=2){
        int B = s-1;
        int p = s*2+B;
        if (p > 1000000000) break;
        int b = B/2;
        while ((long long int)s*s - (long long int)b*b > (long long int)x*x) ++x;
        if (s*s - b*b == x*x ){
            printf("%d-%d-%d P:%d A:%d\n", s, s, B, p, x*b);
            answer += p;
        }
    }
    for (int s = 3, x = 1 ; ; s+=2){
        int B = s+1;
        int p = s*2+B;
        if (p > 1000000000) break;
        int b = B/2;
        while ((long long int)s*s - (long long int)b*b > (long long int)x*x) ++x;
        // h가 실수 인지 어떻게 확인하나???
        if (s*s - b*b == x*x ){
            printf("%d-%d-%d P:%d A:%d\n", s, s, B, p, x*b);
            answer += p;
        }
    }
    printf("Answer is %d\n", answer);

    return 0;
}
