/*
 * Binary Search Tree #2
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

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
        printf("[-----Software, Student ID : 2017038040, Name : Han Gyu Jun-----]\n");
        // 성명과 학번이 출력되도록 소스를 수정했습니다. 한글은 컴파일시 깨져서 영문으로 작성했습니다.
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
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
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
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

	top = -1;

	front = rear = -1;

	return 1;
}

// 트리 전체를 초기화하는 함수입니다. 헤드노드가 NULL이 아니라면 트리가 이미 존재하는 것이기 때문에 freeBST함수를 통해 트리 전체를 초기화합니다.
// 헤드노드가 존재하지 않을 시, 동적할당을 통해 새 헤드노드를 만들고, 앞으로 쓸 스택의 top, 큐에 쓸 front, rear를 -1로 초기화합니다.
// 이후 함수가 잘 마무리되었다면 1을 반환하면서 마무리합니다.


void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

// recursive 방법을 사용한 중위순회 함수입니다. 좌측 자식 노드를 방문하고 부모 노드를 방문한 뒤 우측 노드를 방문합니다.
// 좌측 자식 노드로 갔을 때, 좌측 자식 노드의 입장에서는 다시 자기 자신이 부모 노드가 되고 좌측 자식 노드를 먼저 방문해야 합니다.
// 이때, 좌측 자식 노드가 NULL이라면 함수가 바로 종료되고 해당 노드의 값이 출력된 뒤, 우측 자식 노드를 탐색한 뒤 다시 좌측 노드를 탐색하는 식으로 방문합니다.
// 우측 자식 노드도 NULL이라면 함수가 바로 종료되고, 부모의 부모 노드로 이동하는 식으로 함수가 진행됩니다.

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
    push(node);
    for(;;){
        for(; node; node = node->left) push(node);
        node = pop();

        if(!node) break;

        printf(" [%d] ", node->key);
        node = node->right;
    }
}

// iterative 방식을 사용한 중위순회 함수입니다. 좌측의 가장 끝으로 먼저 이동하면서 노드에 있는 값을 스택에 넣습니다.
// 이후 pop으로 스택에 있는 값을 빼고, 프린트한 뒤 우측 자식노드를 다시 탐색하는 순서로 진행됩니다.
// 트리의 모든 노드를 출력했다면 스택이 비고, 스택이 비었다면, pop이 NULL을 반환해서 node를 NULL로 만들기 때문에 node가 NULL이 되면 함수를 종료합니다.

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr){
    if(!ptr) return;
    enQueue(ptr);

    for(;;){
        ptr = deQueue();
        if(ptr){
            printf(" [%d] ", ptr->key);
            if(ptr->left) enQueue(ptr->left);
            if(ptr->right) enQueue(ptr->right);
        }
        else break;
    }
}

// 같은 레벨의 노드들을 순서대로 출력하는 함수입니다.
// 트리가 비었을 시 아무 일 없이 함수를 종료합니다.
// 트리가 비지 않았다면, enQueue를 통해 좌측 자식노드와 우측 자식노드를 둘 다 큐에 넣습니다.
// 이후 큐에서 deQueue를 통해 뽑아낸 노드를 출력하고, 좌/우측 자식노드를 다시 넣는 것을 반복합니다.
// 이때, 어느 한쪽만을 선택해서 넣는 것이 아니라 같은 레벨의 노드를 한꺼번에 넣고, 다시 그 밑의 노드들을 한꺼번에 넣기 때문에 같은 레벨의 노드들이 순서대로 출력됩니다.


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

// 동적할당을 통해 새로운 노드를 만든 뒤, 왼쪽/오른쪽 자식 노드 경로를 초기화하고 받은 키로 노드의 키를 대체한 다음 위치를 찾아갑니다.
// 트리가 비었다면 새로 만든 노드를 루트노드로 삽입하고, 그렇지 않다면 입력받은 key를 각각의 노드 key와 비교하며 작으면 좌측, 크면 우측으로 내려갑니다.
// 이때, 중복되는 키를 가진 노드가 있다면 다른 작업을 수행하지 않고 1을 반환합니다.
// 더 이상 내려갈 곳이 없다면 부모 노드에 새로 만든 노드로 통하는 경로를 입력하고 1을 반환합니다.


int deleteNode(Node* head, int key){
    Node *pnode, *cnode, *t, *j, *pj;

    pnode = NULL;
    t = head->left;

    while(t != NULL){
        if(t->key == key) break;
        pnode = t;
        if(pnode->key > key) t = pnode->left;
        else if(pnode->key < key) t = pnode->right;
    }

    if(t == NULL){
        printf("[ERROR] [%d] is not exist in tree!!!\n");
        return 0;
    }

    if(t->left == NULL && t->right == NULL){
        if(t == head->left){
            free(t);
            head->left = NULL;
            return 1;
        }
        else if(pnode->left == t){
            pnode->left = NULL;
            free(t);
            return 1;
        }else{
            pnode->right = NULL;
            free(t);
            return 1;
        }
    }
    else if(t->left == NULL){
        if(pnode->left == t){
            pnode->left = t->right;
            free(t);
            return 1;
        }
        if(pnode->right == t){
            pnode->right = t->right;
            free(t);
            return 1;
        }
    }else if(t->right == NULL){
        if(pnode->left == t){
            pnode->left = t->left;
            free(t);
            return 1;
        }else if(pnode->right == t){
            pnode->right = t->left;
            free(t);
            return 1;
        }
    }else{
        pj = t;
        j = t->right;

        while(j->left != NULL){
            pj = j;
            j = j->left;
        }

        if(j->right != NULL) pj->left = j->right;
        if(pnode->left == t) pnode->left = j;
        if(pnode->right == t) pnode->right = j;
        if(t->left != NULL) j->left = t->left;
        if(t->right != NULL && t->right != j)j->right = t->right;
        if(t->right == j) j->right = NULL;
        free(t);
        return 1;
    }

}

// 크게 3가지의 경우로 나누어 노드를 삭제합니다.
// 먼저, t와 pnode를 통해 key를 비교해가며 입력받은 키와 같은 노드를 가진 노드를 찾고, pnode는 그 노드의 부모 노드를 가리키도록 합니다.
// 이때, 트리가 비었다면 트리가 비었다는 에러 메세지를 출력해줍니다.
// 삭제할 노드가 리프노드라면 그 노드가 루트노드인지 확인한 뒤, 루트노드라면 별도로 처리해주고 그렇지 않은 그냥 리프노드라면 부모노드의 링크를 삭제하고 해당 노드를 삭제합니다.
// 삭제할 노드가 자식 노드를 한 개 갖고 있다면, 그 자식 노드가 해당 노드의 좌측 자식인지 우측 자식인지, 삭제할 노드가 부모 노드의 좌측 자식인지 식별한 뒤
// 부모 노드의 경로를 삭제할 노드의 자식 노드로 처리해 올린 뒤, 삭제할 노드를 삭제합니다.
// 마지막으로 삭제할 노드가 자식 노드를 두 개 갖고 있는 경우입니다.
// 이 때는 좌측 부분트리의 가장 큰 값이나 우측 부분트리의 가장 작은 값을 찾아야 합니다.
// 저는 우측 부분트리의 가장 작은 값을 찾기로 했기 때문에 j를 삭제할 노드의 우측 자식노드로 만들어주고 pj를 j의 부모 노드를 가리키게 하면서 먼저 우측 부분트리의 가장 작은 값을 찾습니다.
// 이때, j의 좌측 노드는 가장 작은 값을 찾았기 때문에 존재할 수 없지만, 우측 노드는 존재할 가능성이 있습니다.
// j를 올릴 것이기 때문에, j의 우측 노드를 j의 부모 노드가 가리키도록 한 뒤 삭제할 노드의 부모 노드가 j를 가리키도록 해서 j를 삭제할 노드의 위치로 올립니다.
// 그 뒤 삭제할 노드의 좌/우측 노드가 존재한다면, j가 그 노드들을 가리키게 합니다.
// 마지막으로, j가 t의 바로 우측 자식 노드라면 j가 자기 자신을 가리키게 되어 탐색 시 무한루프에 빠질 가능성이 있기 때문에 그 경우를 처리하는 조건문을 추가합니다.
// 처리가 완료되면, t를 free로 메모리 할당 해제합니다.


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

// 후위순회방식으로 트리를 돌면서 모든 노드를 메모리 할당 해제하는 함수입니다.
// 전위순회나 중위순회방식을 사용할 시, 함수가 진행되기 전에 노드가 해제되어 오류가 발생할 수 있기 때문에 후위순회방식을 사용합니다.

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}

// 이 함수 또한 모든 노드를 메모리 할당 해제하는 함수입니다.
// 먼저, 헤드노드 자신밖에 존재하지 않는 빈 트리라면, 헤드노드를 해제한 뒤 1을 반환해 함수의 정상적 종료를 알립니다.
// 그렇지 않다면, p를 루트노드에 위치시킨 뒤 순회하기 위하여 freeNode함수를 호출하고, 헤드노드를 제외한 모든 트리가 메모리 할당 해제된 뒤 헤드노드를 해제합니다.

Node* pop(){
    Node* x;
    x = stack[top--];
    if(top == -1) return NULL;
    return x;
}

// 스택에서 값을 빼내는 함수입니다.
// 노트포인터 x를 선언한 뒤, 스택에 저장되어 있는 노드의 주소를 x에 넣습니다.
// 이 때, top은 스택의 가장 끝 값을 가리키기 때문에 top에서 데이터를 빼낸 뒤 top을 1줄여주는 후위연산자를 사용합니다.
// top이 -1이라면 스택이 빈 것이기 때문에 NULL을 반환합니다.
// 그렇지 않다면, 노드의 주소가 들어있는 x값을 반환해 스택의 가장 끝에 있는 데이터를 빼서 반환하는 함수를 완성합니다.


void push(Node* aNode)
{
    if(top == MAX_STACK_SIZE-1){
        printf("[ERROR] Stack is Full!!!\n");
        return;
    }
    stack[++top] = aNode;
}

// 스택에 데이터를 넣는 함수입니다.
// top이 스택의 크기보다 1작은 수라면 스택이 가득 찬 것이기 때문에 에러 메세지를 출력하고 함수를 종료합니다.
// 그렇지 않다면, 현재 top에는 이미 데이터가 저장되어 있기 때문에 전위 연산자를 통해 top의 위치를 이동시킨 뒤 스택에 전달받은 노드의 주소를 입력합니다.

Node* deQueue(){
    Node* x;

    if(front == rear){
        return NULL;
    }

    if(front == -1) ++front;
    else if(front != MAX_QUEUE_SIZE-1) front++;
    else front = 0;
    x = queue[front];
    queue[front] = NULL;

    return x;
}

// 큐에서 데이터를 제거하는 함수입니다.
// front와 rear의 값이 같다면 큐가 비어있는 것이기 때문에 NULL을 반환합니다.
// front가 -1인 초기값이라면 front를 0으로 만들어줘, 실제로 사용할 수 있게 합니다.
// front가 큐의 크기보다 1작은 값이라면 front가 0이 되도록 합니다. front의 위치는 항상 비어있기 때문에, 다른 작없을 미리 할 필요는 없습니다.
// x에 큐의 값을 입력한 뒤, front가 있는 큐의 위치에 있는 데이터를 삭제합니다.
// 이후 x를 반환합니다.

void enQueue(Node* aNode){
    if(rear == MAX_QUEUE_SIZE-1 && front == -1){
        printf("[ERROR] Queue is Full!!!\n");
        return;
    }
    if(rear == MAX_QUEUE_SIZE-1) rear = -1;
    if(++rear == front){
        printf("[ERROR] Queue is Full!!!\n");
        rear--;
        return;
    }
    queue[rear] = aNode;
}

// 큐에 데이터를 입력하는 함수입니다.
// rear이 큐의 크기보다 1작은 수라면 front+1부터 큐의 끝까지 데이터가 입력되어 있고, front가 -1이라면 데이터를 한번도 삭제하지 않은, 꽉 찬 큐기 때문에 에러메세지를 출력합니다.
// rear가 큐의 크기보다 1작은 수라면 일단 rear를 -1로 만듭니다.
// 이후 rear를 전위연산자로 더하여 rear+1이 front와 같다면 데이터를 입력하려는 곳에 front가 있다는 뜻이기 때문에 큐가 가득 찼다는 에러메세지를 출력합니다.
// 이후 rear를 -1 빼서 원래대로 만듭니다.
// 이런 경우에 모두 해당하지 않는다면, rear의 값이 조건문의 전위연산자를 통해서 이미 +1되었기 때문에, rear의 위치에 데이터를 입력합니다.
// 이상입니다.
