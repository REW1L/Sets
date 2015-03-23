#include <time.h>
//
// anyFunc - function that needs to be tested
// fa - first argument
// sa - second argument
//
double testTime(int (*anyFunc)(void*), void *fa)
{
	long cl = clock();
	(*anyFunc)(fa);
	cl = clock()-cl;
	double ans = ((double)cl)/CLOCKS_PER_SEC;
	return ans;
}