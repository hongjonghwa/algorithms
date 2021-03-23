#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include"alpha.h"
#include"solution.cpp"
 // 제약조건 2000 번, 10초, 256M


static char photo[16][64];
void shot(int number){
	for (int y = 0 ; y < 16 ; ++y) for (int x = 0 ; x < 64 ; ++x) photo[y][x] = 0;
	int div = 1000;
	int bx = 0;
	for (;div; div /= 10){
		int c = number / div;
		int by = rand() % 9;
		bx += rand() % 9;
		for (int y = 0 ; y < 8 ; ++y){
			for (int x = 0 ; x < 8 ; ++x){
				photo[y+by][x+bx] = alpha[c][y][x];
			}
		}
		bx += 8;
		number %= div;
	}
	for (int y = 0 ; y < 16 ; ++y) 
		for (int x = 0 ; x < 64 ; ++x) 
			if (rand()%10 == 0) photo[y][x] = photo[y][x] == 0 ? 8 : 0;
}

int main(){
	int RESULT = 0;
	for (int c = 0 ; c < 2000 ; ++c){
		int number = rand() % 10000;
		shot(number);
		if (recog(photo) == number) RESULT++;
	}
	printf("RESULT: %d\n", RESULT);
}
