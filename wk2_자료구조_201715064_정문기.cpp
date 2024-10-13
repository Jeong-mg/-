
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMS 101

void get_max_min(int* p, int* last_p, int* max, int* min)
{
	//새로운 변수를 선언하지 마시오.
	//배열의 차원(3x5)을 상수로 사용하지 마시오.
	*max = *min = *p++;

	//1. 아래를 완성하시오.
	while (p <= last_p) {
		if (*p > *max)
			*max = *p;
		else if (*p < *min)
			*min = *p;
		p++;
	}

}

struct point
{
	int x, y;
};

double get_distance(point* p, int size)
{
	//새로운 변수를 선언하지 마시오.
	double tmp, distance = 0.0;

	//2. 아래를 완성하시오. 반복 제어 변수 선언은 허용합니다.
	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size; ++j) {
			double tmp = sqrt(pow(p[i].x - p[j].x, 2) + pow(p[i].y - p[j].y, 2));
			if (tmp > distance)
				distance = tmp;
		}
	}

	return distance;
}
struct {
	double coef;
	int expon;
} terms[MAX_TERMS] = { {8,3}, {7,1}, {1,0}, {10,3}, {3,2},{1,0} };
int avail = 6;

// 두 개의 정수를 비교
int compare(int a, int b)
{
	if (a > b) return 1;
	else if (a == b) return 0;
	else return -1;
}
// 새로운 항을 다항식에 추가한다.
void attach(double coef, int expon)
{
	if (avail > MAX_TERMS) {
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail++].expon = expon;
}
// C = A + B
void poly_sub(int As, int Ae, int Bs, int Be, int* Cs, int* Ce)
{
	double tempcoef;
	*Cs = avail;
	while (As <= Ae && Bs <= Be)
		switch (compare(terms[As].expon, terms[Bs].expon)) {
			//3. 아래를 완성하시오.
		case 1:
			attach(-terms[As].coef, terms[As].expon);
			As++;
			break;
		case 0:
			attach(terms[As].coef - terms[Bs].coef, terms[As].expon);
			As++;
			Bs++;
			break;
		case -1:
			attach(-terms[Bs].coef, terms[Bs].expon);
			Bs++;
			break;
		}
	// A의 나머지 항들을 이동함
	for (; As <= Ae; As++)
		attach(terms[As].coef, terms[As].expon);
	// B의 나머지 항들을 이동함
	for (; Bs <= Be; Bs++)
		attach(-terms[Bs].coef, terms[Bs].expon);
	*Ce = avail - 1;
}
void print_poly(int s, int e)
{
	for (int i = s; i < e; i++)
		printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);
	printf("%3.1fx^%d\n", terms[e].coef, terms[e].expon);
}
typedef struct {
	int row;
	int col;
	int value;
} element;
typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;	// 행의 개수
	int cols;	// 열의 개수
	int terms; 	// 항의 개수
} SparseMatrix;
/* 행렬곱 프로그램
	int mat1[a][b] = { {1, 2, 3}, {4, 5, 6}};
	int mat2[b][c] = { {7, 8}, {9, 10}, {11, 12}};
	int result[a][c] = {0, };

	for(int i = 0; i < a; i++)
		for(int j = 0; j < c; j++)
			for(int k = 0; k < b; k++)
				result[i][j] += mat1[i][k] * mat2[k][j];
*/
void matrix_mult(SparseMatrix a, SparseMatrix b, SparseMatrix* c)
{
	c->rows = a.rows;
	c->cols = b.cols;
	c->terms = 0;

	int** arr = new int* [c->rows];
	for (int i = 0; i < c->rows; i++) {
		arr[i] = new int[c->cols];
		for (int j = 0; j < c->cols; j++)
			arr[i][j] = 0;
	}
	for (int at = 0; at < a.terms; at++) {
		for (int bt = 0; bt < b.terms; bt++) {
			if (a.data[at].col == b.data[bt].row)
				arr[a.data[at].row][b.data[bt].col] += a.data[at].value * b.data[bt].value;
		}
	}

	//4. 아래를 완성하시오. 반복 제어 변수 선언은 허용합니다.
	for (int i = 0; i < c->rows; i++) {
		for (int j = 0; j < c->cols; j++) {
			if (arr[i][j] != 0) {
				c->data[c->terms].row = i;
				c->data[c->terms].col = j;
				c->data[c->terms].value = arr[i][j];
				c->terms++;
			}
		}
	}
}
void matrix_print(SparseMatrix a)
{
	printf("====================\n");
	for (int i = 0; i < a.terms; i++) {
		printf("(%d, %d, %d) \n", a.data[i].row, a.data[i].col, a.data[i].value);
	}
	printf("====================\n");
}

int main(void)
{
	int list[3][5];
	int i, j, max, min;

	//문제 1.
	srand(1);
	printf("list:\n");
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 5; j++) {
			list[i][j] = rand() % 100 + 101;
			printf("%5d", list[i][j]);
		}
		printf("\n");
	}
	get_max_min(*list, *(list + 2) + 4, &max, &min);
	printf("최대값: %d, 최소값: %d\n", max, min);

	//문제 2.
	point point_arr[5] =
	{
		3, 5,
		4, 9,
		1, 9,
		6, 2,
		8, 3,
	};

	printf("\n최대 거리: %.2f\n\n", get_distance(point_arr, 5));

	//문제 3
	int As = 0, Ae = 2, Bs = 3, Be = 5, Cs, Ce;
	poly_sub(As, Ae, Bs, Be, &Cs, &Ce);
	printf("p1(x)= ");
	print_poly(As, Ae);
	printf("p2(x)= ");
	print_poly(Bs, Be);
	printf("p1(x)-p2(x)= ");
	print_poly(Cs, Ce);

	//문제 4
	SparseMatrix m1 = {
	{ { 0, 0, 1 },{ 0, 1, 2 },{ 0, 2, 3 },
	  { 1, 0, 4 },{ 1, 1, 5 },{ 1, 2, 6 } },
	2, 3, 6
	};
	SparseMatrix m2 = {
	{ { 0, 0, 7 },{ 0, 1, 8 },
	  { 1, 0, 9 },{ 1, 1, 10 },
	  { 2, 0, 11 },{ 2, 1, 12 } },
	3, 2, 6
	};
	SparseMatrix m3 = { {{0}}, 0, 0, 0 };
	matrix_mult(m1, m2, &m3);
	matrix_print(m3);

	return 0;
}

/*실제출력결과
list:
  142  168  135  101  170
  125  179  159  163  165
  106  146  182  128  162
최대값: 182, 최소값: 101

최대 거리: 9.22

p1(x)= 8.0x^3 + 7.0x^1 + 1.0x^0
p2(x)= 10.0x^3 + 3.0x^2 + 1.0x^0
p1(x)-p2(x)= -2.0x^3 + -3.0x^2 + -7.0x^1 + 0.0x^0
====================
(0, 0, 58)
(0, 1, 64)
(1, 0, 139)
(1, 1, 154)
====================

C:\Users\USER\source\repos\Project12\x64\Debug\Project12.exe(프로세스 19044개)이(가) 종료되었습니다(코드: 0개).
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요...
*/
/*
예시 출력
list:
  142  168  135  101  170
  125  179  159  163  165
  106  146  182  128  162
최대값: 182, 최소값: 101

최대 거리: 9.22

p1(x)= 8.0x^3 + 7.0x^1 + 1.0x^0
p2(x)= 10.0x^3 + 3.0x^2 + 1.0x^0
p1(x)-p2(x)= -2.0x^3 + -3.0x^2 + 7.0x^1
====================
(0, 0, 58)
(0, 1, 64)
(1, 0, 139)
(1, 1, 154)
====================
계속하려면 아무 키나 누르십시오 . . .
*/