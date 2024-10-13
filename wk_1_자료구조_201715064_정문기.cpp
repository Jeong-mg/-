
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int fib_recur(int n) //��ȯ �˰������� �Ǻ���ġ �� ���
{
	//�Ʒ��� �ϼ��Ͻÿ�.
	if (n <= 1)
		return n;
	return fib_recur(n - 1) + fib_recur(n - 2);

}
int fib_iter(int n)//�Ǻ���ġ �� ������ ���� �迭 ���
{
	int* arr = new int[n + 1];
	arr[0] = 0, arr[1] = 1;
	//�Ʒ��� �ϼ��Ͻÿ�.
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
		//�Ʒ��� �ϼ��Ͻÿ�.
		notation_recur(base, n / base);
		printf("%d", n % base);
	}
}
void notation_iter(int base, int n)
{
	int binary[32], size = 0;
	//�Ʒ��� �ϼ��Ͻÿ�.
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

	start = clock(); //��������
	n = fib_iter(40);
	stop = clock(); //��������
	duration = ((double)stop - (double)start) / CLOCKS_PER_SEC;
	printf("�ݺ�: fib(40)= %d, ����ð��� %f���Դϴ�.\n", n, duration);

	start = clock(); //��������
	n = fib_recur(40);
	stop = clock(); //��������
	duration = ((double)stop - (double)start) / CLOCKS_PER_SEC;
	printf("��ȯ: fib(40)= %d, ����ð��� %f���Դϴ�.\n", n, duration);

	printf("10���� �Է�: ");
	scanf("%d", &n);
	printf("��ȯ: %d, 2����: ", n);
	notation_recur(2, n);
	printf("\n");
	printf("�ݺ�: %d, 2����: ", n);
	notation_iter(2, n);
	printf("\n");
	return 0;
}
/*������°��
�ݺ�: fib(40)= 102334155, ����ð��� 0.000000���Դϴ�.
��ȯ: fib(40)= 102334155, ����ð��� 1.616000���Դϴ�.
10���� �Է�: 29
��ȯ: 29, 2����: 11101
�ݺ�: 29, 2����: 11101

C:\Users\USER\source\repos\Project11\x64\Debug\Project11.exe(���μ��� 12724��)��(��) ����Ǿ����ϴ�(�ڵ�: 0��).
������� ������ �� �ܼ��� �ڵ����� �������� [����] -> [�ɼ�] -> [�����] > [������� �����Ǹ� �ڵ����� �ܼ� �ݱ�]�� ����ϵ��� �����մϴ�.
�� â�� �������� �ƹ� Ű�� ��������...
*/
/*������°��
�ݺ�: fib(40)= 102334155, ����ð��� 0.000000���Դϴ�.
��ȯ: fib(40)= 102334155, ����ð��� 7.448000���Դϴ�.
10���� �Է�: 29
��ȯ: 29, 2����: 11101
�ݺ�: 29, 2����: 11101
����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .
*/