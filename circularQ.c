/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

//크기가 4인 queue와 front, rear가 담긴 구조체를 선언합니다.

QueueType *createQueue();
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);

element getElement();


int main(void)
{
	QueueType *cQ = createQueue();
	element data;

	char command;

	do{
        printf("[-----Software, Student ID : 2017038040, Name : Han Gyu Jun-----]\n");
        // 성명과 학번이 출력되도록 소스를 수정했습니다. 한글은 컴파일시 깨져서 영문으로 작성했습니다.
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		//scanf로 메뉴를 입력받고, 아래 switch - case문으로 알맞은 기능에 접근합니다.

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}


QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

// 위에서 선언한 QueueType구조체를 통해 큐를 동적할당합니다. 이때, 그 큐의 front와 rear도 0으로 초기화한 후 큐 주소를 반환합니다.

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}

// item변수를 선언, 사용자가 입력한 데이터를 item에 받아 반환합니다.

/* complete the function */
int isEmpty(QueueType *cQ)
{
    if((cQ->front)%MAX_QUEUE_SIZE == (cQ->rear)%MAX_QUEUE_SIZE) return 0;
    else return 1;
}

// 큐가 비었을 때 0을 리턴하는 함수입니다. front의 값과 rear의 값이 같으면 큐가 비었다고 판단합니다.
// front가 위치한 자리는 무조건 비어 있기 때문에, empty일 때와 full일 때를 다르게 구분할 수 있습니다.

/* complete the function */
int isFull(QueueType *cQ)
{
    if((cQ->front)%MAX_QUEUE_SIZE == ((cQ->rear)+1)%MAX_QUEUE_SIZE) return 0;
    else return 1;
}

// 큐가 가득 찼을 때 0을 리턴하는 함수입니다. front의 값과 rear+1의 값이 같으면 큐가 가득 찼다고 판단합니다.
// front의 자리가 무조건 비어있기 때문에, rear는 큐가 비어있을 때를 제외하면 front와 같은 값을 가질 수 없습니다.


/* complete the function */
void enQueue(QueueType *cQ, element item)
{
    if(isFull(cQ) == 0) printf("[Error]Queue is Full\n");
	else{
		cQ->rear = ((cQ->rear)+1)%MAX_QUEUE_SIZE;
   	 	cQ->queue[cQ->rear] = item;
	}
}

// 큐가 가득 찼을 때 Error메세지를 출력하고, 그렇지 않으면 큐에 데이터를 입력하는 함수입니다.
// rear가 데이터가 들어갈 자리보다 뒤에 있기 때문에 rear값을 먼저 증가시키고 데이터를 입력합니다. 이때 rear가 큐 사이즈를 초과한다면 다시 0으로 되돌립니다.
// 이렇게 되면, rear증가 -> rear가 가리키는 곳에 데이터 입력이 되어, 데이터 입력을 마쳤을 때는 rear가 항상 맨 뒤의 데이터가 있는 자리를 가리킵니다.

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
    if(isEmpty(cQ) == 0) printf("[Error]Queue is Empty\n");
    else{
        *item = cQ->queue[cQ->front];
		cQ->queue[++cQ->front] = '\0';
	}
    if((cQ->front) == MAX_QUEUE_SIZE) cQ->front = 0;
}

// 큐가 비어 있을 때 Error메세지를 출력하고, 그렇지 않으면 큐에 있는 데이터를 제거하는 함수입니다.
// 큐는 First In First Out이기 때문에 먼저 들어온 데이터부터 제거합니다.
// front가 데이터가 제거될 자리보다 앞에 있기 때문에 front값을 먼저 증가시키고 데이터를 제거합니다. 이때 front가 큐 사이즈를 초과한다면 다시 0으로 되돌립니다.
// 이렇게 되면, front증가 -> front가 가리키는 곳의 데이터 제거가 되어, 데이터 제거를 마쳤을 때에는 front가 첫 데이터의 앞인 빈 공간의 주소를 가리킵니다.
// front가 가리키는 곳의 데이터가 제거되었으므로, front가 가리키는 곳은 큐 내에서 항상 빈 공간입니다.
// front가 큐 사이즈를 초과했을 때 0으로 되돌리는 방법이 rear와 다른 것은 두 방법을 비교해보기 위해 둘 다 시도했기 때문입니다.

void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}

// 큐의 내용을 출력하는 함수입니다. front는 데이터가 담긴 곳 이전의 주소를 가리키기 때문에, 첫 데이터는 front+1에 위치해 있습니다.
// 때문에 front에 +1을 더한 수를 first에 담습니다.
// rear는 마지막 데이터가 담긴 곳의 주소를 가리킵니다. arr[n]배열의 마지막 데이터는 arr[n-1]이기 때문에 반복문의 조건식을 깔끔하게 하기 위해 rear+1을 last로 정합니다.
// 이후 first, last를 사용해 큐를 모두 출력하는 함수를 만듭니다.
// 이때, 큐의 데이터가 꼭 배열의 순서대로 저장되어 있는 것이 아니기 때문에, 배열의 마지막 값에 도달했을 시 배열의 첫번째 값으로 돌려줍니다.

void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

// 현재 배열을 그대로 출력하여 어디에 front가 있는지, 그리고 데이터가 배열의 어디에 위치해 있는지 출력합니다.
// front의 자리는 항상 비어 있기 때문에 front가 있는 곳을 가리킬 때에는 front를 출력하고, 이외에는 데이터를 출력하거나 비었다는 것을 출력합니다.
// 이후 front와 rear값을 정확하게 알기 위해 front와 rear의 값을 출력합니다.