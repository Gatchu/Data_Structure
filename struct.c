#include <stdio.h>

struct student1{
    char lastName;
    int studentId;
    char grade;
};

typedef struct{
    char lastName;
    int studentId;
    char grade;
} student2;

// 내용이 같은 구조체 student1, student2를 선언하는데, 하나는 typedef, 하나는 typedef 없이 선언합니다.

int main(){

    printf("[-----Software, Student ID : 2017038040, Name : Han Gyu Jun-----]\n");
    // 성명과 학번이 출력되도록 소스를 수정했습니다. 한글은 컴파일시 깨져서 영문으로 작성했습니다.
    
    struct student1 st1 = {'A', 100, 'A'};  // student1은 typedef 선언이 아니기 때문에 struct를 써줍니다.

    printf("st1.lastName = %c\n", st1.lastName);    // st1구조체의 char형 변수 lastName => A를 출력합니다.
    printf("st1.studentId = %d\n", st1.studentId);  // st1구조체의 int형 변수 studentId => 100을 출력합니다.
    printf("st1.grade = %c\n", st1.grade);          // st1구조체의 char형 변수 grade => A를 출력합니다.

    student2 st2 = {'B', 200, 'B'}; // student2는 typedef선언을 했기 때문에 struct를 생략해도 됩니다.

    printf("\nst2.lastName = %c\n", st2.lastName);  // st2구조체의 char형 변수 lastName = B를 출력합니다.
    printf("st2.studentId = %d\n", st2.studentId);  // st2구조체의 int형 변수 studentId = 200을 출력합니다.
    printf("st2.grade = %c\n", st2.grade);          // st2구조체의 char형 변수 grade = B를 출력합니다.

    student2 st3;       // typedef선언이 된 student2형 구조체 st3을 선언합니다.

    st3 = st2;      // st3에 st2를 대입합니다.(구조 치환) st2의 변수가 각각 st3에 입력됩니다.

    printf("\nst3.lastName = %c\n", st3.lastName);  // st3구조체의 char형 변수 lastName이 구조 치환되어 B를 출력합니다.
    printf("st3.studentId =%d\n", st3.studentId);   // st3구조체의 int형 변수 studentId가 구조 치환되어 200을 출력합니다.
    printf("st3.grade = %c\n", st3.grade);          // st3구조체의 char형 변수 grade가 구조 치환되어 B를 출력합니다.

    /* equality test */
    /*
    if(st3 == st2)
        printf("equal\n");
    else
        printf("not equal\n");

    이 주석을 실제로 컴파일할 경우 컴파일 불가능이라는 에러가 나타납니다.

    */

   return 0;
}