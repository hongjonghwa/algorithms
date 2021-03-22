#include<stdio.h>
#include<time.h>
#include<string.h>

#define SIZE 64

static unsigned int g_seed = 3;
inline int fastrand() {
    g_seed = 214013 * g_seed + 2531011;
    return (g_seed>>16) & 0x7FFF;
}
static unsigned char image[SIZE][SIZE];

extern int solve(unsigned char image[SIZE][SIZE]);

int rect(){
    int sy, sx, ey, ex, temp;

    while(true){
        sy = fastrand() % SIZE;
        sx = fastrand() % SIZE;
        ey = fastrand() % SIZE;
        ex = fastrand() % SIZE;

        if (sy > ey){ temp = sy; sy = ey; ey = temp; }
        if (sx > ex){ temp = sx; sx = ex; ex = temp; }
        
        if (ey - sy < 9) continue;
        if (ex - sx < 9) continue;

        for (register unsigned int y = sy ; y <= ey ; ++y)
            for (register unsigned int x = sx ; x <= ex ; ++x)
                image[y][x]++;
       
        if (ey - sy == ex - sx) return 1;
        return 0;
    }
}

int build(){
    for (register unsigned int y = 0 ; y < SIZE ; ++y)
        for (register unsigned int x = 0 ; x < SIZE ; ++x)
            image[y][x] = 0;
    int ret = 0;
    for (int i = 0 ; i < 50 ; ++i) ret += rect();
    return ret;
}

int main(){
    long long int clk = clock();
    int score =0;
    for (int t = 0 ; t < 10000 ; ++t){
        int count = build();
        if (count == solve(image)) score ++;
    }

    printf("SCORE is %d\n", score);
    printf("executed time is %f\n", (double)(clock()- clk)/CLOCKS_PER_SEC);
    
}
