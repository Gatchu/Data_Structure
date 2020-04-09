#include <stdio.h>

void print1 (int *ptr, int rows);
// 정수형 포인터변수와 정수형 변수를 매개변수로 받는 void형 함수를 선언합니다.

int main(){
    int one[] = {0,1,2,3,4};    // 0,1,2,3,4를 내용으로 갖는 정수형 배열 one을 선언합니다.

    printf("[-----Software, Student ID : 2017038040, Name : Han Gyu Jun-----]\n");
    // 성명과 학번이 출력되도록 소스를 수정했습니다. 한글은 컴파일시 깨져서 영문으로 작성했습니다.
    printf("one         = %p\n", one);      // 배열의 이름은 주솟값이므로 one배열의 주솟값을 출력합니다.
    printf("&one        = %p\n", &one);     // 주소연산자 &를 사용했으므로 one배열의 주솟값을 출력합니다.
    printf("&one[0]     = %p\n", &one[0]);  // 주소연산자 &을 사용했으므로 one배열의 첫번째 값의 주소를 출력합니다.
    printf("\n");
    
    print1(&one[0], 5);     // one배열의 주솟값을 call by reference로 함수에 넘겨줍니다. 5는 call by value입니다.
    return 0;
}

void print1 (int *ptr, int rows){   // 넘겨진 one배열의 주솟값을 정수형 포인터변수 ptr에, 5를 rows에 받습니다.
    /*print out a one=dimensional array using a pointer */

    int i;      // 정수형 변수 i를 선언합니다.
    printf("Address \t contents\n");
    for(i = 0; i < rows; i++)
        printf("%p \t %5d\n", ptr + i, *(ptr + i));
        /* ptr의 값은 one배열의 주솟값이므로
        ptr + i -> ptr + i * (sizeof(int)) 가 되어 배열의 주솟값을 하나하나 출력합니다.
        (* ptr + i)도 위와 같이 주소를 이동하며 해당하는 주소의 값, 배열의 값을 하나하나 출력합니다. */
    printf("\n");
}