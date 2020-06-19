#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX          20

typedef struct Vertex {
    int num;                    // vertex number
    struct Vertex* link;        // link to a next adjacent vertex
} Vertex;

typedef struct VertexHead {
    Vertex* head;               // linked list of all adjacent vertices
} VertexHead;

typedef struct Graph {
    VertexHead* vlist;          // list of all vertices : vlist[MAX_VERTEX]
} Graph;

int GraphTF[MAX_VERTEX];        // 정점들이 있는지 없는지 확인하기 위해 추가한 배열입니다. 0이면 해당 정점 없음, 1이면 해당 정점 있음 입니다.

int stack[MAX_VERTEX];          // stack자료구조를 사용하기 위하여 만든 스택입니다. 최대 정점 갯수만큼의 용량을 가집니다
int top = -1;                   // DFS에서 스택을 가장 많이 사용하는 경우는 모든 정점이 일렬로 연결된 경우->최대 정점 갯수가 스택에 들어가는 경우이기 때문입니다.                
void pop();                     // 스택을 관리하기 위한 top, pop함수, push함수를 만듭니다.
void push(int v);

int queue[MAX_VERTEX + 1];          // queue자료구조를 사용하기 위해 만든 큐입니다. 최대 정점 갯수만큼의 용량을 가집니다.
int front = -1;                 // front, rear, deQueue함수, enQueue함수를 만듭니다.
int rear = -1;
int deQueue();
void enQueue(int v);

Graph* createGraph(Graph** graph);          // empty graph creation initialize
Graph* destroyGraph(Graph** graph);         // deallocating all allocates memory
void insertVertex(Graph* graph);            // vertex insertion
void insertVertex_range(Graph* graph);      // vertex(range) insertion
void deleteVertex(Graph* graph, int v);     // vertex deletion
void insertEdge(Graph* graph);              // new edge creation between two vertices
void deleteEdge(Graph* graph);              // edge removal
void depthFS(Graph* graph);                 // depth first search using stack vertex
void breadthFS(Graph* graph);               // breadth first search using queue 
void printGraph(Graph* graph);              // printing graph with vertices and edges
void printVertex(Graph* graph);

// createGraph          - 그래프를 만드는 함수입니다.
// destroyGraph         - 그래프를 제거하는 함수입니다.
// insertVertex         - 정점을 만드는 함수입니다.
// insertVertex_range   - 일정 범위 내의 정점을 한꺼번에 만드는 함수입니다.
// deleteVertex         - 정점을 제거하는 함수입니다.
// insertEdge           - 간선을 만드는 함수입니다.
// deleteEdge           - 간선을 제거하는 함수입니다.
// depthFS              - 깊이우선탐색을 하는 함수입니다.
// breadthFS            - 넓이우선탐색을 하는 함수입니다.
// printGraph           - 그래프를 출력하는 함수입니다.
// printVertex          - 현재 있는 정점들을 출력하는 함수입니다.

int main() {

    char command;               // 메뉴를 선택하기 한 변수입니다.
    Graph* graph = NULL;        // 그래프 포인터를 만듭니다. 메모리에 할당된 공간이 아직 없어 NULL처리를 했습니다.
    int v;                      // 정점을 입력받을 변수입니다.


    do {
        printf("\n\n");
        printf("[-----Software, Student ID : 2017038040, Name : Han Gyu Jun-----]\n");
        // 성명과 학번이 출력되도록 소스를 수정했습니다. 한글은 컴파일시 깨져서 영문으로 작성했습니다.
        printf("----------------------------------------------------------------\n");
        printf("                      Term-Project : Graph                      \n");
        printf("----------------------------------------------------------------\n");
        printf(" Create Graph     = c           Quit             = q\n");
        printf(" Destroy Graph    = d           Insert Edge      = n\n");
        printf(" Insert Vertex    = i           Delete Edge      = l\n");
        printf(" Delete Vertex    = e           depth FS         = f\n");
        printf(" Print Graph      = p           breadth FS       = s\n");
        printf(" Print Vertex     = v           Insert V(range)  = r\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'c': case 'C':
            if (graph == NULL) graph = createGraph(&graph);
            else printf("[ERROR] Graph is already exist!!!\n");
            break;
        case 'q': case 'Q':
            if (graph == NULL) break;
            else graph = destroyGraph(&graph);
            break;
        case 'd': case 'D':
            if (graph == NULL) {
                printf("[ERROR] Graph is not exist!!!\n");
                break;
            }
            else graph = destroyGraph(&graph);
            break;
        case 'i': case 'I':
            if (graph == NULL) {
                printf("[ERROR] Graph is not exist!!!\n");
                break;
            }
            else insertVertex(graph);
            break;
        case 'e': case 'E':
            if (graph == NULL) {
                printf("[ERROR] Graph is not exitst!!!\n");
                break;
            }
            else {
                printf("Vertex : ");
                scanf("%d", &v);
                deleteVertex(graph, v);
                break;
            }
        case 'n': case 'N':
            if (graph == NULL) {
                printf("[ERROR] Graph is not exist!!!\n");
                break;
            }
            else insertEdge(graph);
            break;
        case 'l': case 'L':
            if (graph == NULL) {
                printf("[ERROR] Graph is not exist!!!\n");
                break;
            }
            else deleteEdge(graph);
            break;
        case 'f': case 'F':
            if (graph == NULL) {
                printf("[ERROR] Graph is not exist!!!\n");
                break;
            }
            else depthFS(graph);
            break;
        case 's': case 'S':
            if (graph == NULL) {
                printf("[ERROR] Graph is not exist!!!\n");
                break;
            }
            else breadthFS(graph);
            break;
        case 'p': case 'P':
            if (graph == NULL) {
                printf("[ERROR] Graph is not exist!!!\n");
                break;
            }
            else printGraph(graph);
            break;
        case 'v': case 'V':
            if (graph == NULL) {
                printf("[ERROR] Graph is not exist!!!\n");
                break;
            }
            else printVertex(graph);
            break;
        case 'r':case'R':
            if (graph == NULL) {
                printf("[ERROR] Graph is not exist!!!\n");
                break;
            }
            else insertVertex_range(graph);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

// 메뉴가 나오는 main함수는 전체적으로 비슷한 처리를 했습니다.
// 그래프를 만들 때, 이미 그래프가 만들어졌다면 에러 메세지를 출력합니다.
// 메뉴마다 그래프가 만들어지지 않았다면 에러 메세지를 출력하고, 그렇지 않다면 각 함수마다 필요한 인자를 받습니다(그래프, 정점 등)
// 정해진 것 이외의 키를 입력하면 concentration이라는 메세지가 출력됩니다.
// q가 입력되면 프로그램을 종료합니다.


Graph* createGraph(Graph** graph) {
    Graph* temp = *graph;
    temp = (Graph*)malloc(sizeof(Graph));
    temp->vlist = (VertexHead*)malloc(sizeof(VertexHead) * MAX_VERTEX);
    for (int i = 0; i < MAX_VERTEX; i++) temp->vlist[i].head = (Vertex*)malloc(sizeof(Vertex));
    for (int i = 0; i < MAX_VERTEX; i++) GraphTF[i] = 0;

    return temp;
}

// 그래프를 만드는 함수입니다.
// graph를 만들고, main함수에서 이 그래프를 다루기 위해 더블포인터형 인자를 가져오도록 되어 있습니다.
// 먼저, 임시 그래프 포인터 변수를 선언하고 이 그래프 포인터변수를 인자로 받은 그래프에 할당합니다.
// 이 임시 포인터변수로 그래프를 동적할당한 뒤, 그래프의 vlist를 최대 정점 갯수만큼 동적할당합니다.
// 그 다음, 각 정점을 표시하는 vlist마다 간선을 표시하기 위한 연결리스트의 헤드노드인 head를 동적할당합니다.
// 각 정점이 활성화되었는지를 알려주는 GraphTF배열을 모두 0으로 만들어 모든 정점을 초기화합니다.
// 모든 작업이 완료되었다면 temp를 반환해 main으로 그래프의 주솟값을 반환합니다.
// 이 함수가 종료되면 그래프 및 기본구조가 동적할당되어 사용 가능한 상태로 바뀝니다.

Graph* destroyGraph(Graph** graph) {
    Graph* temp = *graph;

    for (int i = 0; i < MAX_VERTEX; i++) {
        if (GraphTF[i] == 1) {
            deleteVertex(temp, i + 1);
        }
    }
    for (int i = 0; i < MAX_VERTEX; i++) free(temp->vlist[i].head);
    free(temp->vlist);
    temp->vlist = NULL;
    free(temp);
    temp = NULL;

    return temp;
}

// 그래프를 제거하는 함수입니다.
// createGraph와 같이, main에서 그래프를 다루기 위해 더블포인터형 인자를 가져옵니다.
// 먼저, GraphTF 배열을 탐색하여 1인 값이 나오면 정점이 존재하는 것이기 때문에 deleteVertex함수를 호출하고, 그래프의 주소와 정점 값을 넘겨줍니다.
// 이때 정점은 1~20을 사용하지만, 배열 등은 0~19의 범위를 갖기 때문에 +1된 값을 넘겨줍니다.
// deleteVertex에서 정점을 제거하면서 동시에 그 정점과 연결된 간선도 모두 제거하기 때문에 연결리스트는 head를 빼고 이미 메모리 할당 해제가 완료된 상황입니다.
// 여기서 head, vlist, temp를 순서대로 메모리 할당 해제하고 NULL값을 가리키도록 만들어 그래프를 제거합니다.
// 해제된 그래프 포인터를 다시 리턴합니다. 이제 그래프는 사용 불가능한 상태입니다.

void insertVertex(Graph* graph) {
    int num;
    printf("Vertex Number(1~20) : ");
    scanf("%d", &num);

    if (num < 1 || num > 20) {
        printf("[ERROR] [ %d ] is not in range!!!\n", num);
        return;
    }

    if (GraphTF[num - 1] == 1) {
        printf("[ERROR] This Vertex is already exist!!!\n");
        return;
    }
    else GraphTF[num - 1] = 1;

    graph->vlist[num - 1].head->link = NULL;
}

// 정점을 삽입하는 함수입니다.
// 그래프 포인터를 인자로 받습니다.
// 정점을 입력받아 num변수에 저장합니다.
// 이때, num이 범위 안의 정수가 아니라면 에러 메세지를 출력하고 함수를 종료하도록 합니다.
// 또, 정점이 이미 존재한다면 에러 메세지를 출력하도록 합니다.
// 그렇지 않다면, 해당 정점의 GraphTF를 1로 만들어 정점이 존재한다고 바꾸고, 해당 정점의 헤드노드 링크를 NULL로 초기화해줍니다.

void insertVertex_range(Graph* graph) {
    int start, end;
    printf("Start Vertex Number(1~20) : ");
    scanf("%d", &start);
    printf("End Vertex Number(1~20) : ");
    scanf("%d", &end);

    if (start < 1 || start > 20) {
        printf("[ERROR] [ %d ] is not in range!!!\n", start);
        return;
    }else if(end < 1 || end > 20) {
        printf("[ERROR] [ %d ] is not in range!!!\n", end);
        return;
    }

    for (int i = start; i < end + 1; i++) {
        if (GraphTF[i - 1] == 1) {
            printf("[ERROR] [ %d ] Vertex is already exist!!!\n", i);
            return;
        }
        else {
            GraphTF[i - 1] = 1;
            graph->vlist[i - 1].head->link = NULL;
        }
    }
}

// 일정 범위 내의 정점을 한꺼번에 선언하는 함수입니다.
// 그래프 포인터를 인자로 받습니다.
// start와 end변수에 시작 정점 번호와 끝 정점 번호를 입력받습니다.
// 시작값과 끝값이 1~20사이의 정수인지를 먼저 확인해줍니다.
// 그 다음, 시작값과 끝값 사이의 정점이 이미 하나라도 존재한다면 에러 메세지를 출력하고 함수를 종료합니다.
// 그렇지 않다면, GraphTF값을 바꿔주고 헤드노드 링크를 초기화합니다.

void insertEdge(Graph* graph) {
    int v1, v2;
    int ae1 = 0;
    int ae2 = 0;
    Vertex* first1 = NULL;
    Vertex* last1;
    Vertex* first2 = NULL;
    Vertex* last2;
    Vertex* nv1 = (Vertex*)malloc(sizeof(Vertex));
    Vertex* nv2 = (Vertex*)malloc(sizeof(Vertex));

    printf("Vertex 1 : ");
    scanf("%d", &v1);
    printf("Vertex 2 : ");
    scanf("%d", &v2);

    if (v1 < 1 || v1 > 20) {
        printf("[ERROR] [ %d ] is not in range!!!\n", v1);
        return;
    }
    else if (v2 < 1 || v2 > 20) {
        printf("[ERROR] [ %d ] is not in range!!!\n", v2);
        return;
    }

    if (GraphTF[v1 - 1] != 1) {
        printf("[ERROR] Vertex1 is not exist!!!\n");
        return;
    }
    else if (GraphTF[v2 - 1] != 1) {
        printf("[ERROR] Vertex2 is not exist!!!\n");
        return;
    }

    last1 = graph->vlist[v1 - 1].head->link;
    last2 = graph->vlist[v2 - 1].head->link;


    while (last1 != NULL) {
        if (last1->num == v2) ae1 = 1;
        if (last1 != NULL && last1->num > v2) break;
        first1 = last1;
        last1 = last1->link;
    }
    while (last2 != NULL) {
        if (last2->num == v1) ae2 = 1;
        if (last2 != NULL && last2->num > v1) break;
        first2 = last2;
        last2 = last2->link;
    }

    if (ae1 == 1 && ae2 == 1) {
        printf("[ERROR] This Edge is already exist!!!\n");
        return;
    }

    if (graph->vlist[v1 - 1].head->link == NULL) {
        graph->vlist[v1 - 1].head->link = nv1;
        nv1->link = NULL;
        nv1->num = v2;
    }
    else if (graph->vlist[v1 - 1].head->link != NULL && graph->vlist[v1 - 1].head->link->num > v2) {
        nv1->link = graph->vlist[v1 - 1].head->link;
        graph->vlist[v1 - 1].head->link = nv1;
        nv1->num = v2;
    }
    else {
        first1->link = nv1;
        if (last1 == NULL) nv1->link = NULL;
        else nv1->link = last1;
        nv1->num = v2;
    }

    if (graph->vlist[v2 - 1].head->link == NULL) {
        graph->vlist[v2 - 1].head->link = nv2;
        nv2->link = NULL;
        nv2->num = v1;
    }
    else if (graph->vlist[v2 - 1].head->link != NULL && graph->vlist[v2 - 1].head->link->num > v1) {
        nv2->link = graph->vlist[v2 - 1].head->link;
        graph->vlist[v2 - 1].head->link = nv2;
        nv2->num = v1;
    }
    else {
        first2->link = nv2;
        if (last2 == NULL) nv2->link = NULL;
        else nv2->link = last2;
        nv2->num = v1;
    }
}

// 간선을 추가하는 함수입니다.
// 그래프 포인터를 인자로 받습니다.
// 먼저, 간선은 연결하는 쪽과 연결되는 쪽 두 곳의 정점 연결 리스트에 간선 정보를 추가해야 하기 때문에 노드를 두 개 동적할당합니다.
// 또, 탐색을 위해 사용할 Vertex포인터들을 선언하고, 연결할 정점 정보를 가질 v1, v2를 추가합니다. 전처리를 위해 사용할 ae1, ae2도 추가합니다.
// v1과 v2에 정점 한개씩을 입력받은 뒤, 각각 범위 내 정수인지, 존재하지 않는 정점인지를 확인합니다. 각각의 경우에 에러 메세지를 출력합니다.
// 해당사항이 없다면, 탐색을 위한 Vertex포인터에 각각 처음 탐색 시작위치를 할당합니다.
// 이후 연결리스트를 삽입과 동시에 정렬하기 위해서, 포인터가 입력받은 정점보다 큰 정점과 연결된 노드 바로 전에 위치하도록 조절합니다.
// 이때, ae1과 ae2가 각각 첫번째 정점과 두번째 정점이 이미 연결리스트에 있는지 확인하고, 두 ae가 동시에 1이 된다면 이미 간선이 리스트에 존재하는 것이기 때문에 에러 메세지를 출력합니다.
// 다음으로, 입력할 정점이 해당 리스트의 첫 번째인지, 아니면 중간에 삽입되는지, 마지막인지의 경우를 나누어서 처리합니다.
// 두번째 정점도 같이 세 경우로 나누어서 처리합니다.

void deleteVertex(Graph* graph, int v) {
    Vertex* first = NULL;
    Vertex* last;

    if (GraphTF[v - 1] == 0) {
        printf("[ERROR] This Vertex is not exist!!!\n");
        return;
    }

    GraphTF[v - 1] = 0;

    last = graph->vlist[v - 1].head->link;

    while (last != NULL) {
        if (graph->vlist[v - 1].head->link != NULL && graph->vlist[v - 1].head->link->link == NULL) {
            graph->vlist[v - 1].head->link = NULL;
            free(last);
            break;
        }
        first = last;
        last = last->link;
        free(first);
    }

    for (int i = 0; i < MAX_VERTEX; i++) {
        if (GraphTF[i] == 1) {
            last = graph->vlist[i].head->link;
            if (last != NULL && last->link != NULL && last->num == v) {
                graph->vlist[i].head->link = graph->vlist[i].head->link->link;
                free(last);
                continue;
            }
            else if (last != NULL && last->link == NULL && last->num == v) {
                graph->vlist[i].head->link = NULL;
                free(last);
                continue;
            }

            while (last != NULL) {
                if (last->num == v) {
                    first->link = last->link;
                    free(last);
                    break;
                }
                first = last;
                last = last->link;
            }
        }
    }
}

// 정점을 제거하는 함수입니다. 그래프 포인터와 정점을 인자로 받습니다.
// 간선 제거를 위한 Vertex포인터 두 개를 선언합니다.
// 이때, 입력받은 정점이 존재하지 않는다면 에러 메세지를 출력하고 함수를 종료합니다.
// 그렇지 않다면, GraphTF를 0으로 만듭니다.
// 간선 제거를 위해서 해당 정점의 헤드노드에 Vertex포인터를 둡니다.
// 이후, 리스트가 하나만 존재하는 경우와 일반적인 경우로 나누어 first, last를 이용해 한 칸씩 뒤로 가면서 모든 간선을 제거합니다.
// 다른 정점에서 해당 정점으로 연결되는 간선이 존재할 수 있으니, 모든 정점을 for문으로 돌면서 GraphTF로 정점이 있는지 확인하고, 있다면 해당 정점마다 리스트를 탐색하여 제거해야 할 노드를 탐색합니다.
// 제거해야할 노드가 있다면, 그 노드의 위치에 따라서 경우의 수를 나눕니다. 제거해야 할 노드가 리스트의 중간에 있다면 링크를 다시 연결하고, 끝에 있다면 NULL처리를 하는 등의 처리를 합니다.
// 모든 노드를 돌았다면, 해당하는 정점에 대한 정보가 그래프 전체에서 지워졌습니다. 함수가 종료됩니다.

void deleteEdge(Graph* graph) {
    int v1, v2;
    int ae1 = 0;
    int ae2 = 0;
    Vertex* first1 = NULL;
    Vertex* last1;
    Vertex* first2 = NULL;
    Vertex* last2;

    printf("Vertex 1 : ");
    scanf("%d", &v1);
    printf("Vertex 2 : ");
    scanf("%d", &v2);

    if (GraphTF[v1 - 1] != 1) {
        printf("[ERROR] Vertex1 is not exist!!!\n");
        return;
    }
    else if (GraphTF[v2 - 1] != 1) {
        printf("[ERROR] Vertex2 is not exist!!!\n");
        return;
    }

    last1 = graph->vlist[v1 - 1].head->link;
    last2 = graph->vlist[v2 - 1].head->link;

    while (last1 != NULL) {
        if (last1->num == v2) {
            ae1 = 1;
            break;
        }
        first1 = last1;
        last1 = last1->link;
    }
    while (last2 != NULL) {
        if (last2->num == v1) {
            ae2 = 1;
            break;
        }
        first2 = last2;
        last2 = last2->link;
    }


    if (last1 == NULL && last2 == NULL && ae1 == 0 && ae2 == 0) {
        printf("[ERROR] This edge is not exist!!!\n");
        return;
    }

    if (last1 == graph->vlist[v1 - 1].head->link) {
        graph->vlist[v1 - 1].head->link = graph->vlist[v1 - 1].head->link->link;
        free(last1);
    }
    else {
        first1->link = last1->link;
        free(last1);
    }

    if (last2 == graph->vlist[v2 - 1].head->link) {
        graph->vlist[v2 - 1].head->link = graph->vlist[v2 - 1].head->link->link;
        free(last2);
    }
    else {
        first2->link = last2->link;
        free(last2);
    }
}

// 간선을 제거하는 함수입니다. 그래프 포인터를 인자로 받습니다.
// 정점 정보를 받는 v1, v2. 예외상황을 위한 ae1, ae2를 선언하고, 탐색을 위한 Vertex포인터들을 선언합니다.
// 먼저 v1, v2를 이용해 입력받은 정점이 존재하는지 검사하고 존재하지 않는다면 에러 메세지를 출력합니다.
// 이후 반복문을 돌면서 해당 정점의 리스트에 간선(노드)가 존재하는지 탐색하는데, 이때 탐색이 완료되면 ae1이나 ae2를 1로 바꿔주고 반복문을 종료합니다.
// ae1과 ae2가 모두 0이라면 해당 간선이 존재하지 않는 것이기 때문에 에러 메세지를 출력하고 함수를 종료합니다.
// 방향 없는 그래프의 특성상, ae1이나 ae2 중 하나만 1이 되는 상황은 존재하지 않습니다.
// 이후 양 정점에서 노드를 지워, 간선 정보를 완전히 제거합니다.

void depthFS(Graph* graph) {
    int v;
    int flag[MAX_VERTEX];
    Vertex* search;

    for (int i = 0; i < MAX_VERTEX; i++) flag[i] = 0;

    printf("Start Vertex : ");
    scanf("%d", &v);
    if (GraphTF[v - 1] == 0) {
        printf("[ERROR] This Vertex is not exist!!!\n");
        return;
    }

    printf("Depth First Search Start\n");

    search = graph->vlist[v - 1].head->link;
    push(v);
    printf(" [ %d ] ", v);
    flag[v - 1] = 1;
    

    while (top != -1) {
        while (search != NULL) {
            if (flag[search->num - 1] == 0) {
                v = search->num;
                search = graph->vlist[v - 1].head->link;
                
                
                printf(" [ %d ] ", v);
                flag[v - 1] = 1;
                push(v);
            }
            else search = search->link;
        }
        pop();
        v = stack[top];
        if (top == -1) break;
        search = graph->vlist[v - 1].head->link;
    }

    printf("\n----- DFS end -----\n");

}

// 깊이 우선 탐색으로 그래프를 탐색하는 함수입니다. 그래프 포인터를 인자로 받습니다.
// 정점 정보를 받는 v, 방문 정보를 입력하는 flag배열, 탐색을 위한 Vertex포인터변수를 선언합니다.
// 방문 정보를 초기화하기 위해 flag배열을 모두 0으로 만듭니다.
// 정점을 입력받은 뒤, 해당 정점이 존재하는지를 먼저 처리합니다.
// DFS가 시작되면, search는 시작 정점의 첫 노드로 이동합니다.
// 첫 정점을 스택에 넣고, 방문정보를 1로 수정하고 해당 정점을 출력합니다.
// 스택이 빌 때까지 반복문을 진행합니다.
// 이때, 탐색을 하던 중 해당 간선이 가리키는 노드가 미방문 노드라면 바로 이동하고, 스택에 해당 정점을 넣고, 해당 정점을 출력합니다.
// 그렇지 않다면, 리스트의 다음 노드로 이동합니다.
// 해당 정점의 모든 노드들을 탐색했다면 pop을 이용해 해당 정점을 제거합니다.
// 이후 v를 stack[top]값으로 만들어 이전에 탐색했지만, 아직 모든 리스트를 탐색하지 않는 노드로 되돌아갑니다.
// 만약 top이 -1이라면 반복문을 스택이 빈 것이기 때문에 반복문을 종료합니다.
// 그 다음, search를 재설정해 이전에 탐색했지만 모든 리스트를 탐색하지 않은 정점의 리스트를 탐색하도록 위치를 조정합니다.
// 이후 DFS가 종료되었다는 메세지를 출력합니다.

void pop() {
    top = top - 1;
//      int x;
//      x = stack[top--];
//      if(top == -1) return NULL;
//      return x;
}

// 스택에서 데이터를 제거하는 pop함수입니다.
// 스택에서 데이터를 제거한 뒤 그것을 정점 정보로 활용하는 방법도 있지만, DFS에서는 Stack의 Top를 통해 직접적으로 접근했습니다.

void push(int v)
{
    if (top == MAX_VERTEX - 1) {
        printf("[ERROR] Stack is Full!!!\n");
        return;
    }
    stack[++top] = v;
}

// 스택에 데이터를 넣는 push함수입니다.
// 정점 정보를 인자로 받습니다.
// 스택이 가득 찼다면, 에러 메세지를 출력하고 함수를 종료합니다.(하지만 스택의 최대값을 설정했기 때문에 해당 상황은 DFS코드 문제가 아니면 없을 것이라 생각합니다.)
// 이후 top을 한 칸 띄우고 해당 정점을 입력합니다.

void breadthFS(Graph* graph) {
    int v;
    int flag[MAX_VERTEX];
    Vertex* search;

    for(int i = 0; i < MAX_VERTEX; i++) flag[i] = 0;

    printf("Start Vertex : ");
    scanf("%d", &v);
    if(GraphTF[v - 1] == 0){
        printf("[ERROR] This Vertex is not exist!!!\n");
        return;
    }

    printf("Breadth First Search Start\n");
    search = graph->vlist[v - 1].head->link;
    flag[v - 1] = 1;
    enQueue(v);
    printf(" [ %d ] ", v);
    v = deQueue();

    do{
        while (search != NULL) {
            if (flag[search->num - 1] == 0) {
                enQueue(search->num);
                printf(" [ %d ] ", search->num);
                flag[search->num - 1] = 1;
                search = search->link;
            }else search = search->link;
        }
        v = deQueue();
        if (v == -99) break;
        search = graph->vlist[v - 1].head->link;

    } while (v != -99);

    printf("\n----- BFS END -----\n");
}

// 넓이 우선 탐색 함수입니다. 그래프 포인터를 인자로 받습니다.
// 정점 정보를 얻기 위한 v, 방문 정보를 적기 위한 flag배열, 탐색을 위한 Vertex포인터변수를 선언합니다.
// 모든 방문플래그를 0으로 초기화합니다.
// 정점을 입력받고, 해당 정점이 없으면 에러 메세지를 출력, 함수를 종료합니다.
// BFS가 시작되면, search를 해당 정점의 리스트의 노드를 가리키도록 조정합니다.
// 이후 방문값을 바꾸고 큐에 데이터를 입력합니다. 사용자에게 보이도록 출력을 한 뒤, 첫 번째의 정점은 일단 다시 큐에서 제거합니다.
// 한 정점이 가진 리스트를 모두 돌면서, 방문하지 않은 노드라면 해당 정점과 연결된 정점들을 순차적으로 큐에 넣고, 출력합니다.
// 이미 방문한 노드라면 리스트를 돌기만 합니다.
// 한 정점에 대한 리스트를 모두 돌았다면, 큐에 입력받은 노드를 꺼내어 다시 search를 조정하고 그 과정을 반복합니다.
// 이때, 큐에 -99값이 저장되어 있다면 이 큐는 비어있는 것이기 때문에 탐색을 종료합니다.

int deQueue() {
    int x;

    if (front == rear) {
        return -99;
    }

    if (front == -1) ++front;
    else if (front != MAX_VERTEX) front++;
    else front = 0;
    x = queue[front];
    queue[front] = -1;

    return x;
}

// 큐에서 데이터를 꺼내는 함수입니다.
// front가 rear와 같다면 -99를 리턴해, 큐가 비었다는 정보를 알립니다.
// 구현한 큐는 원형큐이기 때문에, rear이나 front를 다시 초기화할 필요는 없습니다.
// 이때, 큐 한에 최고로 많이 데이터가 들어가는 경우는 MAX_VERTEX 만큼의 데이터가 입력되는 것이지만, 원형큐는 front가 비어있는 시스템입니다.
// 때문에 큐의 용량을 MAX_VERTEX로 선언하게 되면 front가 비어있어 총 용량은 MAX_VERTEX-1이 됩니다.
// 따라서, 큐의 용량을 MAX_VERTEX+1로 선언했기 때문에 front가 MAX_VERTEX인 경우에 다시 0으로 되돌리는 것입니다.
// 그 다음, 제거할 데이터를 x에 입력한 뒤 front가 있는 곳의 정보를 -1로 하고(의미 없는 값이 되도록) x를 반환, 함수를 종료합니다.

void enQueue(int v) {
    if (rear == MAX_VERTEX - 1 && front == -1) {
        printf("[ERROR] Queue is Full!!!\n");
        return;
    }
    if (rear == MAX_VERTEX) rear = -1;
    if (++rear == front) {
        printf("[ERROR] Queue is Full!!!\n");
        if(rear == 0) rear = MAX_VERTEX;
        else rear--;
        return;
    }
    queue[rear] = v;
}

// 큐에 데이터를 입력하는 함수입니다. 먼저 데이터가 한 번도 제거되지 않았을 때, front는 -1로 초기화되었기 때문에 큐가 가득 찼다는 메시지를 출력하고 함수를 종료합니다.
// rear가 큐의 최대 용량 위치에 도달했다면 rear를 -1로 만들어 큐의 앞부분으로 이동시킵니다.
// 이때, rear의 앞 위치가 front라면 큐가 가득 찬 것이기 때문에 큐가 가득 찼다는 메세지를 출력하고 함수를 종료합니다.
// rear가 0이라면 원래의 rear는 MAX_VERTEX였던 것이기 때문에 해당 경우를 추가합니다. 그렇지 않다면 일반적인 경우이기 때문에 rear에 -1을 합니다.
// 아무 경우도 해당하지 않는다면, rear는 이미 ++되었기 때문에 rear에 전달받은 정점 정보를 입력합니다.

void printGraph(Graph* graph) {
    Vertex* p;
    for (int i = 0; i < MAX_VERTEX; i++) {
        if (GraphTF[i] == 1) {
            printf("[ Vertex %d ]", i + 1);
            p = graph->vlist[i].head->link;
            while (p != NULL) {
                printf(" --> [ %d ]", p->num);
                p = p->link;
            }
            printf("\n");
        }
    }
}

// 그래프를 출력하는 함수입니다. 그래프 포인터를 인자로 받습니다.
// 탐색을 위한 Vertex포인터를 선언합니다.
// 정점을 하나씩 돌면서, GraphTf가 1이라면 정점이 존재하는 것이기 때문에, 존재하는 정점을 출력합니다.
// 이후 그 정점에 대한 리스트를 p가 한 칸씩 돌면서 전부 출력합니다.
// 해당 정점에 대한 리스트가 전부 출력되었다면, 사용자가 보기 쉽게 \n으로 다음 정점에 대한 정보를 밑 줄에 표시하게 합니다.
// 모든 정보를 돌았다면, 인접리스트 기반 그래프가 전부 출력되었습니다.

void printVertex(Graph* graph) {
    for (int i = 0; i < MAX_VERTEX; i++) {
        if (GraphTF[i] == 1) printf("[ %d ] is T\n", i + 1);
    }
}

// 정점만을 출력하는 함수입니다. 디버깅을 할 때 필요해서 제작하게 되었습니다.
// GraphTF를 이용해서 정점이 존재하면 정점을 출력합니다.



// 이상입니다.
