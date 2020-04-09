#include <stdio.h>
#include <stdlib.h>

void main(){
    int **x;

    printf("[-----Software, Student ID : 2017038040, Name : Han Gyu Jun-----]\n");
    // 성명과 학번이 출력되도록 소스를 수정했습니다. 한글은 컴파일시 깨져서 영문으로 작성했습니다.
    printf("sizeof(x) = %lu\n", sizeof(x));
    // 이중포인터변수 x의 크기가 출력됩니다. 이 때, x는 포인터변수이기 때문에 32bit 컴파일러에서는 4바이트의 크기, 64bit 컴파일러에서는 8바이트의 크기를 가집니다.
    printf("sizeof(*x) = %lu\n", sizeof(*x));
    // 포인터변수 *x의 크기가 출력됩니다. 이 때에도 x는 포인터변수이기 때문에 컴파일러에 따라 그 크기가 달라집니다.
    printf("sizeof(**x) = %lu\n", sizeof(**x));
    // **x는 이중포인터변수를 따라간 x의 최종 값이기 때문에 int형 값을 가집니다. 때문에 int형의 크기인 4바이트가 **x의 크기가 됩니다.
}