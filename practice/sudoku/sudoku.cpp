#include<assert.h>
#include<stdio.h>

/*int grid[9][9] = {
	{4, 8, 3, 9, 2, 1, 6, 5, 7},
	{9, 6, 7, 3, 4, 5, 8, 2, 1},
	{2, 5, 1, 8, 7, 6, 4, 9, 3},
	{5, 4, 8, 1, 3, 2, 9, 7, 6},
	{7, 2, 9, 5, 6, 4, 1, 3, 8},
	{1, 3, 6, 7, 9, 8, 2, 4, 5},
	{3, 7, 2, 6, 8, 9, 5, 1, 4},
	{8, 1, 4, 2, 5, 3, 7, 6, 9},
	{6, 9, 5, 4, 1, 7, 3, 8, 2}
};*/

/*
// easy
int grid[9][9] = {
	{4,0,0,0,0,0,8,0,5},
	{0,3,0,0,0,0,0,0,0},
	{0,0,0,7,0,0,0,0,0},
	{0,2,0,0,0,0,0,6,0},
	{0,0,0,0,8,0,4,0,0},
	{0,0,0,0,1,0,0,0,0},
	{0,0,0,6,0,3,0,7,0},
	{5,0,0,2,0,0,0,0,0},
	{1,0,4,0,0,0,0,0,0}
};
*/

// impossible 
/*int grid[9][9] = {
	{0,0,0,0,0,5,0,8,0},
	{0,0,0,6,0,1,0,4,3},
	{0,0,0,0,0,0,0,0,0},
	{0,1,0,5,0,0,0,0,0},
	{0,0,0,1,0,6,0,0,0},
	{3,0,0,0,0,0,0,0,5},
	{5,3,0,0,0,0,0,6,1},
	{0,0,0,0,0,0,0,0,4},
	{0,0,0,0,0,0,0,0,0}
};*/

// hard 
int grid[9][9] = {
	{0,0,0,0,0,6,0,0,0},
	{0,5,9,0,0,0,0,0,8},
	{2,0,0,0,0,8,0,0,0},
	{0,4,5,0,0,0,0,0,0},
	{0,0,3,0,0,0,0,0,0},
	{0,0,6,0,0,3,0,5,4},
	{0,0,0,3,2,5,0,0,6},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0}
};

int suggest[9][9];
int debug_loop = 0;
int BitSize[1025];

inline int bitSize(int i){
	//return __builtin_popcount(i);
	return BitSize[i];
}

inline void bitSet(int &i, int val ){
	i |= (1 << val);
}
inline void bitUnset(int &i, int val ){
	i &= ~(1 << val);
}
inline int bitGet(int i, int val ){
	return i & ( 1 << val);
}

void reportGrid(){
	for (int y = 0 ; y < 9 ; ++y){		
		if (y % 3 == 0) printf("+---+---+---+\n");
		printf("|");
		for (int x = 0 ; x < 9 ; ++x){
			if (grid[y][x])printf("%d", grid[y][x]);
			else printf(" ");
			if (x % 3 == 2) printf("|");
		}
		printf("\n");
		
	}
	printf("+---+---+---+\n");
}
void reportSuggest(){
	for (int y = 0 ; y < 9 ; ++y){		
		if (y % 3 == 0) printf("+---+---+---+\n");
		printf("|");
		for (int x = 0 ; x < 9 ; ++x){
			for (int i = 1 ; i <= 9 ; ++i)
				if (bitGet(suggest[y][x], i))
					printf("%d", i);
				else printf(" ");
			printf("\t");
			if (x % 3 == 2) printf("|");
		}
		printf("\n");
		
	}
	printf("+---+---+---+\n");
}




int unitlist[27][9][2];
void makeUnitlist();
void testUnitlist(int no);
int peerUnit[9][9][3];
void makeSuggest();


void makePeerunit(){
	int cnt[9][9];
	for (int i = 0 ; i < 9 ; ++i)
		for (int j = 0 ; j < 9 ; ++j)
			cnt[i][j] = 0;
	for (int i = 0 ; i < 27 ; ++i){
		for (int j = 0; j < 9 ; ++j){
			int x = unitlist[i][j][0];
			int y = unitlist[i][j][1];
			peerUnit[y][x][ cnt[y][x]++ ] = i;
		}
	}
	for (int i = 0 ; i < 9 ; ++i)
		for (int j = 0 ; j < 9 ; ++j)
			assert(cnt[i][j] == 3);
}

void assign(int y, int x, int val){
	grid[y][x] = val;
	for (int i = 0 ; i < 3 ; ++i){
		int hintNo = peerUnit[y][x][i];
		for (int j = 0 ; j < 9 ; ++j){
			int yy = unitlist[hintNo][j][1];
			int xx = unitlist[hintNo][j][0];
			bitUnset(suggest[yy][xx], val);
		}
	}

}

bool search(){
	debug_loop ++;
	int y = -1, x = -1, suggestCnt = 999;
	int debug_emptyCnt = 0;
	 // 경우의 수가 적은 것 부터 
	for (int i = 0 ; i < 9 ; ++i){
		for (int j = 0 ; j < 9 ; ++j){
			//printf("check : %d %d %d %d\n", y,x,suggest[i][j], bitSize(suggest[i][j]));
			int tmpCnt = bitSize(suggest[i][j]);
			if ( !grid[i][j] ) debug_emptyCnt ++;
			if ( !grid[i][j] && tmpCnt < suggestCnt ){
				y = i;
				x = j;
				suggestCnt = tmpCnt;
			}
		}
	}
	if (y == -1){
		printf ("Finished !!!!!!!!\n");
		return true;
		// finish
	}
	//printf("next : %d %d %d           undefined %d \n", y,x,suggestCnt, debug_emptyCnt);

	int suggestBak = suggest[y][x];
	int flag = false;
	for (int i = 1 ; i <= 9 ; ++i){
		if (bitGet(suggestBak, i)){
			grid[y][x] = i;
			makeSuggest();
			//reportGrid();reportSuggest();
			if (search()) return true;
			grid[y][x] = 0;
		}
	}

	return false;
}
void makeBitSize(int idx, int pick, int curVal){
	if (idx == 10){
		BitSize[curVal] = pick;
		//printf("BitSize %d : %d \n", curVal, pick);
		return;
	}
	makeBitSize(idx+1,pick,curVal);
	makeBitSize(idx+1,pick+1,curVal + (1<<idx));
}


int main(){
	makeBitSize(1,0,0);
	makeUnitlist();
	makePeerunit();
	makeSuggest();


	reportGrid();
	//reportSuggest();
	search();
	printf("debug_loop : %d \n", debug_loop);

	reportGrid();
	//reportSuggest();

/*	printf("suggest %d, %d : %d\n" , 0,0,suggest[0][0]);
	printf("suggest %d, %d : %d\n" , 8,8,suggest[8][8]);
*/
/*	for (int i = 18 ; i < 27 ; ++i)
		testUnitlist(i);
*/
/*	int y,x;
	y = 3; x = 4;
	for (int i = 0 ; i < 3 ; ++i){
		printf("hint %d : \n ", peerUnit[y][x][i]);
		testUnitlist(peerUnit[y][x][i]);
	}
*/
/*	x = 0;
	for (int i = 1 ; i <= 9 ; ++i)
		bitSet(x,i);
	for (int i = 1 ; i <= 9 ; ++i){
		printf("get %d : %d \n" , i, bitGet(x,i));

		assert(bitGet(x,i) != 0);
	}
	printf("allset : %d \n" , x);
*/


	return 0;

}





void makeUnitlist(){
	for (int i = 0 ; i < 9 ; i++){
		for (int j = 0 ; j < 9 ; j++){
			unitlist[i][j][0] = i;
			unitlist[i][j][1] = j;		
		}
		for (int j = 0 ; j < 9 ; j++){
			unitlist[i+9][j][0] = j;
			unitlist[i+9][j][1] = i;		
		}
	}
	for (int i = 0 ; i < 9 ; ++i){
		for (int j = 0 ; j < 9 ; ++j){
			unitlist[i+18][j][0] = j % 3 + 3 * (i%3);
			unitlist[i+18][j][1] = j / 3 + 3 * (i/3);
		}
	}
}
void testUnitlist(int no){
	printf ("Unitlist %d  :", no);
	for (int i = 0; i < 9 ; ++i )
		printf(" (%d,%d)", unitlist[no][i][0], unitlist[no][i][1] );
	printf ("\n");


}

void makeSuggest(){
	for (int i =  0 ; i < 9 ; ++i) for (int j = 0 ; j < 9 ; ++j) suggest[i][j] = 1022;

	for (int i = 0 ; i < 9 ; i++){
		for (int j = 0 ; j < 9 ; j++){
			if (grid[i][j]){
				assign (i,j,grid[i][j]);
			}
		}

	}

}