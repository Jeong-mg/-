
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	int x, y;
} point;
typedef struct ListNode { // 노드 타입
	point data;
	struct ListNode* link;
} ListNode;

ListNode* insert(ListNode* head, point ele) {
	ListNode* prev, * ptr;
	prev = NULL;
	ptr = head;
	double dist = hypot(ele.x, ele.y);

	//아래를 완성하시오.
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

//원점으로 부터의 좌표(x,y)의 길이가 비내림차순으로 정렬되어 연결리스트의 노드를 삭제한다.
ListNode* remove(ListNode* head, point ele) {
	ListNode* prev, * ptr, * removed;
	prev = NULL;
	ptr = head;
	//아래를 완성하시오.
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
	printf("좌표: ");
	for (; head; head = head->link) {
		printf("(%d,%d)=%.2f ", head->data.x, head->data.y, hypot(head->data.x, head->data.y));
	}
	printf("\n");
}

//원점으로 부터의 좌표(x,y)의 길이가 비내림차순으로 정렬되어 연결리스트를 구성한다.
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
/* 실제출력
좌표: (3,1)=3.16 (3,3)=4.24 (4,3)=5.00 (3,4)=5.00 (6,5)=7.81
좌표: (3,3)=4.24 (4,3)=5.00 (3,4)=5.00

C:\Users\USER\source\repos\Project13\x64\Debug\Project13.exe(프로세스 7556개)이(가) 종료되었습니다(코드: 0개).
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요...
*/
/* 예시출력
좌표: (3,1)=3.16 (3,3)=4.24 (3,4)=5.00 (4,3)=5.00 (6,5)=7.81
좌표: (3,3)=4.24 (3,4)=5.00 (4,3)=5.00
계속하려면 아무 키나 누르십시오 . . .
*/
