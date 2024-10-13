#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define MAX_STACK_SIZE 100
#define MAX_SIZE 10

typedef int element;

//=======================================
//���� ���� ����
typedef struct {
	element data[MAX_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_SIZE - 1));
}
// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// ��ũ�Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== ���� �ڵ��� �� ===== 

// =========������ ���α׷� ����===========
//#define MAX_QUEUE_SIZE 5
//typedef char element;
typedef struct { // ť Ÿ��
	element  data[MAX_SIZE];
	int  front, rear;
} DequeType;

// ���� �Լ�
void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// �ʱ�ȭ 
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}
// ���� ���� ���� �Լ�
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}
// ��ȭ ���� ���� �Լ�
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_SIZE == q->front);
}
// ����ť ��� �Լ�
void deque_print(DequeType* q)
{
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}
//�Ĵ� ���� �Լ�
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->data[q->rear] = item;
}

// ���� ���� �Լ�
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_SIZE;
	return q->data[q->front];
}
// ���� ���� �Լ�
void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_SIZE) % MAX_SIZE;
}
//�Ĵ� ���� �Լ� 
element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->rear = (q->rear - 1 + MAX_SIZE) % MAX_SIZE;
	return q->data[prev];
}
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_SIZE];
}

element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[q->rear];
}
// =========������ ���α׷� ��===========

//prob1
//�迭�� ������ ��� ���� �Ʒ��� ���ô�� ���ϸ� �����մϴ�.
#define ROWS 3
#define COLS 4
int fsum_1(int a[][COLS]) {
	int sum = 0;

	//1. �Ʒ��� �ϼ��Ͻÿ�. a�� ���� 2���� �迭�� ����
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			sum += a[i][j];
		}
	}
	return sum;
}
int fsum_2(int* p) {
	int sum = 0;

	//2. �Ʒ��� �ϼ��Ͻÿ�. p�� ���� ������ �����ͷ� ����
	for (int i = 0; i < ROWS * COLS; i++) {
		sum += *(p + i);
	}
	return sum;
}
int fsum_3(int(*p)[COLS]) {
	int sum = 0;

	//3. �Ʒ��� �ϼ��Ͻÿ�. p�� ���� 2���� �迭�� ����
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			sum += p[i][j];
		}
	}
	return sum;
}
int fsum_4(int(*p)[COLS]) {
	int sum = 0;

	//4. �Ʒ��� �ϼ��Ͻÿ�. p�� ���� 1���� �迭�� ����
	for (int i = 0; i < ROWS * COLS; i++) {
		sum += *(*p + i);
	}
	return sum;
}
void prob1(void)
{
	int arr[ROWS][COLS] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12} };
	int sum1 = fsum_1(arr);
	int sum2 = fsum_2(&arr[0][0]);
	int sum3 = fsum_3(arr);
	int sum4 = fsum_4(arr);

	printf("sum1:%d, sum2:%d, sum3:%d, sum4:%d\n", sum1, sum2, sum3, sum4);
}

//prob2
//�Է½��� �����ڴ� *,/,+.-�� ���׿����ڸ� ���ǰ� �� �����ڴ� ��ĭ���� �����Ѵ�.
//�ǿ����ڴ� ������ ������ ���� �Է��� �����ϴ�.
int eval(char exp[])
{
	char seps[] = " ";
	char* token;
	int op1, op2;
	StackType s;
	init_stack(&s);
	token = strtok(exp, seps);

	//�Ʒ��� �ϼ��Ͻÿ�. ���ο� ������ �������� ���ÿ�.
	while (token != NULL) {
		if (atoi(token) != 0)
			push(&s, atoi(token));
		else {
			op2 = pop(&s);
			op1 = pop(&s);
			switch (*token) {
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
		token = strtok(NULL, seps);
	}
	return pop(&s);
}
void prob2() {
	int result;
	char exp[] = "-80 -20 / 35 - 33 222 * +";
	printf("����ǥ����� %s\n", exp);
	result = eval(exp);
	printf("������� %d\n", result);
}

//prob3
//���� ����� ȸ�� �Ǵ�
void prob3() {
	char word[30], * p;
	DequeType queue;

	init_deque(&queue);
	printf("ȸ�� �Է�: ");
	scanf("%s", word);
	p = word;
	while (*p != '\0') {
		add_front(&queue, *p);
		p++;
	}

	//�Ʒ��� �ϼ��Ͻÿ�. ���ο� ������ �������� ���ÿ�.
	//�迭�� �ε����� ������� ���ð� ������ ������ �Լ����� ����Ͻÿ�.
	while (!is_empty(&queue)) {
		if (delete_front(&queue) != delete_rear(&queue)) {
			printf("ȸ���� �ƴմϴ�.\n");
			return;
		}
	if (is_empty(&queue))
		printf("ȸ���Դϴ�.\n");
	else
		printf("ȸ���� �ƴմϴ�.\n");
}
int main(void)
{
	prob1();
	prob2();
	prob3();
	prob3();

	return 0;
}
/*�������
sum1:78, sum2:78, sum3:78, sum4:78
����ǥ����� -80 -20 / 35 - 33 222 * +
������� 7295
ȸ�� �Է�: radar
ȸ���Դϴ�.
ȸ�� �Է�: radfar
ȸ���� �ƴմϴ�.

C:\Users\USER\source\repos\Project3\x64\Debug\Project3.exe(���μ��� 9824��)��(��) ����Ǿ����ϴ�(�ڵ�: 0��).
������� ������ �� �ܼ��� �ڵ����� �������� [����] -> [�ɼ�] -> [�����] > [������� �����Ǹ� �ڵ����� �ܼ� �ݱ�]�� ����ϵ��� �����մϴ�.
�� â�� �������� �ƹ� Ű�� ��������...
*/
/*�������
sum1:78, sum2:78, sum3:78, sum4:78
����ǥ����� -80 -20 / 35 - 33 222 * +
������� 7295
ȸ�� �Է�: radar
ȸ���Դϴ�.
ȸ�� �Է�: radfar
ȸ���� �ƴմϴ�.
����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .
*/