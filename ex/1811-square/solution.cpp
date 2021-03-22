#include<stdio.h>
#include<assert.h>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

#define SIZE 64

// 1, 2, 3, 4 엣지
int solve3(unsigned char image[SIZE][SIZE]){
    
    char ii[SIZE+2][SIZE+2];
    for (int i = 0 ; i < SIZE+2 ; ++i) ii[0][i] = ii[i][0] = ii[SIZE+1][i] = ii[i][SIZE+1] = 0;
    for (int i = 0 ; i < SIZE ; ++i) for (int j = 0 ; j < SIZE ; ++j) ii[i+1][j+1] = image[i][j];

    char ss[SIZE+1][SIZE+1];
    for (int i = 0 ; i <= SIZE ; ++i)
        for (int j = 0 ; j <= SIZE ; ++j){
            int s = ii[i][j] + ii[i+1][j+1] - ii[i+1][j] - ii[i][j+1];
            // 아래와 같은 방식으로는 사각형의 시작점을 알기 힘들다...
            if ( s > 0 && ii[i+1][j+1] > ii[i][j]) ss[i][j] = 1;
            else if ( s > 0 && ii[i+1][j+1] < ii[i][j]) ss[i][j] = 4;
            else if ( s < 0 && ii[i+1][j] < ii[i][j+1]) ss[i][j] = 2;
            else if ( s < 0 && ii[i+1][j] > ii[i][j+1]) ss[i][j] = 3;
            else ss[i][j] = 0;
        }
    // report
    /*
    for (int i = 0 ; i <= SIZE ; ++i){
        for (int j = 0 ; j <= SIZE ; ++j)
            printf("%2d", ss[i][j]);
        printf("\n");
    }
    */

    int count = 0;
    for (int i = 0 ; i <= SIZE ; ++i)
        for (int j = 0 ; j <= SIZE ; ++j)
            if (ss[i][j] == 1)
                for (int k = 9 ; i+k <= SIZE && j+k <= SIZE; ++k)
                    if (ss[i+k][j] == 2 && ss[i][j+k] == 3 && ss[i+k][j+k] == 4) count++;

    //printf(", Yours is %d\n", count);
    return count;
}
int solve2(unsigned char image[SIZE][SIZE]){

    char ii[SIZE+2][SIZE+2];
    for (int i = 0 ; i < SIZE+2 ; ++i)
        ii[0][i] = ii[i][0] = ii[SIZE+1][i] = ii[i][SIZE+1] = 0;

    for (int i = 0 ; i < SIZE ; ++i)
        for (int j = 0 ; j < SIZE ; ++j)
            ii[i+1][j+1] = image[i][j];

    char ss[SIZE+1][SIZE+1];
    for (int i = 0 ; i <= SIZE ; ++i)
        for (int j = 0 ; j <= SIZE ; ++j)
            ss[i][j] = ii[i][j] + ii[i+1][j+1] - ii[i+1][j] - ii[i][j+1];

    // report
    /*
    for (int i = 0 ; i <= SIZE ; ++i){
        for (int j = 0 ; j <= SIZE ; ++j)
            printf("%2d", ss[i][j]);
        printf("\n");
    }
    */

    int count = 0;
    for (int i = 0 ; i <= SIZE ; ++i)
        for (int j = 0 ; j <= SIZE ; ++j)
            if (ss[i][j] > 0)
                for (int k = 9 ; i+k <= SIZE && j+k <= SIZE; ++k)
                    if (ss[i+k][j] < 0 && ss[i][j+k] < 0 && ss[i+k][j+k] > 0) count++;

    //printf(", Yours is %d\n", count);
    return count;
}

// 멍청한 방법
int solve1(unsigned char image[SIZE][SIZE]){
    int c1 = 0, c2 = 0;
    for (int y = 0; y < SIZE ; ++y){
        for (int x = 0 ; x < SIZE ; ++x){
            // 옆칸
            int u = y == 0 ? 0 : image[y-1][x];
            int l = x == 0 ? 0 : image[y][x-1];
            int r = x == 63 ? 0 : image[y][x+1];
            int d = y == 63 ? 0 : image[y+1][x];

            u -= image[y][x];
            l -= image[y][x];
            r -= image[y][x];
            d -= image[y][x];

            int status = 0 ;
            if (u<0 && l<0) {
                int diff  = MIN(-u, -l);
                c1 += diff;
                status += 1;
                //printf("< %d %d %d    %d \n", ++c1, y, x, diff);
            }
            if (r<0 && d<0) {
                int diff  = MIN(-r, -d);
                c2 += diff;
                status += 2;
                //printf("> %d %d %d    %d \n", ++c2, y, x, diff);
            }
            printf("%2d" , image[y][x]);
            /*
            if (status==1) printf("<");
            else if (status==2) printf(">");
            else if (status==3) printf("=");
            else printf(" ");
            */
        }
        printf("\n");
    }

    printf("C1, C2 : %d %d \n", c1, c2);
    return 1;
}
int solve(unsigned char image[SIZE][SIZE]){
    int ret;
    // ret = solve1(image); // 멍청한 방법
    // 
    ret = solve2(image); // 1, -1 엣지, 선수 방법
    // ret = solve3(image); // 1, 2, 3, 4 엣지 --> 오히려 속도가 떨어짐
    return ret;
}
