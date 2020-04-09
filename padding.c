#include <stdio.h>

struct student{
    char lastName[13];  /* 13 bytes */
    int studentId;      /* 4bytes */
    short grade;        /* 2bytes */
};

// 구조체 student를 생성합니다. 이 때, 구조체가 총 차지하는 용량은 13+4+2 = 19bytes입니다.

int main(){
    struct student pst; // typedef선언이 아니기 때문에 struct를 넣어서 선언해줍니다.

    printf("size of student = %ld\n", sizeof(struct student));
    // 마찬가지로, typedef선언이 아니기 때문에 struct를 넣어줍니다.
    // 이 때, 구조체의 총 용량은 19바이트지만 출력은 24바이트가 나오게 되고, 이는 컴파일러가 패딩을 하기 때문입니다.
    // 먼저 lastName이 13바이트인데, 4바이트씩 세었을 때 나머지 3바이트가 패딩처리되어 16바이트가 됩니다.
    printf("size of int = %ld\n", sizeof(int));
    // int형인 studentId는 4바이트이기 때문에 넘어갑니다.
    printf("size of short = %ld\n", sizeof(short));
    // short형인 grade는 2바이트이기 때문에 남은 2바이트가 패딩처리되어 4바이트가 됩니다.
    // 즉, lastName 13바이트+패딩3바이트 = 16바이트, studentId 4바이트,
    // grade 2바이트+패딩 2바이트 = 4바이트를 모두 합하여 16 + 4 + 4 = 24바이트가 나온 것입니다.

    return 0;
}