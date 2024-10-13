
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ListNode { // 노드 타입
	int coef;
	int expon;
	struct ListNode* link;
} ListNode;

// 연결 리스트 헤더(정보)
typedef struct ListType { // 리스트 헤더 타입
	int size;
	ListNode* head;
	ListNode* tail;
} ListType;

// 오류 함수
void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
//  리스트 헤더 생성 함수
ListType* create()
{
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

// plist는 연결 리스트의 헤더를 가리키는 포인터, coef는 계수, 
// expon는 지수
void insert_last(ListType* plist, int coef, int expon)
{
	ListNode* temp =
		(ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL) error("메모리 할당 에러");
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;
	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++;
}
//coef, expon으로 구성된 항을 다항식에 삽입한다.
//다항식은 차수가 큰 항순으로 구성되어 있다.
void insert_mult(ListType* plist3, int coef, int expon) {
	ListNode* prev, * ptr;
	prev = NULL;
	ptr = plist3->head;
	while (ptr != NULL && expon < ptr->expon) {
		prev = ptr;
		ptr = ptr->link;
	}
	//아래를 완성하시오. 새로운 변수를 선언하지 마시오.
	if (ptr != NULL && expon == ptr->expon)
		ptr->coef += coef;
	else {
		ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
		if (temp == NULL) error("메모리 할당 에러");
		temp->coef = coef;
		temp->expon = expon;
		temp->link = ptr;
		if (prev == NULL)
			plist3->head = temp;
		else
			prev->link = temp;
		if (ptr == NULL)
			plist3->tail = temp;
		plist3->size++;
	}
}
	// list3 = list1 * list2
	//다항식의 곱셈은 두 다항식의 각항을 서로 곱한다.
	void poly_multiply(ListType * plist1, ListType * plist2, ListType * plist3)
	{
		ListNode* a, * b;//a:plist1의 head(첫항에 대한 포인터), b:plist2의 head(첫항에 대한 포인터)
		a = plist1->head;;
		//아래를 완성하시오.  새로운 변수를 선언하지 마시오.
		while (a != NULL) {
			b = plist2->head;
			while (b != NULL) {

				insert_mult(plist3, a->coef * b->coef, a->expon + b->expon);

				b = b->link;
			}
			a = a->link;
		}
}
	//
	//
void poly_print(ListType * plist)
	{
		ListNode* p = plist->head;

		printf("polynomial = ");
		for (; p; p = p->link) {
			printf("%d^%d + ", p->coef, p->expon);
		}
		printf("\n");
	}

	int main(void)
	{
		ListType* list1, * list2, * list3;

		// 연결 리스트 헤더 생성
		list1 = create();
		list2 = create();
		list3 = create();

		// 다항식 1을 생성 
		insert_last(list1, 3, 3);
		insert_last(list1, 2, 1);

		// 다항식 2를 생성 
		insert_last(list2, 2, 3);
		insert_last(list2, -3, 1);
		insert_last(list2, 1, 0);

		poly_print(list1);
		poly_print(list2);

		// 다항식 3 = 다항식 1 + 다항식 2
		poly_multiply(list1, list2, list3);
		poly_print(list3);

		//free(list1); free(list2); free(list3);
	}
	/* 실제출력
	polynomial = 3^3 + 2^1 +
polynomial = 2^3 + -3^1 + 1^0 +
polynomial = 6^6 + -5^4 + 3^3 + -6^2 + 2^1 +

C:\Users\USER\source\repos\Project12\x64\Debug\Project12.exe(프로세스 10528개)이(가) 종료되었습니다(코드: 0개).
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요...

	*/
	/* 예시출력
	polynomial = 3^3 + 2^1 +
	polynomial = 2^3 + -3^1 + 1^0 +
	polynomial = 6^6 + -5^4 + 3^3 + -6^2 + 2^1 +
	계속하려면 아무 키나 누르십시오 . . .
	*/
