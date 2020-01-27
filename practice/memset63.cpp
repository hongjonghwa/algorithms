#include<cstring>
#include<cstdio>

int main(){

	int a[10];
	memset (a, 63, sizeof(a));
	printf ("%d \n " , a[3]);
	printf ("%d \n " , a[6]);
	printf ("%d \n " , a[6]+a[5]);
}
