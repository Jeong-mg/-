#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define MAX_STACK_SIZE 100
#define MAX_SIZE 10

typedef int element;

//=======================================
//스택 선언 시작
typedef struct {
	element data[MAX_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_SIZE - 1));
}
// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// 피크함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 

// =========원형덱 프로그램 시작===========
//#define MAX_QUEUE_SIZE 5
//typedef char element;
typedef struct { // 큐 타입
	element  data[MAX_SIZE];
	int  front, rear;
} DequeType;

// 오류 함수
void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 초기화 
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_SIZE == q->front);
}
// 원형큐 출력 함수
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
//후단 삽입 함수
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->data[q->rear] = item;
}

// 전단 삭제 함수
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_SIZE;
	return q->data[q->front];
}
// 전단 삽입 함수
void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_SIZE) % MAX_SIZE;
}
//후단 삭제 함수 
element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->rear = (q->rear - 1 + MAX_SIZE) % MAX_SIZE;
	return q->data[prev];
}
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_SIZE];
}

element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[q->rear];
}
// =========원형덱 프로그램 끝===========

//prob1
//배열과 포인터 사용 예로 아래의 지시대로 안하면 감점합니다.
#define ROWS 3
#define COLS 4
int fsum_1(int a[][COLS]) {
	int sum = 0;

	//1. 아래를 완성하시오. a에 대한 2차원 배열로 접근
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			sum += a[i][j];
		}
	}
	return sum;
}
int fsum_2(int* p) {
	int sum = 0;

	//2. 아래를 완성하시오. p에 대한 일차원 포인터로 접근
	for (int i = 0; i < ROWS * COLS; i++) {
		sum += *(p + i);
	}
	return sum;
}
int fsum_3(int(*p)[COLS]) {
	int sum = 0;

	//3. 아래를 완성하시오. p에 대한 2차원 배열로 접근
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			sum += p[i][j];
		}
	}
	return sum;
}
int fsum_4(int(*p)[COLS]) {
	int sum = 0;

	//4. 아래를 완성하시오. p에 대한 1차원 배열로 접근
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
//입력식의 연산자는 *,/,+.-의 이항연산자만 허용되고 각 연산자는 빈칸으로 구분한다.
//피연산자는 음수를 포함한 정수 입력이 가능하다.
int eval(char exp[])
{
	char seps[] = " ";
	char* token;
	int op1, op2;
	StackType s;
	init_stack(&s);
	token = strtok(exp, seps);

	//아래를 완성하시오. 새로운 변수를 선언하지 마시오.
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
	printf("후위표기식은 %s\n", exp);
	result = eval(exp);
	printf("결과값은 %d\n", result);
}

//prob3
//덱을 사용한 회문 판단
void prob3() {
	char word[30], * p;
	DequeType queue;

	init_deque(&queue);
	printf("회문 입력: ");
	scanf("%s", word);
	p = word;
	while (*p != '\0') {
		add_front(&queue, *p);
		p++;
	}

	//아래를 완성하시오. 새로운 변수를 선언하지 마시오.
	//배열의 인덱스는 사용하지 마시고 덱에서 정의한 함수만을 사용하시오.
	while (!is_empty(&queue)) {
		if (delete_front(&queue) != delete_rear(&queue)) {
			printf("회문이 아닙니다.\n");
			return;
		}
	if (is_empty(&queue))
		printf("회문입니다.\n");
	else
		printf("회문이 아닙니다.\n");
}
int main(void)
{
	prob1();
	prob2();
	prob3();
	prob3();

	return 0;
}
/*실제출력
sum1:78, sum2:78, sum3:78, sum4:78
후위표기식은 -80 -20 / 35 - 33 222 * +
결과값은 7295
회문 입력: radar
회문입니다.
회문 입력: radfar
회문이 아닙니다.

C:\Users\USER\source\repos\Project3\x64\Debug\Project3.exe(프로세스 9824개)이(가) 종료되었습니다(코드: 0개).
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요...
*/
/*예시출력
sum1:78, sum2:78, sum3:78, sum4:78
후위표기식은 -80 -20 / 35 - 33 222 * +
결과값은 7295
회문 입력: radar
회문입니다.
회문 입력: radfar
회문이 아닙니다.
계속하려면 아무 키나 누르십시오 . . .
*/