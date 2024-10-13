
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int fib_recur(int n) //순환 알고리즘으로 피보나치 수 계산
{
	//아래를 완성하시오.
	if (n <= 1)
		return n;
	return fib_recur(n - 1) + fib_recur(n - 2);

}
int fib_iter(int n)//피보나치 수 저장을 위해 배열 사용
{
	int* arr = new int[n + 1];
	arr[0] = 0, arr[1] = 1;
	//아래를 완성하시오.
	for (int i = 2; i <= n; ++i)
		arr[i] = arr[i - 1] + arr[i - 2];

	int result = arr[n];
	delete[] arr;
	return result;
}
void notation_recur(int base, int n)
{
	if (n < base)
		printf("%d", n);
	else
	{
		//아래를 완성하시오.
		notation_recur(base, n / base);
		printf("%d", n % base);
	}
}
void notation_iter(int base, int n)
{
	int binary[32], size = 0;
	//아래를 완성하시오.
	while (n > 0) {
		binary[size++] = n % base;
		n /= base;
	}

	for (int i = size - 1; i >= 0; i--)
		printf("%d", binary[i]);
}
int main()
{
	clock_t start, stop;
	double duration;
	int n;

	start = clock(); //측정시작
	n = fib_iter(40);
	stop = clock(); //측정종료
	duration = ((double)stop - (double)start) / CLOCKS_PER_SEC;
	printf("반복: fib(40)= %d, 수행시간은 %f초입니다.\n", n, duration);

	start = clock(); //측정시작
	n = fib_recur(40);
	stop = clock(); //측정종료
	duration = ((double)stop - (double)start) / CLOCKS_PER_SEC;
	printf("순환: fib(40)= %d, 수행시간은 %f초입니다.\n", n, duration);

	printf("10진수 입력: ");
	scanf("%d", &n);
	printf("순환: %d, 2진수: ", n);
	notation_recur(2, n);
	printf("\n");
	printf("반복: %d, 2진수: ", n);
	notation_iter(2, n);
	printf("\n");
	return 0;
}
/*실제출력결과
반복: fib(40)= 102334155, 수행시간은 0.000000초입니다.
순환: fib(40)= 102334155, 수행시간은 1.616000초입니다.
10진수 입력: 29
순환: 29, 2진수: 11101
반복: 29, 2진수: 11101

C:\Users\USER\source\repos\Project11\x64\Debug\Project11.exe(프로세스 12724개)이(가) 종료되었습니다(코드: 0개).
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요...
*/
/*예시출력결과
반복: fib(40)= 102334155, 수행시간은 0.000000초입니다.
순환: fib(40)= 102334155, 수행시간은 7.448000초입니다.
10진수 입력: 29
순환: 29, 2진수: 11101
반복: 29, 2진수: 11101
계속하려면 아무 키나 누르십시오 . . .
*/