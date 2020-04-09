#include <stdio.h>
#include <stdlib.h>

void main(){
    int list[5];        // int형 5개 크기의 배열을 선언합니다.
    int *plist[5];      // int형 5개 크기의 포인터배열을 선언합니다.

    list[0] = 10;       // list배열의 첫번째 장소에 10을 할당합니다.
    list[1] = 11;       // list배열의 두번째 장소에 11을 할당합니다.

    plist[0] = (int*)malloc(sizeof(int));   // plist배열의 첫번째 장소에 주소를 heap에 동적할당합니다.

    printf("[-----Software, Student ID : 2017038040, Name : Han Gyu Jun-----]\n");
    // 성명과 학번이 출력되도록 소스를 수정했습니다. 한글은 컴파일시 깨져서 영문으로 작성했습니다.
    printf("list[0] \t = %d\n", list[0]);               // list[0]값을 출력합니다.
    printf("address of list \t = %p\n", list);          // 배열의 이름은 주소이므로 list[0]]의 주솟값을 출력합니다.
    printf("address of list[0] \t = %p\n", &list[0]);   // 참조연산자 &를 사용했으므로 list[0]의 주솟값을 출력합니다.
    printf("address of list + 0 \t = %p\n", list+0);    // 배열의 이름에 0만큼 떨어진 주소이므로 list[0]의 주솟값을 출력합니다.
    printf("address of list + 1 \t = %p\n", list+1);    // 배열의 이름에 1*sizeof(int)만큼 떨어진 주소이므로 list[1]의 주솟값을 출력합니다.
    printf("address of list + 2 \t = %p\n", list+2);    // 배열의 이름에 2*sizeof(int)만큼 떨어진 주소이므로 list[2]의 주솟값을 출력합니다.
    printf("address of list + 3 \t = %p\n", list+3);    // 배열의 이름에 3*sizeof(int)만큼 떨어진 주소이므로 list[3]의 주솟값을 출력합니다.
    printf("address of list + 4 \t = %p\n", list+4);    // 배열의 이름에 4*sizeof(int)만큼 떨어진 주소이므로 list[4]의 주솟값을 출력합니다.
    printf("address of list[4] \t = %p\n", &list[4]);   // 참조연산자 &를 사용햇으므로 list[4]의 주솟값을 출력합니다.

    free(plist[0]);     // free를 통해 동적할당한 plist[0]의 값을 재활용할 수 있게 합니다.

}