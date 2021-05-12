#include<math.h>
#include<stdio.h>
#define Pi 3.14159265358979323846  // 소수 20자리의 원주율
const long double PI = acos(-1.0); // 무슨짓을 해도 어차피 더블 (정밀도 15~18자리)

int main(){
    printf("%.20f\n", Pi); 
    printf("%.20Lf\n", PI); 
}
/* 

    3.14159265358979311600 ==> 소수 15자리까지만 일치(double 의 정밀도)

 */
