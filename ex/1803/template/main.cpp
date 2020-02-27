#include<iostream>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

using namespace std;

extern void test(int trash_map[1000][1000]);

static int trash_map[1000][1000];
static int ori_trash_map[1000][1000];
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
	if (y < 0 || y>999 || oy < 0 || oy>999) return;
	if (x < 0 || x>999 || ox < 0 || ox>999) return;
	
	if (ori_trash_map[oy][ox] != -1) return;
	if (ori_trash_map[y][x] == -1) return;

	if (ori_trash_map[y][x] == 0) {
		ori_trash_map[y][x] = -1;
		ori_trash_map[oy][ox] = 0;
	}
	else {
		int canNumber = ori_trash_map[y][x] - 1;
		if (trash_can[canNumber] < 3500) {
			ori_trash_map[oy][ox] = 0;
			trash_can[canNumber]++;
		}
	}
}

void build() {
	for (int y = 0; y < 1000; y++) for (int x = 0; x < 1000; x++) trash_map[y][x] = 0;
	trash_can[0] = trash_can[1] = trash_can[2] = 0;
	for (int c = 0; c < 3;) {
		// int y = rand() % 1000, x = rand() % 1000;
		// Small Set
		int y = rand() % 1000, x = rand() % 1000;
		if (trash_map[y][x] == 0) trash_map[y][x] = ++c;
	}
	for (int c = 0; c < 10000;) {
		int y = rand() % 1000, x = rand() % 1000;
		if (trash_map[y][x] == 0) {
			trash_map[y][x] = -1;
			c++;
		}
	}
	for (int y = 0; y < 1000; y++) for (int x = 0; x < 1000; x++) ori_trash_map[y][x] = trash_map[y][x];
}

int main() {
	
	srand(1);
	for (int t = 0; t < 10; ++t) {
		build();
		long clk = clock();
		test(trash_map);

		for (int y = 0; y < 1000; y++)
			for (int x = 0; x < 1000; x++) 
				if (ori_trash_map[y][x] == -1) RESULT += 10000;

		RESULT += (clock() - clk);
		cout << "Time Execution: " << (double)(clock() - clk) / CLOCKS_PER_SEC << endl;

	}

	cout << "SCORE : " << RESULT << endl;
}
