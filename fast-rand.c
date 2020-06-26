/*
  https://software.intel.com/en-us/articles/fast-random-number-generator-on-the-intel-pentiumr-4-processor/
*/

static unsigned int g_seed = 42;

//Used to seed the generator.
/*
inline void fast_srand( int seed ){
    g_seed = seed;
}
*/

//fastrand routine returns one integer, similar output value range as C lib.
inline int fastrand(){
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}
