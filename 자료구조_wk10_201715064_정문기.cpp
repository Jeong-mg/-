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

// �ʱ�ȭ �Լ�
void init(HeapType* h)
{
	h->heap_size = 0;
}
// ���� �Լ�
void insert_min_heap(HeapType* h, TreePtr ptr)
{
	int i;
	i = ++(h->heap_size);

	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (ptr->weight < h->heap[i / 2]->weight)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = ptr;     // ���ο� ��带 ����
}
// ���� �Լ�
TreePtr delete_min_heap(HeapType* h)
{
	int parent, child;
	TreePtr ptr, tmp;

	ptr = h->heap[1];
	tmp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ���� �� ���� �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child]->weight) > h->heap[child + 1]->weight)
			child++;
		if (tmp->weight <= h->heap[child]->weight) break;
		// �Ѵܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = tmp;
	return ptr;
}

// ���� Ʈ�� ���� �Լ�
TreePtr make_node(TreePtr left, TreePtr right)
{
	TreePtr node_ptr = (TreePtr)malloc(sizeof(TreeNode));
	if (node_ptr == NULL) {
		fprintf(stderr, "�޸� ����\n");
		exit(1);
	}
	node_ptr->left = left;
	node_ptr->right = right;
	return node_ptr;
}
// ���� Ʈ�� ���� �Լ�
void destroy_tree(TreePtr root)
{
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

// ������ �ڵ� ���� �Լ�
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
		//�Ʒ��� �ϼ��Ͻÿ�.
		c1 = delete_min_heap(&heap);
		c2 = delete_min_heap(&heap);

		x = make_node(c1, c2);
		x->weight = c1->weight + c2->weight;

		insert_min_heap(&heap, x);
	}
	return delete_min_heap(&heap); // ���� Ʈ��
}

void traverse(TreePtr p, char code[], int level) {
	// '0'�� �����ϰ� ��ȯȣ���Ѵ�. 
	if (p->left) {
		code[level] = '0';
		traverse(p->left, code, level + 1);
	}

	// '1'�� �����ϰ� ��ȯȣ���Ѵ�. 
	if (p->right) {
		code[level] = '1';
		traverse(p->right, code, level + 1);
	}

	// �ܸ�����̸� �ڵ带 ����Ѵ�. 
	if (p->left == NULL && p->right == NULL) {
		printf("%c: ", p->ch);
		for (int i = 0; i < level; i++)
			printf("%c", code[i]);
		printf("\n");
	}
}
// ���Լ� 
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
/* ���� ���
C: 00
E: 010
D: 011
B: 10
A: 11

C:\Users\USER\source\repos\Project17\x64\Debug\Project17.exe(���μ��� 15400��)��(��) ����Ǿ����ϴ�(�ڵ�: 0��).
������� ������ �� �ܼ��� �ڵ����� �������� [����] -> [�ɼ�] -> [�����] > [������� �����Ǹ� �ڵ����� �ܼ� �ݱ�]�� ����ϵ��� �����մϴ�.
�� â�� �������� �ƹ� Ű�� ��������...
*/
/* ���� ���
C : 00
E : 010
D : 011
B : 10
A : 11
*/