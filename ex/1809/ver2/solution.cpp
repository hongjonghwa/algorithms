// 시험시간에 풀었던 방식 --;
#include<stdio.h>
#include<assert.h>

typedef unsigned int uint;

void _debug_verify(char c);
void _debug_verify2(char c, int i);

uint cur_line, cur_pos;

struct Data {
	char data;
	Data *next;
	Data *prev;
} x[2000000];
Data *cur_x;
uint free_x;

struct Line {
	Line *next;
	Line *prev;
	Data *xhead;
	int size;
} l[20000];
Line *cur_l;
uint free_l;
uint _debug_cnt, _debug_chars;

/* 
  Head pointer 가 필요없는 이유 . => 결론 : linked list 는 *head 를 정의하자
  -> question의 요건에 따라 첫 번째 라인은 바뀔 수 없다. 하여 l[0] 을 head로 사용한다.
     Data 헤더 또난 l[0].xhead 를 사용하면 된다 
  -> 시험에서는 l[0]을 head 로 사용하고 l[1] 부터 데이터 사용 --> 더 헷갈렸음 그냥 head pointer 를 만드는 게 낫다.
     x[0]은 \n을 넣고, 그냥 헤드로 사용( x[0] 헤더는 안 바뀔 것을 알았다. 
      
  => 헤더가 필요하면 *head 를 선언하자, 안 그러면 더 헷갈림
*/

void create() {
	cur_line = cur_pos = 0;
	for (int i = 0; i < 2000000; ++i) x[i].next = x[i].prev = 0;
	for (int i = 0; i < 20000; ++i) {
		l[i].next = l[i].prev = 0;
		l[i].xhead = 0;
	}
	x[0].data = '\n';
	l[0].xhead = cur_x = &x[0];
	l[0].size = 1;
	cur_l = &l[0];

	free_x = free_l = 1;

	_debug_cnt = _debug_chars = 0;
}

void put_char(char c) {
	//_debug_verify('p');
	if (cur_x == 0 || cur_l == 0) return;
	assert(cur_x && cur_l); // 언제나 포인트가 존재
	// 뒤에 붙인다
	x[free_x].data = c;
	x[free_x].next = cur_x->next;
	x[free_x].prev = cur_x;
	if (cur_x->next) cur_x->next->prev = &x[free_x];
	cur_x->next = &x[free_x];

	cur_pos++;
	cur_l->size++;

	cur_x = cur_x->next;
	free_x++;

	//_debug_verify2('p',-1);
}
void put_backspace() {
	//_debug_verify('b');
	if (cur_x == &x[0]) {
		// printf("Backspace in start of document!!!!\n");
		// assert(cur_x == 0 && cur_pos == 0); // 처음
		return; // do nothing!
	}

	/* 현재 노드 삭제 */
	cur_x->prev->next = cur_x->next;
	if (cur_x->next) cur_x->next->prev = cur_x->prev;

	/* 라인 머지 */
	if (cur_x->data == '\n') { // line merge at start
		assert(cur_pos == 0); // 라인의 처음이다!
		cur_l->prev->next = cur_l->next;
		if (cur_l->next) cur_l->next->prev = cur_l->prev;
		cur_pos = cur_l->prev->size;


		cur_l->prev->size += cur_l->size; 
		cur_l = cur_l->prev;
		
		cur_line--;
	}

	cur_pos--;
	cur_l->size--; // 여기서 실수 (1) : 길이가 안 맞으면 cursor_up/down 에서 position 찾을 때 null 떨어짐 (아마 시험에서도 잘못한 듯 )
	cur_x = cur_x->prev; // 여기도 실수 (2) : 시험때는 제대로 했었나? 기억이 안남,,, ==> 결과적으로 치명적인 소소한 버그를 찾기가 어려웠음.

	//_debug_verify2('b',-1);
}
void put_enter() {
	//_debug_verify('e');
	put_char('\n');

	l[free_l].next = cur_l->next;
	l[free_l].prev = cur_l;
	l[free_l].size = cur_l->size - cur_pos;
	l[free_l].xhead = cur_x;

	if (cur_l->next) cur_l->next->prev = &l[free_l];
	cur_l->next = &l[free_l];
	cur_l->size = cur_pos;

	cur_l = cur_l->next;
	cur_line++;
	cur_pos = 0;

	free_l++;
	//_debug_verify2('e',-1);
}
void cursor_up(int i) {
	int ii = i;
	//_debug_verify('U');
	//if (_debug_cnt == 382) printf("cursor up : %d \n", i);

	while (i--) {
		// for (int i = 0; i < 4; ++i) printf("%d %d %d %d %d \n", i, l[i].prev - &l[0], l[i].next - &l[0], l[i].size, l[i].xhead - &x[0]);
		// printf("cur (line %d /pos %d )  cur_l %d, cur_x %d \n", cur_line, cur_pos, cur_l - l, cur_x - x );
		if (cur_line > 0) {
			cur_l = cur_l->prev;
			//assert(cur_l);
			cur_line--; 
		}
	}
	//if (_debug_cnt == 382) printf("cur_pos : %d , cur_l->size : %d \n", cur_pos, cur_l->size);
	if (cur_pos > cur_l->size - 1) cur_pos = cur_l->size - 1;
	//if (_debug_cnt == 382) printf("cur_pos : %d , cur_l->size : %d \n", cur_pos, cur_l->size);
	

	cur_x = cur_l->xhead;
	for (int i = 0; i < cur_pos; ++i) {
		//if (_debug_cnt == 382) printf("i : %d/%d , cur_x : %d, cur_x->next : %d, cur_x->prev : %d \n", i, cur_pos, cur_x, cur_x->next, cur_x->prev);
		cur_x = cur_x->next;
	}	

	//_debug_verify2('U',ii);
}
void cursor_down(int i) {
	int ii = i;
	//_debug_verify('D');
	while (i--) {
		if (cur_l->next) {
			cur_l = cur_l->next;
			cur_line++;
			

		}
	}
	if (cur_pos > cur_l->size - 1) cur_pos = cur_l->size - 1;
	cur_x = cur_l->xhead;
	for (int i = 0; i < cur_pos; ++i) {
		cur_x = cur_x->next;
		assert(cur_x);
	}

	//_debug_verify2('D', ii);
}
void cursor_left(int i) {
	int ii = i;
	//_debug_verify('L');
	while (i--) {
		if (cur_pos > 0) {
			cur_pos--;
			cur_x = cur_x->prev; // 오류(이상하다)!
		}
		else if (cur_line > 0) {
			cur_l = cur_l->prev;
			cur_line--;
			cur_pos = cur_l->size - 1;

			cur_x = cur_x->prev; // 오류(이상하다)!
		}
		else; // do nothing, line of start
	}

	//_debug_verify2('L',ii);
}
void cursor_right(int i) {
	int ii = i;
	//_debug_verify('R');
	while (i--) {
		if (cur_x->next) {
			cur_x = cur_x->next;

			if (cur_x->data == '\n') { // line changed
				cur_line++;
				cur_pos = 0;
				cur_l = cur_l->next;
			}
			else {
				cur_pos++;
			}
		}
	}

	//_debug_verify2('R',ii);
}
void close(char *document) {
	//_debug_verify('c');
	Data *dp = &x[0];

	int idx = 0;
	int cnt = 1024 * 1024;
	while (dp->next && cnt--) {
		dp = dp->next;
		document[idx++] = dp->data;
	}
	document[idx] = 0;

	/*
	int idx = 0;
	for (unsigned int i = 0; i < v.size(); ++i) {
		for (unsigned int j = 0; j < v[i].size(); ++j) document[idx++] = v[i][j];
		if (i == v.size() - 1) document[idx++] = 0;
		else document[idx++] = '\n';
	}
	*/
}
void debug(unsigned int &cur_l, unsigned int &cur_p) {
	cur_l = cur_line;
	cur_p = cur_pos;
}

void _debug_verify(char c) {
	_debug_cnt++;
	if (!cur_x || !cur_l) {
		printf("[%c] _debug_cnt %d _debug_chars %d \n", c, _debug_cnt, _debug_chars);
		assert(0);
	}
	if (_debug_cnt == 856){
		Line *lp = &l[0];
		for (int i = 0; lp; ++i, lp = lp->next) {
			Data *xx = lp->xhead;
			uint ll1 = lp->size;
			uint ll2 = 0;
			while (xx) {
				if (cur_l->next && cur_l->next->xhead == xx) break;
				ll2++;
				xx = xx->next;
			}
			printf("%d ll1 %d, ll2 %d, cur_pos %d, cur_line %d, %c, %d, %d \n", i, ll1, ll2, cur_pos, cur_line, c, _debug_cnt, _debug_chars);
		}
	}
}

void _debug_verify2(char c, int i) {
	printf("DV2 [%c %d] _debug_cnt %d _debug_chars %d, cur_pos %d, cur_line %d  \n", c, i, _debug_cnt, _debug_chars, cur_pos, cur_line);
	Data *xx = cur_l->xhead;
	uint ll1 = cur_l->size;
	uint ll2 = 0;
	while (xx ) {
		if (cur_l->next && cur_l->next->xhead == xx) break;
		ll2++;
		xx = xx->next;
	}
	if (ll1 != ll2) {
		printf("ll1 %d, ll2 %d, cur_pos %d, cur_line %d, %c, %d, %d \n", ll1, ll2, cur_pos, cur_line, c, _debug_cnt, _debug_chars);
		assert(0);
	}
}
