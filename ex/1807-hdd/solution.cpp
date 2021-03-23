#include<stdio.h>
#include<assert.h>
#define DEBUG 0
/* user 영역 메모리 제한 40 M */
template <class T>
inline T min2(T a, T b) {
	if (a < b) return a;
	return b;
}

// 16 * 1024 => 16384
extern void change_disk(int i);
extern void read_sector(int i, char data[1024]);
extern void write_sector(int i, char data[1024]);

inline void read(int sector, char data[1024]) {
	change_disk(sector / 1024);
	read_sector(sector % 1024, data);
}
inline void write(int sector, char data[1024]) {
	change_disk(sector / 1024);
	write_sector(sector % 1024, data);
}
int hash(char *filename) {
	int ret = 0;
	for (int i = 0; i < 16; ++i)
		ret = ret * 31 + (filename[i] - 'a');
	return ret;
}

struct SectorInfo { // 128K
	int size;
	int nextno;
    // 사용 여부는 size==0, nextno==-1 로 확인, 마지막 노드가 size 가 0이 되면 자동으로 빠짐
} sinfo[16384];
int sinfo_idx = 0;

int headno[100];
char filename[100][16];
int filename_idx;
int filehash[100]; // 해시로 저장하면 속도가 빨라질까?

int debug_w_cnt, debug_r_cnt, debug_d_cnt;

void optimize() {
	int debug_merge_cnt = 0;

	for (int f = 0; f < 100; ++f) {
		int c = headno[f]; // current
		if (c == -1) continue;
		int n; // next

		while (c != -1 && (n = sinfo[c].nextno) != -1) {
			if (sinfo[c].size + sinfo[n].size <= 1024) { // n을 날린다
				char d[2048];

				read(c, d);
				read(n, d + sinfo[c].size);
				write(c, d);
				sinfo[c].nextno = sinfo[n].nextno;
				sinfo[c].size += sinfo[n].size;
				sinfo[n].nextno = -1;
				sinfo[n].size = 0;

				debug_merge_cnt++;
			}
			else { // 1024 보다 크면, 다음으로 넘긴다.
				c = n;
			}
		}
	}
	printf("merged count : %d \n", debug_merge_cnt);
}

int find_free_sector() {
	for (int i = 0; i < 16384; ++i) { // 10% 찾아봐도 없으면 optimize 한다.
		if (sinfo[sinfo_idx].size == 0 && sinfo[sinfo_idx].nextno == -1) return sinfo_idx;
		sinfo_idx++;
		if (sinfo_idx == 16384) sinfo_idx -= 16384;
	}
	printf("Can't find free sector! debug w_cnt %d, d_cnt %d \n", debug_w_cnt, debug_d_cnt);
	assert(0); // impossible!
	return -1;
}

int findno(char *file) {
	// method (1) file name search (파일 이름으로 찾아도 시간 차이는 미미하다. ) -> 의미 없다
	for (int i = 0; i < filename_idx; ++i) {
		bool same = true;
		for (int j = 0; j < 16; ++j)
			if (file[j] != filename[i][j]) {
				same = false;
				break; // escape
			}
		if (same) return i;
	}
	
	// method (2) file hash search ( hash 로 찾는게 미미하게 빠르다 )
	/*
	int h = hash(file);
	for (int i = 0; i < filename_idx; ++i) {
		if (h == filehash[i]) {
			bool same = true;
			for (int j = 0; j < 16; ++j)
				if (file[j] != filename[i][j]) {
					same = false;
					break;
				}

			if (same) return i;
		}
	}
	*/
	// 파일명 저장
	for (int j = 0; j < 16; ++j) filename[filename_idx][j] = file[j];
	filehash[filename_idx] = hash(file);

	return filename_idx++;
}

void init() {
	debug_d_cnt = debug_r_cnt = debug_w_cnt = 0;
	filename_idx = 0;
	for (int i = 0; i < 100; ++i) headno[i] = -1;
	for (int i = 0; i < 16384; ++i) sinfo[i].size = 0, sinfo[i].nextno = -1;

}
void debug_stage_end() {
	printf("debug w_cnt %d, d_cnt %d, r_cnt %d \n", debug_w_cnt, debug_d_cnt, debug_r_cnt);
}


void hdd_write(char *file, int offset, int size, char data[4096]) {
	debug_w_cnt++;

	// if (debug_w_cnt % 4000 == 0) optimize(); // 하드의 데이터를 변경하는 도중에 optimize를 시행하면 좋겠지만 구현이 난감하다. 시행 도중에 한 번만 시행
	// if (debug_w_cnt == 3500) optimize(); // 더 빨라지지 않는다
	if (debug_w_cnt % 1000 == 0) optimize(); // 무난

	int fno = findno(file);

	int h = headno[fno];
	// n (next), p (prev) : hdd_write 의 next 와 prev 블록.
	int n = h, p = -1;

	assert(h != -1 || offset == 0); // head가 없으면, offset 이 반드시 0 이다.

	while (n != -1 &&  offset >= sinfo[n].size){ // 1) size 가 0이면 무조건 진행 2) offset = size 라도 진행 3) offset > size 진행	
		offset -= sinfo[n].size;
		p = n;
		n = sinfo[n].nextno; // 다음으로 이동
		// if (DEBUG) printf("next no : %d \n", n);
	}

	assert(offset < sinfo[n].size || n == -1); // 현재 섹터를 나눠야 하거나, 새로운 노드를 만들어야 함.

	if (offset > 0) { // split
		
		assert(n != -1); // 나누기 위해서는 노드가 반드시 존재한다..
		assert(offset < sinfo[n].size); // offset는 맨 끝이 아니다. (맨 끝이면 다음으로 넘어갔을 것임)

		// if (DEBUG) printf("split! \n");

		int newno = find_free_sector();

		char d[1024];
		read(n, d); 
		write(newno, d + offset);

		sinfo[newno].nextno = sinfo[n].nextno;
		sinfo[newno].size = sinfo[n].size - offset;

		sinfo[n].nextno = newno;
		sinfo[n].size = offset;

		// split 노드 사이에 포지셔닝
		p = n;
		n = newno;
		offset = 0;
	}

	// printf("write size: %d, offset:  %d -- %d \n", size, offset, sinfo[no].size);
	// split

	assert(size > 0);// 기록할 size
	int scnt = (size + 1023) / 1024; // sector 수 (ceiling)
	if (DEBUG) printf("scnt : %d \n", scnt);
	// no 와 newno 사이에 셀을 하나씩 삽입
	// p == -1 이면, 현재셀이 헤드임.
	// c == -1  이면, 현재셀은 새로 만들어야 함.
	
	/*
	h c p : -1 -1 -1
            newno 0
			0  0  -1
	p 는 지난 노드, c은 다음 노드(밀어야함)
	*/
	for (int i = 0; i < scnt; ++i) {
		int newno = find_free_sector();
		int s = min2(1024, size);
		// p와 c 사이에 하나씩 끼워 넣는다.
		write(newno, data); // data를 1024 바이트까지 기록
		sinfo[newno].size = s;
		sinfo[newno].nextno = n;
		if (p == -1) headno[fno] = newno; 
		else sinfo[p].nextno = newno;

		p = newno; // 밀어넣은 노드가 p가 되어야 한다.
		size -= s;
		data += s;
	}
}
void hdd_delete(char *file, int offset, int size) {
	debug_d_cnt++;
	int fno = findno(file);

	int head = headno[fno];
	int n = head; // next
	int p = -1; // 지나간 노드

	// if (head == -1 && offset > 0) printf("IMPOSSIBLE!");
	assert(offset == 0 || head != -1);

	if (DEBUG) printf("hdd_del1 offset:%d size:%d n:%d sec_size:%d \n", offset, size, n, sinfo[n].size);

	while (n != -1 && offset >= sinfo[n].size) // 1) size 가 0이면 무조건 진행 2) offset = size 라도 진행 3) offset > size 진행
	{
		if (DEBUG) printf("Dnext!");
		assert(n != -1);
		offset -= sinfo[n].size;

		p = n;
		n = sinfo[n].nextno;
		if (DEBUG) printf("hdd_del2 offset:%d size:%d n:%d sec_size:%d \n", offset, size, n, sinfo[n].size);

	}

	assert(size > 0);
	assert(offset < sinfo[n].size);
	// 실제 삭제 시작
	
	
	while(size > 0){
		
		if (offset + size >= sinfo[n].size) { // offset 위치부터 끝까지 삭제
			
			assert(n != -1);
			if (offset == 0) { // 처음부터 끝까지 삭제.. (sector free)
				if (DEBUG) printf("hdd_del3 offset:%d size:%d n:%d sec_size:%d \n", offset, size, n, sinfo[n].size);
				size -= sinfo[n].size;

				// p는 유지
				int next_n = sinfo[n].nextno;

				sinfo[n].size = 0;
				sinfo[n].nextno = -1;

				if (p == -1) headno[fno] = next_n; // 만일 지금 노드가 처음이면 head 이동
				else sinfo[p].nextno = next_n;

				n = next_n;
				offset = 0;

				
			}
			else { // 중간부터
				if (DEBUG) printf("hdd_del4 offset:%d size:%d n:%d sec_size:%d \n", offset, size, n, sinfo[n].size);
				size -= (sinfo[n].size - offset);

				sinfo[n].size = offset;

				p = n;
				n = sinfo[n].nextno;

				offset = 0;
			}
		}
		else { // offset 위치부터 중간까지 삭제 --> 남은 데이터를 앞으로 땡겨야 한다. 
			assert(offset + size < sinfo[n].size);
			if (DEBUG) printf("hdd_del5 offset:%d size:%d n:%d sec_size:%d \n", offset, size, n, sinfo[n].size);
			char d[1024];
			read(n, d);
			// if (DEBUG) printf("before : %d, %d, \n", d[0], d[1]);
			for (int i = offset; i < sinfo[n].size - size; ++i) {
				d[i] = d[i + size];
				// printf("d[%d] = d[%d] \n", i, i + size);
			}
			write(n, d);

			sinfo[n].size -= size; // 표시를 해 줘야 하는데,,,!
			size = 0; // 중간까지 삭제하는 것은 더 이상 삭제 하지 않는다는 것 (break 로도 가능?)

			/* 불필요
			p = n;
			n = sinfo[n].nextno;
			*/
			
		}

	}
}
void hdd_read(char *file, int offset, int size, char data[4096]) {
	debug_r_cnt++;
	int fno = findno(file);
	int orisize = size;

	int dataidx = 0;
	int no = headno[fno];
	while (size > 0) {
		if (DEBUG) printf("\nread no:%d, size:%d, offset:%d, sec_size:%d \n ", no, size, offset, sinfo[no].size);
		assert(no != -1);
		if (sinfo[no].size <= offset) {
			offset -= sinfo[no].size;
			no = sinfo[no].nextno;
		}
		else {
			int canreadsize = min2(sinfo[no].size - offset, size);
			char d[1024];
			read(no, d);
			for (int i = offset; i < offset + canreadsize; ++i) {
				data[dataidx++] = d[i];
			}
			offset = 0;
			size -= canreadsize;
			no = sinfo[no].nextno;
		}

	}
	if (DEBUG) printf(" read idx : %d %d \n", dataidx, orisize);
	assert(dataidx == orisize);
}

