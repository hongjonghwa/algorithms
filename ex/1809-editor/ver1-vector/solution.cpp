#include<assert.h>
#include<string>
#include<vector>

std::vector<std::string> v;

unsigned int cur_line, cur_pos;
void create() {
	v.clear();
	v.resize(1);
	cur_line = cur_pos = 0;
}
void put_char(char c) {
	assert(cur_line < v.size() && cur_pos <= v[cur_line].size());
	v[cur_line].insert(cur_pos, std::string(1, c));
	cur_pos++;
}
void put_backspace() {
	if (cur_pos > 0) {
		cur_pos--;
		v[cur_line].erase(cur_pos, 1);
	}
	else if (cur_line > 0) {
		cur_line--;
		cur_pos = v[cur_line].size();
		v[cur_line] = v[cur_line] + v[cur_line + 1];
		v.erase(v.begin() + cur_line + 1, v.begin() + cur_line + 2);
	}
	else;// do nothing. start of document.
}
void put_enter() {
	std::string l = v[cur_line].substr(0, cur_pos);
	std::string r = v[cur_line].substr(cur_pos, v[cur_line].size() - cur_pos);
	v[cur_line] = l;
	v.insert(v.begin() + cur_line + 1, r);
	cur_line++;
	cur_pos = 0;
}
void cursor_up(int i) {
	while (i--) {
		if (cur_line > 0) cur_line--;
	}
	if (cur_pos > v[cur_line].size()) cur_pos = v[cur_line].size();
}
void cursor_down(int i) {
	while (i--) {
		if (cur_line < v.size() - 1) cur_line++;
	}
	if (cur_pos > v[cur_line].size()) cur_pos = v[cur_line].size();
}
void cursor_left(int i) {
	while (i--) {
		if (cur_pos > 0) cur_pos--;
		else if (cur_line > 0) {
			cur_line--;
			cur_pos = v[cur_line].size();
		}
		else; // do nothing. start of document.
	}
}
void cursor_right(int i) {
	while (i--) {
		if (cur_pos < v[cur_line].size()) cur_pos++;
		else if (cur_line < v.size() - 1) {
			cur_line++;
			cur_pos = 0;
		}
		else; // do nothing. end of document.
	}
}
void close(char *document) {
	int idx = 0;
	for (unsigned int i = 0; i < v.size(); ++i) {
		for (unsigned int j = 0; j < v[i].size(); ++j) document[idx++] = v[i][j];
		if (i == v.size() - 1) document[idx++] = 0;
		else document[idx++] = '\n';
	}
}
void debug(unsigned int &cur_l, unsigned int &cur_p) {
	cur_l = cur_line;
	cur_p = cur_pos;
}
