/* 
 * 개선점 : 헤더는 중요하다, 4개가 아니라 10개 저장해야함
 */
#include<stdio.h>
#include<assert.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define OFFSET 1000
// 250 정도가 안전
#define OPTIMIZE_CNT 500
#define F_DUP 4


extern void hdd_read(int s, char data[512]);
extern void hdd_write(int s, char data[512]);

// not used
char most_char4(char *d){
    if (d[0] == d[1] || d[0] == d[2] || d[0] == d[3]) return d[0];
    if (d[1] == d[2] || d[1] == d[3]) return d[1];
    return d[2];
}


void hdd_read2(int s, char data[256], int dup){
	char h[512];
	hdd_read(s,h);
    int l = 512/dup;

    if (dup == 3){
        for (int i = 0 ; i < l ; ++i){
            int o = i * dup;
            int candidate;
            if (h[o] == h[o+1] || h[o] == h[o+2]) candidate = h[o];
            else candidate = h[o+1];
            data[i] = candidate;
        }
    }else if (dup == 4){
        for (int i = 0 ; i < l ; ++i){
            int o = i * dup;
            //data[i] = most_char4(h+o); // 여기서 함수 호출하면 속도 저하가 큼

            int candidate;
            if (h[o] == h[o+1] || h[o] == h[o+2] || h[o] == h[o+3]) candidate = h[o];
            else if (h[o+1] == h[o+2] || h[o+1] == h[o+3]) candidate = h[o+1];
            else candidate = h[o+2];

            data[i] = candidate;
        }
    }else if (dup == 5){
        for (int i = 0 ; i < l ; ++i){
            int o = i * dup;
            int candidate = h[o], count = 1;
            for (int c = 1; c < dup ; ++c){
                if (count == 0){
                    candidate = h[o+c];
                    count = 1;
                }else if (candidate == h[o+c]) count++;
                else count--;
            }

            int t = 0;
            for (int c = 0 ; c < dup ; ++c)
                if (h[o+c] == candidate)
                    ++t;
            // faster!
            if (t * 2 < dup){ // 50% 미만
                if (h[o] == h[o+1] || h[o] == h[o+2] || h[o] == h[o+3] || h[o] == h[o+4]) candidate = h[o];
                else if (h[o+1] == h[o+2] || h[o+1] == h[o+3] || h[o+1] == h[o+4]) candidate = h[o+1];
                else if (h[o+2] == h[o+3] || h[o+2] == h[o+4]) candidate = h[o+2];
                else candidate = h[o+3];
            }
            data[i] = candidate;
        }
    }else{
        // 5 >
        for (int i = 0 ; i < l ; ++i){
            int o = i * dup;
            int candidate = h[o], count = 1;
            for (int c = 1; c < dup ; ++c){
                if (count == 0){
                    candidate = h[o+c];
                    count = 1;
                }else if (candidate == h[o+c]) count++;
                else count--;
            }

            int t = 0;
            for (int c = 0 ; c < dup ; ++c)
                if (h[o+c] == candidate)
                    ++t;

            if (t * 2 < dup){ // 50% 미만
                int best = 1;
                for (int c = 0; c < dup; ++c){
                    int t = 0;
                    for (int d = 0 ; d < dup; ++d) if (h[o+c] == h[o+d]) t++;
                    if (t > best) {
                        candidate = h[o+c];
                        best = t;
                    }
                }
            }
            data[i] = candidate;
        }
    }


}
void hdd_write2(int s, char data[256], int dup){
	char h[512];
    int l = 512/dup;
	for (int i = 0 ; i < l ; ++i){
        int o = i * dup;
        for (int j = 0 ; j < dup ; ++j){
            h[o+j] = data[i];
        }
    }
	hdd_write(s,h);
}


int hash(char* c){
	int ret = 0;
	for (int i = 0 ; i < 32; ++i)
		ret = ret*31+(c[i]-'A');
	return ret;
}

int header_status(int h[256], int fh, int extendSize, int &refSize){
    int HDUP = 4; // 헤더 중복수 
    int RSEC = 512/4/ HDUP; // 필요 섹터수

	for (int i = 0 ; i < RSEC; ++i)
		hdd_read2(i,(char*)(h+RSEC*i), HDUP);
	int &loop = h[0]; // alias
	int &filecnt = h[1];
	int *filehash = &h[2];
	int *filesize = &h[102];

	int ret = -1;
	for (int i = 0 ; i < filecnt ; ++i){
		if (fh == filehash[i]){
			ret = i;
			break;
		}
	}
	if (ret == -1){
		filehash[filecnt] = fh;
		ret = filecnt;
		filecnt++;
	}
	if (filesize[ret] < extendSize) filesize[ret] = extendSize;
	refSize = filesize[ret];

	loop++;
	//printf("Loop : %d \n", loop);
	//printf ("R : "); for (int i = 0 ; i < 10; ++i) printf("%d ", h[i]); printf ("\n");
	for (int i = 0 ; i < RSEC; ++i)
		hdd_write2(i,(char*)(h+RSEC*i), HDUP);


	char tmp[256];
	if (loop % OPTIMIZE_CNT == 0){

        int dup = F_DUP;
        int l = 512/dup;
        int fof = (65535+l) / l; // file 간 sector 간격 

		for (int f = 0 ; f < filecnt ; ++f){
            if (filesize[f] == 0) continue;
            int e = 512;
			for (int i = 0 ; i < e ; ++i){
				hdd_read2(i + f*fof + OFFSET, tmp, dup);
				hdd_write2(i + f*fof + OFFSET, tmp, dup);
			}
		}
	}
	return ret;
	
}

//pos 64K-1, size 4K
//64K 저장하는데 512 sector 필요(sec 당 128byte 저장)
void file_read(char filename[32],int size, int pos, char data[4096]){
	int h[256];
	int fh = hash(filename);
	int filesize; 


	int fno = header_status(h, fh, size, filesize);
	assert(fno<100);
	//printf("1 %s, %d,  %d %d  \n", filename, fh, size, pos);
	//printf("1 %d, %d %d  \n", fno, size, pos);
    //
	char temp[4400];
	if (size + pos > 65536) pos = 65536 - size;
	if (size + pos > filesize) pos = filesize - size;

    int dup = F_DUP;
    int l = 512/dup;
    int fof = (65535+l) / l; // file 간 sector 간격 

	int sec_start = pos / l;
	int sec_end = (pos + size - 1) / l;

	//printf("1  fno %d, pos %d, size %d, s %d, e %d \n", fno, pos, size, sec_start, sec_end);
	for (int i = sec_start, k = 0 ; i <= sec_end ; ++i, ++k){
        int spos = fno * fof + OFFSET + i;
		hdd_read2(spos, temp + (k * l), dup);
    }

    // offset 시프트 
    int offset = pos % l; 
    for (int i = 0 ; i < size ; ++i) data[i] = temp[i+offset]; // 직접 넣으면 불필요한데, 넘치는것은??
} 
void file_write(char filename[32], int size, int pos, char data[4096]){
	int h[256];
	int fh = hash(filename);
	int filesize; 
	if (pos+size > 65536) size = 65536 - pos;
	int fno = header_status(h, fh, pos+size, filesize);
	assert(fno<100);
	//printf("2 %s, %d, %d, %d %d  \n", filename, fh, fno, size, pos);
	//printf("2 %d, %d %d  \n", fno, size, pos);
	char temp[4400];

    int dup = F_DUP;
    int l = 512/dup;
    int fof = (65535+l) / l;

	int sec_start = pos / l;
	int sec_end = (pos + size - 1) / l;

	int offset = pos % l;

	//printf("2  fno %d, pos %d, size %d, s %d, e %d \n", fno, pos, size, sec_start, sec_end);
	hdd_read2(sec_start + fno*fof + OFFSET ,temp, dup);	
	if (sec_start != sec_end) hdd_read2(sec_end + fno*fof + OFFSET, &temp[(sec_end-sec_start)*l], dup);

	for (int i = 0 ; i < size ; ++i) temp[i+offset] = data[i];

	for (int i = sec_start, k = 0 ; i <= sec_end ; ++i, ++k){
		hdd_write2(i + fno*fof + OFFSET,&temp[k*l], dup);	
	}

}
