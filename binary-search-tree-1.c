/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
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

	do{
		printf("\n\n");
        printf("[-----Software, Student ID : 2017038040, Name : Han Gyu Jun-----]\n");
        // 성명과 학번이 출력되도록 소스를 수정했습니다. 한글은 컴파일시 깨져서 영문으로 작성했습니다.
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

// 트리를 초기화하는 함수입니다. 빈 트리가 아닐 시, freeBST라는 트리 전체 노드 메모리 할당해제 함수를 사용해 트리를 없앱니다.
// 헤드노드를 하나 동적할당으로 만들고, 헤드의 우측 링크는 자기 자신을 가리키도록, 좌측 링크는 널로 만듭니다.
// 이후, 헤드노드임을 표시하는 특정한 키 값인 -9999를 삽입하고 1을 반환해 함수가 제대로 종료되었음을 표시합니다.

void inorderTraversal(Node* ptr){
    if(ptr){
        inorderTraversal(ptr->left);
        printf(" [%d] ", ptr->key);
        inorderTraversal(ptr->right);
    }
}

// 재귀적 방법을 사용한 중위순회 함수입니다. 좌측 자식 노드를 방문하고 부모 노드를 방문한 뒤 우측 노드를 방문합니다.
// 좌측 자식 노드로 갔을 때, 좌측 자식 노드의 입장에서는 다시 자기 자신이 부모 노드가 되고 좌측 자식 노드를 먼저 방문해야 합니다.
// 이때, 좌측 자식 노드가 NULL이라면 함수가 바로 종료되고 해당 노드의 값이 출력된 뒤, 우측 자식 노드를 탐색한 뒤 다시 좌측 노드를 탐색하는 식으로 방문합니다.
// 우측 자식 노드도 NULL이라면 함수가 바로 종료되고, 부모의 부모 노드로 이동하는 식으로 함수가 진행됩니다.

void preorderTraversal(Node* ptr){
    if(ptr){
        printf(" [%d] ", ptr->key);
        preorderTraversal(ptr->left);
        preorderTraversal(ptr->right);
    }
}

// 재귀적 방법을 사용한 전위순회 함수입니다. 부모를 먼저 프린트한 뒤, 좌측 자식 노드와 우측 자식 노드를 순서대로 방문합니다.
// 먼저 현재 있는 노드의 값을 출력하고, 좌측 자식 노드가 있다면 그 값을 출력하고 다시 좌측 노드로 갑니다.
// 좌측 자식 노드가 NULL이라면, 우측 자식 노드를 찾고 다시 좌측 노드를 먼저 찾는 식으로 방문합니다.
// 우측 자식 노드도 NULL이라면 함수가 부모의 부모 노드로 다시 올라가서 우측 노드를 찾는 식으로 진행됩니다.

void postorderTraversal(Node* ptr){
    if(ptr){
        postorderTraversal(ptr->left);
        postorderTraversal(ptr->right);
        printf(" [%d] ", ptr->key);
    }
}

// 재귀적 방법을 사용한 후위순회 함수입니다. 좌측 자식 노드와 우측 자식 노드를 순서대로 방문한 뒤 현 노드를 출력합니다.
// 먼저 좌측 노드가 존재한다면 계속 좌측 노드로 이동하고, 좌측 자식 노드가 NULL이라면 우측 노드를 탐색합니다.
// 우측 노드도 NULL이라면, 그제서야 현 노드를 출력한 뒤 부모 노드 단계의 함수로 다시 이동하는 식으로 진행됩니다.

int insert(Node* head, int key){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    Node* p;

    if(head->left == NULL){
        head->left = node;
        node->left = NULL;
        node->right = NULL;
        return 1;
    }

    p = head->left;

    while(1){
        if(node->key < p->key && p->left == NULL){
            p->left = node;
            node->left = NULL;
            node->right = NULL;
            return 1;
        }
        else if(node->key > p->key && p->right == NULL){
            p->right = node;
            node->left = NULL;
            node->right = NULL;
            return 1;
        }
        else if(node->key < p->key && p->left != NULL) p = p->left;
        else if(node->key > p->key && p->right != NULL) p = p->right;
        else if(node->key == p->key){
            printf("[ERROR]%d is already exist!!!.\n", key);
            free(node);
            return 0;
        }
    }
}

// 트리에 노드를 추가하는 함수입니다.
// 먼저 노드를 하나 동적할당한 뒤, 입력받은 키를 노드의 키로 삽입합니다. 그리고 노드 포인터 변수인 p를 하나 만듭니다.
// 헤드가 가리키는 노드가 없다면 트리가 비어있는 것이기 때문에, 이 노드를 루트노드로 만듭니다.
// 그렇지 않다면, p가 루트노드를 가리키게 한 다음 p가 가리키는 노드의 key값과 입력받은 key값을 비교해가면서 작으면 왼쪽, 크면 오른쪽으로 이동합니다.
// 이때, 크기 비교가 되면서 더 이상 p가 이동할 곳이 없다면, 그 곳에 node를 삽입하고 1을 반환해 함수의 정상적 종료를 알립니다.
// 이때, 입력받은 key와 p의 키 값이 같은 경우가 있다면 이미 존재한다는 에러 메시지를 출력하고, 동적할당해 둔 node를 메모리에서 할당 해제한 뒤 0을 반환해 에러를 알립니다.

int deleteLeafNode(Node* head, int key){
    Node* pre;
    Node* p;

    if(head->left == NULL){
        printf("[ERROR]Tree is Empty!!!\n");
        return 0;
    }

    p = head->left;

    while(1){
        if(key < p->key && p->left == NULL){
            printf("[ERROR]%d is not exist in this tree!!!\n", key);
            return 0;
        }
        else if(key > p->key && p->right == NULL){
            printf("[ERROR]%d is not exist in this tree!!!\n", key);
            return 0;
        }
        else if(key < p->key && p->left != NULL){
            pre = p;
            p = p->left;
        }
        else if(key > p->key && p->right != NULL){
            pre = p;
            p = p->right;
        }
        else if(key == p->key && p->left == NULL && p->right == NULL){
            if(key < pre->key) pre->left = NULL;
            if(key > pre->key) pre->right = NULL;
            free(p);
            return 1;
        }else if(key == p->key && (p->left != NULL || p->right != NULL)){
            printf("[ERROR]%d is not in leaf node!!!\n", key);
            return 0;
        }
    }
}

// Leafnode를 제거하는 함수입니다. 먼저 pre와 p 두 개의 노드포인터변수를 생성합니다.
// 이때, 헤드노드가 루트노드를 가리키지 않는다면 트리가 비었다는 것이기 때문에 에러메세지를 출력하고 0을 반환해 에러를 알립니다.
// 그렇지 않다면 p가 루트노드를 가리키게 한 뒤, 반복문을 통해 순회를 시작합니다. 이때, pre는 p의 이전 단계 노드를 가리키게 합니다.
// 방향을 계속 찾는 도중, 올바른 방향임에도 불구하고 해당 방향에 노드가 없다면 트리에 입력받은 key값을 가진 노드가 없는 것이기 때문에 에러 메세지를 출력하고 0을 반환합니다.
// 해당 노드를 발견했을 시, pre가 해당 노드를 가리키는 링크를 NULL로 만들고, p를 할당 해제한 뒤 1을 반환해 함수의 정상 종료를 알립니다.
// 이때, 입력받은 key와 같은 key를 가진 노드가 존재하지만 leafnode가 아닌 경우, 에러메세지를 출력합니다.
// leafnode는 자식 노드가 없기 때문에, 좌측 자식 노드와 우측 자식 노드 둘 중 하나만 있어도 에러메세지를 출력합니다.

Node* searchRecursive(Node* ptr, int key){
    if(!ptr) return NULL;
    if(key == ptr->key) return ptr;
    if(key < ptr->key) return searchRecursive(ptr->left, key);
    return searchRecursive(ptr->right, key);
}

// 재귀적 방식의 트리 검색 함수입니다.
// ptr이 NULL이라면 NULL값을 반환해, 해당 key값을 가진 노드가 없다는 메세지를 출력합니다.
// 트리가 비었다면, 이 조건에 걸려서 해당 상황을 마무리할 수 있습니다.
// 해당 key값과 같은 key값을 가진 노드를 찾는다면, 해당 노드의 주소를 반환합니다.
// 이때, 위의 두 조건을 만족하지 않으면서 입력받은 key값이 해당 노드의 key값보다 작을 시에는 좌측 자식 노드를 탐색합니다.
// 입력받은 key값이 해당 노드의 key값보다 크다면 우측 자식 노드를 탐색합니다.

Node* searchIterative(Node* head, int key){
    Node* p;
    p = head->left;
    while(p){
        if(key == p->key) return p;
        if(key < p->key) p = p->left;
        else p = p->right;
    }
    return NULL;
}

// 재귀적 방식이 아닌 트리 검색 함수입니다.
// 노드포인터변수 p를 선언하고, p가 루트노드를 가리키도록 합니다.
// 이후 반복문으로, p가 입력받은 key와 일치하는 key를 가진 노드를 가리킨다면 그 노드의 주소를 반환합니다.
// 입력받은 key가 현재 가리키고 있는 노드의 key보다 작다면 좌측 자식 노드를 탐색합니다.
// 입력받은 key가 현재 가리키고 있는 노드의 key보다 크다면 우측 자식 노드를 탐색합니다.
// 어떠한 경우에도 속하지 않아서 해당 트리에 입력받은 key값과 같은 key값을 가진 노드가 없다면 NULL을 반환해 에러 메세지를 출력합니다.


int freeBST(Node* head){
    if(head){
        if(head->right == head){
            free(head);
            return 1;
        }
        freeBST(head->left);
        freeBST(head->right);
        free(head);
    }
    return 1;
}

// 트리 내의 모든 노드를 메모리 할당 해제하는 함수입니다.
// 트리 안의 노드가 헤드노드밖에 없다면, 헤드노드를 메모리 할당 해제하고 1을 반환해 함수의 정상 종료를 알립니다.
// 그렇지 않다면, 재귀적 방식을 사용해 후위 순회로 좌측 자식 노드와 우측 자식 노드를 먼저 메모리 할당 해제한 뒤 부모 노드를 할당 해제합니다.
// 전위 순회 방식과 중위 순회 방식은 순서에 문제가 있어서 에러가 발생합니다.
// 이상입니다.
