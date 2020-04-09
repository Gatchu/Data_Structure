#include <stdio.h>

#define MAX_SIZE 100    // 배열의 크기를 선언합니다.

float sum(float [], int);       // 실수형 반환값을 가지고 매개 변수로 실수 배열과 정수를 받는 함수 sum을 선언합니다.
float input[MAX_SIZE], answer;  // 미리 정의해둔 크기 100을 가진 실수형 배열 input, 실수형 변수 answer을 선언합니다.
int i;                          // 정수형 변수 i를 선언합니다.
void main(void){

   printf("[-----Software, Student ID : 2017038040, Name : Han Gyu Jun-----]\n");
    // 성명과 학번이 출력되도록 소스를 수정했습니다. 한글은 컴파일시 깨져서 영문으로 작성했습니다.

   for (i = 0; i < MAX_SIZE; i++)      //i가 0부터 99까지, 순서대로 배열에 입력됩니다.
        input[i] = i;

    /* for checking call by reference*/
    printf("address of input = %p\n", input);   // 배열의 이름은 주소이므로 input배열의 주솟값이 출력됩니다.

   answer = sum(input, MAX_SIZE);
   // input배열의 주소(call by reference), 배열의 크기(call by value)를 넘긴 sum함수의 반환값을 answer에 저장합니다.
   printf("The sum is: %f\n", answer);      // 총합을 실수형으로 출력합니다.
}

float sum(float list[], int n){             // input배열의 주솟값을 list배열로 넘겨받고, MAX_SIZE를 n으로 넘겨받습니다.

   printf("value of list = %p\n", list);
   // list의 값을 출력하는데, input배열의 주솟값을 call by reference로 넘겨받았으므로 input배열의 주솟값이 출력됩니다.
   printf("address of list = %p\n\n", &list);   // 주소연산자 &가 사용되어 list의 주솟값이 출력됩니다.

   int i;                   // 정수형 변수 i를 선언합니다.
   float tempsum = 0;       // 실수형 변수 tempsum을 선언하고 0으로 초기화합니다.
   for(i = 0; i < n; i++)   
        tempsum += list[i]; // 반복문을 이용해 list배열의 모든 값 => input배열의 모든 값을 0부터 n까지 더합니다.
   return tempsum;          // 구한 합을 반환합니다.
}