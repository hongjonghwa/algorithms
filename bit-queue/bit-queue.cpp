#include "assert.h"
#include "stdio.h"


int MAX_VALUE_PER_LEN[17] = {
	1, // 0
	2,4,8,16,32,64,128,256, // 1~8
	512,1024,2048,4096,8192, 16384, 32768, 65536
};

void report (unsigned char data[1024]){
	for (int i = 0 ; i < 5; ++i){
		for (int j = 7 ; j >= 0 ; --j){
			if (data[i] & (1<<j)) printf("1");
			else printf("0");
		}
		if (i % 8 == 7) printf("\n");
		else printf(" ");
	}
	printf("\n");
}

void enque(unsigned char data[1024], unsigned int offset, unsigned int len, unsigned int val) {
	assert(val < MAX_VALUE_PER_LEN[len]);
	printf("enque ==> %d,%d,%d\t", offset,len,val); // debug

	for ( ; len > 0 ; --len, ++offset){
		int pos = offset / 8;
		int bpos = 7 - ( offset % 8 );
		if (val & ( 1 << (len - 1)))
			data[pos] |= (1 << bpos); // set
		else
			data[pos] &= ~(1 << bpos); // unset
	}

	report(data); // debug
	return;
}

unsigned int deque(unsigned char data[1024], unsigned int offset, unsigned int len) {
	printf("deque ==> %d,%d => ", offset,len); // debug

	unsigned int ret = 0;
	for ( ; len > 0 ; --len, ++offset){
		ret *= 2;
		int pos = offset / 8;
		int bpos = 7 - ( offset % 8 );
		if (data[pos] & (1 << bpos)) ret += 1;
	}

	printf("%d\n", ret);  // debug
	return ret;
}

int X[5][2] = { 
	{5,23},
	{7,100},
	{14,10000},
	{5,21},
	{8,200}
};
int X_LEN = 5;

int main(){
	unsigned char data[1024];
	for (int i = 0; i < 1024; ++i) data[i] = 0;

	int offset;
	offset = 0;
	
	for (int i = 0; i < X_LEN; ++i) {
		enque(data, offset, X[i][0], X[i][1]);
		offset += X[i][0];	
		
	}
	printf("\n");

	for (int loop = 0 ; loop < 2 ; ++loop){ // 2회 반복
		offset = 0;
		for (int i = 0; i < X_LEN; ++i) {
			unsigned int r = deque(data, offset, X[i][0]);
			offset += X[i][0];
			assert(r == X[i][1]);
		}
		printf("\n");
	}


}
