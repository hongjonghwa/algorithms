#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

char SRC[1000][100];
char QRC[1000][100][100];
char GRAY[1000][100][100];
char DST[1000][100];

int MAXN = 1000;


void encode(char QRC[100][100], char SRC[100]);
void decode(char GRAY[100][100], char DST[100]);

void report_noisy(int offsety, int offsetx, char tmp[200][200]){
	for ( int y = 0 ; y < 16 ; ++y){
		for (int x = 0 ; x < 100 ; ++x){
			if (tmp[y+offsety][x+offsetx] == 1) printf("#");
            else printf(".");
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
	srand(2);
    // A~Z 까지의 100 lenth 문자열
	for(int i = 0 ; i < MAXN; ++i)
		for(int j = 0 ; j < 100; ++j)
			SRC[i][j] = rand() % 26 + 'A';


    int ret = 0;
    int error_cnt = 0;
    long long int clk = clock();
    // QRC에 복사
	for(int i = 0 ; i < MAXN; ++i){
		encode(QRC[i], SRC[i]);
        //if ( i == 2) break;
    }

	for(int i = 0 ; i < MAXN; ++i){
		char tmp[200][200];
		for ( int y = 0 ; y < 200; ++y)
			for (int x = 0 ; x < 200 ; ++x)
				tmp[y][x] = rand() % 2;

		int offsety = rand() % 101;
		int offsetx = rand() % 101;
		for ( int y = 0 ; y < 100; ++y)
			for (int x = 0 ; x < 100 ; ++x)
				tmp[y+offsety][x+offsetx] = QRC[i][y][x];

		for ( int j = 0 ; j < 13000; ++j)
			tmp[rand() % 200][rand() % 200] = 1;
        //report_noisy(offsety, offsetx, tmp);

		for ( int y = 0 ; y < 100; ++y)
			for (int x = 0 ; x < 100 ; ++x){
				GRAY[i][y][x] +=  tmp[y*2][x*2] == 1 ? 1 : 0;
				GRAY[i][y][x] +=  tmp[y*2+1][x*2] == 1 ? 1 : 0;
				GRAY[i][y][x] +=  tmp[y*2][x*2+1] == 1 ? 1 : 0;
				GRAY[i][y][x] +=  tmp[y*2+1][x*2+1] == 1 ? 1 : 0;
			}

        // what is this ?? 기억이 안남
        /*
		for ( int y = 0 ; y < 100; ++y)
			for (int x = 0 ; x < 100 ; ++x)
				GRAY[i][y][x] +=  tmp[y*2][x*2] == 1 ? 1 : 0;
        */

		decode(GRAY[i], DST[i]);
        if (memcmp(SRC[i], DST[i], 100) != 0){
            ret += 10000;
            error_cnt ++ ;
        }
		// SRC와 DST 비교해서, 틀릴때마다 10000 점 감점
        //if (i == 2) break;
	}
    ret += (double)(clock()-clk) * 1000 / CLOCKS_PER_SEC;
    printf("Score : %d \n", ret);
    printf("err : %d \n", error_cnt);
}
