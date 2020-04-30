/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;		// 노드. 자기자신을 가지는 링크와 키를 가짐
} listNode;

typedef struct Head {
	struct Node* first;		// 헤더 노드의 first가 노드를 가리키게 되어 있음
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("[-----Software, Student ID : 2017038040, Name : Han Gyu Jun-----]\n");
        // 성명과 학번이 출력되도록 소스를 수정했습니다. 한글은 컴파일시 깨져서 영문으로 작성했습니다.
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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

// q라는 글자가 입력되기 전까지 메뉴를 계속 반복하며 조건을 입력받는 main함수입니다.

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

// headNode가 NULL이라면 freeList함수를 호출해 전체 리스트를 삭제합니다.
// 이후 headNode를 새롭게 할당해 리스트를 이어붙일 수 있는 구조를 만듭니다.

int freeList(headNode* h){
	/* h와 연결된 listNode메모리 해제
	 * headNode메모리도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}

// p가 리스트의 처음부터 끝까지(NULL이 나올 때까지) while반복문을 이용해 돌면서, 모든 리스트에 free를 선언해주는 함수입니다.

/**
 * list 처음에 key에 대한 노드 하나를 추가
 */
int insertFirst(headNode* h, int key) {	// 다른 함수도 유사하게 돌아가니 참고해서 활용

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}

// 리스트의 첫 부분에 새 노드를 할당하는 함수입니다.
// 다른 노드가 존재한다면, head를 새 노드에 할당하고 새 노드가 원래 노드를 가리키게 하여 노드 순서를 변경합니다.


/* 리스트를 검색하여 입력받은 key보다 큰 값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* p;
	node->key = key;
	p = h->first;

	if (h->first == NULL) {
		h->first = node;
		node->link = NULL;
		return 0;
	}
	if(p->key > node->key){
		h->first = node;
		node->link = p;
		return 0;
	}
	while (p->link != NULL) {
		if (p->link->key > (node->key)) {
			node->link = p->link;
			p->link = node;
			return 0;
		}
		p = p->link;
	}
	if((h->first != NULL) && (h->first->link == NULL) && (p->key > node->key)){
			h->first = node;
			node->link = p;
			return 0;
		}
	else if(p->link == NULL){
		p->link = node;
		node->link = NULL;
	}

	return 0;
}

// 리스트를 처음부터 끝까지 돌면서 입력받은 key값보다 큰 값이 나오는 노드 앞에 삽입하는 함수입니다.
// 이때, p->link가 null이 될 때까지 돌면서 검사하는 방법은 head가 가리키는 맨 첫 노드를 검사하지 못합니다.
// 따라서, head가 가리키는 맨 첫 노드를 검사하는 if문을 하나 만들어줍니다.
// 리스트가 비었다면, 비었다는 메세지를 출력하도록 if문을 하나 만듭니다.
// key값보다 큰 값이 나오는 노드가 없다면, 맨 마지막에 새로 입력받은 노드를 넣는 if문을 만듭니다.

/**
 * list에 key에 대한 노드를 하나 추가
 */
int insertLast(headNode* h, int key) {

    listNode* node = (listNode*)malloc(sizeof(listNode));
    listNode* p;

    node->key = key;

    p = h->first;
	if(h->first == NULL){
		h->first = node;
		node->link = NULL;
		return 0;
	}
	while(p->link != NULL){
		p = p->link;
	}

	p->link = node;
	node->link = NULL;

	return 0;
}

// 리스트의 마지막에 입력받은 key값을 가진 노드를 하나 추가해주는 함수입니다.
// 이때, 동적할당으로 생성된 node의 link는 NULL값을 가지고 있지 않기 때문에, 맨 끝에 이어붙인 뒤 node->link를 NULL로 초기화합니다.
// 지금의 while문은 리스트가 비었을 때 노드를 추가해주지 못하므로, if문을 만들어 리스트가 비었을 시 노드가 추가되도록 합니다.


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* p;
	listNode* first;
	first = h->first;
	if(h->first == NULL){
		printf("[ERROR] List in Empty!!!\n");
		return 0;
	}
	p = h->first->link;
	free(first);
	h->first = p;

	return 0;
}

// p를 두 번째 노드의 주소로 지정하고, head가 가리키는 노드를 free선언을 통해 삭제한 뒤 head가 가리키는 곳을 p(두번째 노드)로 바꿔줍니다.
// 이때, 리스트가 비었다면 리스트가 비었다는 에러 메세지를 출력하도록 하는 if문을 만듭니다.


/**
 * list의 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* p;
	listNode* l;

	p = h->first;
	if(h->first == NULL){
		printf("[ERROR] List is Empty!!!\n");
		return 0;
	}
	if(h->first->key == key){
		h->first = p->link;
		free(p);
		return 0;
	}
	while(p != NULL) {
		if(p->key == key) break;
		l = p;
		p = p->link;
	}
	if(p == NULL){
		printf("[ERROR] There is not %d\n", key);
		return 0;
	}

	l->link = p->link;
	free(p);

	return 0;

}

// 입력받은 key값과 같은 key값을 가진 노드를 삭제하는 함수입니다.
// 이때의 while문은 첫 번째 노드와 노드가 비었을 때를 검사해주지 못합니다.
// 따라서, 첫 번째 노드를 검사하고, 조건이 맞다면 삭제하는 if문을, 리스트가 비었을 때 에러메세지를 출력하는 함수를 추가합니다.
// 또, 입력받은 key값을 가진 노드가 없을 시 에러 메세지를 출력하는 if문도 추가합니다.

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* p;
		
	p = h->first;
	if(h->first == NULL){
		printf("[ERROR] List is Empty!!!\n");
		return 0;
	}
	if(h->first != NULL && h->first->link == NULL){
		h->first = NULL;
		free(p);
		return 0;
	}
	while(p->link->link != NULL){
		p = p->link;
	}
	free(p->link);
	p->link = NULL;
	return 0;
}

// 리스트의 마지막 노드를 삭제하는 함수입니다.
// p->link->link를 이용해 p의 두번째 뒤 노드가 존재하지 않을 때, p의 다음 노드를 삭제하는 함수입니다.
// 이때, while문은 노드가 하나일 때와 노드가 비었을 때 동작하지 않으므로, 각각의 경우를 처리해주는 if문을 추가합니다.


/**
 * 노드의 순서를 역으로
 */
int invertList(headNode* h) {
	listNode* first = NULL;
	listNode* middle = NULL;
	listNode* last;

	last = h->first;

	if(h->first == NULL){
		printf("[ERROR] List is Empty!!!\n");
		return 0;
	}
	if(h->first != NULL && h->first->link == NULL) return 0;
	if(h->first->link != NULL && h->first->link->link == NULL){
		h->first = last->link;
		last->link->link = last;
		last->link = NULL;
		return 0;
	}
	while(last != NULL){
		first = middle;
		middle = last;
		last = last->link;

		middle->link = first;
	}
	h->first = middle;
	return 0;
}

// first, middle, last를 이용해 노드의 순서를 역으로 바꿔주는 함수입니다.
// 세 개의 포인터를 이용하지 않을 시엔, 한 노드가 가리키는 노드를 바꿨을 때 특정 노드에 접근할 수 있는 수단을 잃어버리기 때문에 세 개의 포인터를 사용했습니다.
// first, middle, last가 각각 한 칸의 차이를 두고 증가하며, 이때 middle이 가리키는 노드가 first를 가리키게 바꾸어주고, 다음으로 진행합니다.
// 이 때, 포인터 세 개를 이용하기 때문에 노드가 한 개일 때와 두 개일 때의 문제가 있습니다. 따라서, 노드가 한 개일 때는 작업을 수행하지 않는 if문을 추가해줍니다.
// 노드가 두 개일 때는 두 노드의 순서를 바꿔주는 if문을 추가합니다.
// 또, 리스트가 비었다면 에러 메세지를 출력하는 if문을 추가합니다.


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

// 리스트를 모두 출력하는 함수입니다.
// 리스트가 비었을 때에는 비었다는 메세지를 출력합니다.
// 리스트가 비지 않았을 때에는, p가 NULL이 될 때까지 리스트에 포함된 노드를 하나씩 출력합니다.
// 이때 i를 하나씩 증가시켜, 노드의 총 갯수를 센 다음 노드의 갯수를 출력합니다.