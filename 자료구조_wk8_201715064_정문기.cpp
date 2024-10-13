#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100
#define SEL_NUM 10

typedef struct {
	int list[SEL_NUM + 1];
	int heap_size;
} HeapType;


// �ʱ�ȭ �Լ�
void init(HeapType* h)
{
	h->heap_size = 0;
}

// �ּ��� ���� �Լ�
void insert_min_heap(HeapType* h, int item)
{
	int i;
	i = ++(h->heap_size);

	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item < h->list[i / 2])) {
		h->list[i] = h->list[i / 2];
		i /= 2;
	}
	h->list[i] = item;     // ���ο� ��带 ����
}

// �Ʒ� �Լ��� �ϼ��Ͻÿ�.
void down_heap(HeapType* h, int item)
{
	// item �� ��Ʈ���� �۰ų� ������ �̹� ū Ű�� ���� �����Ͽ����Ƿ� �����Ѵ�. 


	// ��Ʈ�� Ű�� item���� ��ü�� �� �ּ��� �籸��
	int parent, child;
	parent = 1;
	child = 2;

	if (item <= h->list[1]) {
		return;
	}

	h->list[parent] = item;

	while (child <= h->heap_size) {

		if (child < h->heap_size && h->list[child] > h->list[child + 1]) {
			child++;
		}

		if (h->list[parent] <= h->list[child]) {
			break;
		}


		int temp = h->list[parent];
		h->list[parent] = h->list[child];
		h->list[child] = temp;


		parent = child;
		child *= 2;
	}
}

int main()
{
	int i;
	int list[MAX_ELEMENT];
	HeapType heap;

	init(&heap);
	srand(1);
	printf("���  ����Ʈ");
	for (int i = 0; i < MAX_ELEMENT; i++) {
		list[i] = rand() % 100;
		if (i % 10 == 0)
			printf("\n");
		printf("%d ", list[i]);
	}
	printf("\n");
	for (i = 0; i < SEL_NUM; i++)
		insert_min_heap(&heap, list[i]);
	for (; i < MAX_ELEMENT; i++)
		down_heap(&heap, list[i]);

	printf("\nū Ű %d ���� ����Ʈ\n", SEL_NUM);
	for (int i = 1; i <= SEL_NUM; i++)
		printf("%d ", heap.list[i]);
	printf("\n");

	return 0;
}/* ���� ���
 ���  ����Ʈ
41 67 34 0 69 24 78 58 62 64
5 45 81 27 61 91 95 42 27 36
91 4 2 53 92 82 21 16 18 95
47 26 71 38 69 12 67 99 35 94
3 11 22 33 73 64 41 11 53 68
47 44 62 57 37 59 23 41 29 78
16 35 90 42 88 6 40 42 64 48
46 5 90 29 70 50 6 1 93 48
29 23 84 54 56 40 66 76 31 8
44 39 26 23 37 38 18 82 29 41

ū Ű 10 ���� ����Ʈ
90 90 91 93 92 94 91 95 99 95

C:\Users\USER\source\repos\Project16\x64\Debug\Project16.exe(���μ��� 33452��)��(��) ����Ǿ����ϴ�(�ڵ�: 0��).
������� ������ �� �ܼ��� �ڵ����� �������� [����] -> [�ɼ�] -> [�����] > [������� �����Ǹ� �ڵ����� �ܼ� �ݱ�]�� ����ϵ��� �����մϴ�.
�� â�� �������� �ƹ� Ű�� ��������...
 */
 /*���� ���
 ���  ����Ʈ
 41 67 34 0 69 24 78 58 62 64
 5 45 81 27 61 91 95 42 27 36
 91 4 2 53 92 82 21 16 18 95
 47 26 71 38 69 12 67 99 35 94
 3 11 22 33 73 64 41 11 53 68
 47 44 62 57 37 59 23 41 29 78
 16 35 90 42 88 6 40 42 64 48
 46 5 90 29 70 50 6 1 93 48
 29 23 84 54 56 40 66 76 31 8
 44 39 26 23 37 38 18 82 29 41

 ū Ű 10 ���� ����Ʈ
 90 90 91 93 92 94 91 95 99 95
 ����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .
 */
