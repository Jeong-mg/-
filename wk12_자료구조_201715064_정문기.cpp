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
	int median_index = (left + right) / 2;//n은 홀수라 가정

	//아래를 완성하시오
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

// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_max_heap(HeapType* h, int item) {
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item > h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;     // 새로운 노드를 삽입
}
// 삭제 함수
int delete_max_heap(HeapType* h) {
	int parent, child;
	int item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드중 키값이 더 큰 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child]) < h->heap[child + 1])
			child++;
		if (temp >= h->heap[child]) break;
		// 한단계 아래로 이동
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
	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item < h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}
// 삭제 함수
int delete_min_heap(HeapType* h) {
	int parent, child;
	int item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드중 더 큰 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child]) > h->heap[child + 1])
			child++;
		if (temp <= h->heap[child]) break;
		// 한단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
// 초기화 함수
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

		//아래를 완성하시오
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

	printf("힙 중앙값: %d, 분할 중앙값:%d\n", heap_median, part_median);

	return 0;
}
/*실제 출력
힙 중앙값: 506, 분할 중앙값:506

C:\Users\USER\source\repos\Project19\x64\Debug\Project19.exe(프로세스 21848개)이(가) 종료되었습니다(코드: 0개).
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요...
*/
/* 예시출력
힙 중앙값: 506, 분할 중앙값:506
계속하려면 아무 키나 누르십시오 . . .
*/