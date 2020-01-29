#define N 5
#define COL 5
#define ROW 12
#include<stdio.h>
#include<string.h>
#include"pentomino-blocks.h"

template<class T>
inline void SWAP(T & a, T & b){
	T tmp = a; a = b; b = tmp;
}

//int B[12][4][2];
struct Node{
	int x[4][2];
	void coord_sort(){
		for (int i = 1 ; i <= 3 ;++i){
			for (int j = i ; j>0 ; --j){
				if (x[j-1][0] > x[j][0] || (x[j-1][0] == x[j][0] && x[j-1][1] > x[j][1])){
					int t;// swap
					t = x[j-1][0] ; x[j-1][0] = x[j][0]; x[j][0] = t;
					t = x[j-1][1] ; x[j-1][1] = x[j][1]; x[j][1] = t;
				}
			}
		}
	}
	bool operator<(const Node &rhs) const{
		for (int i = 0 ; i < 4; ++i)
			for (int j = 0 ; j < 2 ; ++j){
				if (x[i][j] < rhs.x[i][j] ) return true;
				if (x[i][j] > rhs.x[i][j] ) return false;
			}
		return false;
	}
	bool operator>(const Node &rhs) const{
		for (int i = 0 ; i < 4; ++i)
			for (int j = 0 ; j < 2 ; ++j){
				if (x[i][j] > rhs.x[i][j] ) return true;
				if (x[i][j] < rhs.x[i][j] ) return false;
			}
		return false;
	}
	bool operator==(const Node &rhs) const{
		for (int i = 0 ; i < 4; ++i)
			for (int j = 0 ; j < 2 ; ++j)
				if (x[i][j] != rhs.x[i][j] ) return false;
		return true;
	}
	bool operator!=(const Node &rhs) const{
		for (int i = 0 ; i < 4; ++i)
			for (int j = 0 ; j < 2 ; ++j)
				if (x[i][j] != rhs.x[i][j] ) return true;
		return false;
	}
};
Node B[12];
Node BALL[12][8];
int BALL_CNT[12];

void init_brick2coordinate(){
	for (int k = 0 ; k < 12 ; ++k){
		int y = -1, x = -1; // startpos
		int idx = 0;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				if (BLOCK[k][i][j] == '#'){ // 첫번째 만나는 #의 위치에 따라 상대 좌표로 변환
					if (y == -1){
						y = i;
						x = j;
					}else{
						B[k].x[idx][0] = i-y;
						B[k].x[idx][1] = j-x;
						idx ++;
					}
				}
	} // loop k
}
void rotate(Node &b){
	for (int i = 0; i < 4 ; ++i){
		int y = b.x[i][0];
		int x = b.x[i][1];
		b.x[i][0] = -x;
		b.x[i][1] = y;
	}
}
void mirror(Node &b){
	for (int i = 0; i < 4 ; ++i){
		b.x[i][0] = -b.x[i][0];
	}
}
void init_allbrick(){
	for (int k = 0 ; k < 12 ; ++k){
		Node t = B[k];
		BALL[k][0] = t;
		rotate(t); BALL[k][1] = t;
		rotate(t); BALL[k][2] = t;
		rotate(t); BALL[k][3] = t;
		mirror(t); BALL[k][4] = t;
		rotate(t); BALL[k][5] = t;
		rotate(t); BALL[k][6] = t;
		rotate(t); BALL[k][7] = t;

		// 좌상단이 기준이 되도록
		for (int kk = 1 ; kk<=7 ; ++kk){
			int y = 0, x = 0, topleft = -1;
			for (int i = 0; i < 4; ++i){
				int &yy = BALL[k][kk].x[i][0];
				int &xx = BALL[k][kk].x[i][1];
				if (yy < y || (yy == y && xx < x)){
					y = yy;
					x = xx;
					topleft = i;
				}
			}

			// 좌표 조정
			if (topleft != -1){
				for (int i = 0; i < 4; ++i){
					int &yy = BALL[k][kk].x[i][0];
					int &xx = BALL[k][kk].x[i][1];
					yy -= y;
					xx -= x;
				}
				BALL[k][kk].x[topleft][0] = -y;
				BALL[k][kk].x[topleft][1] = -x;
			}

			// 좌표 정렬
			BALL[k][kk].coord_sort();
		}

		BALL_CNT[k] = 8;
	}
}
void init_casesort(){
	for (int k = 0 ; k < 12 ; ++k){
		// isort
		for (int i = 1 ; i <= 7 ;++i){
			for (int j = i ; j>0 && BALL[k][j-1] > BALL[k][j] ; --j){
				SWAP(BALL[k][j-1], BALL[k][j]);
			}
		}
	}
}
void init_caseuniq(){
	for (int k = 0 ; k < 12 ; ++k){
		int idx = 0;
		for (int i = 1 ; i <= 7 ;++i){
			if (BALL[k][i] != BALL[k][idx]){
				idx++;
				if (i != idx){
					BALL[k][idx] = BALL[k][i];
				}
			}
		}
		BALL_CNT[k] = idx+1;
	}
}
void print_node(Node & b){
	for (int i = 0; i < 4 ; ++i)
		printf("(%d, %d) ", b.x[i][0], b.x[i][1]);
	printf("\n");
}

/* 
	row/col 이  3/20 일 때는 40 분 20/3일 때는 0.1초 검리는 이유는?
	: 20칸 1줄을 채우는 방법이 너무 많음... 더 적은 가지수를 먼저!!!
*/


int BOARD[100][100];
int VISIT[12];

int answer_cnt = 0;

void report_board(){
	for (int i = 0 ; i < ROW ; ++i){
		for (int j = 0 ; j < COL ; ++j){
			printf("%c" , (BOARD[i][j] ? 'A'+BOARD[i][j]-1 : ' '));
		}
		printf("\n");
	}

}

bool cover(int y, int x, int k, int c, int delta){
	bool ret = true;
	if (BOARD[y][x]) ret = false; // 아래에 숫자가 있을 때 
	BOARD[y][x] += (k+1)*delta;

	for (int i = 0 ; i < 4; ++i){
		int &yy = BALL[k][c].x[i][0];
		int &xx = BALL[k][c].x[i][1];
		if (y+yy < 0 || x+xx < 0 || y+yy >= ROW || x+xx >= COL) ret = false;
		else{
			if (BOARD[y+yy][x+xx]) ret = false; // 아래에 숫자가 있을 때 
			BOARD[y+yy][x+xx] += (k+1)*delta;
		}
	}
	return ret;
}

void bt(){
	int y = -1, x = -1;
	//  y-x 축을 바꿔도 되는가? No : 블록의 기준점이 top left임 
	// 축을 바꾸려면 블록의 기준점을 left-top으로 같이 바꿔야함 
	for (int i = 0 ; i < ROW ; ++i){
		for (int j = 0 ; j < COL ; ++j){
			if (BOARD[i][j] == 0){
				y = i;
				x = j;
				break;
			}
		}
		if (y!=-1) break;
	}
	//printf ("%d %d \n", y, x);
	if (y == -1){
		printf("Pick!!!\n");
		report_board();
		++answer_cnt;
		printf(" %d \n ", answer_cnt);
		return;
	};
	for (int next = 0 ; next < 12 ; ++next){
		if (VISIT[next]) continue;
		for (int c = 0 ; c < BALL_CNT[next] ; ++c){
			VISIT[next] = 1;
			//printf(" %d %d %d %d %d \n", y,x,next,c,1);
			if (cover(y,x,next,c,1)) {
				//printf("############################\n");
				//report_board();
				bt();
			}
			cover(y,x,next,c,-1);
			VISIT[next] = 0;
		}
	}
}


int main(){

	// 12개 블럭 좌표화
	init_brick2coordinate();
	// 각 블럭 8방향으로 좌표 계산
	init_allbrick();
	/*
	int no = 5;
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j)
			printf("%c",BLOCK[no][i][j]);
		printf("\n");
	}
	*/
	//print_node(B[no]);
	//for (int i = 0 ; i < 8 ; ++i) print_node(BALL[no][i]);
	// 좌표로 소팅
	init_casesort();
	//printf("\n");
	//for (int i = 0 ; i < BALL_CNT[no] ; ++i) print_node(BALL[no][i]);
	// 중복 블록 제거
	init_caseuniq();
	//printf("\n");
	//for (int i = 0 ; i < BALL_CNT[no] ; ++i) print_node(BALL[no][i]);

	//for (int i = 0 ; i < 12 ; ++i) printf(" %d 's len is %d \n", i, BALL_CNT[i]);

	// static 은 이미 0, 불필요 
	memset(BOARD,0, sizeof(BOARD));
	memset(VISIT,0, sizeof(VISIT));

	bt();

	printf("all case is %d \n ", answer_cnt);
}
