#include<stdio.h>
#include<assert.h>
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

struct Cell{
    unsigned char map[256][256];
	unsigned char edge[4][256];
    bool is_edge[4]; // top, left, right, bottom 엣지 여부
    bool is_used;
    /*
	void init(){
        is_edge[0] = is_edge[1] = is_edge[2] = is_edge[3]  = 0;
        is_used = 0;
	}
    */
} cell[256];
int answer[16][16];


bool is_empty(int c, int sy, int sx, int ey, int ex){
	for (int y = sy ; y < ey ; ++y)
		for (int x = sx ; x < ex ; ++x)
			if (cell[c].map[y][x]!= 0) 
                return false;
    return true;
}

int detect_edge(int *x){
    if (x[0] == 0) return 0;
    //detect candidate
    int candidate = x[0], count = 1;
    int i;
    for (i = 1 ; i < 8 && x[i] != 0 ; ++i ){
        if (count == 0){
            candidate = x[i];
            count = 1;
        }else if (candidate == x[i]) count++;
        else count--;
    }
    int len = i;
    count = 0;
    for (int i = 0; i < len ; ++i) if (x[i] == candidate) count++;

    if (len == 1) return 0;
    if (len == 2) return count == 2 ? candidate : 0;
    return count * 2 > len ? candidate : 0 ; // 50% 초과 
}

void init_cell(int c){
    cell[c].is_used = false;

    cell[c].is_edge[TOP] = is_empty(c, 0,0, 16,256);
    cell[c].is_edge[LEFT] = is_empty(c, 0,0, 256,16);
    cell[c].is_edge[RIGHT] = is_empty(c, 0,240, 256,256);
    cell[c].is_edge[BOTTOM] = is_empty(c, 240,0, 256,256);

    int t[8];
    for (int i = 0 ; i < 256 ; ++i){
        for (int j = 0 ; j < 8 ; ++j) t[j] = cell[c].map[j][i]; // top
        cell[c].edge[TOP][i] = detect_edge(t);
        for (int j = 0 ; j < 8 ; ++j) t[j] = cell[c].map[i][j]; // left
        cell[c].edge[LEFT][i] = detect_edge(t);
        for (int j = 0 ; j < 8 ; ++j) t[j] = cell[c].map[i][255-j]; // right
        cell[c].edge[RIGHT][i] = detect_edge(t);
        for (int j = 0 ; j < 8 ; ++j) t[j] = cell[c].map[255-j][i]; // bottom
        cell[c].edge[BOTTOM][i] = detect_edge(t);
    }
}

void init(unsigned char map[4096][4096]){
    // answer -1
    for (int y = 0 ; y < 16 ; ++y)
        for (int x = 0 ; x < 16 ; ++x)
            answer[y][x] = -1;
    // 256 개 셀로 분할
    int c = 0;
    for (int y = 0 ; y < 16 ; ++y){
        for (int x = 0 ; x < 16 ; ++x){
            int dy = y * 256, dx = x * 256;
            for (int yy = 0 ; yy < 256 ; ++yy)
                for (int xx = 0 ; xx < 256 ; ++xx)
                    cell[c].map[yy][xx] = map[dy+yy][dx+xx];
            c++;
        }
    }
    // 셀 단위 초기화
    for (c = 0 ; c < 256 ; ++c)
        init_cell(c);


    // ASSERTION
    /*
    int debug = 0;
    for (int i = 0 ; i < 256 ; ++i) if (cell[i].is_edge[TOP]) debug++; assert(debug == 16);
    for (int i = 0 ; i < 256 ; ++i) if (cell[i].is_edge[LEFT]) debug++; assert(debug == 32);
    for (int i = 0 ; i < 256 ; ++i) if (cell[i].is_edge[RIGHT]) debug++; assert(debug == 48);
    for (int i = 0 ; i < 256 ; ++i) if (cell[i].is_edge[BOTTOM]) debug++; assert(debug == 64);
	*/
}

bool debug_is_same(int cy, int cx, unsigned char map1[4096][4096], unsigned char map2[4096][4096]){
	int dy = cy * 256, dx = cx * 256;
	for (int y = 0 ; y < 256 ; ++y){
		for (int x = 0 ; x < 256 ; ++x){
			if (map1[y+dy][x+dx] != map2[y+dy][x+dx]) return false;
		}
	}
	return true;
}

void debug_cell_all(int c){
	for (int y = 0 ; y < 256 ; ++y){
		for (int x = 0 ; x < 256 ; ++x){
			printf("%3d ", cell[c].map[y][x] );
		}
		printf("\n");
	}
	printf("\n");

    printf ("TOP\n");
    for (int i = 0 ; i < 256 ; ++i)
		printf("%3d ", cell[c].edge[TOP][i] );
	printf("\n\n");

    printf ("LEFT\n");
    for (int i = 0 ; i < 256 ; ++i)
		printf("%3d ", cell[c].edge[LEFT][i] );
	printf("\n\n");

    printf ("RIGHT\n");
    for (int i = 0 ; i < 256 ; ++i)
		printf("%3d ", cell[c].edge[RIGHT][i] );
	printf("\n\n");

    printf ("BOTTOM\n");
    for (int i = 0 ; i < 256 ; ++i)
		printf("%3d ", cell[c].edge[BOTTOM][i] );
	printf("\n\n");
}

int calc(unsigned char a[256], unsigned char b[256]){
    int ret = 0;
    for (int i = 0 ; i < 256 ; ++i) if (a[i] == b[i]) ret++;
    return ret;
}

void test(unsigned char map[4096][4096]){
	// 원래 문제
	init(map);

    // 모서리
    for (int i = 0 ; i < 256 ; ++i){
        if (cell[i].is_edge[TOP] && cell[i].is_edge[LEFT]) answer[0][0] = i, cell[i].is_used = true;
        if (cell[i].is_edge[TOP] && cell[i].is_edge[RIGHT]) answer[0][15] = i, cell[i].is_used = true;
        if (cell[i].is_edge[BOTTOM] && cell[i].is_edge[LEFT]) answer[15][0] = i, cell[i].is_used = true;
        if (cell[i].is_edge[BOTTOM] && cell[i].is_edge[RIGHT]) answer[15][15] = i, cell[i].is_used = true;
    }
    // top 엣지
    for (int p = 1 ; p < 15 ; p++){
        int best = -1, best_score = -1;
        for (int i = 0 ; i < 256; ++i){
            if (cell[i].is_used || !cell[i].is_edge[TOP]) continue;
            int score = calc(cell[answer[0][p-1]].edge[RIGHT], cell[i].edge[LEFT]);
            if (score > best_score) best = i,  best_score = score;
        }
        answer[0][p] = best;
        cell[best].is_used = true;
    }

    // bottom 엣지
    for (int p = 1 ; p < 15 ; p++){
        int best = -1, best_score = -1;
        for (int i = 0 ; i < 256; ++i){
            if (cell[i].is_used || !cell[i].is_edge[BOTTOM]) continue;
            int score = calc(cell[answer[15][p-1]].edge[RIGHT], cell[i].edge[LEFT]);
            if (score > best_score) best = i,  best_score = score;
        }
        answer[15][p] = best;
        cell[best].is_used = true;
    }

    // left 엣지
    for (int p = 1 ; p < 15 ; p++){
        int best = -1, best_score = -1;
        for (int i = 0 ; i < 256; ++i){
            if (cell[i].is_used || !cell[i].is_edge[LEFT]) continue;
            int score = calc(cell[answer[p-1][0]].edge[BOTTOM], cell[i].edge[TOP]);
            if (score > best_score) best = i,  best_score = score;
        }
        answer[p][0] = best;
        cell[best].is_used = true;
    }

    // right 엣지
    for (int p = 1 ; p < 15 ; p++){
        int best = -1, best_score = -1;
        for (int i = 0 ; i < 256; ++i){
            if (cell[i].is_used || !cell[i].is_edge[RIGHT]) continue;
            int score = calc(cell[answer[p-1][15]].edge[BOTTOM], cell[i].edge[TOP]);
            if (score > best_score) best = i,  best_score = score;
        }
        answer[p][15] = best;
        cell[best].is_used = true;
    }

    // inner
    for (int y = 1 ; y < 15; ++y){
        for (int x = 1 ; x < 15 ; ++x){
            int best = -1, best_score = -1;
            for (int i = 0 ; i < 256; ++i){
                if (cell[i].is_used) continue;
                int score = 
                    calc(cell[answer[y-1][x]].edge[BOTTOM], cell[i].edge[TOP]) +
                    calc(cell[answer[y][x-1]].edge[RIGHT], cell[i].edge[LEFT]);
                if (score > best_score) best = i ,  best_score = score;
            }
            answer[y][x] = best;
            cell[best].is_used = true;
        }
    }

    // copy
    for (int y = 0 ; y < 16 ; ++y)
        for (int x = 0 ; x < 16 ; ++x){
            int dy = y * 256, dx = x * 256, c = answer[y][x];
            for (int yy = 0 ; yy < 256 ; ++yy)
                for (int xx = 0 ; xx < 256 ; ++xx)
                    map[dy+yy][dx+xx] = cell[c].map[yy][xx];
        }

}

void test2(unsigned char map[4096][4096], unsigned char orgmap[4096][4096]){
    test(map);
	// 복사한 문제

    // correctless 확인
    int DEBUG = 0;
    if (DEBUG){
        for (int y = 0 ; y < 16 ; ++y){
            for (int x = 0 ; x < 16 ; ++x)
                printf ("%c", debug_is_same(y,x,map,orgmap)? 'O' : 'X' );
            printf("\n");
        }
        printf("\n\n");
    }
    /*
    */
}


