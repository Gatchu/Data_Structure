/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

// 이번에는 headnode를 선언하지 않은 모습을 볼 수 있습니다.

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

// headnode을 아예 일반 노드로 선언을 했습니다.
// 이 때, headnode는 키 값(-9999)를 이용해 구별을 하는 모습입니다.
// headnode가 NULL이 아니면, freenode를 호출해서 전체를 초기화합니다.
// 이후 headnode를 동적할당하여 리턴합니다.
// headnode를 더블포인터로 받았기 때문에, 주소를 리턴할 필요가 없습니다.
// 더블포인터형으로 선언, 수정을 했기 때문에 headnode의 값이 직접 수정되었기 때문입니다.
// 함수가 잘 진행되었다면, 1을 리턴해 함수의 정상 종료를 알립니다.

/* 메모리 해제 */
int freeList(listNode* h){
	listNode* p = h->rlink;
	listNode* prev = NULL;

	while( p->key != -9999 ){
		prev=p;
		p=p->rlink;
		free(prev);
	}
	free(h);

	return 1;
}

// headnode 및 리스트 전체를 초기화하는 함수입니다.
// p가 리스트를 한 바퀴 돌면서 headnode로 다시 돌아올 때까지 지나가는 곳에 있는 노드를 할당 해제합니다.
// 이후 headnode도 초기화하고, 1을 리턴해 함수의 정상 종료를 알립니다.


void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

// 리스트를 한 바퀴 돌면서 headnode부터 마지막 노드까지의 주소, llink, rlink를 출력하는 함수입니다.



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* p;

	node->key = key;

	p = h->rlink;

	if(h->rlink == h && h->llink == h){
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
		return 1;
	}

	while(p->rlink != h){
		p = p->rlink;
	}

	p->rlink = node;
	node->llink = p;
	node->rlink = h;
	h->llink = node;

	return 1;
}

// key를 입력받고, 리스트의 마지막에 이 노드를 추가하는 함수입니다.
// 리스트가 비어있는 경우, 헤드노드가 자신을 가리키기 때문에 조건을 추가하고, 리스트의 맨 처음에 노드를 추가합니다.
// 그렇지 않은 경우, p가 맨 마지막 노드까지 이동하도록 반복문을 만듭니다.
// 이후 새 노드가 마지막 노드가 되도록 link들을 수정하여 함수를 마칩니다.
// 함수가 잘 마무리될 시 1을 리턴하도록 합니다.

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	listNode* p;
	listNode* change;

	p = h->rlink;

	if(h->rlink == h && h->llink == h){
		printf("[ERROR] List is Empty!!!\n");
		return 0;
	}
	if(h->rlink == h->llink){
		h->rlink = h;
		h->llink = h;
		free(p);
		return 1;
	}
	while(p->rlink != h){
		p = p->rlink;
	}

	p->llink->rlink = h;
	h->llink = p->llink;
	free(p);

	return 1;
}

// 리스트의 마지막 노드를 삭제하는 함수입니다.
// 리스트가 비었을 경우, 에러 메세지를 출력하고 0을 반환하는 조건문을 만듭니다.
// 그렇지 않고 headnode의 rlink와 llink가 같다면, 리스트 안에 노드가 한 개밖에 존재하지 않는 것이므로 그 노드를 삭제하고 headnode가 자신을 가리키도록 수정합니다.
// 다른 예외의 경우는 따로 없으므로, p가 마지막 노드까지 이동하도록 반복문을 짠 뒤, 헤드노드의 링크와 전 노드의 링크를 연결하고, 마지막 노드를 삭제합니다.
// 함수가 잘 실행되었다면 1을 반환합니다.


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if(h->rlink == h && h->llink == h){
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
		return 1;
	}else{
		node->rlink = h->rlink;
		node->llink = h;
		h->rlink = node;
		node->rlink->llink = node;
		return 1;
	}

	return 1;
}

// 리스트의 처음에 입력받은 key값을 가진 노드를 하나 추가하는 함수입니다.
// 입력받은 키를 노드의 키로 추가합니다.
// 이후, 리스트가 비었다면 헤드노드가 노드를 가리키도록, 노드가 헤드노드를 가리키도록 하여 노드를 추가합니다.
// 리스트가 비지 않았다면, 첫 노드의 링크와 헤드노드의 링크, 노드의 링크를 각각 조절해 노드를 삽입합니다.
// 어떤 경우의 수가 되었던, 함수가 잘 실행되었다면 1을 반환합니다.


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	listNode* p;

	p = h->rlink;

	if(h->rlink == h && h->llink == h){
		printf("[ERROR] List is Empty!!!\n");
		return 0;
	}
	if(h->rlink == h->llink){
		h->rlink = h;
		h->llink = h;
		free(p);
		return 1;
	}

	h->rlink = p->rlink;
	p->rlink->llink = h;
	free(p);

	return 1;

}

// 리스트의 첫 번째에 위치한 노드를 삭제하는 함수입니다.
// 리스트가 비었다면, 리스트가 비었다는 에러 메세지를 출력하고 0을 반환하는 조건문을 만듭니다.
// 리스트에 노드가 하나밖에 없다면, 그 하나의 노드를 삭제하는 함수를 만듭니다.
// 다른 예외는 없기 때문에, 두 개 이상의 노드가 존재할 시 링크를 수정해 첫 노드를 삭제하고 메모리 할당 해제합니다.
// 잘 진행되었다면, 1을 반환합니다.


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	listNode* p;
	listNode* s;

	p = h->rlink;

	if(h->rlink == h && h->llink == h){
		printf("[ERROR] List is Empty!!!\n");
		return 0;
	}
	if(h->rlink == h->llink) return 1;
	while(p != h){
		s = p;
		p = p->rlink;
		s->rlink = s->llink;
		s->llink = p;
	}

	p->llink = p->rlink;
	p->rlink = s;

	return 1;
}

// 리스트의 노드들을 역순으로 배치하는 함수입니다. p와 s를 선언합니다.
// 리스트가 비었을 시, 에러 메세지를 출력하고 0을 반환하는 조건문을 만듭니다.
// 리스트에 노드가 하나만 존재할 시, 아무것도 하지 않고 1을 반환하는 조건문을 만듭니다.
// 예외상황에 해당하지 않을 시, 일단 headnode의 링크들을 건드리지 않고 p가 먼저 가고 s가 따라오면서 s의 링크들을 거꾸로 바꿉니다.
// p가 headnode에 도달하면, headnode의 링크를 빼고는 전부 링크들이 바뀐 상태이고, p가 headnode를 가리킵니다.
// 따라서, headnode의 양쪽 링크를 바꾸고 1을 반환하면 리스트가 역순으로 재배치됩니다.



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* p;

	node->key = key;
	p = h->rlink;

	if(h->rlink == h && h->llink == h){
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
		return 1;
	}
	if(h->rlink != h->llink && h->rlink->rlink == h && h->rlink->key > node->key){
		node->rlink = h->rlink;
		node->llink = h;
		node->rlink->llink = node;
		h->rlink = node;
		return 1;
	}
	if(h->rlink->key > node->key){
		node->rlink = h->rlink;
		node->llink = h;
		h->rlink = node;
		node->rlink->llink = node;
		return 1;
	}
	while(p->rlink != h){
		if(p->rlink->key > node->key){
			node->rlink = p->rlink;
			node->llink = p;
			p->rlink->llink = node;
			p->rlink = node;
			return 1;
		}
		p = p->rlink;
	}

	p->rlink = node;
	node->rlink = h;
	node->llink = p;
	h->llink = node;

	return 1;
}

// 입력받은 key 를 동적할당한 노드의 key로 갖게 하고, 입력받은 key보다 큰 값을 가진 노드 앞에 새 노드를 삽입하는 함수입니다.
// 노드가 비었을 때, headnode와 새 노드가 서로를 가리키게 해 새 노드를 삽입합니다.
// 노드가 한 개밖에 없고, 그 노드의 key가 새 노드의 key보다 클 시 headnode와 node, 새 노드의 링크를 조절해 새 노드를 삽입합니다.
// 노드가 한 개 이상이고 그 노드의 key가 새 노드의 key보다 클 시의 경우도 예외상황으로 두고 처리합니다.
// 다른 예외상황은 없으므로, p를 마지막 링크까지 이동시키면서 입력받은 key보다 큰 key를 가진 노드를 검색합니다.
// 그런 노드가 있다면, 그 노드 앞에 노드를 삽입하고 1을 리턴, 함수를 종료하는 조건문을 넣습니다.
// 입력받은 key보다 큰 key를 가진 노드가 존재하지 않을 시, 리스트의 맨 마지막에 새 노드를 추가하도록 한 뒤 1을 반환해 함수의 정상적 종료를 알립니다.


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode* p;

	p = h->rlink;

	if(h->rlink == h && h->llink == h){
		printf("[ERROR] List is Empty!!!\n");
		return 0;
	}
	if(h->rlink->key == key){
		if(p->rlink == h){
			h->rlink = h;
			h->llink = h;
			free(p);
			return 1;
		}else{
			p->rlink->llink = h;
			h->rlink = p->rlink;
			free(p);
			return 1;
		}
	}

	while(p != h){
		if(p->key == key) break;
		p = p->rlink;
	}
	if(p == h){
		printf("[ERROR] There is not %d\n", key);
		return 0;
	}else{
		p->rlink->llink = p->llink;
		p->llink->rlink = p->rlink;
		free(p);
		return 1;
	}

	return 1;
}

// 리스트에서 입력받은 key와 같은 key를 가지고 있는 노드를 삭제하는 함수입니다.
// 먼저, 리스트가 비었다면 에러 메세지를 출력하고 0을 반환하는 조건문을 만듭니다.
// 첫 노드의 key가 입력받은 key와 같다면, 경우의 수를 나누어 노드가 하나인 경우, 노드가 하나가 아닌 경우를 처리합니다.
// 이후는 p가 리스트를 순회하면서 입력받은 key와 같은 key를 가진 노드가 있을 시 반복문에서 빠져나옵니다.
// 이때, 일치하는 노드가 없어서 p가 다시 headnode로 돌아오면 에러 메세지를 출력하고 0을 반환합니다.
// 그렇지 않다면 해당 노드를 삭제하고, 1을 반환합니다.
// 이상입니다.
