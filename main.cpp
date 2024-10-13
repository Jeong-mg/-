
#include "ga.h"

void init_pop();
void ga_impl();

int main(void)
{

	clock_t t_start, t_end;;
	double duration;

	//srand(seedval);

	init_pop();
	t_start = clock();
	ga_impl();
	t_end = clock();
	duration = ((double)t_end - (double)t_start) / CLOCKS_PER_SEC;
	printf("경과시간: %f초\n", duration);


	return 0;
}
/*예시결과
solution population
x0:1 1 0 0
x1:0 0 1 1
x2:1 0 0 0
x3:0 1 1 1
x4:0 0 1 1
x5:1 1 0 0
generation: 0, fitness avg: 42.7
pop-max : x:8, f(x):56
best-max: x:8, f(x):56
generation: 10, fitness avg: 55.0
pop-max : x:8, f(x):56
best-max: x:8, f(x):56
generation: 20, fitness avg: 55.0
pop-max : x:8, f(x):56
best-max: x:8, f(x):56
generation: 30, fitness avg: 56.0
pop-max : x:8, f(x):56
best-max: x:8, f(x):56
generation: 40, fitness avg: 56.0
pop-max : x:8, f(x):56
best-max: x:8, f(x):56
generation: 50, fitness avg: 56.0
pop-max : x:8, f(x):56
best-max: x:8, f(x):56
generation: 60, fitness avg: 56.0
pop-max : x:8, f(x):56
best-max: x:8, f(x):56
generation: 70, fitness avg: 55.0
pop-max : x:8, f(x):56
best-max: x:8, f(x):56
generation: 80, fitness avg: 55.0
pop-max : x:8, f(x):56
best-max: x:8, f(x):56
generation: 90, fitness avg: 56.0
pop-max : x:8, f(x):56
best-max: x:8, f(x):56
generation: 100, fitness avg: 56.0
pop-max : x:8, f(x):56
best-max: x:8, f(x):56
generation: 100, fitness avg: 56.0
pop-max : x:8, f(x):56
best-max: x:8, f(x):56
경과시간: 0.008000초
계속하려면 아무 키나 누르십시오 . . .
*/

/*실제결과

*/

