// 2 - Stack
/*
Double Linked List 보다 조금 쉽거나 비슷했다.
Struct Line 안에 버그를 찾기 어려웠다. 스캐폴드가 없는 시험때였으면 아마 못 찾았을 것이다. --> 실패
시간 소요는 거의 비슷했다. 
-> 연산의 복잡도? 스택을 서로 넘기는 부담?
*/

#include<stdio.h>
#include<assert.h>

typedef unsigned int uint;

int _debug_move = 1;
uint cur_line, cur_pos;
struct stack {
	char *data;
	int capacity, len;
	stack() {
		capacity = 100;
		len = 0;
		data = new char[capacity];
	}
	void init() {
		len = 0;
	}
	bool empty() {
		return len == 0;
	}
	char pop() {
		assert(len > 0);
		return data[(len--)-1];
	}
	void push(char c) {
		if (len == capacity) { // expand
			capacity *= 2;
			char *ndata = new char[capacity];
			for (int i = 0; i < len; ++i) ndata[i] = data[i];
			delete[] data;
			data = ndata;
		}
		data[len++] = c;
	}
	void clone(stack *origin) {
		assert(len == 0);
		for (int i = 0; i < origin->len; ++i) {
			push(origin->data[i]);
		}
	}
};
struct Line {
	stack l, r;
	Line *prev, *next;
	void move_all_left() { // 모두 l로 보냄
		//for (int i = 0; i < r.len; ++i) { // 여기도 잘못 됨... 아래에서 r의 값이 변한다.
		while (r.len){
			char c = r.pop();
			l.push(c);
		}
	}
	void move_all_right() { // 모두 r로 보냄
		//for (int i = 0; i < l.len; ++i) { // 여기도 잘못 됨... 아래에서 r의 값이 변한다.
		while (l.len) {
			char c = l.pop();
			r.push(c);
		}
	}
	void move_to(int to) { // 잘못 된건 한참 찾았다. 알기 어려움!
		// printf("move to %d -> %d \n", l.len, to);
		if (l.len < to) {
			//for (int i = 0; i < to - l.len; ++i) { // l은 계속 변한다. 상수로 변경 ( 왜 몰랐나 !)
			int c = to - l.len;
			while(c--){
				if (r.empty()) break;
				char c = r.pop();
				l.push(c);
			}
		}
		else if (l.len > to) {
			//for (int i = 0; i < l.len - to; ++i) { // l은 계속 변한다. 상수로 변경 ( 왜 몰랐나 !)
			int c = l.len - to;
			while (c--) {
				if (l.empty()) break;
				char c = l.pop();
				r.push(c);
			}
		}
	}


} line[20000]; // x[0] 을 헤더로 사용, (헤더는 바뀌지 않음) 
int line_free;
Line *cur;

Line* newLine() {
	return &line[line_free++];
}

void create() {
	for (int i = 0; i < 20000; ++i) {
		line[i].l.init();
		line[i].r.init();
		line[i].prev = line[i].next = 0;
	}
	cur = &line[0];

	line_free = 1;
	cur_line = cur_pos = 0;
}
void put_char(char c) {
	//if (_debug_move) printf("put '%c'\n", c);
	cur->l.push(c);
}
void put_backspace() {
	//if (_debug_move) printf("back \n");
	if (cur->l.empty()) {
		if (!cur->prev) return; // 첫 라인이다, do nothing!

		cur->prev->move_all_left(); // 윗라인을 좌측으로 다 보낸다
		if (!cur->r.empty()) { // 우측에 남은 개 있으면 복사한다
			assert(cur->prev->r.empty());
			cur->prev->r.clone(&(cur->r)); // 우측에 현재 라인을 복사한다.
			cur->r.len = 0;// 빈칸
		}

		// 현재 라인을 없앤다 
		if (cur->prev) cur->prev->next = cur->next;
		if (cur->next) cur->next->prev = cur->prev;

		cur = cur->prev;
	}
	else {
		cur->l.pop();
	}
}
void put_enter() {
	//if (_debug_move) printf("enter \n");
	Line *n = newLine();
	n->prev = cur;
	n->next = cur->next;
	
	if (cur->next) cur->next->prev = n;
	cur->next = n;
	if (!cur->r.empty()) {
		n->r.clone(&(cur->r));
		cur->r.len = 0;
	}

	cur = cur->next;
}
void cursor_up(int i) {
	//if (_debug_move) printf("cursor up %d \n", i);
	int cur_pos = cur->l.len;
	while (i--) {
		if (cur->prev) {
			cur = cur->prev;
		}
	}
	cur->move_to(cur_pos);
}
void cursor_down(int i) {
	//if (_debug_move) printf("cursor down %d \n", i);
	int cur_pos = cur->l.len;
	//if (_debug_move) printf("pos cur %d \n", cur_pos);
	while (i--) {
		if (cur->next) {
			cur = cur->next;
		}
	}
	cur->move_to(cur_pos);
	//if (_debug_move) printf("l/r %d/%d \n", cur->l.len, cur->r.len);
}
void cursor_left(int i) {
	/* 조금 더 빠르게, 라인을 넘길때는 buffer를 옮기지 않는다.  (약 4% 빨라졌다) */
	if (i > cur->l.len && cur->prev) {
		i -= (cur->l.len + 1);
		cur = cur->prev;

		while (i > cur->l.len + cur->r.len && cur->prev) {
			i -= (cur->l.len + cur->r.len + 1);
			cur = cur->prev;
		}
		cur->move_to(cur->l.len + cur->r.len - i);
		return;
	}

	while(i--){
		if (cur->l.empty()) {
			if (cur->prev == 0) return;
			cur = cur->prev;
			cur->move_all_left();
		}
		else {
			char c = cur->l.pop();
			cur->r.push(c);
		}
	}
}
void cursor_right(int i) {
	/* 조금 더 빠르게, 라인을 넘길때는 buffer를 옮기지 않는다.  (약 4% 빨라졌다) */
	if (i > cur->r.len && cur->next) {
		i -= (cur->r.len + 1);
		cur = cur->next;

		while (i > cur->l.len + cur->r.len && cur->next) {
			i -= (cur->l.len + cur->r.len + 1);
			cur = cur->next;
		}
		cur->move_to(i);
		return;
	}
	
	while(i--){
		if (cur->r.empty()) {
			if (cur->next == 0) return;
			cur = cur->next;
			cur->move_all_right();
		}
		else {
			char c = cur->r.pop();
			cur->l.push(c);
		}
	}
}
void close(char *document) {
	//_debug_verify('c');
	Line *p = &line[0];
	int idx = 0;
	while (p) {
		for (int i = 0; i < p->l.len; ++i) {
			document[idx++] = p->l.data[i];
		}
		for (int i = p->r.len -1 ; i>= 0 ; --i) {
			document[idx++] = p->r.data[i];
		}
		if (p->next) document[idx++] = '\n';

		p = p->next;
	}
	document[idx] = 0;
  
  
  
  
  // Stack total size.
  int t = 0, t2 = 0;
  for (int i = 0 ; i < 20000; ++i){
    t+=line[i].l.len;
    t+=line[i].r.len;
    t2+=line[i].l.capacity;
    t2+=line[i].r.capacity;
  }
  printf("total stack size : %d / %d \n", t, t2);
}
void debug(unsigned int &cur_l, unsigned int &cur_p) {
	cur_l = cur_line;
	cur_p = cur_pos;
}
