#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 100
typedef struct TreeNode {
	char ch;
	int weight;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;
typedef TreeNode* TreePtr;
typedef struct {
	TreeNode* heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// 초기화 함수
void init(HeapType* h)
{
	h->heap_size = 0;
}
// 삽입 함수
void insert_min_heap(HeapType* h, TreePtr ptr)
{
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (ptr->weight < h->heap[i / 2]->weight)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = ptr;     // 새로운 노드를 삽입
}
// 삭제 함수
TreePtr delete_min_heap(HeapType* h)
{
	int parent, child;
	TreePtr ptr, tmp;

	ptr = h->heap[1];
	tmp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child]->weight) > h->heap[child + 1]->weight)
			child++;
		if (tmp->weight <= h->heap[child]->weight) break;
		// 한단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = tmp;
	return ptr;
}

// 이진 트리 생성 함수
TreePtr make_node(TreePtr left, TreePtr right)
{
	TreePtr node_ptr = (TreePtr)malloc(sizeof(TreeNode));
	if (node_ptr == NULL) {
		fprintf(stderr, "메모리 에러\n");
		exit(1);
	}
	node_ptr->left = left;
	node_ptr->right = right;
	return node_ptr;
}
// 이진 트리 제거 함수
void destroy_tree(TreePtr root)
{
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

// 허프만 코드 생성 함수
TreePtr huffman_tree(char ch_arr[], int freq[], int n)
{
	int i;
	TreePtr x, c1, c2;
	HeapType heap;

	init(&heap);
	for (i = 0; i < n; i++) {
		x = make_node(NULL, NULL);
		x->ch = ch_arr[i];
		x->weight = freq[i];
		insert_min_heap(&heap, x);
	}
	while (heap.heap_size > 1) {
		//아래를 완성하시오.
		c1 = delete_min_heap(&heap);
		c2 = delete_min_heap(&heap);

		x = make_node(c1, c2);
		x->weight = c1->weight + c2->weight;

		insert_min_heap(&heap, x);
	}
	return delete_min_heap(&heap); // 최종 트리
}

void traverse(TreePtr p, char code[], int level) {
	// '0'을 저장하고 순환호출한다. 
	if (p->left) {
		code[level] = '0';
		traverse(p->left, code, level + 1);
	}

	// '1'을 저장하고 순환호출한다. 
	if (p->right) {
		code[level] = '1';
		traverse(p->right, code, level + 1);
	}

	// 단말노드이면 코드를 출력한다. 
	if (p->left == NULL && p->right == NULL) {
		printf("%c: ", p->ch);
		for (int i = 0; i < level; i++)
			printf("%c", code[i]);
		printf("\n");
	}
}
// 주함수 
int main(void)
{
	char ch_arr[] = { 'A', 'B', 'C', 'D', 'E' };
	int freq[] = { 15, 12, 8, 6, 4 };
	TreeNode* node = huffman_tree(ch_arr, freq, 5);
	char h_code[100];

	traverse(node, h_code, 0);
	destroy_tree(node);

	return 0;
}
/* 실제 출력
C: 00
E: 010
D: 011
B: 10
A: 11

C:\Users\USER\source\repos\Project17\x64\Debug\Project17.exe(프로세스 15400개)이(가) 종료되었습니다(코드: 0개).
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요...
*/
/* 예시 출력
C : 00
E : 010
D : 011
B : 10
A : 11
*/