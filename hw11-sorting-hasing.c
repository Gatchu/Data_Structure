/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

// 각 선택지를 나타내는 메뉴입니다.
// 배열을 전달할 때, 포인터로 넘겨야 배열을 수정할 수 있기 때문에 포인터로 배열을 넘깁니다.
// 마찬가지로, 해쉬테이블도 포인터로 넘깁니다.
// 배열을 생성할 때 난수를 발생시켜야 하기 때문에 srand기능을 사용합니다.
// 다른 함수들이 끝날 때에는 0을 리턴시켜서 일반함수의 종료를 알리지만, 메인함수가 종료할 때에는 1을 반환해 메인함수의 정상적 종료를 나타냅니다.


int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

// 초기화를 하는 함수입니다. 배열 array의 값을 직접 수정할 수 있도록, 배열의 포인터를 넘겨받습니다.
// 먼저, 배열 a가 NULL이라면 배열이 할당되지 않았다는 것이기 때문에 정해진 크기만큼 배열의 공간을 temp에 할당합니다.
// 이후 temp에 할당된 공간을 배열포인터 a가 가리키게 함으로 배열포인터 a의 값을 직접 변경합니다.
// 배열 a가 NULL이지 않다면, 배열이 할당된 것이기 때문에 새로 공간을 할당할 필요가 없습니다. 따라서, temp가 배열 a를 직접 포인팅하도록 합니다.
// 이후 temp와 a는 같은 배열을 포인팅하고 있기 때문에, 배열a의 값을 랜덤으로 하나씩 할당합니다. 배열 a는 array의 더블포인터를 전달받은 것이기 때문에 배열 array의 값이 변합니다.
// 이후 0을 리턴시켜 함수가 종료되었음을 알립니다.

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

// 배열을 메모리에서 할당 해제하는 함수입니다.
// 배열 array의 포인터를 넘겨받아서 배열을 직접 수정할 수 있습니다.
// free(a)를 통해 동적할당된 배열 array를 메모리에서 할당 해제한 뒤 0을 리턴해 함수의 종료를 알립니다.
// do while문이기 때문에, 조건을 맨 마지막에 검사합니다.
// 그렇기 때문에 command가 q였을 때의 if문을 실행한 뒤 while문의 조건에 걸려 반복문을 탈출합니다.
// 즉, freeArray함수를 먼저 실행시켜 배열을 메모리에서 할당 해제한 뒤에 반복문을 탈출, 프로그램을 종료합니다.

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

// 배열 전체를 출력하는 함수입니다.
// 만약 넘겨받은 배열이 NULL이라면 배열이 동적할당되지 않았다는 뜻이기 때문에 아무것도 출력할 것이 없다는 메세지를 출력한 후 함수를 종료합니다.
// 그렇지 않다면, 배열이 initialize함수를 거쳐 랜덤 값들도 입력되었다는 뜻이기 때문에, 배열의 max size까지 출력합니다.
// 이 때, 사용자의 편의성을 위하여 보기 좋게 첫 줄에는 배열의 몇 번째 공간인지를 출력하고, 그 다음 줄에 해당 공간에 있는 수를 출력합니다. 이때, %2d와 %5d로 공간을 맞춰서 출력합니다.
// 이후 초기 메뉴와 겹치지 않기 위해서 한 줄을 띄워준 뒤 함수를 종료합니다.

int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

// 선택 정렬 함수입니다. array의 포인터를 받았기 때문에 배열을 수정할 수 있습니다.
// 일단 처음의 배열 상태를 알려주기 위해서 처음 배열을 출력합니다.
// 초기에는 배열의 가장 첫 번째 값과 인덱스를 가장 작은 값으로 잡고 시작합니다.
// 이때, 배열의 남은 수를 전부 하나씩 탐색하면서, min보다 더 작은 값이 발견되면 바로 min값에 그 값을 넣고, 인덱스도 변경합니다.
// 이렇게 되면, min에는 제일 작은 값이(원래 a[j]값), minindex에는 j(인덱스)가 들어갑니다. 그 다음에는 a[i]을 a[j](a[minindex])에 넣고 a[i]에 min을 넣음으로 두 값을 교체합니다.
// i이후 모든 값을 탐색했기 때문에 i값에는 가장 작은 값이 들어가 있습니다.
// 이 값은 정렬되었기 때문에, i에 1을 더해서 정렬이 되지 않은 나머지 배열에 같은 작업을 수행합니다.
// 정렬된 공간은 i가 진행하면서 자연스럽게 앞쪽으로 빠지기 때문에 위의 작업을 수행하면 정렬이 끝납니다.
// 이후 정렬된 배열을 출력하고 함수를 종료합니다.

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

// 삽입 정렬 함수입니다.
// 맨 처음에 인덱스 i의 값을 t에 저장하고 j를 인덱스 i와 같은 값을 가지도록 합니다.
// 맨 처음 인덱스 i는 1로 시작하고, 이때 배열은 인덱스 i의 좌/우로 나뉩니다.
// j가 i부터 시작하여 1씩 감소하면서, 좌측에 있는 원소가 우측의 원소보다 크다면 좌측의 원소를 우측으로 옮깁니다. 이후 1에 있는 값을 0으로 옮깁니다.
// 다음 반복문으로 들어가면, 좌측 배열의 크기가 하나 더 증가하고 우측 배열의 크기가 하나 더 감소합니다.
// 좌측 배열의 인덱스 0과 1은 이미 정렬되어 있기 때문에 인덱스2에 해당하는 원소가 인덱스 1, 0과 비교하면서 작다면 좌측으로 한 칸씩 이동시키면서 정렬합니다.
// 다음 반복문에서 좌측 배열의 크기가 다시 하나 더 증가하고 우측 배열의 크기가 하나 더 감소합니다.
// 같은 원리로 좌측 배열이 하나씩 증가하면서 정렬되고, 우측 배열은 하나씩 감소하면서 점차 정렬된 배열이 전체 배열을 차지합니다.
// 마지막으로, 좌측 배열이 전체를 차지하고 마지막 값이 배열의 좌측으로 한 칸씩 이동하면서 자신의 좌측 위치보다 작다면 좌측으로, 그렇지 않다면 그 위치에 정렬됩니다.
// 정렬된 배열을 출력한 뒤 함수를 마무리합니다.

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

// 버블 정렬 함수입니다.
// 인접한 숫자를 서로 비교하면서 가장 큰 값부터 정렬하는 함수입니다. j로 반복문을 돌면서 j보다 뒤에 있는 수와 j를 비교합니다. 이때, j-1에 있는 수가 크다면 j인덱스로 이동시켜 큰 수를 뒤로 뺍니다.
// 이때 j가 계속 진행됨에 따라서 가장 큰 수가 배열에서 골라져서 가장 뒤에 가도록 됩니다.
// 가장 큰 수가 배열의 맨 뒤에 위치한 다음, j를 사용하는 반복문을 빠져나오므로 i가 1 증가해 반복문을 다시 진행합니다.
// j를 사용하는 반복문이 다시 진행되면서 가장 큰 수를 찾아서 맨 뒤에 놓는데, 이때 이미 가장 큰 수가 맨 뒤에 위치해 있으므로 그 다음 큰 수가 자연스럽게 뒤에서 두 번째 인덱스로 이동합니다.
// 이것이 배열의 크기만큼 반복되면, 가장 큰 수부터 가장 작은 수까지의 정렬이 완성됩니다.

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

// 쉘 정렬 함수입니다.
// 먼저 h를 전체 배열 크기의 절반으로 나누어 배열을 분할합니다.
// 이때 나누어진 두 배열의 첫 원소를 서로 비교하고, 두 배열의 두 번째 원소를 서로 다시 비교하는 식으로 첫 정렬을 합니다.
// 그 다음, 배열을 전 크기의 절반으로 더 세분화하여 배열을 분할합니다.
// 이때 나눠진 배열들의 첫 원소를 비교하고, 해당 위치에 있는 원소들을 정렬합니다.
// 이 방법을 반복하는데, h는 마지막에 결국 1이 되므로 모든 원소들을 정렬하게 됩니다.
// h가 1일 때, i와 j의 반복문은 선택 정렬과 일치합니다. 따라서, 원소들을 적당히 정리한 뒤 마지막에 선택정렬을 이용하는 것입니다.
// 이때, 미리 조금씩 정렬되었기 때문에 정렬이 되지 않을 배열보다 평균 속도가 높습니다.
// h가 1 다음으로 0.5가 되고, 이때 h는 int형이므로 소숫점이 잘려서 0이 됩니다. 그러면 반복문의 조건을 만족하지 못해 탈출하면서 함수가 끝납니다.

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

// 퀵 정렬에 대한 함수입니다.
// 퀵 정렬을 할 때, array배열과 배열 전체 크기를 전달받습니다.
// 이때, v를 a[n-1]로 삼아 기준값으로 정합니다. 이때의 기준값을 배열의 가장 마지막 값입니다.
// 그 뒤, i를 배열의 가장 처음 값으로, j를 배열의 가장 마지막 값으로 정합니다.
// 반복문에 들어가면, 다시 반복문으로 v보다 작은 값을 배열의 처음부터, v보다 큰 값을 배열의 마지막부터 찾습니다. 이후 조건 v보다 작으면서 반 이전에 있는 값과 v보다 크면서 반 이후에 있는 값을 교환합니다.
// 한 칸씩 진행하면서 이것을 반복하면, v보다 큰 값은 우측으로 쏠려 있고 v보다 작은 값은 좌측으로 쏠리게 됩니다.
// 이때, 내부적으로는 완벽하게 정렬이 되지 않았기 때문에, i와 j가 교차하는 시점을 기준으로 배열을 세분화하여 다시 재귀적으로 퀵 정렬을 실행하면 점차 세밀하게 정렬됩니다.

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

// 해쉬 함수입니다.
// 해시 함수는 키를 전체 배열 크기만큼 나눈 나머지를 리턴합니다.

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

// 해시 환경을 만드는 함수입니다. 전체 배열을 저장할 수 있는 만큼의 배열을 동적할당합니다. 이때, 이미 배열이 할당되어 있다면 배열을 재활용합니다. 그 다음 해쉬 테이블은 -1로 초기화합니다.
// key값에 배열에서 해쉬테이블에 할당할 값을 넣은 뒤 해쉬함수를 사용해서 키에 해당하는 해쉬 인덱스를 얻습니다.
// 해당 해쉬 인덱스가 비어 있다면 해쉬 테이블의 값이 -1이기 때문에 키를 삽입합니다.
// 그렇지 않은 경우, 충돌과 오버플로우가 일어난 것이기 때문에 인덱스에 1을 더한 뒤 해쉬함수(배열의 최대 크기만큼 나눈 뒤 나머지를 인덱스로 삼는 것)를 진행시켜 새 인덱스를 만들어냅니다.
// 결과적으로 해당 키에 대한 인덱스는 전의 인덱스보다 1증가한 값이고, 전체 배열만큼 나눈 나머지의 값이기 때문에 원래 인덱스가 배열의 마지막 위치였다면 새 인덱스는 배열의 첫 위치로 갑니다.
// 즉, 인덱스를 1씩 증가시키면서 비어 있는 해쉬 테이블을 찾고, 그곳에 키 값을 삽입하는 것입니다.
// 해쉬 테이블이 비어 있는 곳을 찾았다면, 반복문에서 탈출하고 해쉬테이블의 해당 인덱스에 키 값이 들어갑니다.
// 이후 함수를 종료합니다.

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}

// 검색 함수입니다.
// 해시함수를 이용해서 해당 키에 알맞은 인덱스를 얻습니다.
// 만약 해당 인덱스에 키가 있지 않다면, 충돌, 오버플로우가 발생한 것입니다.
// 따라서, 해시함수를 다시 이용해서 얻어낸 인덱스에 키 값이 존재하는지 알아내는 방법을 사용합니다.
// 키 값이 존재하면 해당 인덱스를 리턴합니다.
// 이상입니다.
