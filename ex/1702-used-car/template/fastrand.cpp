int seed = 1983;
int fastrand() {
	seed = seed * 31 + 29989;
	//return seed & 0x7FFF;
	return (seed>>16) & 0x7FFFFFFF;
}
