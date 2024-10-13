
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMS 101

void get_max_min(int* p, int* last_p, int* max, int* min)
{
	//���ο� ������ �������� ���ÿ�.
	//�迭�� ����(3x5)�� ����� ������� ���ÿ�.
	*max = *min = *p++;

	//1. �Ʒ��� �ϼ��Ͻÿ�.
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
	//���ο� ������ �������� ���ÿ�.
	double tmp, distance = 0.0;

	//2. �Ʒ��� �ϼ��Ͻÿ�. �ݺ� ���� ���� ������ ����մϴ�.
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

// �� ���� ������ ��
int compare(int a, int b)
{
	if (a > b) return 1;
	else if (a == b) return 0;
	else return -1;
}
// ���ο� ���� ���׽Ŀ� �߰��Ѵ�.
void attach(double coef, int expon)
{
	if (avail > MAX_TERMS) {
		fprintf(stderr, "���� ������ �ʹ� ����\n");
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
			//3. �Ʒ��� �ϼ��Ͻÿ�.
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
	// A�� ������ �׵��� �̵���
	for (; As <= Ae; As++)
		attach(terms[As].coef, terms[As].expon);
	// B�� ������ �׵��� �̵���
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
	int rows;	// ���� ����
	int cols;	// ���� ����
	int terms; 	// ���� ����
} SparseMatrix;
/* ��İ� ���α׷�
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

	//4. �Ʒ��� �ϼ��Ͻÿ�. �ݺ� ���� ���� ������ ����մϴ�.
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

	//���� 1.
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
	printf("�ִ밪: %d, �ּҰ�: %d\n", max, min);

	//���� 2.
	point point_arr[5] =
	{
		3, 5,
		4, 9,
		1, 9,
		6, 2,
		8, 3,
	};

	printf("\n�ִ� �Ÿ�: %.2f\n\n", get_distance(point_arr, 5));

	//���� 3
	int As = 0, Ae = 2, Bs = 3, Be = 5, Cs, Ce;
	poly_sub(As, Ae, Bs, Be, &Cs, &Ce);
	printf("p1(x)= ");
	print_poly(As, Ae);
	printf("p2(x)= ");
	print_poly(Bs, Be);
	printf("p1(x)-p2(x)= ");
	print_poly(Cs, Ce);

	//���� 4
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

/*������°��
list:
  142  168  135  101  170
  125  179  159  163  165
  106  146  182  128  162
�ִ밪: 182, �ּҰ�: 101

�ִ� �Ÿ�: 9.22

p1(x)= 8.0x^3 + 7.0x^1 + 1.0x^0
p2(x)= 10.0x^3 + 3.0x^2 + 1.0x^0
p1(x)-p2(x)= -2.0x^3 + -3.0x^2 + -7.0x^1 + 0.0x^0
====================
(0, 0, 58)
(0, 1, 64)
(1, 0, 139)
(1, 1, 154)
====================

C:\Users\USER\source\repos\Project12\x64\Debug\Project12.exe(���μ��� 19044��)��(��) ����Ǿ����ϴ�(�ڵ�: 0��).
������� ������ �� �ܼ��� �ڵ����� �������� [����] -> [�ɼ�] -> [�����] > [������� �����Ǹ� �ڵ����� �ܼ� �ݱ�]�� ����ϵ��� �����մϴ�.
�� â�� �������� �ƹ� Ű�� ��������...
*/
/*
���� ���
list:
  142  168  135  101  170
  125  179  159  163  165
  106  146  182  128  162
�ִ밪: 182, �ּҰ�: 101

�ִ� �Ÿ�: 9.22

p1(x)= 8.0x^3 + 7.0x^1 + 1.0x^0
p2(x)= 10.0x^3 + 3.0x^2 + 1.0x^0
p1(x)-p2(x)= -2.0x^3 + -3.0x^2 + 7.0x^1
====================
(0, 0, 58)
(0, 1, 64)
(1, 0, 139)
(1, 1, 154)
====================
����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .
*/