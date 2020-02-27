/* 처음 풀었던 방식 */
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"alpha.h"


static int _offset;
static int _debug_flag = 0;
static int _debug_answer = 0;

static int _score[10][6]; // score, y, x, match, b, w
static int _score2[8][8][3]; // best, score, match
static int _cnt[10] = { 7,11,14,7,7,11,14,7,10,10 };

void calc(char photo[16][64], int dy, int dx, int n, int &score, int &match, int &b, int &w) {
	score = match = b = w = 0;
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			if (photo[y + dy][x + dx] == 8 && alpha[n][y][x] == 8) b++;
			if (photo[y + dy][x + dx] == 0 && alpha[n][y][x] == 0) w++;
		}
	}
	match = b + w;
	/*
	*  틀린 갯수가 더 중요... 틀릴 때마다 -1000;
	*/
	// 1) 39% 알고리즘
	score = 10000 * b / _cnt[n] + 10000 * w / (64 - _cnt[n]);
	// 2) 10% 알고리즘
	// score = 10000 * (b + w) / 64; 
	//score -= (_cnt[n] - b) * 200;
}
int recog2(char photo[16][64]) {
	if (_debug_flag) {
		for (int y = 0; y < 16; ++y) { for (int x = 0; x < 16; ++x) printf("%d", photo[y][x + _offset] == 8); printf("\n"); } printf("\n");
	}

	for (int i = 0; i < 10; ++i) _score[i][0] = _score[i][1] = _score[i][2] = _score[i][3] = 0;
	memset(_score2, 0, sizeof(_score2));


	int score, match, b, w;
	int distw = 0;

	for (int x = 0; x <= 8; ++x) {
		int curbest = -1;
		for (int y = 0; y <= 8; ++y) {

			for (int n = 0; n < 10; ++n) {
				calc(photo, y, x + _offset, n, score, match, b, w);
				score += distw;
				if (match < 50) continue;
				if (x< 8 && score > _score[n][0]) {
					_score[n][0] = score;
					_score[n][1] = y;
					_score[n][2] = x;
					_score[n][3] = match;
					_score[n][4] = b;
					_score[n][5] = w;
				}
				if (x == 8) {
					if (curbest != 0 && _score[curbest][2] == 0 && score > _score[n][0] + 3000) {
						_score[n][0] = score;
						_score[n][1] = y;
						_score[n][2] = x;
						_score[n][3] = match;
						_score[n][4] = b;
						_score[n][5] = w;
					}
					else if (score > _score[n][0]) {
						_score[n][0] = score;
						_score[n][1] = y;
						_score[n][2] = x;
						_score[n][3] = match;
						_score[n][4] = b;
						_score[n][5] = w;
					}
				}

			}
		}

		for (int i = 0; i < 10; ++i)
			if (curbest == -1 || _score[i][0] > _score[curbest][0])
				curbest = i;
		distw -= 1;
	}
	// best pick
	int best = 0;
	for (int i = 1; i < 10; ++i) {
		if (_score[i][3] < 40) continue; // 50개 미만 matching 은 스킵
										 /*
										 if (_score[i][0] > _score[best][0] ||
										 (_score[i][3] == _score[best][3] && _score[i][2] < _score[best][2])
										 ) best = i;
										 * */
		if (_score[i][0] > _score[best][0]) best = i;
	}
	if (_debug_flag) {
		for (int i = 1; i < 10; ++i)
			printf("  Candidate[%d]: %d %d %d %d %d/%d %d\n",
				i,
				_score[i][0], _score[i][1], _score[i][2], _score[i][3], _score[i][4], _cnt[i], _score[i][5]);
		printf(" Best %d: %d %d %d %d %d %d\n\n", best, _score[best][0], _score[best][1], _score[best][2], _score[best][3], _score[best][4], _score[best][5]);

	}
	_offset += _score[best][2];
	_offset += 8;
	return best;
}


int recog(char photo[16][64]) {
	if (_debug_flag) {
		for (int y = 0; y < 16; ++y) { for (int x = 0; x < 64; ++x) printf("%d", photo[y][x] == 8); printf("\n"); } printf("\n");
	}
	_offset = 0;
	int ret = 0;
	ret += recog2(photo) * 1000;
	ret += recog2(photo) * 100;
	ret += recog2(photo) * 10;
	ret += recog2(photo);

	return ret;
}
