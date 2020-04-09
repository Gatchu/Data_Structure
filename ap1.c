#include <stdio.h>
#include <stdlib.h>

void main(){
    int list[5];                //int형 5개 배열 선언입니다.
    int *plist[5] = {NULL,};    //int형 5개 포인터배열 선언 및 NULL초기화입니다.

    plist[0] = (int*)malloc(sizeof(int));   // plist[0]에 malloc을 사용해 동적배열  주소를 할당합니다.(heap에 저장)

    list[0] = 1;        // list배열 첫번째에 값 1을 할당합니다.
    list[1] = 100;      // list배열 두번째에 값 100을 할당합니다.

    *plist[0] = 200;    // plist[0]이 가리키는 공간에 값 200을 할당합니다.

    printf("[-----Software, Student ID : 2017038040, Name : Han Gyu Jun-----]\n");
    // 성명과 학번이 출력되도록 소스를 수정했습니다. 한글은 컴파일시 깨져서 영문으로 작성했습니다.

    printf("value of list[0] = %d\n", list[0]);                 // list[0]의 값이 출력됩니다. 위에서 list[0]에 1을 할당했기 때문에 1이 출력됩니다.
    printf("address of list[0]      = %p\n", &list[0]);         // list[0]의 주솟값이 출력됩니다.
    printf("value of list           = %p\n", list);             // 배열의 이름은 배열의 첫 번째 값의 주소이기 때문에 list[0]의 주솟값이 출력됩니다.
    printf("address of list (&list) = %p\n", &list);            // 마찬가지로, 배열의 이름은 배열의 첫 번째 값의 주소이기 때문에 주솟값이 출력됩니다.

    printf("---------------------------------------\n\n");
    printf("value of list[1]    = %d\n", list[1]);              // list[1]의 값이 출력됩니다. 위에서 list[1]에 100을 할당했기 때문에 100이 출력됩니다.
    printf("address of list[1]  = %p\n", &list[1]);             // list[1]의 주솟값이 출력됩니다.
    printf("value of *(list+1)  = %d\n", *(list + 1));          
    // list는 첫 번째 주솟값이고, *(list+1)은 list의 자료형의 크기만큼 주솟값이 더해져(sizeof(int)), 처음 주솟값+int형 크기 => 다음 주솟값을 역참조하여 list[1]값인 100이 출력됩니다.
    printf("address of list+1   = %p\n", list + 1);             // list는 첫 번째 주솟값이고, 주솟값에 +1을 하므로 int형 크기만큼이 더해져 다음 주솟값인 list[1]의 주솟값이 출력됩니다.


    printf("---------------------------------------\n\n");

    printf("value of *plist[0]  = %d\n", *plist[0]);            // plist[0]의 값이 출력됩니다. 처음 *plist[0] =200이라고 선언했기 때문에 200이 출력됩니다.
    printf("&plist[0]           = %p\n", &plist[0]);            // plist[0]의 주솟값이 출력됩니다.
    printf("&plist              = %p\n", &plist);               // 배열의 이름은 주솟값과 동일하기 때문에 plist[0]의 주솟값이 출력됩니다.
    printf("plist               = %p\n", plist);                // 마찬가지로, 배열의 이름은 주솟값과 동일해 plist[0]의 주솟값이 출력됩니다.
    printf("plist[0]            = %p\n", plist[0]);             // plist가 가진 주소를 출력합니다. 즉, *plist[0]의 주솟값이 출력됩니다.
    printf("plist[1]            = %p\n", plist[1]);             // plist[0]만 주소를 설정했고, plist[1~4]는 주소를 NULL로 초기화했기 때문에 NULL값이 출력됩니다.
    printf("plist[2]            = %p\n", plist[2]);
    printf("plist[3]            = %p\n", plist[3]);
    printf("plist[4]            = %p\n", plist[4]);

    free(plist[0]);                                             // plist[0]의 값을 동적할당했기 때문에 free선언으로 코드의 끝에서 재활용 가능하도록 만듭니다. 

}