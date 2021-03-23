#include<stdio.h>
#include<string.h>
#include<time.h>
void test(unsigned char map[4096][4096]);
void test2(unsigned char map[4096][4096], unsigned char orgmap[4096][4096]);

unsigned char orgmap[4096][4096];
unsigned char map[4096][4096];

unsigned char xoverlay[4096][4096];
unsigned char yoverlay[4096][4096];
unsigned char dummy[4096];
unsigned char dummy2[256];


static unsigned int SEED;
inline void srand(int seed) {
    SEED = seed;
}
inline int rand(void) {
    SEED = (214013*SEED+2531011);
    return (SEED>>16)&0x7FFF;
}


bool checkline(int y1, int x1, int y2, int x2){
	if (y2-y1 < 16 || x2-x1 < 16) return false;
	if ( memcmp (&xoverlay[y1][x1], dummy, x2-x1+1) != 0 ) return false;
	if ( memcmp (&xoverlay[y2][x1], dummy, x2-x1+1) != 0 ) return false;
	if ( memcmp (&yoverlay[x1][y1], dummy, y2-y1+1) != 0 ) return false;
	if ( memcmp (&yoverlay[x2][y1], dummy, y2-y1+1) != 0 ) return false;	
	
	return true;
}
void drawline(int y1, int x1, int y2, int x2, int c){
	memset(&xoverlay[y1][x1], 1, x2-x1+1);
	memset(&xoverlay[y2][x1], 1, x2-x1+1);
	memset(&yoverlay[x1][y1], 1, y2-y1+1);
	memset(&yoverlay[x2][y1], 1, y2-y1+1);
	
	
	memset(&map[y1][x1], c, x2-x1+1);
	memset(&map[y2][x1], c, x2-x1+1);
	for (int y = y1 + 1 ; y < y2 ; ++y){
		map[y][x1] = map[y][x2] = c;
	}
}


void build(){
	memset(map, 0, 16777216);
	memset(xoverlay, 0, 16777216);
	memset(yoverlay, 0, 16777216);
	memset(dummy, 0, 4096);
	
	
	//for (int i = 0 ; i  < 1024 ; ++i){
	int y1, x1, y2, x2, t;
	for (int i = 0 ; i  < 1024 ; ++i){
		
		while (true){
			y1 = rand() % 4064 + 16;
			x1 = rand() % 4064 + 16;
			y2 = rand() % 4064 + 16;
			x2 = rand() % 4064 + 16;

			if (y1 > y2) { 
				t = y1; 
				y1 = y2; 
				y2 = t;
			}
			if (x1 > x2) { 
				t = x1; 
				x1 = x2; 
				x2 = t;
			}
			
			if ( checkline( y1, x1, y2, x2 ) ){
				int c = rand() % 256 + 1 ;
				drawline( y1, x1, y2, x2, c ) ;
				break;
			}
		}
	}
	
	memcpy(orgmap, map, 16777216);

	// shuffle
	for (int i = 0 ; i < 1024 ; ++i){
		int y1 = rand() % 16;
		int x1 = rand() % 16;
		int y2 = rand() % 16;
		int x2 = rand() % 16;
		for (int l = 0 ; l < 256; ++l){
			memcpy(dummy2, &map[y1*256+l][x1*256], 256);
			memcpy(&map[y1*256+l][x1*256], &map[y2*256+l][x2*256], 256);
			memcpy(&map[y2*256+l][x2*256], dummy2, 256);
		}
	}

	/*
	
	for (int i = 0 ; i < 256 ; ++i){
		switching two cell
	}
	*/
}

int main(){
	srand(0);
	int ret = 0;
	int success = 0, fail = 0;
	for (int t = 0 ; t < 10 ; ++t){
		build();
		
		long clk = clock();
		test2(map, orgmap);
		ret += (clock()-clk) / (CLOCKS_PER_SEC/1000);
		
		if (memcmp(map, orgmap, 16777216) != 0){
			ret += 10000;
			fail++;
		}else{
			success++;
		}
		//break;
	}
	
	printf("Score : %d\n", ret);
	printf("%d / %d (success / try)\n", success, success + fail);
	
}
