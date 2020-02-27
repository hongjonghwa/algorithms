#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"alpha.h"

static int _offset;
static int _debug_flag = 1;
static int _debug_answer = 0;

// old
static int _score[10][6]; // score, y, x, match, b, w
static int _score2[8][8][3]; // best, score, match

static int _cnt[10] = { 7,11,14,7,7,11,14,7,10,10 };

int _ss [9][57][10]; // 각 스코어 
int _tt [65]; // 각 줄의 b 갯수 (노이즈) 1 부터, partial sum

// new
void _calc(char photo[16][64], int dy, int dx, int n){
    int &ret = _ss[dy][dx][n];
    ret = 0 ;
	// 1) 저장
	int bb = 0, ww = 0, bw = 0, wb = 0; // 앞은 photo, 뒤는 alpha
    for (int y = 0 ; y < 8; ++y){
        for (int x = 0 ; x < 8 ; ++x){
			if (alpha[n][y][x] == 8){
				if (photo[y + dy][x + dx] == 8) bb++;
				else bw++;
			}else {
				if (photo[y + dy][x + dx] == 8) wb++;
				else ww++;
			}
        }
    }
	int d = 0;
    for (int y = 0 ; y < 8; ++y)
        for (int x = 0 ; x < 8 ; ++x)
            if (photo[y+dy][x+dx] != alpha[n][y][x]) d ++;

	// bb 노이즈 아님 _tt 에서 뺌
	// ww 노이즈 아님
	// wb 노이즈 (이미 _tt에 포함되있음) 
	// bw 노이즈인데 _tt에 포함 안되어 있어,  b가 w로 바뀌었음으로 노이즈
	// -> 먼저 각 행의 b 갯수를 모두 노이즈로 잡은 후 계산한 값을 빼줌
	int noise = (_tt[dx + 8] - _tt[dx]) - bb + bw;// 4글자 맞은 비율 72%
	ret = 1000 - noise; // ret를 _ss에 저장(DP)
}
void _init(char photo[16][64]) {
	_tt[0];
	for (int i = 0; i < 64 ; ++i){
		int sum =0;
		for (int j = 0 ; j < 16 ; ++j) if (photo[j][i] == '8') sum++;
		_tt[i+1] = _tt[i] + sum;
	}
	
    for (int y = 0 ; y <=8 ; ++y) // 0 ~ 8
        for (int x= 0 ; x <= 56 ; ++x) // 0 ~ 57
            for (int i = 0 ; i < 10 ; ++i)
                _calc(photo, y, x, i);

}
int _guess(int &offset){
    //printf("GUESS, %d", offset);
    int score = -1, best, pos_x;
    for (int x = 0 ; x <= 8 ; ++x){
        for (int y = 0 ; y <= 8 ; ++y){
            for (int i = 0 ; i < 10 ; ++i){
                if (_ss[y][x+offset][i] > score){ // best pick
                    score = _ss[y][x+offset][i];
                    best = i; 
                    pos_x = x+offset;
                }
            }
        }
    }
    offset = pos_x + 8;
    return best;
}

int recog(char photo[16][64]) {
    _init(photo);

	_offset = 0;
	int ret = 0;
    ret += _guess(_offset) * 1000;
    ret += _guess(_offset) * 100;
    ret += _guess(_offset) * 10;
    ret += _guess(_offset);
    //printf("\n");

	return ret;
}
