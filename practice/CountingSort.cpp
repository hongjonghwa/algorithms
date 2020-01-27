#include<stdio.h>
#include<string.h>

int strlen(char *c){
	int i=0;
	while (c[i]) ++i;
	return i;
}
int main()
{
	char arr[] = "geeksforgeeks";//"applepp";
	printf("Input character array is %s\n", arr);
	printf("Length : %d\n", strlen(arr));

	int count[256];
	char output[strlen(arr)];
	
	for (int i = 0; i < 256; ++i)
		count[i] = 0;

	for (int i = 0; arr[i] ; ++i)
		++count[arr[i]];

	for (int i = 1; i < 256 ; ++i)
		count[i] += count[i-1];

	for (int i = 0; arr[i] ; ++i){
		output[count[arr[i]]-1] = arr[i];
		--count[arr[i]];
	}
	for (int i = 0; arr[i] ; ++i)
		arr[i] = output[i];


	printf("Sorted character array is %s\n", arr);
	return 0;
}
