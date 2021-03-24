#include<stdio.h>
#include<time.h>
#include<string.h>
#include"solution.cpp"
typedef long long int lint;
// static int seed = 1234567891;
static int seed = 1;
int frand(){
	seed = seed * 10007 + 33333331;
	return seed & 0x3FFF;

}

static char hdd[65536][512]; // 32M HDD
static char filedata[100][65536];
static char filename[100][32];
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
        int len = frand() % 32 + 1;
        for (int j = 0 ; j < len ; ++j) filename[i][j] = 'A' + frand() % 26;
        filesize[i] = 0;
    }
    
    long long int clk = clock();
    int score = 0;
    char data[4096], data2[4096];
    for (register int i = 0 ; i < 25000 ; ++i){
        int mode = i < 5000 ? 10 : frand() % 10;
        int file = frand() % 100;
        int size = frand() % 4096 + 1;
        int pos = ((frand() << 10) + frand()) % 65536;
        if (i < 30){
            //printf ("%d %d %d %d \n", mode, file, size, pos);
        }
        if (mode >= 9){ // write;
            memset(data,0,sizeof(data));
            for (int i = 0 ; i < size ; ++i) data[i] = frand() % 256;
            _file_write(file, size, pos, data);
            file_write(filename[file], size, pos,data);
        }else{
            _file_read(file, size, pos, data);
            file_read(filename[file],size, pos,data2);
            if( memcmp(data, data2, size) != 0 ) score += 10000;
            
        }
        for (int j = 0 ; j < 20 ; ++j){
            int p = ((frand() << 14) + frand()) % (65536 * 512);
            //if (i <= 1) printf("error : %d \n", p);
            hdd[p/512][p%512] = frand() % 256;
        }
    }
    lint duration = clock() - clk;
    //score += duration;
    printf("executed time is %f\n", (double)(duration)/CLOCKS_PER_SEC);
    printf("score is %d\n", score);
    
}
