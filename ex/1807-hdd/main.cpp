#include<stdio.h>
#include<time.h>
#include<string.h>
#include<assert.h>

template<class T>
inline T min2(T a, T b) {
	return a < b ? a : b;
}

#define NAIVE_DEBUG 1

int SEED = 1981;
int fastrand() {
	SEED = SEED * 214013 + 2531011;
	return (SEED >> 16) & 0x7fff;
}

// verify
char *verify_data[100];
int verify_len[100];

// data
char hdd[16][1024][1024]; // 16 메가
char _filename[100][16];
int _filesize[100];
int total_size = 0;
int cur_disk = -1;

extern void hdd_write(char *file, int offset, int size, char data[4096]);
extern void hdd_delete(char *file, int offset, int size);
extern void hdd_read(char *file, int offset, int size, char data[4096]);

extern void init();
extern void debug_stage_end();

void verify_clean() {
	for (int i = 0; i < 100; ++i) verify_len[i] = 0;
	for (int i = 0; i < 100; ++i) {
		if (verify_data[i]) delete verify_data[i];
		verify_data[i] = 0;
	}
}
void verify_add(int fno, int offset, int size, char data[4096]) {
	int oldsize = verify_len[fno];
	if (oldsize == 0) {
		assert(offset == 0);
		if (verify_data[fno]) delete verify_data[fno];
		verify_data[fno] = new char[size];
		memcpy(verify_data[fno], data, size);
		verify_len[fno] = size;
		return;
	}

	int newsize = oldsize + size;
	char *t = new char[newsize];
	if (offset > 0) memcpy(t, verify_data[fno], offset);
	memcpy(t + offset, data, size);
	if (offset < oldsize) memcpy(t + offset + size, verify_data[fno] + offset, oldsize - offset);

	delete verify_data[fno];
	verify_data[fno] = t;
	verify_len[fno] = newsize;
}
void verify_remove(int fno, int offset, int size) {
	int oldsize = verify_len[fno];
	assert(oldsize >= offset + size);
	int newsize = oldsize - size;
	if (newsize == 0) {
		if (verify_data[fno]) delete verify_data[fno];
		verify_data[fno] = 0;
		verify_len[fno] = 0;
		return;
	}

	char *t = new char[newsize];
	if (offset > 0) memcpy(t, verify_data[fno], offset);
	if (offset  + size < oldsize) memcpy(t + offset, verify_data[fno] + offset + size, oldsize - offset - size);

	delete verify_data[fno];
	verify_data[fno] = t;
	verify_len[fno] = newsize;
}
void verify_read(int fno, int offset, int size, char data[4096]) {
	memcpy(data, verify_data[fno] + offset, size);
}
void verify_check(int fno, int offset, int size) {
	// printf("Verify %d %d %d ", fno, offset, size);
	char data1[4096], data2[4096];

	hdd_read(_filename[fno], offset, size, data1);
	verify_read(fno, offset, size, data2);

	int cmp = memcmp(data1, data2, size);
	assert(cmp == 0);
}

void change_disk(int i) {
	cur_disk = i;
}
void read_sector(int i, char data[1024]) {
	memcpy(data, hdd[cur_disk][i], 1024);
}
void write_sector(int i, char data[1024]) {
	memcpy(hdd[cur_disk][i], data, 1024);
}

void _build() {
	total_size = 0;
	for (int i = 0; i < 100; ++i)
		for (int j = 0; j < 16; ++j)
			_filename[i][j] = fastrand() % 26 + 'a';
	for (int i = 0; i < 100; ++i) _filesize[i] = 0;

	init();
	if (NAIVE_DEBUG) verify_clean();
}

void _remove() {
	int fileno = fastrand() % 100; // 0 ~ 99
	if (_filesize[fileno] == 0) return;

	int offset = fastrand() % (_filesize[fileno]);  // 0  <=  ...  <  _filesize
	int size = fastrand() % 4096 + 1; // 1 ~ 4096
	if (offset + size > _filesize[fileno]) size = _filesize[fileno] - offset;

	hdd_delete(_filename[fileno], offset, size);
	_filesize[fileno] -= size;
	total_size -= size;

	if (NAIVE_DEBUG) {
		if (_filesize[fileno] > 0) {
			verify_remove(fileno, offset, size);

			// after verify;
			if (offset > 100) offset -= 100;
			int check_size = min2(_filesize[fileno] - offset, 4096);

			//printf("rem V fno: %d offset: %d size:%d check_size: %d file_size: %d \n", fileno, offset, size, check_size, _filesize[fileno]);
			verify_check(fileno, offset, check_size);
		}
	}
}
void _add() {
	int fileno = fastrand() % 100; // 0 ~ 99
	int offset = fastrand() % (_filesize[fileno] + 1);  //  0 <= .. <= _filesize
	int size = fastrand() % 4096 + 1; // 1 ~ 4096

	// offset = 0; // no random 맨 처음만
	// offset = _filesize[fileno]; // no random 맨 끝만

	char data[4096];
	for (int i = 0; i < size; ++i) data[i] = fastrand() % 256; // random
	// for (int i = 0; i < size; ++i) data[i] = i % 256; // series (debugging 용)

	hdd_write(_filename[fileno], offset, size, data);
	_filesize[fileno] += size;
	total_size += size;

	if (NAIVE_DEBUG) {
		verify_add(fileno, offset, size, data);
		// after verify;

		if (offset > 100) offset -= 100;
		int check_size = min2(_filesize[fileno] - offset, 4096);
		 
		//printf("add V fno:%d offset:%d check_size:%d file_size:%d \n", fileno, offset, check_size, _filesize[fileno]);
		//verify_check(fileno, offset, size);
	}
}



void _read() {
	int fileno = fastrand() % 100; // 0 ~ 99
	int offset = fastrand() % (_filesize[fileno] + 1);  //  0 <= .. <= _filesize
	int size = fastrand() % 4096 + 1; // 1 ~ 4096

	if (offset + size > _filesize[fileno]) size = _filesize[fileno] - offset;
	if (size == 0) return;
	verify_check(fileno, offset, size);

}

int main() {
	long long int clk = clock();
	for (int t = 0; t < 10; ++t) {
		_build();
		printf("RUN #%d \n", t);
		while (total_size < 10 * 1024 * 1024  * 100/100) {
			int r = fastrand() % 5;
			if (r == 0)  _remove();
			else _add();
			//printf(" Round= %d %d %d \n", r, total_size, t);
		}

		if (NAIVE_DEBUG) {
			for (int i = 0; i < 10000 ; ++i) _read();
			
			// verify all
			for (int i = 0; i < 100; ++i) {
				int filelen = _filesize[i];
				int offset = 0;
				while (offset < filelen) {
					verify_check(i, offset, min2(4096, filelen - offset));
					offset += 4096;
				}
			}
		}

		debug_stage_end();
		// break;
	}
	printf("Time executed : %f \n", ((double)clock() - clk) / CLOCKS_PER_SEC);
	// Time executed : 2.341000 do nothing!
	// 3.140 naive , 0.664 no naive --> 데이터가 랜덤이 아닐때 
	// 5.884 naive , 3.396 no naive --> 데이터 랜덤(시간을 가장 많이 소요)

	// HANG!
	// for (int i = 0; i < 10000 * 10000; ++i) for (int j = 0; i < 10000 * 10000; ++j) int k = i * j;
} 
