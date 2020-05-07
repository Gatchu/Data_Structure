/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

// 저번의 singly-linked-list.c와는 다르게 initialize로 넘기는 매개변수가 더블 포인터형입니다.
// 이전에는 함수 선언시 headNode 포인터형을 반환하도록 선언했기 때문에 싱글포인터형으로 붙여도 됐습니다.
// 그러나 현재는 반환형이 int형이기 때문에 headnode를 넘길 때 더블포인터형으로 넘겨야 제대로 된 접근과 수정이 가능합니다.

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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


int initialize(headNode** h) {

    if(*h != NULL) freeList(*h);

    headNode* temp = (headNode*)malloc(sizeof(headNode));
    temp->first = NULL;
    *h = temp;

	return 1;
}

// 더블포인터형을 받아서 headnode를 초기화하는 함수입니다.
// 더블포인터형으로 받았기 때문에 *h를 이용해 **h를 포인팅하는 *h를 수정하는 모습입니다.
// 이때, 지난 singly의 경우에는 return값이 포인터형이었기 때문에 temp를 그냥 넘겼지만, 지금의 경우에는 더블포인터 h를 통째로 갖고와야 하기 때문에 *h = temp를 통해 값을 바꿔주는 모습입니다.
// 이후 return 1을 통해 함수가 정상적으로 종료되었다고 알려줍니다.

int freeList(headNode* h){
    listNode* p = h->first;
    listNode* prev = NULL;

    while(p != NULL){
        prev = p;
        p = p->rlink;
        free(prev);
    }
    free(h);
	return 1;
}

// 리스트 전체적으로 초기화하는 함수입니다. headnode를 전달받아 p가 첫 번째 노드를 가리키게 하고, p가 한칸씩 앞으로 이동하고, prev가 p를 뒤따라가면서 노드를 하나씩 free(prev)로 제거합니다.
// 그 다음 p가 NULL이 되면 반복문을 벗어나고, headnode인 h까지 free로 초기화를 한 뒤 1을 반환해서 함수가 정상적으로 종료되었다고 알립니다.

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
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}

// 리스트를 모두 출력하는 함수입니다. headnode를 전달받아 if문을 통해 리스트가 비어있지 않다면 p를 첫 노드에 할당합니다.
// 이후 p가 NULL이 아니게 될 때까지 노드를 하나씩 타면서 키를 프린트한 뒤 p가 NULL이 되면 함수를 벗어납니다.
// 이 때, i가 p가 증가될 때마다 증가하면서 전체 리스트에 들어있는 item의 수를 셉니다.




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
    listNode* p;

    node->key = key;

    p = h->first;

    if(h->first == NULL){
        h->first = node;
        node->rlink = NULL;
        node->llink = NULL;
        return 1;
    }
    while(p->rlink != NULL){
        p = p->rlink;
    }

    p->rlink = node;
    node->rlink = NULL;
    node->llink = p;

	return 1;
}

// 리스트의 맨 끝에 노드를 추가하는 함수입니다.
// 노드 하나를 동적할당으로 만들고, 입력받은 키를 노드의 키로 추가한 뒤, 먼저 리스트가 비어있는 경우 노드를 첫 노드로 추가합니다.
// 그 뒤에는 예외상황이 따로 없으므로, p->rlink가 NULL인경우까지 이동 후 마지막 노드를 추가합니다.



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
    listNode* p;
    listNode* changenode;

    p = h->first;

    if(h->first == NULL){
        printf("[ERROR] List is Empty!!!\n");
        return 0;
    }
    if(h->first != NULL && h->first->rlink == NULL){
        h->first = NULL;
        free(p);
        return 1;
    }
    while(p->rlink != NULL){
        p = p->rlink;
    }
    
    changenode = p->llink;
    free(p);
    changenode->rlink = NULL;

	return 1;
}

// 마지막 노드를 삭제하는 함수입니다. 리스트가 빈 경우 리스트가 비었다는 메세지를 출력합니다. 그 뒤 0을 리턴해 에러가 발생했다고 전달합니다.
// 노드가 한 개만 존재하는 경우, 마지막 노드가 첫 노드이므로 첫 노드 삭제 뒤 1을 반환해 작업을 제대로 마쳤다는 신호를 보냅니다.
// 이외의 경우에는 반복문으로, p가 마지막 노드에 위치할때까지 간 후 changenode가 맨 마지막 노드의 전 노드에 있고, p(마지막 노드)를 free선언 해 준 뒤 changenode가 마지막 노드가 되므로
// changenode의 rlink를 NULL로 만들어주는 함수입니다. 이후 작업이 잘 마무리 되면 1을 반환합니다.



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;

    if(h->first == NULL){
        h->first = node;
        node->rlink = NULL;
        node->llink = NULL;
    }else{
        node->rlink = h->first;
        node->llink = NULL;
        h->first = node;
        h->first->rlink->llink = node;
    }
    

	return 1;
}

// List의 맨 처음에 key에 대한 노드 하나를 추가하는 함수입니다.
// 노드를 동적할당을 통해 새로 하나 만든 뒤, 입력받은 키를 노드의 키에 넣습니다.
// 그 다음 리스트가 비었다면 새 노드를 headnode가 가리키도록 만들어 첫 노드로 만듭니다.
// 그 다음 node의 좌, 우 링크를 모두 NULL로 만들어 초기화시켜줍니다.
// 리스트가 비지 않았다면, 노드가 먼저 첫번째 노드를 가리키게 한 다음 headnode가 node를 가리키게 해 node를 첫 노드로 만듭니다.
// node->rlink가 이전의 첫 노드를 가리키고 있으므로, node 다음 노드로 이동한 뒤 그 노드의 llink를 첫 노드를 가리키게 해서 작업을 완료합니다.
// 작업이 잘 되었다면 1을 리턴합니다.

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
    listNode* p;

    p = h->first;

    if(h->first == NULL){
        printf("[ERROR] List is Empty!!!\n");
        return 0;
    }
    if(h->first != NULL && h->first->rlink == NULL){
        h->first = NULL;
        free(p);
        return 1;
    }

    h->first = p->rlink;
    free(p);
    h->first->llink = NULL;

	return 1;
}

// 먼저 p를 첫 번째 노드를 가리키도록 합니다.
// 리스트가 비어있을 시에는 에러 메세지를 프린트하고, 0을 반환하도록 하는 if문을 만듭니다.
// 리스트가 비지 않았고, 노드가 한 개만 존재할 시 첫 노드를 삭제한 뒤 headnode의 first를 NULL로 만들고, p를 free선언으로 메모리에서 할당 해제합니다. 그 다음 1을 리턴해 작업을 잘 마쳤음을 보입니다.
// 예외 상황에 해당하지 않았을 시, headnode가 두 번째 노드를 가리키게 한 뒤, 아직 첫 노드를 가리키는 p 노드를 삭제합니다.
// 작업을 잘 마쳤을 때 1을 리턴합니다.


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
    listNode* first = NULL;
    listNode* last;

    last = h->first;

    if(h->first == NULL){
        printf("[ERROR] List is Empty!!!\n");
        return 0;
    }
    if(h->first != NULL && h->first->rlink == NULL) return 1;
    while(last != NULL){
        first = last;
        last = last->rlink;
        first->rlink = first->llink;
        first->llink = last;
    }
    h->first = first;
	return 1;
}

// 이번에는 llink가 존재해, 노드의 뒤로 이동할 수 있으므로 포인터변수가 두 개 필요합니다.
// 노드가 비었을 때는 노드가 비었다는 에러 메세지를 출력한 뒤 0을 반환하는 if문을 만듭니다.
// 노드가 1개만 존재할 시에는 별다른 작업을 하지 않고 1을 반환합니다.
// 예외상황이 없다면, last가 먼저 하나씩 앞으로 이동하고 first가 뒤를 따라갑니다.
// 이 때, first의 양쪽 링크가 가리키는 노드를 바꾸면서 리스트를 역순으로 만듭니다.
// 첫 노드였던 곳은 llink가 NULL이었기 때문에 rlink가 NULL로 바뀌어 마지막 노드로 잘 초기화됩니다.
// 마지막 노드였던 곳은 rlink가 NULL이었기 때문에 llink가 NULL을 가리키게 되어 첫 노드로 잘 초기화됩니다.
// 이후 headnode가 첫 노드로 바뀐 노드를 가리키게 하고, 1을 리턴해 작업을 잘 마쳤다고 전달합니다.



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
    listNode* p;

    node->key = key;
    p = h->first;

    if(h->first == NULL){
        h->first = node;
        node->rlink = NULL;
        node->llink = NULL;
        return 1;
    }
    if((h->first != NULL) && (h->first->rlink == NULL) && (h->first->key > node->key)){
        node->rlink = h->first;
        h->first = node;
        node->llink = NULL;
        node->rlink->llink = node;
        return 1;
    }
    if(h->first->key > node->key){
        node->rlink = h->first;
        h->first = node;
        h->first->rlink->llink = node;
        node->llink = NULL;
        return 1;
    }
    while(p->rlink != NULL){
        if(p->rlink->key > node->key){
            node->rlink = p->rlink;
            p->rlink->llink = node;
            p->rlink = node;
            node->llink = p;
            return 1;
        }
        p = p->rlink;
    }

    p->rlink = node;
    node->llink = p;
    node->rlink = NULL;

    return 1;
    
}

// 동적할당으로 새 노드를 선언하고, 입력받은 키를 노드의 키로 삽입합니다.
// p를 첫 노드를 가리키게 합니다.
// 이때, 리스트가 비었다면 p를 바로 첫 노드로 만들고 1을 리턴하는 if문을 추가합니다.
// 노드가 하나만 존재하고, 그 노드의 key가 node의 키보다 클 때 새로 만들어진 노드가 첫 노드가 되도록 하는 if문을 추가합니다.
// 노드가 여러 개 존재하지만 새 노드를 첫 노드로 삽입해야 할 경우를 처리하는 if문도 추가로 만들어줍니다.
// 예외상황이 없을 시, p->rlink가 NULL을 가리키지 않는다면(p가 마지막 노드가 아니라면) p가 다음 노드로 이동하며 조건에 맞는 노드를 찾아 새 노드를 삽입하는 반복문을 만듭니다.
// 해당사항이 없다면 리스트의 맨 마지막에 노드를 추가하고, llink를 이전 노드를 가리키도록, rlink에 NULL을 넣어 마무리합니다.
// 이후 작업이 잘 마무리되었다면 1을 리턴합니다.


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
    listNode* p;

    p = h->first;

    if(h->first == NULL){
        printf("[ERROR] List is Empty!!!\n");
        return 0;
    }
    if(h->first->key == key){
        if(p->rlink == NULL){
            h->first = NULL;
            free(p);
            return 1;
        }else{
            h->first = p->rlink;
            h->first->llink = NULL;
            free(p);
            return 1;
        }
    }
    while(p != NULL){
        if(p->key == key) break;
        p = p->rlink;
    }
    if(p == NULL){
        printf("[ERROR] There is not %d\n", key);
        return 0;
    }
    if(p->rlink == NULL){
        p->llink->rlink = NULL;
        free(p);
        return 1;
    }else{
        p->rlink->llink = p->llink; // p->rlink != NULL
        p->llink->rlink = p->rlink;
        free(p);
        return 1;
    }

    free(p);

	return 1;
}

// 입력받은 key와 일치하는 key를 가진 노드를 삭제하는 노드입니다.
// 먼저 리스트가 비었을 때 에러 메세지를 출력하는 if문을 만듭니다.
// 첫 번째 노드가 일치하는 경우, 그 다음 노드가 없을 시(노드가 한 개만 존재할 시) 첫 번째 노드를 삭제하고 headnode가 NULL을 가리키게 합니다.
// 첫 번째 노드가 일치하고, 그 다음의 노드가 존재하면 두 번째의 노드를 첫 번째 노드로 만들고, 첫 번째였던 노드를 free선언을 통해 삭제합니다.
// 이후 p가 한 단계씩 이동하면서 key를 가진 노드에서 멈추거나 NULL에 도달하는 반복문을 만듭니다.
// p가 NULL에 도달했다면 리스트 안에 key를 가진 함수가 없다는 뜻이므로 리스트에는 그 값이 없다는 에러 메세지를 출력하고 0을 리턴합니다.
// 그렇지 않은 경우는 p가 입력받은 key와 일치하는 key를 가진 노드를 가리키고 있습니다.
// 이때, p가 마지막 노드라면(p->rlink == NULL이라면) 마지막 노드 전 노드의 rlink를 NULL로 만들어 마지막 노드로 만든 뒤, 마지막이었던 노드를 삭제합니다.
// 여러 상황에 해당하지 않는다면, p 다음의 노드의 llink가 p의 전 노드를 가리키도록, p 전의 노드가 p 다음의 노드를 가리키도록 연결해 p 이전 노드와 p 다음 노드가 서로 가리키도록 합니다.
// 그 뒤 p를 free선언으로 삭제합니다.