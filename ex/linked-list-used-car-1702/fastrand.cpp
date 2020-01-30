int seed = 1;
int fastrand() {
	seed = seed * 214013 + 2531011;
	return (seed>>16) & 0x7FFF;
}
