
#define _CRT_SECURE_NO_WARNINGS
#define MAXWORD 80

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

typedef struct element {
	char word[MAXWORD];
	int count;
} element;
typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
} TreeNode;

// 순환적인 탐색 함수
TreeNode* search(TreeNode* node, char* word)
{
	if (node == NULL) return NULL;
	int cmp = strcmp(node->data.word, word);
	if (cmp == 0)
		return node;
	else if (cmp > 0)
		return search(node->left, word);
	else
		return search(node->right, word);
}
TreeNode* new_node(char* word)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	strcpy(temp->data.word, word);
	temp->data.count = 1;
	temp->left = temp->right = NULL;
	return temp;
}
TreeNode* insert_node(TreeNode* node, char* word)
{
	// 트리가 공백이면 새로운 노드를 반환한다. 
	if (node == NULL) return new_node(word);

	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	int cmp = strcmp(node->data.word, word);
	if (cmp == 0)
		node->data.count++;
	else if (cmp > 0)
		node->left = insert_node(node->left, word);
	else
		node->right = insert_node(node->right, word);

	// 변경된 루트 포인터를 반환한다. 
	return node;
}

int get_height(TreeNode* node) {
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}
// 맨 왼쪽 단말 노드를 찾으러 내려감
TreeNode* delete_min_value_node(TreeNode* current, element* data_p)
{
	TreeNode* node;
	if (current->left == NULL) {
		*data_p = current->data;
		node = current;
		current = current->right;
		free(node);
	}
	else
		current->left = delete_min_value_node(current->left, data_p);
	return current;
}
// 맨 오른쪽 단말 노드를 찾으러 내려감
TreeNode* delete_max_value_node(TreeNode* current, element* data_p)
{
	TreeNode* node;
	//아래를 완성하시오.
	if (current->right == NULL) {
		*data_p = current->data; // 삭제 전 데이터 저장
		node = current;          // 삭제할 노드 저장
		current = current->left; // 부모 노드를 왼쪽 자식과 연결
		free(node);              // 노드 메모리 해제
	}
	else {
		// 오른쪽으로 이동
		current->right = delete_max_value_node(current->right, data_p);
	}
	return current;
}
// 이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고 
// 새로운 루트 노드를 반환한다. 
TreeNode* delete_node(TreeNode* root, char* word)
{
	if (root == NULL) return root;

	int cmp = strcmp(root->data.word, word);
	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (cmp < 0)
		root->right = delete_node(root->right, word);
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	else if (cmp > 0)
		root->left = delete_node(root->left, word);
	// 키가 루트와 같으면 이 노드를 삭제하면 됨
	else {
		root->data.count--;
		if (root->data.count > 0) 	//count>0
			return root;

		//count==0
		// 첫 번째나 두 번째 경우
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		// 세 번째 경우
		if (get_height(root->left) >= get_height(root->right))
			root->left = delete_max_value_node(root->left, &(root->data));
		else
			root->right = delete_min_value_node(root->right, &(root->data));
	}
	return root;
}

// 중위 순회
void inorder(TreeNode* root) {
	if (root) {
		inorder(root->left);// 왼쪽서브트리 순회
		printf("%-10s %d\n", root->data.word, root->data.count);
		inorder(root->right);// 오른쪽서브트리 순회
	}
}

int main(void)
{
	TreeNode* root = NULL;

	FILE* fp;
	char word[MAXWORD];

	fp = fopen("data.txt", "r");
	while (fscanf(fp, "%s", word) != EOF) {
		printf("%s ", word);
		root = insert_node(root, word);
	}
	printf("\n");
	fclose(fp);

	printf("단어 \t회수\n");
	inorder(root);

	printf("삭제할 단어(종료:0): ");
	scanf_s("%s", word, sizeof(word));
	while (word[0] != '0') {
		delete_node(root, word);
		inorder(root);
		printf("삭제할 단어(종료:0): ");
		scanf("%s", word);
	}

	return 0;
}
/*실제출력
The output from Huffmans algorithm can be viewed as a variable length code table for encoding a source symbol such as a character in a file
단어    회수
Huffmans   1
The        1
a          4
algorithm  1
as         2
be         1
can        1
character  1
code       1
encoding   1
file       1
for        1
from       1
in         1
length     1
output     1
source     1
such       1
symbol     1
table      1
variable   1
viewed     1
삭제할 단어(종료:0): a
Huffmans   1
The        1
a          3
algorithm  1
as         2
be         1
can        1
character  1
code       1
encoding   1
file       1
for        1
from       1
in         1
length     1
output     1
source     1
such       1
symbol     1
table      1
variable   1
viewed     1
삭제할 단어(종료:0): The
Huffmans   1
a          3
algorithm  1
as         2
be         1
can        1
character  1
code       1
encoding   1
file       1
for        1
from       1
in         1
length     1
output     1
source     1
such       1
symbol     1
table      1
variable   1
viewed     1
삭제할 단어(종료:0): output
Huffmans   1
a          3
algorithm  1
as         2
be         1
can        1
character  1
code       1
encoding   1
file       1
for        1
from       1
in         1
length     1
source     1
such       1
symbol     1
table      1
variable   1
viewed     1
삭제할 단어(종료:0): length
Huffmans   1
a          3
algorithm  1
as         2
be         1
can        1
character  1
code       1
encoding   1
file       1
for        1
from       1
in         1
source     1
such       1
symbol     1
table      1
variable   1
viewed     1
삭제할 단어(종료:0): 0

C:\Users\USER\source\repos\Project15\x64\Debug\Project15.exe(프로세스 21456개)이(가) 종료되었습니다(코드: 0개).
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요...
*/
/*출력결과 예시
The output from Huffmans algorithm can be viewed as a variable length code table
 for encoding a source symbol such as a character in a file
단어    회수
Huffmans   1
The        1
a          4
algorithm  1
as         2
be         1
can        1
character  1
code       1
encoding   1
file       1
for        1
from       1
in         1
length     1
output     1
source     1
such       1
symbol     1
table      1
variable   1
viewed     1
삭제할 단어(종료:0): a
Huffmans   1
The        1
a          3
algorithm  1
as         2
be         1
can        1
character  1
code       1
encoding   1
file       1
for        1
from       1
in         1
length     1
output     1
source     1
such       1
symbol     1
table      1
variable   1
viewed     1
삭제할 단어(종료:0): The
Huffmans   1
a          3
algorithm  1
as         2
be         1
can        1
character  1
code       1
encoding   1
file       1
for        1
from       1
in         1
length     1
output     1
source     1
such       1
symbol     1
table      1
variable   1
viewed     1
삭제할 단어(종료:0): output
Huffmans   1
a          3
algorithm  1
as         2
be         1
can        1
character  1
code       1
encoding   1
file       1
for        1
from       1
in         1
length     1
source     1
such       1
symbol     1
table      1
variable   1
viewed     1
삭제할 단어(종료:0): length
Huffmans   1
a          3
algorithm  1
as         2
be         1
can        1
character  1
code       1
encoding   1
file       1
for        1
from       1
in         1
source     1
such       1
symbol     1
table      1
variable   1
viewed     1
삭제할 단어(종료:0): 0
계속하려면 아무 키나 누르십시오 . . .
*/

