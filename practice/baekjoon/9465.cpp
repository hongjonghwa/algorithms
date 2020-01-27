#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) ((a)>(b)?(a):(b))
#include <stdio.h>

int T, n;
int x[100000][2];

int main() {
	scanf("%d", &T);
	for (int t = 0; t < T; ++t) {
		scanf("%d", &n);
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < n ; ++j)
				scanf("%d", &x[j][i]);

		int upper = x[0][0], lower = x[0][1], none = 0;
		for (int i = 1; i < n; ++i) {
			int ll = MAX(lower, none);
			int uu = MAX(upper, none);

			none = MAX(ll, uu);
			upper = ll + x[i][0];
			lower = uu + x[i][1];
		}

		int ret = none;
		ret = MAX(ret, upper);
		ret = MAX(ret, lower);
		printf("%d\n", ret);
	}

}