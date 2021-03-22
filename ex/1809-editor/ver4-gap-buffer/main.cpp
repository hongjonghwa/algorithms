/* 힙 256M, 스택 1M, 시간 10초 */
// 횟수 10번? 100번? 100번으로 기억
#define TIME_LOOP 100
#define NN 1024*1024
//#define NN 1000

#include <stdio.h>
#include <time.h>

extern void create();
extern void put_char(char c);
extern void put_enter();
extern void put_backspace();
extern void cursor_up(int i);
extern void cursor_down(int i);
extern void cursor_left(int i);
extern void cursor_right(int i);
extern void close(char *document);

void debug(unsigned int &cur_l, unsigned int &cur_p);

char *document = new char[NN + 2]; // +2가 필요한 이유, enter와 put_char 가 동시에 일어나면 +1, '\0' 입력 포함하면 +2
unsigned int debug_line, debug_pos;

int SEED = 1;
int rand() {
	SEED = SEED * 214013 + 2531011;
	return (SEED >> 16) & 0x7fff;
}
int hash() {
	int ret = 0;
	for (int i = 0; i < NN; ++i) {
		ret = ret * 31 + document[i];
	}
	return ret;
}

int strlen(char *p){
  char *s = p;
  while (*s){s++;}
  return s-p;
}
void _debug_report() {
	close(document); debug(debug_line, debug_pos);  printf("*** Text(%d/%d) ***\n%s (len: %d)\n", debug_line, debug_pos, document, strlen(document));
}
void test() {
	put_char('1');
	put_char('2');

	put_char('3');
	put_enter();
	put_enter();
	put_char('4');
	put_backspace();
	put_char('5');
	put_char('6');
	_debug_report();
	cursor_up(20);

	_debug_report();
	put_char('7');
	put_char('8');
	_debug_report();

	cursor_down(20);
	put_char('9');
	_debug_report();

	cursor_right(3);
	put_backspace();
	put_enter();
	cursor_right(3);
	put_enter();


	cursor_left(50);

	put_char('1');
	put_char('2');
	put_backspace();
	put_char('3');
	put_enter();
	put_backspace();
	put_enter();
	put_char('4');
	put_char('5');
	put_backspace();
	put_char('6');
	_debug_report();
	cursor_up(20);

	_debug_report();
	put_char('7');
	put_backspace();
	put_char('8');
	cursor_down(20);
	put_char('9');
	cursor_right(3);
	put_enter();
	cursor_right(3);
	put_enter();

	cursor_right(50);

	put_char('1');
	put_char('2');

	put_char('3');
	put_enter();
	put_enter();
	put_char('4');
	put_char('5');
	put_char('6');
	_debug_report();
	cursor_up(20);

	_debug_report();
	put_char('7');
	put_char('8');
	cursor_down(20);
	put_char('9');
	cursor_right(3);
	put_enter();
  _debug_report();

	cursor_right(3);
	put_enter();

  _debug_report();
	put_backspace(); put_backspace(); put_backspace(); put_backspace();

	_debug_report();
}

int main() {
	int total_ms = 0;

	// create(); test(); return 0;

	for (register int t = 0; t < TIME_LOOP; ++t) {
		int DS = 0;
		long long int clk = clock();
		create();
		while (DS < NN) {
			if (rand() % 100 == 99) {
				put_backspace();
				DS--;
			}
			if (rand() % 100 == 99) {
				switch (rand() % 4) {
				case 0: cursor_up(rand() % 100 + 1); break;
				case 1: cursor_down(rand() % 100 + 1); break;
				case 2: cursor_left(rand() % 100 + 1); break;
				case 3: cursor_right(rand() % 100 + 1); break;
				}
			}
			if (rand() % 100 == 99) {
				put_enter();
				DS++;
			}
			put_char(rand() % 26 + 'A');
			DS++;
		}
		close(document);
    // printf("***(len:%d)\n%s\n***\n", strlen(document), document);
		clk = (double)(clock() - clk) / (CLOCKS_PER_SEC / 1000);
		total_ms += clk;
		int h = hash();

		printf("no %3d %11d %d \n", t+1, h, int(clk));
	}
	printf("Time excuted : %f \n", (double)total_ms/1000);
}
