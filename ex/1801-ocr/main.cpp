#include<stdio.h>
#include<time.h> 
#include<string.h>
#include<stdlib.h>
#include"alpha.h"



extern char alpha[10][8][8];
extern int recog(char photo[16][64]);

static int _debug = 0;
static int _debug_flag = 0;
// static int _LOOP = 2000;
static int _LOOP = 2000;


// 제약조건 2000 번, 10초, 256M
static char photo[16][64];
static char photo_debug[16][64];
void shot(int number) {
	// printf("number : %d \n", number);
	for (int y = 0; y < 16; ++y) for (int x = 0; x < 64; ++x) photo[y][x] = 0;
	int div = 1000; // 첫 나누기
	int bx = 0;
	for (; div; div /= 10) {
		int c = number / div;
		int by = rand() % 9;
		bx += rand() % 9;
		for (int y = 0; y < 8; ++y) {
			for (int x = 0; x < 8; ++x) {
				photo[y + by][x + bx] = alpha[c][y][x];
			}
		}
		bx += 8;
		number %= div;
	}

	// copy
	for (int y = 0; y < 16; ++y) for (int x = 0; x < 64; ++x) photo_debug[y][x] = photo[y][x];

    // noise
	for (int y = 0; y < 16; ++y)
		for (int x = 0; x < 64; ++x)
			if (rand() % 10 == 0) photo[y][x] = photo[y][x] == 0 ? 8 : 0;
   
}

int main() {
	// srand(42);
	int RESULT = 0;
    long long int clk = clock();
	for (int c = 0; c < _LOOP; ++c) {
        // break;
		if (_debug && c == 20) break;
		int number = rand() % 10000;
		// int number = rand() % 10;
		shot(number);
        //printf("number %d \n", number);
		int guess = recog(photo);
		if (guess == number) RESULT++;
		
		if (_debug) {
			_debug_flag = 1;
			for (int y = 0; y < 16; ++y) { for (int x = 0; x < 64; ++x) printf("%d", photo_debug[y][x] == 8); printf("\n"); } printf("\n");
			printf("\n");
			for (int y = 0; y < 16; ++y) { for (int x = 0; x < 64; ++x) printf("%d", photo[y][x] == 8); printf("\n"); } printf("\n");
			printf("\n");
			// printf("Loop %d answer %d guess %d \n\n", c, number, guess);
			_debug_flag = 0;
		}
		if (_debug) printf("Loop %d answer %d guess %d \n\n", c, number, guess);
	}
	printf("RESULT: %d (SUCCESS %d%%)\n", RESULT, RESULT * 100 / _LOOP);
	printf("Execution Time: %f \n", ((double)clock() - clk) / CLOCKS_PER_SEC);
}
