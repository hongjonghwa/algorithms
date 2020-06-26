#include<stdio.h>
#define MIN(a,b) ((a)<(b)?(a):(b))
/*
bool hypotenuse_integer(int adjacent, int opposite){
    int pythagoras = adjacent * adjacent + opposite * opposite;
    int l = 0, h = adjacent + opposite;
    while (l+1 < h){
        int m = (l+h)/2;
        if (m*m < pythagoras) l = m;
        else h = m;
    }
    return (l+1)*(l+1) == pythagoras;
}
*/

int pythagoras(int adjacent, int opposite){
    return adjacent * adjacent + opposite * opposite;
}

bool integer_sqroot(long area){
    long l = 0, h = area;
    while (l+1 < h){
        long int m = (l+h)/2;
        if (m*m < area) l = m;
        else h = m;
    }
    return (l+1)*(l+1) == area;

}
bool solv(int z, int y, int x){
    int area = 987654321;
    long t = pythagoras(x, y+z);
     if (t < area) area = t;

    return integer_sqroot(area);
}


int main(){
    int count = 0;
    int N = 500;
    
    int CASE = 1;
    if (CASE == 1){
        for (int z = 1 ; z <= N ; ++z) // z가 가장 작은 수
            for (int y = z ; y <= N ; ++y)
                for (int x = y ; x <= N ; ++x){
                    if (solv(z,y,x)) {
                        count++;
                        printf("%d %d %d\n", z, y, x);
                    }
                }
        // 1,000 ==> 31655, 17s
    }

    if (CASE == 2){
        for (int z = 1 ; z <= N ; ++z) // z가 가장 큰 수
            for (int xy = 2 ; xy < z*2 ; ++xy)
                if (integer_sqroot(z*z + xy*xy)){
                    int l = (xy+1)/2;
                    int h = MIN(z, xy-1);
                    count += h-l+1;
                    for (int j = l ; j <= h ; ++j){
                        printf("%d %d %d\n", xy-j, j, z);
                    }
                    //printf("xy:%d l:%d h:%d z:%d\n", xy, l, h, z);
                }
    }

    printf("count is %d\n", count);
}
