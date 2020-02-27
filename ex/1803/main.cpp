#include<iostream>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include"const.h"
#include<unistd.h>

using namespace std;

extern void test(int trash_map[N][N]);

static int trash_map[N][N];
static int ori_trash_map[N][N];
static int RESULT = 0;
static int trash_can[3];


void move_trash(int y, int x, int d) {
	RESULT++;

	int oy = y, ox = x;
	switch (d) {
	    case 1: y++; break;
	    case 2: y--; break;
	    case 3: x++; break;
	    case 4: x--; break;
	}
	if (y < 0 || y>=N || oy < 0 || oy>=N) return;
	if (x < 0 || x>=N || ox < 0 || ox>=N) return;
	
	if (ori_trash_map[oy][ox] != -1) return;
	if (ori_trash_map[y][x] == -1) return;

	if (ori_trash_map[y][x] == 0) {
		ori_trash_map[y][x] = -1;
		ori_trash_map[oy][ox] = 0;
	}
	else {
		int canNumber = ori_trash_map[y][x] - 1;
		if (trash_can[canNumber] < TRASH_CAPACITY) {
			ori_trash_map[oy][ox] = 0;
			trash_can[canNumber]++;
		}
	}
}

void build() {
	for (int y = 0; y < N; y++) for (int x = 0; x < N; x++) trash_map[y][x] = 0;
	trash_can[0] = trash_can[1] = trash_can[2] = 0;
	for (int c = 0; c < 3;) {
		// int y = rand() % 1000, x = rand() % 1000;
		// Small Set
		int y = rand() % N, x = rand() % N;
		if (trash_map[y][x] == 0) trash_map[y][x] = ++c;
	}
	for (int c = 0; c < TRASH_N;) {
		int y = rand() % N, x = rand() % N;
		if (trash_map[y][x] == 0) {
			trash_map[y][x] = -1;
			c++;
		}
	}
	for (int y = 0; y < N; y++) for (int x = 0; x < N; x++) ori_trash_map[y][x] = trash_map[y][x];
}

int main() {
	
	srand(1);
	for (int t = 0; t < 10; ++t) {
        cout << "[LOOP " << (t+1) << "]\n";
		build();
		long clk = clock();
		test(trash_map);

        // 검증
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++) 
				if (ori_trash_map[y][x] == -1){
				    RESULT += 10000;	
				    cout << "E";
                    assert(0); // trash remained
				} 

		RESULT += (clock() - clk);
		cout << "Time Execution: " << (double)(clock() - clk) / CLOCKS_PER_SEC << endl;
		// break; // 1time
	}

	cout << "SCORE : " << RESULT << endl;

    //cout << "Sleep in 10 second..."<< endl; 
    //sleep(10);
}
