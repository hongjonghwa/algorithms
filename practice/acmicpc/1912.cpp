#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) ( (a)>(b) ? (a) : (b) )
#include <stdio.h>
int N;

int main() {
	scanf("%d", &N);
	int x;
	int maxToHere = 0;
	int ret = -9999;
	for (int i = 0; i < N; ++i) {
		scanf("%d", &x);
		//maxToHere = MAX(maxToHere + x, 0); // i번째 까지의 최대 값
		//적어도 하나는 선택해야함.
		maxToHere += x;
		ret = MAX(ret, maxToHere);
		if (maxToHere < 0) maxToHere = 0;
	}
	printf("%d\n", ret);
	return 0;
}