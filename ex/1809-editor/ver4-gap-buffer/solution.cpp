// hash 값이 틀리다. -> 다른 버전과 결과가 다름
// gap buffer 는  cursor_up/down 을 빠르게 처리하지 못한다. ( 전체 수행 시간의 87% )
// 

#include<assert.h>
#include<string>
#include<vector>

#define BUFSIZE 1024*1024+2
char buffer[BUFSIZE];
int gap_left, gap_right, size;

unsigned int cur_line, cur_pos;
void create() {
	gap_left = 0;
	gap_right = BUFSIZE-1;
}
void put_char(char c) {
	buffer[gap_left++] = c;
}
void put_backspace() {
	gap_left--;
}
void put_enter() {
	buffer[gap_left++] = '\n';
}
void cursor_left(int n){
	if (n > gap_left) n = gap_left;

	for (int i = 0 ; i < n ; ++i)
		buffer[gap_right--] = buffer[--gap_left];
}
void cursor_right(int n) {
	if (n > BUFSIZE - gap_right - 1) n = BUFSIZE - gap_right - 1;

	for (int i = 0 ; i < n ; ++i)
		buffer[gap_left++] = buffer[++gap_right];
}
void cursor_up(int n) {

	int pos = 0; // 현재 위치
	int i = gap_left-1;
	while (i>=0 && buffer[i] != '\n'){
		pos++;
		i--;
	}

	if (i == -1) return; // 첫 라인 -> 아무것도 하지 않는다.

	// n번의 라인을 건너 뛴다.
	while (n--){
		assert(i == -1 || buffer[i] == '\n');
		if (i>0) i--;
		while (i>=0 && buffer[i] != '\n'){
			i--;
		}
	}

	// 이동할 포지션
	i++;
	while (pos--){
		if (buffer[i] == '\n') break;
		i++;
	}
	cursor_left(gap_left - i);
}

void cursor_down(int n) {
	int pos = 0; // 현재 위치
	int i = gap_left-1;
	while (i>=0 && buffer[i] != '\n'){
		pos++;
		i--;
	}
	int j = gap_right+1;
	while (j < BUFSIZE  && buffer[j] != '\n'){
		j++;
	}
	if (j==BUFSIZE) return; // 마지막 라인 -> 아무것도 하지 않는다.


	// (n-1)번 더 내려간다..
	while (--n){
		assert(j == BUFSIZE || buffer[j] == '\n');
		if (j == BUFSIZE) break;
		j++;
		while (j < BUFSIZE && buffer[j] != '\n'){
			j++;
		}
	}
	// 한 줄 위로 
	assert(j == BUFSIZE || buffer[j] == '\n');
	j--;
	while (buffer[j] != '\n'){
		j--;
	}
	// pos 까지 진행
	j++;
	while (pos--){
		if (j < BUFSIZE && buffer[j] == '\n') break;
		j++;
	}
	cursor_right(j - gap_right);
}


void close(char *document) {
	int t = 0;
	for (int i = 0 ; i < gap_left ; ++i)
		document[t++] = buffer[i];
	for (int i = gap_right+1 ; i < BUFSIZE ; ++i)
		document[t++] = buffer[i];
	document[t] = 0;
}

void debug(unsigned int &cur_l, unsigned int &cur_p) {
	cur_l = 0;
	cur_p = 0;
}
