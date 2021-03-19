#include<stdio.h>
#include<time.h>
#include<string.h>

#include"solution.cpp"
typedef long long int lint;
static int seed = 1234567891;
//static int seed = 1;
//static int seed = 31;
//static int seed = 251; // 2 error by 250 
//static int seed = 32; // 4 error by 250
inline int fastrand(){
    seed = 214013*seed + 2531011;
	return (seed>>16) & 0x7FFF;
}

static char hdd[65536][512]; // 32M HDD
static char dummy1[100000];
static char filedata[100][65536]; // 0으로 초기화되어있다!
static char dummy2[100000];
static char filename[100][32];
static char dummy3[100000];
static int filesize[100];

void hdd_read(int s, char data[512]){
	memcpy(data, hdd[s], 512);
}
void hdd_write(int s, char data[512]){
	memcpy(hdd[s], data, 512);
}

void _file_write(int file, int size, int pos, char data[4096]){
    if (pos+size > 65536) size = 65536 - pos;
    if (pos+size > filesize[file]) filesize[file] = pos + size;
    memcpy(filedata[file]+pos, data, size);
}
void _file_read(int file, int size, int pos,  char data[4096]){
    if (size > filesize[file]) size = filesize[file];
    if (size + pos > filesize[file]) pos = filesize[file] - size;
    memcpy(data, filedata[file] + pos, size);
}

extern void file_read(char filename[32],int size, int pos, char data[4096]);
extern void file_write(char filename[32], int size, int pos, char data[4096]);

int main(){
    for (int i = 0 ; i < 100 ; ++i){
        int len = fastrand() % 32 + 1;
        for (int j = 0 ; j < len ; ++j) filename[i][j] = 'A' + fastrand() % 26;
        filesize[i] = 0;
		filename[i][len] = 0;
    }
    //for (int i = 0 ; i < 100 ; ++i) printf("%i %s \n", i, filename[i]);
    
    long long int clk = clock();
    int score = 0;
    char data[4096], data2[4096];
    for (register int i = 0 ; i < 25000/1 ; ++i){
        int mode = i < 5000 ? 10 : fastrand() % 10;
        int file = fastrand() % 100;
        int size = fastrand() % 4096 + 1;
        //int pos = rand() % 65536;
        int pos = ((fastrand() << 15) + fastrand()) % 65536;

        if (mode >= 8){ // write; / 20%
            memset(data,0,sizeof(data));
            for (int i = 0 ; i < size ; ++i) data[i] = fastrand() % 256;
            _file_write(file, size, pos, data);
            file_write(filename[file], size, pos,data);
        }else{
            _file_read(file, size, pos, data);
            file_read(filename[file],size, pos,data2);
            if( memcmp(data, data2, size) != 0 ) {
				score += 10000;
				printf("fail loop:%d , file:%d, pos:%d, size:%d \n", i, file, pos, size );
			}
            
        }

        /* HDD 노이즈 */
        for (int j = 0 ; j < 20/1 ; ++j){
            /* 
             * 연산 우선 순위가 bit-shift가 +, - 보다 낮다
             * 한마디로 << >> 는 엄청 낮다
             * */
            int pos = ((fastrand() << 15) + fastrand()) % 65536;
            int b = fastrand()%512;
            int n = fastrand()%256;
            hdd[pos][b] = n;
            //printf("%5d   %3d   %3d \n", pos, b, n);
        }
    }
    lint duration = clock() - clk;
    //score += duration;
    printf("executed time is %f\n", (double)(duration)/CLOCKS_PER_SEC);
    printf("score is %d\n", score);
    
    return 0;
}
