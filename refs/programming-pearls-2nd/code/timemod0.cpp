/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* timemod0.c -- Simple experiments on C run time costs */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{	int i, n, ia, ib, ic;
	float fa, fb, fc;
	n = 1000000000;	/* run time in secs gives nanosecs/loop */
	ia = ib = ic = 9;
	fa = fb = 9.0;
	for (i = 0; i < n; i++) {
		/* null loop        // 2.722s */
		//ia = ib + ic;     // 2.669s
		//ia = ib - ic;     // 
		//ia = ib * ic;     // 
		//ia = ib % ic;     // 
		//ia = ib / ic;     // 
		//ia = rand();      // 9.347s
		//fa = sqrt(fb);    // 7.931s
		free(malloc(8));    //28.609s
	}
	return 0;
}
