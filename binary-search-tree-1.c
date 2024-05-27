/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("[----- [KIMGEONWOO] [2021041010] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr)
	{
		inorderTraversal(ptr->left); // 왼쪽 서브트리 순회
		printf("[%d] ", ptr->key); // 키 출력
		inorderTraversal(ptr->right); // 오른쪽 서브트리 순회
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr)
	{
		printf("[%d] ", ptr->key); // 키 출력
		preorderTraversal(ptr->left); // 왼쪽 서브트리 순회
		preorderTraversal(ptr->right); // 오른쪽 서브트리 순회
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr)
	{
		postorderTraversal(ptr->left); // 왼쪽 서브트리 순회
		postorderTraversal(ptr->right); // 오른쪽 서브트리 순회
		printf("[%d] ", ptr->key); // 키 출력
	}

}	


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // 새로운 노드 생성
	newNode->key = key; // 키 값 설정
	newNode->left = NULL; // 왼쪽 자식 노드 NULL로 초기화
	newNode->right = NULL; // 오른쪽 자식 노드 NULL로 초기화

	if(head->left == NULL) // 루트 노드가 없을 경우
	{
		head->left = newNode; // 루트 노드로 설정
		return 1;
	}

	Node* ptr = head->left; // 루트 노드부터 시작
	Node* parent = NULL; // 부모 노드

	while(ptr != NULL) // NULL이 아닐 때까지 반복
	{
		if(ptr->key == key) // 중복된 키가 있을 경우
		{
			printf("Duplicate Key\n"); // 중복된 키라고 출력
			return 0;
		}

		parent = ptr; /// 부모 노드 설정

		if(ptr->key > key) // 키 값이 작을 경우
			ptr = ptr->left; // 왼쪽 자식 노드로 이동
		else
			ptr = ptr->right; // 키 값이 클 경우 오른쪽 자식 노드로 이동
	}

	if(parent->key > key) // 부모 노드의 키 값이 클 경우
		parent->left = newNode; // 새로운 노드를 부모 노드의 왼쪽 자식으로 설정
	else
		parent->right = newNode; // 작을 경우에는 새로운 노드를 부모 노드의 오른쪽 자식으로 설정

	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	Node* parent = head;  
	Node* ptr = head->left;

	if(ptr == NULL)
	{
		printf("Tree is Empty\n"); // 트리가 비어있을 경우 Tree is Empty 출력
		return 0;
	}

	while(ptr != NULL)
	{
		if(ptr->key == key) // 키 값이 일치할 경우
			break; // 반복문 종료

		parent = ptr; 

		if(ptr->key > key) // 키값에 따라 이동
			ptr = ptr->left; // 왼쪽 자식 노드로 이동
		else
			ptr = ptr->right; // 오른쪽 자식 노드로 이동
	}

	if(ptr == NULL)
	{
		printf("Cannot find the node [%d]\n", key); // 찾을 수 없을 경우 Cannot find the node 출력
		return 0;
	}

	if(ptr->left == NULL && ptr->right == NULL) // 리프 노드일 경우
	{
		if(parent->left == ptr)  
			parent->left = NULL; // 부모 노드의 왼쪽 자식 노드를 NULL로 설정
		else
			parent->right = NULL; // 부모 노드의 오른쪽 자식 노드를 NULL로 설정

		free(ptr);
		return 1;
	}

	printf("The node [%d] is not a leaf node\n", key); // 리프 노드가 아닐 경우 The node is not a leaf node 출력
	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)
		return NULL; // NULL일 경우 NULL 반환 

	if(ptr->key == key) 
		return ptr; // 키 값이 일치할 경우 해당 노드 반환

	if(ptr->key > key) // 키 값을 비교하여 이동
		return searchRecursive(ptr->left, key); // 왼쪽 자식 노드로 이동
	else
		return searchRecursive(ptr->right, key); // 오른쪽 자식 노드로 이동
}

Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left; // 루트 노드부터 시작

	while(ptr != NULL) // NULL이 아닐 때까지 반복
	{
		if(ptr->key == key)
			return ptr; // 키 값이 일치할 경우 해당 노드 반환

		if(ptr->key > key) // 키 값에 따라 이동
			ptr = ptr->left; // 키 값이 작을 경우 왼쪽 자식 노드로 이동
		else
			ptr = ptr->right; // 키 값이 클 경우 오른쪽 자식 노드로 이동
	}

	return NULL;
}	


int freeBST(Node* head)
{
	if(head->left != NULL) // 루트 노드가 NULL이 아닐 경우
		freeBST(head->left); // 왼쪽 서브트리 순회

	free(head); // 노드 해제
	return 1;
}





