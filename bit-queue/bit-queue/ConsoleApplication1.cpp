#include "assert.h"
#include "pch.h"
#include <iostream>


void enque(unsigned char data[1024], unsigned int offset, unsigned int len, unsigned int val) {
	printf("IN ==> %d\n", val);
	int s_pos = offset / 8;
	int e_pos = (offset + len - 1) / 8;

	int remained = offset % 8;
	if (remained == 0) remained = 8;

	int writable = (len > remained ? remained : len);


	return;
}

unsigned int deque(unsigned char data[1024], unsigned int offset, unsigned int len) {
	unsigned int ret = 0;
	printf("OUT ==> %d\n", ret);
	return ret;
}

int X[5][2] = { 
	{5,23},
	{7,100},
	{24,10000},
	{5,21},
	{8,200}
};
int X_LEN = 5;


int main()
{
	unsigned char data[1024];
	for (int i = 0; i < 1024; ++i) data[i] = 0;

	int offset;
	offset = 0;
	for (int i = 0; i < X_LEN; ++i) {
		enque(data, offset, X[i][0], X[i][1]);
	}

	offset = 0;
	for (int i = 0; i < X_LEN; ++i) {
		unsigned int r = deque(data, offset, X[i][0]);
		// assert(r == X[i][1]);
	}

	// again!
	offset = 0;
	for (int i = 0; i < X_LEN; ++i) {
		unsigned int r = deque(data, offset, X[i][0]);
		// assert(r == X[i][1]);
	}

}
