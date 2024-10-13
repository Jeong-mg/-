
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ListNode { // ��� Ÿ��
	int coef;
	int expon;
	struct ListNode* link;
} ListNode;

// ���� ����Ʈ ���(����)
typedef struct ListType { // ����Ʈ ��� Ÿ��
	int size;
	ListNode* head;
	ListNode* tail;
} ListType;

// ���� �Լ�
void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
//  ����Ʈ ��� ���� �Լ�
ListType* create()
{
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

// plist�� ���� ����Ʈ�� ����� ����Ű�� ������, coef�� ���, 
// expon�� ����
void insert_last(ListType* plist, int coef, int expon)
{
	ListNode* temp =
		(ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL) error("�޸� �Ҵ� ����");
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
//coef, expon���� ������ ���� ���׽Ŀ� �����Ѵ�.
//���׽��� ������ ū �׼����� �����Ǿ� �ִ�.
void insert_mult(ListType* plist3, int coef, int expon) {
	ListNode* prev, * ptr;
	prev = NULL;
	ptr = plist3->head;
	while (ptr != NULL && expon < ptr->expon) {
		prev = ptr;
		ptr = ptr->link;
	}
	//�Ʒ��� �ϼ��Ͻÿ�. ���ο� ������ �������� ���ÿ�.
	if (ptr != NULL && expon == ptr->expon)
		ptr->coef += coef;
	else {
		ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
		if (temp == NULL) error("�޸� �Ҵ� ����");
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
	//���׽��� ������ �� ���׽��� ������ ���� ���Ѵ�.
	void poly_multiply(ListType * plist1, ListType * plist2, ListType * plist3)
	{
		ListNode* a, * b;//a:plist1�� head(ù�׿� ���� ������), b:plist2�� head(ù�׿� ���� ������)
		a = plist1->head;;
		//�Ʒ��� �ϼ��Ͻÿ�.  ���ο� ������ �������� ���ÿ�.
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

		// ���� ����Ʈ ��� ����
		list1 = create();
		list2 = create();
		list3 = create();

		// ���׽� 1�� ���� 
		insert_last(list1, 3, 3);
		insert_last(list1, 2, 1);

		// ���׽� 2�� ���� 
		insert_last(list2, 2, 3);
		insert_last(list2, -3, 1);
		insert_last(list2, 1, 0);

		poly_print(list1);
		poly_print(list2);

		// ���׽� 3 = ���׽� 1 + ���׽� 2
		poly_multiply(list1, list2, list3);
		poly_print(list3);

		//free(list1); free(list2); free(list3);
	}
	/* �������
	polynomial = 3^3 + 2^1 +
polynomial = 2^3 + -3^1 + 1^0 +
polynomial = 6^6 + -5^4 + 3^3 + -6^2 + 2^1 +

C:\Users\USER\source\repos\Project12\x64\Debug\Project12.exe(���μ��� 10528��)��(��) ����Ǿ����ϴ�(�ڵ�: 0��).
������� ������ �� �ܼ��� �ڵ����� �������� [����] -> [�ɼ�] -> [�����] > [������� �����Ǹ� �ڵ����� �ܼ� �ݱ�]�� ����ϵ��� �����մϴ�.
�� â�� �������� �ƹ� Ű�� ��������...

	*/
	/* �������
	polynomial = 3^3 + 2^1 +
	polynomial = 2^3 + -3^1 + 1^0 +
	polynomial = 6^6 + -5^4 + 3^3 + -6^2 + 2^1 +
	����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .
	*/
