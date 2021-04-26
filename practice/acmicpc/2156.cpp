#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) ( (a) > (b) ? (a) : (b) )
#include <stdio.h>

int N;
//int x[10000];
int cache[2][3];

int main() {
	scanf("%d", &N);
	scanf("%d", &cache[0][1]);

	int cur, prev, x;
	for (int i = 1; i < N; ++i) {
		scanf("%d", &x);
		cur = i % 2, prev = (i - 1) % 2; // �߰����� �����ϸ�, sliding window �� �ʿ����..

		cache[cur][0] = MAX(cache[prev][1], cache[prev][2]);
		cache[cur][0] = MAX(cache[cur][0], cache[prev][0]); // �� �� �������� �� ���� �� �ִ� �Ϳ� ����
		cache[cur][1] = cache[prev][0] + x;
		cache[cur][2] = cache[prev][1] + x;

	}
	int ret = 0;
	ret = MAX(ret, cache[cur][0]);
	ret = MAX(ret, cache[cur][1]);
	ret = MAX(ret, cache[cur][2]);
	printf("%d\n", ret);

	return 0;
}