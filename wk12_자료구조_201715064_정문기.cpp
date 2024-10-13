#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1001
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

int list[MAX_SIZE];
int n;

int partition(int list[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do
			low++;
		while (low <= right && list[low] < pivot);
		do
			high--;
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp);
	} while (low < high);

	SWAP(list[left], list[high], temp);
	return high;
}

int get_median_partition(int list[], int n)
{
	int left = 0, right = n - 1;
	int pivot;
	int median_index = (left + right) / 2;//n�� Ȧ���� ����

	//�Ʒ��� �ϼ��Ͻÿ�
	while (left <= right) {
		pivot = partition(list, left, right);
		if (pivot == median_index) {
			return list[pivot];
		}
		else if (pivot < median_index) {
			left = pivot + 1;
		}
		else {
			right = pivot - 1;
		}
	}
	return list[pivot];
}

typedef struct {
	int heap[MAX_SIZE];
	int heap_size;
} HeapType;

// ���� ����� ������ heap_size�� ���� h�� item�� �����Ѵ�.
// ���� �Լ�
void insert_max_heap(HeapType* h, int item) {
	int i;
	i = ++(h->heap_size);

	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item > h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;     // ���ο� ��带 ����
}
// ���� �Լ�
int delete_max_heap(HeapType* h) {
	int parent, child;
	int item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ���� Ű���� �� ū �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child]) < h->heap[child + 1])
			child++;
		if (temp >= h->heap[child]) break;
		// �Ѵܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;
	return item;
}
void insert_min_heap(HeapType* h, int item) {
	int i;
	i = ++(h->heap_size);
	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item < h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // ���ο� ��带 ����
}
// ���� �Լ�
int delete_min_heap(HeapType* h) {
	int parent, child;
	int item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ���� �� ū �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child]) > h->heap[child + 1])
			child++;
		if (temp <= h->heap[child]) break;
		// �Ѵܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
// �ʱ�ȭ �Լ�
void init(HeapType* h)
{
	h->heap_size = 0;
}

int get_median_heap(int list[], int n) {
	HeapType max_heap, min_heap;
	int i;

	init(&max_heap);
	init(&min_heap);
	insert_max_heap(&max_heap, list[0]);

	for (i = 1; i < n; i++) {
		if (list[i] <= max_heap.heap[1])
			insert_max_heap(&max_heap, list[i]);
		else
			insert_min_heap(&min_heap, list[i]);

		//�Ʒ��� �ϼ��Ͻÿ�
		if (max_heap.heap_size > min_heap.heap_size + 1) {
			insert_min_heap(&min_heap, delete_max_heap(&max_heap));
		}
		else if (min_heap.heap_size > max_heap.heap_size) {
			insert_max_heap(&max_heap, delete_min_heap(&min_heap));
		}
	}
	return max_heap.heap[1];
}
int main(void)
{
	n = MAX_SIZE;
	int i;
	int heap_median, part_median;

	srand((unsigned)1);
	//srand((unsigned)time(NULL));
	for (i = 0; i < n; i++)
		list[i] = rand() % MAX_SIZE;
	heap_median = get_median_heap(list, n);
	part_median = get_median_partition(list, n);

	printf("�� �߾Ӱ�: %d, ���� �߾Ӱ�:%d\n", heap_median, part_median);

	return 0;
}
/*���� ���
�� �߾Ӱ�: 506, ���� �߾Ӱ�:506

C:\Users\USER\source\repos\Project19\x64\Debug\Project19.exe(���μ��� 21848��)��(��) ����Ǿ����ϴ�(�ڵ�: 0��).
������� ������ �� �ܼ��� �ڵ����� �������� [����] -> [�ɼ�] -> [�����] > [������� �����Ǹ� �ڵ����� �ܼ� �ݱ�]�� ����ϵ��� �����մϴ�.
�� â�� �������� �ƹ� Ű�� ��������...
*/
/* �������
�� �߾Ӱ�: 506, ���� �߾Ӱ�:506
����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .
*/