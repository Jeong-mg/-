#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100
#define SEL_NUM 10

typedef struct {
	int list[SEL_NUM + 1];
	int heap_size;
} HeapType;


// 초기화 함수
void init(HeapType* h)
{
	h->heap_size = 0;
}

// 최소힙 삽입 함수
void insert_min_heap(HeapType* h, int item)
{
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item < h->list[i / 2])) {
		h->list[i] = h->list[i / 2];
		i /= 2;
	}
	h->list[i] = item;     // 새로운 노드를 삽입
}

// 아래 함수를 완성하시오.
void down_heap(HeapType* h, int item)
{
	// item 이 루트보다 작거나 같으면 이미 큰 키로 힙을 구성하였으므로 제외한다. 


	// 루트의 키를 item으로 대체한 후 최소힙 재구성
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
	printf("대상  리스트");
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

	printf("\n큰 키 %d 선택 리스트\n", SEL_NUM);
	for (int i = 1; i <= SEL_NUM; i++)
		printf("%d ", heap.list[i]);
	printf("\n");

	return 0;
}/* 실제 출력
 대상  리스트
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

큰 키 10 선택 리스트
90 90 91 93 92 94 91 95 99 95

C:\Users\USER\source\repos\Project16\x64\Debug\Project16.exe(프로세스 33452개)이(가) 종료되었습니다(코드: 0개).
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요...
 */
 /*예시 결과
 대상  리스트
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

 큰 키 10 선택 리스트
 90 90 91 93 92 94 91 95 99 95
 계속하려면 아무 키나 누르십시오 . . .
 */
