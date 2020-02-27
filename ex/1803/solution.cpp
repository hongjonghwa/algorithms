#include<iostream>
#include<assert.h>
#include<string.h>
#include<time.h>
#include"const.h"
#define MIN(x,y) ( (x) < (y) ? (x) : (y) )
using namespace std;

template<class T>
inline void SWAP(T &a, T &b) {
	T tmp = a;	a = b;	b = tmp;
}
inline int ABS(int a) {
	return a < 0 ? -a : a;
}

extern void move_trash(int y, int x, int d);


struct Trash {
	int y, x;
	int dist[3]; // 각 쓰레기통 까지의 맨하튼 거리
	int ord[3]; // 맨하튼 거리 가까운 순서
	char arrive; // 도착여부 
	char destination; // 목적지

} trash[10000];

struct Can {
	int y, x, cnt;
} can[3];

int can_distance[3][1000][1000];
int DEBUG_CNT1 = 0;
int DEBUG_CNT2 = 0;
int DEBUG_CNT3 = 0;


void move_trash_clone(int y, int x, int d, int trash_map[N][N]) {
    // 쓰레기의 움직임을 추적할 필요!
	move_trash(y, x, d);

	int oy = y, ox = x;
	switch (d) {
	case 1: y++; break;
	case 2: y--; break;
	case 3: x++; break;
	case 4: x--; break;
	}
	if (y < 0 || y>=N || oy < 0 || oy>=N) { cout << "###"; return;}
	if (x < 0 || x>=N || ox < 0 || ox>=N) { cout << "!!!"; return;}

	if (trash_map[oy][ox] != -1) {cout << "'''"; return;}
	if (trash_map[y][x] == -1) {cout << "\"\"\""; return;}

	if (trash_map[y][x] == 0) {
		trash_map[y][x] = -1;
		trash_map[oy][ox] = 0;
	}
	else {
		int canNumber = trash_map[y][x] - 1;
		if (can[canNumber].cnt < TRASH_CAPACITY) {
			trash_map[oy][ox] = 0;
            can[canNumber].cnt++;
		}else{
			cout << "TRASH_OVER" << endl;
		}

	}
}

void report_small_map(int trash_map[N][N]) {
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			if (trash_map[y][x] == -1) cout << "@";
			else if (trash_map[y][x] == 0) cout << " ";
			else cout << trash_map[y][x] - 1;
		}
		cout << endl;
	}
}
void report_small_map2(int trash_map[N][N]) {
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			if (trash_map[y][x] == -1)
				for (int ii = 0 ; ii < N ; ++ii)
					if (trash[ii].y == y && trash[ii].x == x)
						cout << char(trash[ii].destination + '0');
			else if (trash_map[y][x] == 0) cout << " ";
			else cout << char(' '+trash_map[y][x]);
		}
		cout << endl;
	}
}
void report_dist_map(int c) {
	cout << "MAP: " << c << endl;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			cout << can_distance[c][y][x] << " ";
		}
		cout << endl;
	}
}

void init(int trash_map[N][N]) {
    can[0].cnt = can[1].cnt = can[2].cnt = 0;
	int t = 0;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			if (trash_map[y][x] == -1) {
				trash[t].y = y;
				trash[t].x = x;
				++t;
			}
			else if (trash_map[y][x] > 0) {
				int canNumber = trash_map[y][x] - 1;
				can[canNumber].y = y;
				can[canNumber].x = x;
			}
		}
	}
	for (int i = 0; i < TRASH_N; ++i) {
		Trash &tr = trash[i];
		for (int c = 0 ; c < 3 ; ++c) {
			tr.dist[c] = ABS(tr.y - can[c].y) + ABS(tr.x - can[c].x);
			tr.ord[c] = c; // 0,1,2
		}
        // 가까운 쓰레기통 순으로 배열
		if (tr.dist[tr.ord[0]] > tr.dist[tr.ord[1]]) SWAP(tr.ord[0], tr.ord[1]);
		if (tr.dist[tr.ord[1]] > tr.dist[tr.ord[2]]) SWAP(tr.ord[1], tr.ord[2]);
		if (tr.dist[tr.ord[0]] > tr.dist[tr.ord[1]]) SWAP(tr.ord[0], tr.ord[1]);
		tr.arrive = tr.destination = 0;
	}
}
void report_can() {
	for (int i = 0; i < 3; ++i) {
		cout << "[" << i << "]";
		cout << can[i].y << ",";
		cout << can[i].x << ",";
		cout << can[i].cnt << "\t";
	}
	cout << endl;
}

void report_trash() {
	for (int i = 0; i < 10; ++i) {
		if (trash[i].arrive == 1) continue;
		cout << "[" << trash[i].y << ","<< trash[i].x << "] ";
		for (int c = 0 ; c < 3; ++c){
			cout << trash[i].dist[c] << ":";
			cout << can_distance[c][trash[i].y][trash[i].x] << " ";
		}
		cout << "/";
		cout << " A" << (int)trash[i].arrive << " D" << (int)trash[i].destination << " ";
		cout << trash[i].ord[0] << trash[i].ord[1] << trash[i].ord[2] << endl;

	}
}

int QUE[1000000];
int QUE_HEAD, QUE_LEN;
int DY[4] = {+1,-1,0,0}, DX[4] = { 0,0,+1,-1 };

void calc_distance(int trash_map[N][N]) {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k)
				can_distance[i][j][k] = -1;
	
	for (int c = 0; c < 3; ++c) {
		QUE_HEAD = QUE_LEN = 0;

		can_distance[c][can[c].y][can[c].x] = 0; // 시작점 
		QUE[QUE_LEN++] = (can[c].y << 16) + can[c].x; // que in 

		while (QUE_HEAD < QUE_LEN) {
			int oy = QUE[QUE_HEAD] >> 16;
			int ox = QUE[QUE_HEAD] & 0xFFFF;
			int cur_dist = can_distance[c][oy][ox];
			QUE_HEAD++;

			for (int i = 0; i < 4; ++i) {
				int y = oy + DY[i];
				int x = ox + DX[i];

				if (y < 0 || y >= N || x < 0 || x >= N) continue; // BOUND!!
				if (can_distance[c][y][x] == -1) {
					can_distance[c][y][x] = cur_dist + 1; // 첫 방문  -- 현재 위치에서 쓰레기통 까지의 거리를 기록
					if (trash_map[y][x] == 0){ //  빈공간만 que in , 쓰레기 제외 -- 빈 공간일때 다른 쓰레기가 이동할 수 있도록 queue in
						QUE[QUE_LEN++] = (y << 16) + x;
					}
				}
			}

		}
		/*
		cout << "QUE HEAD " << QUE_HEAD << " QUE LENGTH " << QUE_LEN << endl;
		*/
	}
}

long clk = clock();
void TIME_CHK(const char *str) {
	cout << "\tTime CHK[" << str << "]: " << (double)(clock() - clk) / CLOCKS_PER_SEC << endl;
	clk = clock();

}
void move_out_trash(int i, int trash_map[N][N]){
	int &y = trash[i].y;
	int &x = trash[i].x;
	char &dest = trash[i].destination;

	int d;
	while(can_distance[dest][y][x]){
		/*
		cout << "!" << y << "," << x << "," << (int)dest << "->";
		cout << "!" << can[dest].y << "," << can[dest].x << " (len:" << can_distance[dest][y][x] << ")" << endl;
		*/
        /* dy/dx 로 for 문 돌릴 수 있음 */
		if (y < N-1 && 
			can_distance[dest][y][x] -1 == can_distance[dest][y+1][x] &&  // y up
			( trash_map[y+1][x] == 0 || trash_map[y+1][x] == dest + 1 )
		) {
			d = 1; 
			move_trash_clone(y,x,d, trash_map);
			y++;
		}
		else if (y > 0 && 
			can_distance[dest][y][x] -1 == can_distance[dest][y-1][x] &&  // y down
			( trash_map[y-1][x] == 0 || trash_map[y-1][x] == dest + 1 )
		) {
			d = 2;
			move_trash_clone(y,x,d, trash_map);
			y--;
		}
		else if (x < N-1 && 
			can_distance[dest][y][x] -1 == can_distance[dest][y][x+1] && // x up
			( trash_map[y][x+1] == 0 || trash_map[y][x+1] == dest + 1 )
		) {
			d = 3;
			move_trash_clone(y,x,d, trash_map);
			x++;
		}
		else if (x > 0 && 
			can_distance[dest][y][x] -1 == can_distance[dest][y][x-1] &&  // x down
			( trash_map[y][x-1] == 0 || trash_map[y][x-1] == dest + 1 )
		) {
			d = 4;
			move_trash_clone(y,x,d, trash_map);
			x--;
		}
		else {
			cout << "!" << y << "," << x << "," << (int)dest << "->";
			cout << "!" << can[dest].y << "," << can[dest].x << " (len:" << can_distance[dest][y][x] << ")" << endl;
			cout << "@" << y << "," << x << "," << d << "," << (int)dest << endl;
			for (int yy = 165 ; yy  < 175 ; yy++){
				for (int xx = 735 ; xx  < 781 ; xx++){
					cout << can_distance[dest][yy][xx] << "\t";
				}
				cout << endl;
			}
			cout << "IMPOSSIBLE!" << endl;
		}
		/*
		report_small_map(trash_map);
		cout << "@" << y << "," << x << "," << d << "," << (int)dest << endl;
		*/
	}
	trash[i].arrive = 1;
}

void isort1(){
    // 맨하튼 정렬
	for (int i = 1; i < TRASH_N; ++i){
		for (int j = i; j > 0; --j){
			// 음수 로 정방향 정렬
			int cur = trash[j].dist[trash[j].ord[0]] - trash[j].dist[trash[j].ord[1]]; 
			int prev = trash[j - 1].dist[trash[j - 1].ord[0]] - trash[j - 1].dist[trash[j - 1].ord[1]]; // 음수

			if ( prev > cur ){
 				SWAP(trash[j - 1], trash[j]);
			}else{
				break;
			}
		}
	}
}
void qsort1(int l, int u){
    // 1번째 거리 - 2번째 거리(음수) 로 정렬 -> descending
	if (l >=  u) return;
	int pivot = trash[l].dist[trash[l].ord[0]] - trash[l].dist[trash[l].ord[1]];

	int m = l;
	for (int i = l+1 ; i <= u ; ++i){
		int t = trash[i].dist[trash[i].ord[0]] - trash[i].dist[trash[i].ord[1]];
		if (t < pivot){
			SWAP(trash[++m], trash[i]);
		}
	}
	SWAP(trash[m], trash[l]);
	qsort1(l, m-1);
	qsort1(m+1, u);
}
void test(int trash_map[N][N]) {
	TIME_CHK("Begin");
	init(trash_map);
	TIME_CHK("INIT");

	// 맨하튼 거리로 목적지 부여 --> 시간이 중요하다면 최단거리로 소팅하는 것이 조금 더 낫다
    // sort: min ascending 
	// isort1();
	qsort1(0, TRASH_N -1);
	TIME_CHK("SORT");
	// 목적지 
	int tt[3] = {0,0,0};
	for (int i = 0; i < TRASH_N; ++i){
		for (int j = 0 ; j < 3; ++j){
			int c = trash[i].ord[j];
			if (tt[c] < TRASH_CAPACITY){ // 쓰레기통 용량이 남았을 때
				// cout << "!";
				trash[i].destination = c;
				tt[c]++;
				break;
			}
		}
	}


	int f = TRASH_N;

	TIME_CHK("CALC B");
	calc_distance(trash_map); // que 계산 
	TIME_CHK("CALC F");

    // 맨하탄 거리가 일치하는 것만 먼저 보내고, 최단거리를 다시 계산한다
    // : 스텝을 줄일 수 있지만, 시간이 더 걸린다.
    // --> 스텝수/시간 가중치에 따라 선별 적용
    /*
	for (int i = 0; i < TRASH_N; ++i) {
		if (trash[i].arrive == 1) continue;

		int &y = trash[i].y;
		int &x = trash[i].x;
		char &dest = trash[i].destination;
		if (trash[i].dist[dest]  == can_distance[dest][y][x]){ // 맨하튼 거리와 최단거리가 일치!
			move_out_trash(i, trash_map);
            --f;
		}
	}
	cout << "REMAIN COUNT: " << f << endl;

	TIME_CHK("CALC B");
	calc_distance(trash_map); // que 계산 
	TIME_CHK("CALC F");
    */

	for (int i = 0; i < TRASH_N; ++i) {
		if (trash[i].arrive == 1) continue;
		move_out_trash(i, trash_map);
        --f;
	}
	cout << "\tREMAIN COUNT: " << f << endl;

	while (f>0){ // 갖힌 쓰레기는 처음에 이동을 못할 텐데, 그럴때 재 계산 : 현재는 불필요 (쓰레기의 분포 확률상 8방향 모두에서 둘러싸일 가능성이 없음)
	    TIME_CHK("RE-CALC B");
	    calc_distance(trash_map); // que 계산 
	    TIME_CHK("RE-CALC F");
	    for (int i = 0; i < TRASH_N; ++i) {
		    if (trash[i].arrive == 1) continue;
		    move_out_trash(i, trash_map);
            --f;
	    }
    }

	/* debug
		report_small_map(trash_map);
		cout  << endl << endl;
		report_small_map2(trash_map);
		cout  << endl << endl;
		report_trash();
	*/

	/*
	// move_trash_clone(y, x, d, trash_map);
	report_trash();
	// report_can();
	cout << "[AFTER]" << endl;
	report_small_map(trash_map);
	*/
	TIME_CHK("END");
}
