
#define _CRT_SECURE_NO_WARNINGS
#define MAXWORD 80

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct element {
	char word[MAXWORD];
	int count;
} element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

// �ʱ�ȭ �Լ�
ListNode* init(ListNode* head)
{
	head = (ListNode*)malloc(sizeof(ListNode));
	if (head == NULL) exit(1);
	head->link = NULL;
	return head;
}
//��� ��带 �̿��� ���� �Լ�
void insert_node(ListNode* head, char* key)
{
	//�Ʒ��� �ϼ��Ͻÿ�
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	if (newNode == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	strcpy(newNode->data.word, key);
	newNode->data.count = 1;
	newNode->link = NULL;

	ListNode* prev = head;
	ListNode* current = head->link;

	while (current != NULL && strcmp(current->data.word, key) < 0) {
		prev = current;
		current = current->link;
	}

	if (current != NULL && strcmp(current->data.word, key) == 0) {
		current->data.count++;
		free(newNode); 
	}
	else {
		newNode->link = current;
		prev->link = newNode;
	}
}

//��� ��带 �̿��� ���� �Լ�
void delete_node(ListNode* head, char* key)
{
	//�Ʒ��� �ϼ��Ͻÿ�
	ListNode* prev = head;
	ListNode* current = head->link;

	
	while (current != NULL && strcmp(current->data.word, key) != 0) {
		prev = current;
		current = current->link;
	}

	if (current == NULL) {
		return;
	}

	if (current->data.count > 1) {
		current->data.count--;
	}
	else {
		prev->link = current->link;
		free(current);
	
	}
}
void sort_print(ListNode* head) {
	ListNode* ptr = head->link;

	printf("�ܾ� \tȸ��\n");
	while (ptr) {
		printf("%s \t%d\n", ptr->data.word, ptr->data.count);
		ptr = ptr->link;
	}
}
int main()
{
	FILE* fp;
	char word[MAXWORD];
	ListNode* head = NULL;

	head = init(head);

	//fopen_s(&fp, "data.txt", "r");
	fp = fopen("data.txt", "r");
	//while (fscanf_s(fp, "%s", word, sizeof(word)) != EOF) {
	while (fscanf(fp, "%s", word) != EOF) {
		printf("%s ", word);
		insert_node(head, word);
	}
	printf("\n");
	fclose(fp);

	sort_print(head);

	printf("������ �ܾ�(����:0): ");
	scanf_s("%s", word, sizeof(word));
	while (word[0] != '0') {
		delete_node(head, word);
		sort_print(head);
		printf("������ �ܾ�: ");
		//scanf_s("%s", word, sizeof(word));
		scanf("%s", word);
	}

	return 0;
}
/*�������
���� ����� ����ϴ� ���� ����� ���� ���� �ƴմϴ� �ٸ� ������� ���� ȫ�ȸ��� ����������� ����� ���� ��ߵ� ����ϴ� ����Դϴ�
�ܾ�    ȸ��
����    1
����    1
�����  1
����Դϴ�      1
����    2
����    1
�ٸ�    1
�����  1
�����  1
��ߵ�  1
�������        1
����ϴ�        2
�����������    1
�ƴմϴ�        1
����    1
ȫ�ȸ���        1
������ �ܾ�(����:0): ����
�ܾ�    ȸ��
����    1
�����  1
����Դϴ�      1
����    2
����    1
�ٸ�    1
�����  1
�����  1
��ߵ�  1
�������        1
����ϴ�        2
�����������    1
�ƴմϴ�        1
����    1
ȫ�ȸ���        1
������ �ܾ�: ����
�ܾ�    ȸ��
����    1
�����  1
����Դϴ�      1
����    1
����    1
�ٸ�    1
�����  1
�����  1
��ߵ�  1
�������        1
����ϴ�        2
�����������    1
�ƴմϴ�        1
����    1
ȫ�ȸ���        1
������ �ܾ�: ����
�ܾ�    ȸ��
����    1
�����  1
����Դϴ�      1
����    1
����    1
�ٸ�    1
�����  1
�����  1
��ߵ�  1
�������        1
����ϴ�        2
�����������    1
�ƴմϴ�        1
����    1
ȫ�ȸ���        1
������ �ܾ�: 0

C:\Users\USER\source\repos\Project14\x64\Debug\Project14.exe(���μ��� 26904��)��(��) ����Ǿ����ϴ�(�ڵ�: 0��).
������� ������ �� �ܼ��� �ڵ����� �������� [����] -> [�ɼ�] -> [�����] > [������� �����Ǹ� �ڵ����� �ܼ� �ݱ�]�� ����ϵ��� �����մϴ�.
�� â�� �������� �ƹ� Ű�� ��������...
*/
/*���� ���
���� ����� ����ϴ� ���� ����� ���� ���� �ƴմϴ� �ٸ� ������� ���� ȫ�ȸ���
����������� ����� ���� ��ߵ� ����ϴ� ����Դϴ�
�ܾ�    ȸ��
����    1
����    1
�����  1
����Դϴ�      1
����    2
����    1
�ٸ�    1
�����  1
�����  1
��ߵ�  1
�������        1
����ϴ�        2
�����������    1
�ƴմϴ�        1
����    1
ȫ�ȸ���        1
������ �ܾ�(����:0): ����
�ܾ�    ȸ��
����    1
�����  1
����Դϴ�      1
����    2
����    1
�ٸ�    1
�����  1
�����  1
��ߵ�  1
�������        1
����ϴ�        2
�����������    1
�ƴմϴ�        1
����    1
ȫ�ȸ���        1
������ �ܾ�: ����
�ܾ�    ȸ��
����    1
�����  1
����Դϴ�      1
����    1
����    1
�ٸ�    1
�����  1
�����  1
��ߵ�  1
�������        1
����ϴ�        2
�����������    1
�ƴմϴ�        1
����    1
ȫ�ȸ���        1
������ �ܾ�: ����
�ܾ�    ȸ��
����    1
�����  1
����Դϴ�      1
����    1
����    1
�ٸ�    1
�����  1
�����  1
��ߵ�  1
�������        1
����ϴ�        2
�����������    1
�ƴմϴ�        1
����    1
ȫ�ȸ���        1
������ �ܾ�: 0
����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .
*/