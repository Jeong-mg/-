
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	int x, y;
} point;
typedef struct ListNode { // ��� Ÿ��
	point data;
	struct ListNode* link;
} ListNode;

ListNode* insert(ListNode* head, point ele) {
	ListNode* prev, * ptr;
	prev = NULL;
	ptr = head;
	double dist = hypot(ele.x, ele.y);

	//�Ʒ��� �ϼ��Ͻÿ�.
	while (ptr != NULL && dist > hypot(ptr->data.x, ptr->data.y)) {
		prev = ptr;
		ptr = ptr->link;
	}
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	if (temp != NULL) {
		temp->data = ele;
		temp->link = ptr;
		if (prev == NULL)
			head = temp;
		else
			prev->link = temp;
	}

	return head;
}
ListNode* insert_first(ListNode* head, point ele)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));//(1)
	p->data = ele;		//(2)
	p->link = head;		//(3)
	return p;			//(4)
}

//�������� ������ ��ǥ(x,y)�� ���̰� �񳻸��������� ���ĵǾ� ���Ḯ��Ʈ�� ��带 �����Ѵ�.
ListNode* remove(ListNode* head, point ele) {
	ListNode* prev, * ptr, * removed;
	prev = NULL;
	ptr = head;
	//�Ʒ��� �ϼ��Ͻÿ�.
	while (ptr != NULL) {
		if (ptr->data.x == ele.x && ptr->data.y == ele.y) {
			ListNode* removed = ptr; 
			if (prev == NULL) { 
				head = ptr->link;
			}
			else {
				prev->link = ptr->link;
			}
			ptr = ptr->link; 
			free(removed);
		}
		else {
			prev = ptr; 
			ptr = ptr->link; 
		}
	}
	return head;
}
void print(ListNode* head)
{
	printf("��ǥ: ");
	for (; head; head = head->link) {
		printf("(%d,%d)=%.2f ", head->data.x, head->data.y, hypot(head->data.x, head->data.y));
	}
	printf("\n");
}

//�������� ������ ��ǥ(x,y)�� ���̰� �񳻸��������� ���ĵǾ� ���Ḯ��Ʈ�� �����Ѵ�.
int main(void)
{
	ListNode* head = NULL;

	point p;

	p.x = 6, p.y = 5;
	head = insert_first(head, p);
	p.x = 3, p.y = 4;
	head = insert_first(head, p);
	p.x = 4, p.y = 3;
	head = insert_first(head, p);
	p.x = 3, p.y = 3;
	head = insert_first(head, p);
	p.x = 3, p.y = 1;
	head = insert_first(head, p);
	print(head);

	p.x = 6, p.y = 5;
	head = remove(head, p);
	p.x = 3, p.y = 1;
	head = remove(head, p);
	print(head);
}
/* �������
��ǥ: (3,1)=3.16 (3,3)=4.24 (4,3)=5.00 (3,4)=5.00 (6,5)=7.81
��ǥ: (3,3)=4.24 (4,3)=5.00 (3,4)=5.00

C:\Users\USER\source\repos\Project13\x64\Debug\Project13.exe(���μ��� 7556��)��(��) ����Ǿ����ϴ�(�ڵ�: 0��).
������� ������ �� �ܼ��� �ڵ����� �������� [����] -> [�ɼ�] -> [�����] > [������� �����Ǹ� �ڵ����� �ܼ� �ݱ�]�� ����ϵ��� �����մϴ�.
�� â�� �������� �ƹ� Ű�� ��������...
*/
/* �������
��ǥ: (3,1)=3.16 (3,3)=4.24 (3,4)=5.00 (4,3)=5.00 (6,5)=7.81
��ǥ: (3,3)=4.24 (3,4)=5.00 (4,3)=5.00
����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .
*/
